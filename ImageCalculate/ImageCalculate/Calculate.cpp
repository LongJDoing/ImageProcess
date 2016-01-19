#include "StdAfx.h"
#include "Calculate.h"
#include <math.h>

CCalculate::CCalculate(void)
{
}


CCalculate::~CCalculate(void)
{
}

double CCalculate::CalculateMean(unsigned char *bitmap, int *labelmap, int width, int height, int maxarea, int labelIndex)
{
	m_Mean = 0.0;
	for(int i = 0; i < width*height; i++)
	{
		if(labelmap[i] == labelIndex)
			m_Mean += (double)bitmap[i] / maxarea;
	}
	return m_Mean;
}

double CCalculate::CalculateVariance(unsigned char *bitmap, int *labelmap, int width, int height, int maxarea, int labelIndex)
{
	m_Variance = 0.0;
	double m_Mean = CalculateMean(bitmap, labelmap, width, height, maxarea, labelIndex);
	for(int i = 0; i < width*height; i++)
	{
		if(labelmap[i] == labelIndex)
			m_Variance += (double)sqrt((bitmap[i]-m_Mean)*(bitmap[i]-m_Mean)) / maxarea;
	}
	return m_Variance;
}

int CCalculate::CalculateArea(int *labelmap, int width, int height, int labelIndex)
{
	int Area = 0;
	for(int i = 0; i < width * height; i++)
	{
		if(labelmap[i] == labelIndex)
			Area++;
	}
	return Area;
}