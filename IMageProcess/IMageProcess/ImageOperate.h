#pragma once
class CImageOperate
{
public:
	CImageOperate(void);
	~CImageOperate(void);
public:
	void calhistogram(CImage *, int *);
	CImage * CreateHistogram(int *);
	int calotsuThreshold(int *);
	int calentropyThreshold(int *);
	void ToBinary(CImage *, int);
	double *  Gussianfilter();
	double *   Medianfilter();
	double *   SobelKernel();
	double *   PrewittKernel();
	int *   LaplaceKerner();
	void calconvolution(CImage *, int, int *);
	void calconvolution(float **, int, double *, int, int);
};

