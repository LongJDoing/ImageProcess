#include "StdAfx.h"
#include "ImageOperate.h"

#include <math.h>

CImageOperate::CImageOperate(void)
{
}


CImageOperate::~CImageOperate(void)
{
}
void CImageOperate::calhistogram(CImage * image, int * hisarr)
{
	int width = image->GetWidth();
	int height = image->GetHeight();
	byte * pData;
	pData = (byte *)image->GetBits();
	int pit = image->GetPitch();
	int bitCount = image->GetBPP()/8;

	byte r;
	for(int cx = 0; cx < width; cx++)
		for(int cy = 0; cy < height; cy++)
		{
			r = *(pData + cy*pit + cx*bitCount);
			hisarr[r]++;
		}
}

CImage * CImageOperate::CreateHistogram(int * hisarr)
{
	CImage * image = new CImage();
	image->Create(400, 300, 24);
	for(int cx = 0; cx < 400; cx++)
		for(int cy = 0; cy < 300; cy++)
			image->SetPixelRGB(cx, cy, 255, 255, 255);
	int m = 0;
	int Max = 0;
	for(int i = 0 ; i < 256; i++)
	{
		Max = (Max < hisarr[i]) ? hisarr[i] : Max;
	}
	for(int i = 0; i < 256; i++)
	{
		hisarr[i] = 280 * (hisarr[i]) / Max;
	}
	for(int i = 80; i < 80+256; i++)
	{
		for(int j = 0; j < hisarr[m]; j++)
		{
			image->SetPixelRGB(i, 290-j, 0, 0, 0);
		}
		m++;
	}
	return image;
}

int CImageOperate::calotsuThreshold(int * m_hisArr)
{
	 int otsuthreshold = 0;

    double Sum_w = 0;
    double Sum_m = 0;
    for(int i = 0; i < 256; i++)
    {
        Sum_w += m_hisArr[i];
        Sum_m += i * m_hisArr[i];
    }
    double MidValue = 0;
    double TempValue = 0;
    for (int t = 0; t < 256; t++)
    {
        int w0 = 0;
        int w1 = 0;
        int u0 = 0;
        int u1 = 0;
        for (int i  = 0; i <= t; i++)
        {
            w0 += m_hisArr[i];

            u0 += i * m_hisArr[i];

        }
        w1 = Sum_w - w0;
        u1 = Sum_m - u0;

       // if((w0 != 0) && (w1 !=0))
        MidValue = (double)w0 * w1 *((double)u0 / w0 -(double)u1 / w1)*((double)u0 / w0 - (double)u1 / w1);
        if (TempValue < MidValue)
        {
            TempValue = MidValue;
            otsuthreshold = t;
        }
      }
    return otsuthreshold;
}

int CImageOperate::calentropyThreshold(int * m_hisArr)
{
    int entropythreshold = 0;

    double HAll = 0;

    for(int t = 0; t < 256; t++)
    {
        int pixnum1 = 0;
        int pixnum2 = 0;
        double tempH = 0;
        double Ha = 0;
        double Hw = 0;

        for (int i = 0; i < t; i++)
        {
            pixnum1 += m_hisArr[i];
        }
        for (int i = 0; i < t; i++)
        {
            if(m_hisArr[i] > 0)
            Ha += (double)m_hisArr[i] / pixnum1 * log10(double(m_hisArr[i]) / pixnum1);
        }
        Ha = -Ha;

        for (int i = t+1; i < 256; i++)
        {
            pixnum2 += m_hisArr[i];
        }
        for (int i = t+1; i < 256; i++)
        {
            if(m_hisArr[i] > 0)
            Hw += (double)m_hisArr[i] / pixnum2 * log10((double)m_hisArr[i] / pixnum2);
        }
        Hw = -Hw;

        tempH = Ha + Hw;

        if(HAll < tempH)
        {
            HAll = tempH;
            entropythreshold = t;
        }

    }
    return entropythreshold;
}

void CImageOperate::ToBinary(CImage * image, int threshold)
{
	byte r;
	int width = image->GetWidth();
	int height = image->GetHeight();
	byte * pData;
	pData = (byte *)image->GetBits();
	int pit = image->GetPitch();
	int bitCount = image->GetBPP()/8;

	for(int cx = 0; cx < width; cx++)
		for(int cy = 0; cy < height; cy++)
		{
			r = *(pData + cy*pit + cx*bitCount);
			if(r < threshold)
				r = 0;
			else 
				r = 255;
			*(pData + cy*pit + cx*bitCount) = r; 
		}
}
double *  CImageOperate::Gussianfilter()
{
	const int conlength = 16;
	int d = sqrt(float(conlength));
	double * m_conArr;
	m_conArr = new double[conlength];
    double gaussianvalue ; // ±ê×¼²î
	gaussianvalue = 1.0;
	double SumGaussian = 0.0;
    for (int i = 0; i < d; i++)
        for(int j = 0; j < d; j++)
            {
            m_conArr[i*d + j] = exp((double)(-((i-2)*(i-2) + (j-2)*(j-2) )) /(2* gaussianvalue * gaussianvalue) ) * 1.0 / (2 * 3.14 * gaussianvalue * gaussianvalue);
            SumGaussian += m_conArr[i*4 + j];
            }
    for (int i = 0; i < d; i++)
        for(int j = 0; j < d; j++)
            {
            m_conArr[i*d + j] = m_conArr[i*d + j] / SumGaussian;
            }//    for(int i = 0; i < 9; i++)
	return m_conArr;
}

double * CImageOperate::Medianfilter()
{
    //std::cout << medianvalue << std::endl;
    const int conlength = 9;
	double * m_conArr;
    m_conArr = new double[conlength];

    for(int i = 0; i < conlength; i++)
    {
        m_conArr[i] = 1.0 / conlength ;

    }
	return  m_conArr;
}

double *  CImageOperate::PrewittKernel()
{
   int conlength = 9;
   double * m_conArr;
   m_conArr = new double[conlength];

   for(int i = 0; i < 9; i++)
   {
       if(i < 3)
           m_conArr[i] = 1;
       else if(i > 5)
           m_conArr[i] = -1;
       else
           m_conArr[i] = 0;
   }
   return m_conArr;
}

double * CImageOperate::SobelKernel()
{
	int conlength = 9;
	double * m_conArr;
    m_conArr = new double[conlength];

    {
        m_conArr[0] = 1 ; m_conArr[1] = 2 ; m_conArr[2] = 1 ;
        m_conArr[3] = 0 ; m_conArr[4] = 0 ; m_conArr[5] = 0 ;
        m_conArr[6] = -1 ; m_conArr[7] = -2 ;m_conArr[8] = -1 ;

    }
	return  m_conArr;
}

int * CImageOperate::LaplaceKerner()
{
	int conlength = 9;
	int * m_conArr;
    m_conArr = new int[conlength];

    {
        m_conArr[0] = 0; m_conArr[1] = 1 ; m_conArr[2] = 0 ;
        m_conArr[3] = 1 ; m_conArr[4] = -4 ; m_conArr[5] = 1 ;
        m_conArr[6] = 0 ; m_conArr[7] = 1 ;m_conArr[8] = 0 ;

    }
	return  m_conArr;

}
void CImageOperate::calconvolution(CImage * image, int conlength, int *m_conArr)
{
	int width = image->GetWidth();
	int height = image->GetHeight();
	byte r;
    COLORREF * color = new COLORREF[conlength];

    if(conlength == 4)
    {

        for (int i = 0; i < width-1; i++)
            for (int j = 0; j < height-1; j++)
            {
                int graycolor  = 0 ;
				color[0] = COLORREF(image->GetPixel(i, j));
                color[1] = COLORREF(image->GetPixel(i+1, j));
                color[2] = COLORREF(image->GetPixel(i, j+1));
                color[3] = COLORREF(image->GetPixel((i+1), (j+1)));

                for(int k = 0; k < 4; k++)
				{
					r = GetRValue(color[k]);
                    graycolor += r * m_conArr[k];
				}
                if((graycolor < 0))
                    graycolor = 0 ;
                if(graycolor > 255)
                    graycolor = 255;
				image->SetPixelRGB(i, j, graycolor, graycolor, graycolor);
            }
    }
     int length = (sqrt((double)(conlength)));
     if(conlength != 4)
     {
         for (int i = length -2; i < width-length +2; i++)
             for (int j = length -2; j < height-length +2; j++)
            {
                int graycolor  = 0 ;

                for(int m = 0; m < length; m++)
                    for(int n = 0; n < length; n++)
                    {
						color[m * length + n] = COLORREF(image->GetPixel((i-1 + m) , (j-1 + n) ));
                    }

                for (int k = 0; k < conlength; k++)
				{
					r = GetRValue(color[k]);
                    graycolor += r * m_conArr[k];
                if((graycolor < 0))
                    graycolor = 0 ;
                if(graycolor > 255)
                    graycolor = 255;
				image->SetPixelRGB(i, j, graycolor, graycolor, graycolor);
				}
		}
	 }
	 delete color;

}

void CImageOperate::calconvolution(float ** image,  int conlength, double *m_conArr, int width, int height)
{
	float * color = new float[conlength];
	float r;
	 if(conlength == 4)
    {

        for (int i = 0; i < width-1; i++)
            for (int j = 0; j < height-1; j++)
            {
                float graycolor  = 0 ;
				color[0] = image[i][j];
                color[1] = image[i+1][j];
                color[2] = image[i][j+1];
                color[3] = image[i+1][j+1];

                for(int k = 0; k < 4; k++)
				{
					r = color[k];
                    graycolor += r * m_conArr[k];
				}
				image[i][j] = graycolor;
            }
    }
     int length = (sqrt((double)(conlength)));
     if(conlength != 4)
     {
         for (int i = length -2; i < width-length +2; i++)
             for (int j = length -2; j < height-length +2; j++)
            {
                float graycolor  = 0 ;

                for(int m = 0; m < length; m++)
                    for(int n = 0; n < length; n++)
                    {
						color[m * length + n] = image[i-1 + m][j-1 + n];
                    }

                for (int k = 0; k < conlength; k++)
				{
					r = color[k];
                    graycolor += r * m_conArr[k];
                	image[i][j] = graycolor;
				}
		}
	 }
	 delete color;
}