/*
N-body code

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


#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <random>
#include <sys/time.h>
#include "BMP24.h"


struct Data {
  // mass, 3D position, 3D velocity, 3D acceleration
  float mass, posx, posy, posz, velx, vely, velz, accx, accy, accz;
};


static void outputBMP(const int nbodies, const Data* const data, const int step)
{
  const int width = 512;
  BMP24 bmp(0, 0, width, width);
  bmp.clear(0);

  for (int i = 0; i < nbodies; i++) {
    const float fz = data[i].posz + 3.0f;
    if (fz > 0) {
      const float fx = data[i].posx;
      const float fy = data[i].posy;
      const int x = atanf(fx / fz) * (width / 2) + (0.5f + width / 2);
      const int y = atanf(fy / fz) * (width / 2) + (0.5f + width / 2);
      bmp.dot(x, y, 0xffff00);
    }
  }

  char name [32];
  sprintf(name, "nbody%d.bmp", step + 1000);
  bmp.save(name);
}


// based on SPLASH-2 code at https://github.com/staceyson/splash2/blob/master/codes/apps/barnes/code.C)
static void generateInput(const int nbodies, Data* const data)
{
  const double rsc = 0.5890486225481;
  const double vsc = sqrt(1.0 / rsc);
  std::mt19937 mt(0);
  std::uniform_real_distribution<double> rndval(0.0, 1.0);

  for (int i = 0; i < nbodies; i++) {
    data[i].mass = 1.0 / nbodies;

    const double r = 1.0 / sqrt(pow(rndval(mt) * 0.999, -2.0 / 3.0) - 1.0);
    double x, y, z, sq;
    do {
      x = rndval(mt) * 2.0 - 1.0;
      y = rndval(mt) * 2.0 - 1.0;
      z = rndval(mt) * 2.0 - 1.0;
      sq = x * x + y * y + z * z;
    } while (sq > 1.0);
    const double scalep = rsc * r / sqrt(sq);
    data[i].posx = x * scalep;
    data[i].posy = y * scalep;
    data[i].posz = z * scalep;

    do {
      x = rndval(mt);
      y = rndval(mt) * 0.1;
    } while (y > x * x * pow(1.0 - x * x, 3.5));
    const double v = x * sqrt(2.0 / sqrt(1.0 + r * r));
    do {
      x = rndval(mt) * 2.0 - 1.0;
      y = rndval(mt) * 2.0 - 1.0;
      z = rndval(mt) * 2.0 - 1.0;
      sq = x * x + y * y + z * z;
    } while (sq > 1.0);
    const double scalev = vsc * v / sqrt(sq);
    data[i].velx = x * scalev;
    data[i].vely = y * scalev;
    data[i].velz = z * scalev;
  }

  for (int i = 0; i < nbodies; i++) {
    data[i].accx = 0;
    data[i].accy = 0;
    data[i].accz = 0;
  }
}


static void computeForce(const int nbodies, Data* const data, const int step, const float dthf)
{
  const float epssq = 0.05f * 0.05f;

  for (int i = 0; i < nbodies; i++) {
    const float px = data[i].posx;
    const float py = data[i].posy;
    const float pz = data[i].posz;

    float ax = 0.0f;
    float ay = 0.0f;
    float az = 0.0f;

    for (int j = 0; j < nbodies; j++) {
      const float dx = data[j].posx - px;
      const float dy = data[j].posy - py;
      const float dz = data[j].posz - pz;
      float tmp = dx * dx + dy * dy + dz * dz;
      tmp = 1.0f / sqrtf(tmp + epssq);
      tmp = data[j].mass * tmp * tmp * tmp;
      ax += dx * tmp;
      ay += dy * tmp;
      az += dz * tmp;
    }

    if (step > 0) {
      data[i].velx += (ax - data[i].accx) * dthf;
      data[i].vely += (ay - data[i].accy) * dthf;
      data[i].velz += (az - data[i].accz) * dthf;
    }

    data[i].accx = ax;
    data[i].accy = ay;
    data[i].accz = az;
  }
}


static void integrate(const int nbodies, Data* const data, const float dthf)
{
  const float dtime = dthf + dthf;
  for (int i = 0; i < nbodies; i++) {
    const float dvelx = data[i].accx * dthf;
    const float dvely = data[i].accy * dthf;
    const float dvelz = data[i].accz * dthf;

    const float velhx = data[i].velx + dvelx;
    const float velhy = data[i].vely + dvely;
    const float velhz = data[i].velz + dvelz;

    data[i].posx += velhx * dtime;
    data[i].posy += velhy * dtime;
    data[i].posz += velhz * dtime;

    data[i].velx = velhx + dvelx;
    data[i].vely = velhy + dvely;
    data[i].velz = velhz + dvelz;
  }
}


int main(int argc, char *argv[])
{
  printf("N-body v1.2\n");

  // check command line
  if (argc != 4) {fprintf(stderr, "USAGE: %s number_of_bodies number_of_timesteps generate_images\n", argv[0]); exit(-1);}
  const int nbodies = atoi(argv[1]);
  if (nbodies < 4) {fprintf(stderr, "ERROR: number_of_bodies must be at least 4\n"); exit(-1);}
  const int timesteps = atoi(argv[2]);
  if (timesteps < 1) {fprintf(stderr, "ERROR: number_of_timesteps must be at least 1\n"); exit(-1);}
  const int genimages = atoi(argv[3]);
  if ((genimages != 0) && (genimages != 1)) {fprintf(stderr, "ERROR: generate_images must be either 0 or 1\n"); exit(-1);}
  printf("bodies: %d\n", nbodies);
  printf("time steps: %d\n", timesteps);
  printf("images: %s\n", genimages ? "yes" : "no");

  // allocate and initialize data
  Data* data = new Data [nbodies];
  generateInput(nbodies, data);

  // start time
  timeval beg, end;
  gettimeofday(&beg, NULL);

  // compute result for each time step
  const float dthf = 0.025f * 0.5f;
  for (int step = 0; step < timesteps; step++) {
    computeForce(nbodies, data, step, dthf);
    integrate(nbodies, data, dthf);
    // write result to BMP file
    if (genimages) outputBMP(nbodies, data, step);
  }

  // end time
  gettimeofday(&end, NULL);
  const double runtime = end.tv_sec - beg.tv_sec + (end.tv_usec - beg.tv_usec) / 1000000.0;
  printf("compute time: %.6f s\n", runtime);

  delete [] data;
  return 0;
}
