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
/*
  Worked by:
    - Chuong Dinh Vu
    - Noah del Angel
*/


#include <cstdio>
#include <algorithm>
#include <cuda.h>
#include <sys/time.h>


static const int ThreadsPerBlock = 512;


static __global__ void collatz(const long start, const long top, int* const maxlen)
{
  // Determine what thread we are
  const long idx = start + (threadIdx.x + blockIdx.x * (long)blockDim.x) * 2;

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
    fprintf(stderr, "CUDA error %d on line %d; %s\n", e, line, cudaGetErrorString(e));
    exit(-1);
  }
}


int main(int argc, char* argv [])
{
  printf("Collatz v1.8\n");

  // check command line
  if (argc != 3) {fprintf(stderr, "USAGE: %s start_value upper_bound\n", argv[0]); exit(-1);}
  const long start = atol(argv[1]);
  const long top = atol(argv[2]);
  printf("start value: %ld\n", start);
  printf("upper bound: %ld\n", top);

  // allocate variable on CPU
  int maxlen = 0;

  // allocate variable on GPU
  int* const d_maxlen = new int;

  cudaMalloc((void **) &d_maxlen, sizeof(int));
  CheckCuda(__LINE__);

  // initialize the values
  cudaMemcpy(d_maxlen, &maxlen, sizeof(int), cudaMemcpyHostToDevice);
  CheckCuda(__LINE__);

  // start time
  timeval beg, end;
  gettimeofday(&beg, NULL);

  // execute timed code
  collatz<<<((top - start + 1)/2 + ThreadsPerBlock - 1) / ThreadsPerBlock, ThreadsPerBlock>>>(start, top, d_maxlen);
  cudaDeviceSynchronize();  // wait for kernel to finish

  // end time
  gettimeofday(&end, NULL);
  CheckCuda(__LINE__);
  const double runtime = end.tv_sec - beg.tv_sec + (end.tv_usec - beg.tv_usec) / 1000000.0;
  printf("compute time: %.6f s\n", runtime);

  // get result from GPU 
  cudaMemcpy(&maxlen, d_maxlen, sizeof(int), cudaMemcpyDeviceToHost);
  CheckCuda(__LINE__);

  // print result
  printf("maximum length: %d\n", maxlen);

  // clean up
  cudaFree(d_maxlen);
  return 0;
}
