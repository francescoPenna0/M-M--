#include "funzioni.h"


double poisson(double RISOLUZIONE,double lambda)
// genera un tempo di interarrivo distribuito secondo Poisson
{
return (-logl(1 - (random((double)RISOLUZIONE) / (double)RISOLUZIONE) / (double)lambda)))));
}