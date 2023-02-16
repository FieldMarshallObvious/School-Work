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
#include <pthread.h>
#include <sys/time.h>

// Shared variables
static long threads;
static long start;
static long top;
static long maxlen;
pthread_mutex_t mutex;


static void* collatz(void* arg)
{
  int myMaxLen = 0;

  const long my_rank = (long)arg;

  // compute sequence lengths
  for (long i = start + my_rank * 2; i < top; i += 2 * threads) {
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
    myMaxLen = std::max(myMaxLen, len);
  }

  // Return this threads max to the global
  pthread_mutex_lock(&mutex);
  maxlen = std::max(maxlen, (long)myMaxLen);

  pthread_mutex_unlock(&mutex);

  return NULL;
}


int main(int argc, char* argv [])
{
  printf("Collatz v1.8\n");

  // check command line
  if (argc != 4) {fprintf(stderr, "USAGE: %s start_value upper_bound\n", argv[0]); exit(-1);}
  start = atol(argv[1]);
  top = atol(argv[2]);
  printf("start value: %ld\n", start);
  printf("upper bound: %ld\n", top);
  threads = atol(argv[3]);
  if( threads < 1){fprintf(stderr, "ERROR: threads must be at least 1\n"); exit(-1);}
  printf("threads: %d\n", threads);

  // initialize the mutex
  pthread_mutex_init(&mutex, NULL);

  // Initalize pthread variables
  pthread_t* const handle = new pthread_t[threads - 1];

  // start time
  timeval beg, end;
  gettimeofday(&beg, NULL);

  // initial value for maxlen
  maxlen = 0;

  // launch threads
  for (long thread = 0; thread < threads - 1; thread++) {
    pthread_create(&handle[thread], NULL, collatz, (void*)thread);
  }

  // work for master
  collatz((void*)(threads - 1));

  // join threads
  for(long thread = 0; thread < threads - 1; thread++) {
    pthread_join(handle[thread], NULL);
  }

  // end time
  gettimeofday(&end, NULL);
  const double runtime = end.tv_sec - beg.tv_sec + (end.tv_usec - beg.tv_usec) / 1000000.0;
  printf("compute time: %.6f s\n", runtime);

  // print result
  printf("maximum length: %d\n", maxlen);

  // destory mutex
  pthread_mutex_destroy(&mutex);

  // deallocate memory
  delete [] handle;

  return 0;
}
