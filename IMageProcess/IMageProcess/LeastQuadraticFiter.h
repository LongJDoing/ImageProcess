#pragma once
#define MY_SIZE_MAX 300
class CLeastQuadraticFiter
{
public:
	CLeastQuadraticFiter(void);
	~CLeastQuadraticFiter(void);
public:
	double LeastQuadraticFiter(int *x, int *y, double *coff, int samplepoints, int powers);
	void GaussTriangleSpliter(double *matrix, double *vector, int n);
};

