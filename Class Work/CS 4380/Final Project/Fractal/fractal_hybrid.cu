/*
Fractal code

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
#include <cmath>
#include <cuda.h>


static const int ThreadsPerBlock = 512;


static __global__ void fractal(const int start_frame, const int stop_frame, const int frames, const int width, unsigned char* const pic)
{
  // todo: compute the pixels of all frames in the range
  const int i = threadIdx.x + blockIdx.x * blockDim.x;
  const int col = i % width;
  const int row = ( i / width ) % width;
  const int frame = i / ( width * width ) + start_frame;

  const double Delta = 0.004937716;
  const double xMid = -0.664689302;
  const double yMid =  0.355561972;

    // compute pixels of each frame
  if( i < ( stop_frame *  width * width )){  // frames
    const double delta = Delta * (1.5 + cos(2.0 * M_PI * frame / frames));
    const double xMin = xMid - delta;
    const double yMin = yMid - delta;
    const double dw = 2.0 * delta / width;
    const double cy = yMin + row * dw;
    const double cx = xMin + col * dw;
    double x = cx;
    double y = cy;
    double x2, y2;
    int count = 256;
    do {
      x2 = x * x;
      y2 = y * y;
      y = 2.0 * x * y + cy;
      x = x2 - y2 + cx;
      count--;
    } while ((count > 0) && ((x2 + y2) < 4.0));
    pic[((frame-start_frame) * width * width + row * width + col)] = (unsigned char)count;
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


unsigned char* GPU_Init(const int gpu_frames, const int width)
{
  unsigned char* d_pic;
  cudaMalloc((void **)&d_pic, gpu_frames * width * width * sizeof(unsigned char));
  CheckCuda(__LINE__);
  return d_pic;
}


void GPU_Exec(const int start_frame, const int stop_frame, const int frames, const int width, unsigned char* d_pic)
{
  // todo: launch the kernel with just the right number of blocks and ThreadsPerBlock threads per block and do nothing else
  fractal<<<(((stop_frame - start_frame) * width * width) + ThreadsPerBlock - 1 ) / ThreadsPerBlock , ThreadsPerBlock>>>(start_frame, stop_frame, frames, width, d_pic);
}


void GPU_Fini(const int gpu_frames, const int width, unsigned char* pic, unsigned char* d_pic)
{
  // todo: copy the result from the device to the host and free the device memory
  cudaMemcpy(pic, d_pic, gpu_frames * width * width * sizeof(unsigned char), cudaMemcpyDeviceToHost);
  CheckCuda(__LINE__);
  cudaFree(d_pic);
  CheckCuda(__LINE__);
}
