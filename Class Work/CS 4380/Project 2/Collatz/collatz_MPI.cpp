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
#include <sys/time.h>
#include <mpi.h>



static int collatz(const long start, const long top, const int my_rank, const int increment)
{
  int maxlen = 0;


  // compute sequence lengths
  for (long i = start + my_rank * 2; i < top ; i += increment * 2) {
    long val = i;
    int len = 1;

    do {
      len++;
      if ((val % 2) != 0) {
        val = 3 * val + 1;  // odd
      } else {
        val = val / 2;  // even
      }
    } while (val != 1);
    maxlen = std::max(maxlen, len);
  }

  return maxlen;
}


int main(int argc, char* argv [])
{

  // set up MPI
  int comm_sz, my_rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if( my_rank == 0 ) printf("Collatz v1.8\n");

  // check command line
  if (argc != 3) 
  {
    if ( my_rank == 0 )
    {
        fprintf(stderr, "USAGE: %s start_value upper_bound\n", argv[0]); 
    }
    // cleanup
    MPI_Finalize();
    exit(-1);
  }
  const long start = atol(argv[1]);
  const long top = atol(argv[2]);

  if ( my_rank == 0 )
  {
    printf("start value: %ld\n", start);
    printf("upper bound: %ld\n", top);
    printf("processes: %d\n", comm_sz);
  }


  // Initialize destination location
  int* res = NULL;
  if( my_rank == 0 ) res = new int[1];

  // start time
  timeval beg, end;
  MPI_Barrier(MPI_COMM_WORLD); // Wait for all processes for better timing
  gettimeofday(&beg, NULL);

  // execute timed code
  const int maxlen = collatz(start, top, my_rank, comm_sz);
  const int* sendBuf = &maxlen;

  MPI_Reduce(sendBuf, res, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);


  // end time
  gettimeofday(&end, NULL);
  const double runtime = end.tv_sec - beg.tv_sec + (end.tv_usec - beg.tv_usec) / 1000000.0;
  if( my_rank == 0 )
  {
    printf("compute time: %.6f s\n", runtime);
    // print result
    printf("maximum length: %d\n", res[0]);

    delete [] res;
  }

  // cleanup
  MPI_Finalize();

  return 0;
}
