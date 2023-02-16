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
#include <cuda.h>
#include <cmath>
#include <algorithm>
#include <sys/time.h>
#include "BMP24.h"

static const int ThreadsPerBlock = 512;

static __global__ void fractal(const int frames, const int width, unsigned char* const pic)
{
  // Determine what iteration we are 
  const int i = threadIdx.x + blockIdx.x * blockDim.x;

  // Calculate the current frame and row
  const int col = i % width;
  const int row = ( i / width ) % width;
  const int frame = i / ( width * width );

  const float Delta = 0.004937716f;
  const float xMid = -0.664689302f;
  const float yMid =  0.355561972f;

  // compute pixels of each frame
  if( i < frames * ( width * width ) ){  // frames
    const float delta = Delta * (1.5f + cosf(2.0f * (float)M_PI * frame / frames));
    const float xMin = xMid - delta;
    const float yMin = yMid - delta;
    const float dw = 2.0f * delta / width;
    const float cy = yMin + row * dw;
    const float cx = xMin + col * dw;
    float x = cx;
    float y = cy;
    float x2, y2;
    int count = 256;
    do {
      x2 = x * x;
      y2 = y * y;
      y = 2.0f * x * y + cy;
      x = x2 - y2 + cx;
      count--;
    } while ((count > 0) && ((x2 + y2) < 4.0f));
    pic[frame * width * width + row * width + col] = (unsigned char)count;
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
  printf("Fractal v2.3\n");

  // check command line
  if (argc != 3) {fprintf(stderr, "USAGE: %s frame_width number_of_frames\n", argv[0]); exit(-1);}
  const int width = atoi(argv[1]);
  if (width < 10) {fprintf(stderr, "ERROR: frame_width must be at least 10\n"); exit(-1);}
  const int frames = atoi(argv[2]);
  if (frames < 1) {fprintf(stderr, "ERROR: number_of_frames must be at least 1\n"); exit(-1);}
  printf("frames: %d\n", frames);
  printf("width: %d\n", width);

  // allocate picture array 
  unsigned char* pic = new unsigned char [frames * width * width];

  // Allocate picture array on GPU
  unsigned char* d_pic;
  cudaMalloc((void **) &d_pic, sizeof(unsigned char) * frames * width * width );
  CheckCuda(__LINE__);

  // start time
  timeval beg, end;
  gettimeofday(&beg, NULL);

  // execute timed code
  fractal<<<( (frames * width * width) + ThreadsPerBlock - 1 ) / ThreadsPerBlock , ThreadsPerBlock>>>(frames, width, d_pic);
  cudaDeviceSynchronize();  // wait for kernel to finish

  // end time
  gettimeofday(&end, NULL);
  CheckCuda(__LINE__);
  const float runtime = end.tv_sec - beg.tv_sec + (end.tv_usec - beg.tv_usec) / 1000000.0;
  printf("compute time: %.6f s\n", runtime);

  // Get resule from GPU
  cudaMemcpy( pic, d_pic, sizeof(unsigned char) * frames * width * width, cudaMemcpyDeviceToHost);
  CheckCuda(__LINE__);
  // write result to BMP files
  if (width <= 256) {
    for (int frame = 0; frame < frames; frame++) {
      BMP24 bmp(0, 0, width, width);
      for (int y = 0; y < width; y++) {
        for (int x = 0; x < width; x++) {
          bmp.dot(x, y, pic[frame * width * width + y * width + x] * 0x000001 + 0x50ff00 - pic[frame * width * width + y * width + x] * 0x000100);
        }
      }
      char name [32];
      sprintf(name, "fractal%d.bmp", frame + 1000);
      bmp.save(name);
    }
  }

  // clean up
  cudaFree(d_pic);
  delete [] pic;
  return 0;
}
