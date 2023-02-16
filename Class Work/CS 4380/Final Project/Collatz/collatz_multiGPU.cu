/*
Collatz code

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


#include <cstdio>
#include <algorithm>
#include <cuda.h>
#include <sys/time.h>


static const int ThreadsPerBlock = 512;


static __global__ void collatz(const long start, const long top, const long increment, int* const maxlen)
{
  // Determine what thread we are
  const long idx = start + (threadIdx.x + blockIdx.x * (long)blockDim.x) * increment;

  // compute sequence lengths
  if ( idx < top )
  {
    long val = idx;
    int len = 1;
    do {
      len++;
      if ((val % 2) != 0) {
        val = 3 * val + 1;  // odd
      } else {
        val = val / 2;  // even
      }
    } while (val != 1);
    atomicMax(maxlen, len);
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
  printf("Collatz v1.8\n");

  // check command line
  if (argc != 4) {fprintf(stderr, "USAGE: %s start_value upper_bound number_of_GPUs\n", argv[0]); exit(-1);}
  const long start = atol(argv[1]);
  const long top = atol(argv[2]);
  const int gpus = atoi(argv[3]);
  if ((gpus < 1) || (gpus > 4)) {fprintf(stderr, "ERROR: number of GPUs must be between 1 and 4\n"); exit(-1);}
  printf("start value: %ld\n", start);
  printf("upper bound: %ld\n", top);
  printf("number of GPUs: %d\n", gpus);

  // allocate and initialize GPU memory
  int maxlen = 0;
  int* d_maxlen [4];
  for (int d = 0; d < gpus; d++) {
    cudaSetDevice(d);
    cudaMalloc((void **)&d_maxlen[d], sizeof(int));
    CheckCuda(__LINE__);
  }
  // todo: set the maximum length on each GPU to zero by copying maxlen to the GPU
  for (int d = 0; d < gpus; d++) {
    cudaSetDevice(d);
    cudaMemcpy(d_maxlen[d], &maxlen, sizeof(int), cudaMemcpyHostToDevice);
    CheckCuda(__LINE__);
  }

  // start time
  timeval beg, end;
  gettimeofday(&beg, NULL);

  // execute timed code
  for (int d = 0; d < gpus; d++) {
    cudaSetDevice(d);
    const long begin = start + d * (((top - start + 1)/2 + ThreadsPerBlock - 1) / ThreadsPerBlock);
    const long incr = 2 * gpus;
    collatz<<< ((top - start + 1)/2 + ThreadsPerBlock - 1) / ThreadsPerBlock, ThreadsPerBlock>>>(begin, top, incr, d_maxlen[d]);
  }
  for (int d = 0; d < gpus; d++) {
    cudaSetDevice(d);
    cudaDeviceSynchronize();  // wait for kernel to finish
  }

  // end time
  gettimeofday(&end, NULL);
  CheckCuda(__LINE__);
  const double runtime = end.tv_sec - beg.tv_sec + (end.tv_usec - beg.tv_usec) / 1000000.0;
  printf("compute time: %.6f s\n", runtime);

  // todo: get the result from each GPU and reduce the values on the CPU into a final global result
  for( int d = 0; d < gpus; d++ ) {
    int tempMax = 0;
    
    cudaSetDevice(d);
    cudaMemcpy(&tempMax, d_maxlen[d], sizeof(int), cudaMemcpyDeviceToHost);
    CheckCuda(__LINE__);

    // Only assign CPU maxlen if the one from 
    // the gpu is greater 
    if( tempMax > maxlen ) {
      maxlen = tempMax;
    }
  }
  printf("maximum length: %d\n", maxlen);

  for (int d = 0; d < gpus; d++) {
    cudaSetDevice(d);
    cudaFree(d_maxlen[d]);
    CheckCuda(__LINE__);
  }
  return 0;
}
