/*****************************************************************************
*                                                                            *
*  ------------------------------ nummeths.h ------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef NUMMETHS_H
#define NUMMETHS_H

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

int interpol(const double *x, const double *fx, int n, double *z, double *pz,
   int m);

void lsqe(const double *x, const double *y, int n, double *b1, double *b0);

int root(double (*f)(double x), double (*g)(double x), double *x, int *n,
   double delta);

#endif
