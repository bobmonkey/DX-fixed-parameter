#include <Rcpp.h>
#include <stdio.h>
#include <stdlib.h>
#include <R_ext/Random.h>
using namespace Rcpp;

#define K_MAX	3500
#define PP 2147483647  //2^31-1
#define B_X1 536869888 
#define K_X1 47
#define T_X1 1
static int I_X, T_X, K_X;           /* running index */

unsigned long MODP(unsigned long z) {return ((((z)&PP)+((z)>>31)) &PP);}

static double res;
static int nseed = K_X1;
static Int32 seed[K_MAX];

double * user_unif_rand()
{
  int II0 = I_X;
  if(++I_X >= K_X)  I_X = 0;     /*wrap around running index */
  seed[I_X] = MODP(B_X1 * seed[I_X] + seed[II0]);
  res = (double) seed[I_X] /(double) PP;
  return &res;
}

void user_unif_init(Int32 seed_in) { 
  int i;
  K_X=K_X1;
  T_X=T_X1;
  srand(seed_in);
  for (i=0; i<K_X; i++) seed[i] = rand() & PP;
  I_X=K_X-1;
}

int * user_unif_nseed() { return &nseed; }
int * user_unif_seedloc() { return (int *) &seed; }
