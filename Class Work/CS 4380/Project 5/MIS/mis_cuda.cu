/*
Maximal independent set code

Copyright 2022 Martin Burtscher

Redistribution in source or binary form, with or without modification, is not
permitted. Use in source or binary form, with or without modification, is only
permitted for academic use in CS 4380 and CS 5351 at Texas State University.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*
  Worked by:
    - Chuong Dinh Vu
    - Noah del Angel
*/


#include <cstdlib>
#include <cstdio>
#include <sys/time.h>
#include <cuda.h>
#include "ECLgraph.h"


static const unsigned char included = 0;
static const unsigned char excluded = 1;
static const unsigned char undecided = 2;

static const int ThreadsPerBlock = 512;



// https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
static __device__ unsigned int hash(unsigned int val)
{
  val = ((val >> 16) ^ val) * 0x45D9F3B;
  val = ((val >> 16) ^ val) * 0x45D9F3B;
  return (val >> 16) ^ val;
}

static __global__ void init( const  ECLgraph  g, volatile unsigned int* const priority, volatile unsigned char* const status ) 
{
  const int v = threadIdx.x + blockIdx.x * blockDim.x;
  
  // initialize arrays
  if (v < g.nodes) {
    status[v] = undecided;
    priority[v] = hash(v + 712813837);
  }
}

static __global__ void mis(const  ECLgraph  g,  volatile  unsigned char* const status, const unsigned int* const priority, volatile bool* const repeat)
{
  const int v = threadIdx.x + blockIdx.x * blockDim.x;

  // go over all nodes
  if ( v < g.nodes ) {
    if (status[v] == undecided) {
      int i = g.nindex[v];
      // try to find a neighbor whose priority is higher
      while ((i < g.nindex[v + 1]) && ((status[g.nlist[i]] == excluded) || (priority[v] > priority[g.nlist[i]]) || ((priority[v] == priority[g.nlist[i]]) && (v < g.nlist[i])))) {
        i++;
      }
      if (i < g.nindex[v + 1]) {
        // found such a neighbor -> status of v still unknown
        *repeat = true;
      } else {
        // no such neighbor -> all neighbors are "excluded" and v is "included"
        status[v] = included;
        for (int i = g.nindex[v]; i < g.nindex[v + 1]; i++) {
          status[g.nlist[i]] = excluded;
        }
      }
    }
  }
}

static void CheckCuda(const int line)
{
  cudaError_t e;
  cudaDeviceSynchronize();
  if (cudaSuccess != (e = cudaGetLastError())) {
    fprintf(stderr, "CUDA error %d on line %d: %s\n", e, line, cudaGetErrorString(e));
    exit(-1);
  }
}


int main(int argc, char* argv [])
{
  printf("Maximal independent set v1.9\n");

  // check command line
  if (argc != 2) {fprintf(stderr, "USAGE: %s input_file\n", argv[0]); exit(-1);}

  // read input
  ECLgraph g = readECLgraph(argv[1]);
  printf("input: %s\n", argv[1]);
  printf("nodes: %d\n", g.nodes);
  printf("edges: %d\n", g.edges);

  // allocate arrays
  unsigned char* const status = new unsigned char [g.nodes];
  unsigned int* const priority = new unsigned int [g.nodes];

  // Allocate repeate flag
  bool repeat;

  // alloace GPU items
  unsigned char* const d_status = new unsigned char [g.nodes];
  bool* d_repeat;

  cudaMalloc((void **) &d_status, sizeof(unsigned char) * g.nodes);
  CheckCuda(__LINE__);
  cudaMalloc((void **) &d_repeat, sizeof(bool));
  CheckCuda(__LINE__);

  // Allocate g graph to GPU
  ECLgraph d_g = g; 
  cudaMalloc((void **)&d_g.nindex, sizeof(int) * (g.nodes + 1)); 
  CheckCuda(__LINE__); 
  cudaMalloc((void **)&d_g.nlist, sizeof(int) * g.edges); 
  CheckCuda(__LINE__); 
  cudaMemcpy(d_g.nindex, g.nindex, sizeof(int) * (g.nodes + 1), cudaMemcpyHostToDevice); 
  CheckCuda(__LINE__); 
  cudaMemcpy(d_g.nlist, g.nlist, sizeof(int) * g.edges, cudaMemcpyHostToDevice); 
  CheckCuda(__LINE__);


  // start time
  timeval beg, end;
  gettimeofday(&beg, NULL);

  // execute timed code
  init <<<( g.nodes + ThreadsPerBlock - 1 ) / ThreadsPerBlock, ThreadsPerBlock>>>(d_g, priority, d_status);

  // repeat until all nodes' statuses have been decided
  do {
    repeat = false;
    cudaMemcpy(d_repeat, &repeat, sizeof(bool), cudaMemcpyHostToDevice);


    mis<<<( g.nodes + ThreadsPerBlock - 1 ) / ThreadsPerBlock, ThreadsPerBlock>>>(d_g, d_status, priority, d_repeat);
    cudaDeviceSynchronize();
    
    // return the repeat to the host
    cudaMemcpy(&repeat, d_repeat, sizeof(bool), cudaMemcpyDeviceToHost);
  } while (repeat);

  // end time
  gettimeofday(&end, NULL);
  CheckCuda(__LINE__);

  const double runtime = end.tv_sec - beg.tv_sec + (end.tv_usec - beg.tv_usec) / 1000000.0;
  printf("compute time: %.6f s\n", runtime);


  // Return status array from GPU
  cudaMemcpy(status, d_status, sizeof(unsigned char) * g.nodes, cudaMemcpyDeviceToHost);
  CheckCuda(__LINE__);

  // determine and print set size
  int cnt = 0;
  for (int v = 0; v < g.nodes; v++) {
    if (status[v] == included) cnt++;
  }
  printf("elements in set: %d (%.1f%%)\n", cnt, 100.0 * cnt / g.nodes);

  // verify result
  for (int v = 0; v < g.nodes; v++) {
    if ((status[v] != included) && (status[v] != excluded)) {fprintf(stderr, "ERROR: found undecided node\n"); exit(-1);}
    if (status[v] == included) {
      for (int i = g.nindex[v]; i < g.nindex[v + 1]; i++) {
        if (status[g.nlist[i]] == included) {fprintf(stderr, "ERROR: found adjacent nodes in MIS\n"); exit(-1);}
      }
    } else {
      bool flag = true;
      for (int i = g.nindex[v]; i < g.nindex[v + 1]; i++) {
        if (status[g.nlist[i]] == included) {
          flag = false;
          break;
        }
      }
      if (flag) {fprintf(stderr, "ERROR: set is not maximal\n"); exit(-1);}
    }
  }
  printf("verification passed\n");

  // clean up
  freeECLgraph(g);
  delete [] priority;
  delete [] status;
  cudaFree(d_g.nindex);
  cudaFree(d_g.nlist);
  cudaFree(d_status);
  cudaFree(d_repeat);
  return 0;
}
