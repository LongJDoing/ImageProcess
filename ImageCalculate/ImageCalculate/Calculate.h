#pragma once
class CCalculate
{
public:
	CCalculate(void);
	~CCalculate(void);
	double CalculateMean(unsigned char *, int *, int, int, int, int);
	double CalculateVariance(unsigned char *, int *, int, int, int, int);
//	int  FindCentralPosition(unsigned char *, int *, int, int, int, int);
	int CalculateArea(int *, int, int, int);

public:
	double m_Mean;
	double m_Variance;
	int m_CentralPosition;
	int m_MaxArea;

};

