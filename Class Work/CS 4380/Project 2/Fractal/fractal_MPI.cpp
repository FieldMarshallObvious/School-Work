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
#include <algorithm>
#include <sys/time.h>
#include "BMP24.h"
#include <mpi.h>


static void fractal(const int start_frame, const int end_frame, const int frames, const int width, unsigned char* const pic)
{
  const double Delta = 0.004937716;
  const double xMid = -0.664689302;
  const double yMid =  0.355561972;

  // compute pixels of each frame
  for (int frame = start_frame; frame < end_frame; frame++) {  // frames
    const double delta = Delta * (1.5 + cos(2.0 * M_PI * frame / (frames)));
    const double xMin = xMid - delta;
    const double yMin = yMid - delta;
    const double dw = 2.0 * delta / width;
    for (int row = 0; row < width; row++) {  // rows
      const double cy = yMin + row * dw;
      for (int col = 0; col < width; col++) {  // columns
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
        pic[frame * width * width + row * width + col] = (unsigned char)count;
      }
    }
  }
}


int main(int argc, char* argv [])
{
  // set up MPI
  int comm_sz, my_rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if( my_rank == 0 ) printf("Fractal v2.3\n");

  // check command line
  if (argc != 3) {
    if( my_rank == 0 ) fprintf(stderr, "USAGE: %s frame_width number_of_frames\n", argv[0]);
    
    // cleanup
    MPI_Finalize();
    exit(-1);
  }
  const int width = atoi(argv[1]);
  if (width < 10) {
    if( my_rank == 0 ) fprintf(stderr, "ERROR: frame_width must be at least 10\n"); 

    // cleanup
    MPI_Finalize();
    exit(-1);
  }
  const int frames = atoi(argv[2]);
  if (frames < 1) {
    if( my_rank == 0 ) fprintf(stderr, "ERROR: number_of_frames must be at least 1\n"); 

    // cleanup
    MPI_Finalize();
    exit(-1);
  }
  if (frames % comm_sz != 0 ) {
    if( my_rank == 0 ) fprintf(stderr, "ERROR: number_of_frames must be a multiple of comm_sz\n"); 

    // cleanup
    MPI_Finalize();
    exit(-1);
  }

  if( my_rank == 0 ) {
    printf("frames: %d\n", frames);
    printf("width: %d\n", width);
    printf("processes: %d\n", comm_sz);
  }

  // determine the frames for this process to calculate
  const int my_start_frame = my_rank * (long)frames / comm_sz;
  const int my_end_frame = (my_rank + 1) * (long)frames / comm_sz;
  const int range = (my_end_frame - my_start_frame) * width * width;


  // allocate picture array
  unsigned char* pic = new unsigned char [frames * width * width];

  // create result picture array
  unsigned char* res_pic = NULL;

  if (my_rank == 0) res_pic = new unsigned char [frames * width * width];

  // start time
  timeval beg, end;
  MPI_Barrier(MPI_COMM_WORLD); // Wait for all processes for better timing
  gettimeofday(&beg, NULL);

  // execute timed code
  fractal(my_start_frame, my_end_frame, frames, width, pic);
  
  MPI_Gather(&pic[my_start_frame * width * width], range, MPI_UNSIGNED_CHAR, res_pic, range, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);


  // end time
  gettimeofday(&end, NULL);
  const double runtime = end.tv_sec - beg.tv_sec + (end.tv_usec - beg.tv_usec) / 1000000.0;

  if( my_rank == 0 ) printf("compute time: %.6f s\n", runtime);

  // write result to BMP files
  if (width <= 256 && my_rank == 0) {
    for (int frame = 0; frame < frames; frame++) {
      BMP24 bmp(0, 0, width, width);
      for (int y = 0; y < width; y++) {
        for (int x = 0; x < width; x++) {
          bmp.dot(x, y, res_pic[frame * width * width + y * width + x] * 0x000001 + 0x50ff00 - res_pic[frame * width * width + y * width + x] * 0x000100);
        }
      }
      char name [32];
      sprintf(name, "fractal%d.bmp", frame + 1000);
      bmp.save(name);
    }
  }

  // clean up
  delete [] pic;
  delete [] res_pic;
  MPI_Finalize();
  return 0;
}
