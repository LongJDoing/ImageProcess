#include "StdAfx.h"
#include "LeastQuadraticFiter.h"
#include <math.h>

CLeastQuadraticFiter::CLeastQuadraticFiter(void)
{
}


CLeastQuadraticFiter::~CLeastQuadraticFiter(void)
{
}
double CLeastQuadraticFiter::LeastQuadraticFiter(int *x, int *y, double *coeff, int samplepoints, int powers)
{
	double matrix[MY_SIZE_MAX*MY_SIZE_MAX]={0}, vector[MY_SIZE_MAX]={0};
	for ( int j=0; j<powers; j++ )
	{
		for (int i=0; i<samplepoints; i++)
			vector[j] = vector[j] + y[i]*pow(double(x[i]),j);
		for ( int k=0; k<powers; k++ )
		{
			for (int i=0; i<samplepoints; i++)
				matrix[powers*k+j] = matrix[powers*k+j] + pow(double(x[i]),k)*pow(double(x[i]),j);
		}
	}
	
	GaussTriangleSpliter(matrix, vector, powers);
	double fitvalue[MY_SIZE_MAX]={0}, error = 0.;
	for (int i=0; i<samplepoints; i++)
		for (int j=0; j<powers; j++)
			fitvalue[i] = fitvalue[i] + vector[j]*pow(double(x[i]), j); 
	for (int i=0; i<samplepoints; i++)
		error = error + pow(fitvalue[i] - y[i], 2);
	for (int i=0; i<powers; i++) coeff[i] = vector[i];
	return sqrt(error);
}


void CLeastQuadraticFiter::GaussTriangleSpliter(double *matrix, double *vector, int n)
{
	int i, j, k;
	for (i=1; i<n; i++)
		matrix[n*i] = matrix[n*i]/matrix[0];
	
	for (i=1; i< n; i++)
	{
		for (j=i; j<n; j++)
		{
			double temp = 0.;
			for (k=0; k<i; k++)
				temp = temp + matrix[n*i+k]*matrix[n*k+j];
			matrix[n*i+j] = matrix[n*i+j] - temp;
			temp =0.;
			for (k=0; k<i; k++)
				temp = temp + matrix[n*(j+1)+k]*matrix[n*k+i];
			if( j+1 != n)
			{
				matrix[n*(j+1)+i] = (matrix[n*(j+1)+i] - temp)/matrix[n*i+i];
			}
		}
	}
	
	for (i=1; i<n; i++)
	{
		double temp = 0.;
		for (j=0; j<i; j++)
		{
			temp = temp + matrix[n*i+j]*vector[j];
		}
		vector[i] = vector[i] - temp;
	}	
	vector[n-1] = vector[n-1]/matrix[(n+1)*(n-1)];
	for (i=n-2; i>=0; i--)
	{
		double temp = 0.;
		for (j=i+1; j<n; j++)
		{
			temp = temp + matrix[n*i+j]*vector[j];
		}
		vector[i] = (vector[i] - temp)/matrix[n*i+i];
	}
}
