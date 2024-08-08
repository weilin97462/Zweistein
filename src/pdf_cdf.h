#ifndef __pdfcdf__
#define __pdfcdf__ 1
extern double DTC_pdf[15625][20];
extern double DTC_cdf[15625][20];
void init();
int encode_id(int dist[]);
#endif