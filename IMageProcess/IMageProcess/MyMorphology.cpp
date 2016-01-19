#include "StdAfx.h"
#include "MyMorphology.h"


CMyMorphology::CMyMorphology(void)
{
}


CMyMorphology::~CMyMorphology(void)
{
}

void CMyMorphology::grayDilation(CImage * grayimage, int * graykernel)
{
	int width = grayimage->GetWidth();
	int height = grayimage->GetHeight();
	CImage * tempimage = new CImage();
	tempimage->Create(width, height, 24);

	COLORREF * color = new COLORREF[9];
	int * temppixel = new int[9];
	
	for(int cx = 1; cx < width - 1; cx++)
		for(int cy = 1; cy < height - 1; cy++)
		{
			for(int m = 0; m < 3; m++)
                for(int n = 0; n < 3; n++)
                {
					color[m * 3 + n] = grayimage->GetPixel((cx-1 + m) , (cy-1 + n));
                }
			int r; 
			for(int m = 0; m < 3; m++)
			    for(int n = 0; n < 3; n++)
                {
					r = GetRValue(color[8 - m * 3 - n]);
                    temppixel[m * 3 + n] = graykernel[m * 3 + n] + r;
                }
			int maxpixel = 0;
			 for(int k = 0; k < 9; k++)
                if(maxpixel < temppixel[k])
                {
                    maxpixel = temppixel[k];
                }
            if(maxpixel > 255)
                maxpixel = 255;
			tempimage->SetPixelRGB(cx, cy, maxpixel, maxpixel, maxpixel);
		}
	delete color, temppixel;
	COLORREF colortemp;
	for(int cx = 0; cx < width ; cx++)
		for(int cy = 0; cy < height ; cy++)
		{
			colortemp = tempimage->GetPixel(cx, cy);
			grayimage->SetPixel(cx, cy, colortemp);
		}
	delete tempimage;
}

void CMyMorphology::grayErosion(CImage * grayimage, int * graykernel)
{
	int width = grayimage->GetWidth();
	int height = grayimage->GetHeight();
	CImage * tempimage = new CImage();
	tempimage->Create(width, height, 24);

	COLORREF * color = new COLORREF[9];
	int * temppixel = new int[9];
	
	for(int cx = 1; cx < width - 1; cx++)
		for(int cy = 1; cy < height - 1; cy++)
		{
			for(int m = 0; m < 3; m++)
                for(int n = 0; n < 3; n++)
                {
					color[m * 3 + n] = grayimage->GetPixel((cx-1 + m) , (cy-1 + n));
                }
			int r; 
			for(int m = 0; m < 3; m++)
			    for(int n = 0; n < 3; n++)
                {
					r = GetRValue(color[8 - m * 3 - n]);
                    temppixel[m * 3 + n] = graykernel[m * 3 + n] + r;
                }
			int minpixel = 255;
            for(int k = 0; k < 9; k++)
                if(minpixel > temppixel[k])
                {
                    minpixel = temppixel[k];
                }
            if(minpixel < 0)
                minpixel = 0;
			tempimage->SetPixelRGB(cx, cy, minpixel, minpixel, minpixel);
		}
	delete color, temppixel;
	COLORREF colortemp;
	for(int cx = 0; cx < width ; cx++)
		for(int cy = 0; cy < height ; cy++)
		{
			colortemp = tempimage->GetPixel(cx, cy);
			grayimage->SetPixel(cx, cy, colortemp);
		}
	delete tempimage;
}

//grayscale dilation
/* kernel r=3
   2  1  2
   1  0  1
   2  1  2
   */
int * CMyMorphology::graykernel()
{
	int * m_graykerArr = new int[9];
    m_graykerArr[0] = m_graykerArr[2] = m_graykerArr[6] = m_graykerArr[8] =2;
    m_graykerArr[1] = m_graykerArr[3] = m_graykerArr[5] = m_graykerArr[7] =1;
    m_graykerArr[4] = 0;

	return m_graykerArr;
}

void CMyMorphology::grayOpening(CImage * grayimage, int * graykernel)
{
	this->grayErosion(grayimage, graykernel);
	this->grayDilation(grayimage, graykernel);
}

void CMyMorphology::grayClosing(CImage * grayimage, int * graykernel)
{
	this->grayDilation(grayimage, graykernel);
	this->grayErosion(grayimage, graykernel);
}

void CMyMorphology::grayEdge(CImage * grayimage, int * graykernel)
{
	CImage * tempimaged = new CImage();
	CImage * tempimagee = new CImage();
	int width = grayimage->GetWidth();
	int height = grayimage->GetHeight();
	tempimaged->Create(width, height, 24);
	tempimagee->Create(width, height, 24);

	COLORREF color;
	for(int cx = 0; cx < width ; cx++)
		for(int cy = 0; cy < height ; cy++)
		{
			color = grayimage->GetPixel(cx, cy);
			tempimaged->SetPixel(cx, cy, color);
			tempimagee->SetPixel(cx, cy, color);
		}
	this->grayDilation(tempimaged, graykernel);
	this->grayErosion(tempimagee, graykernel);
	for(int cx = 0; cx < width ; cx++)
		for(int cy = 0; cy < height ; cy++)
		{
			COLORREF colord = tempimaged->GetPixel(cx, cy);
			COLORREF colore = tempimagee->GetPixel(cx, cy);

			int r = GetRValue(colord) - GetRValue(colore);
			r = (r > 255) ? 255 : r;
			r = (r < 0) ? 0 : r;
			grayimage->SetPixelRGB(cx, cy, r, r, r);
		}
	delete tempimaged, tempimagee;
}

//grayscale dilation
/* kernel r=3
   1  1  1
   1  1  1
   1  1  1
   */

void CMyMorphology::binaryDilation(CImage * binaryimage, int * binarykernel)
{
	int width = binaryimage->GetWidth();
	int height = binaryimage->GetHeight();
	CImage * tempimage = new CImage();
	tempimage->Create(width, height, 8);

	byte * color = new byte[9];
	bool * value = new bool[9];
	byte * pData, *newpData;
	pData = (byte*)binaryimage->GetBits();
	newpData = (byte*)tempimage->GetBits();
	int pit = binaryimage->GetPitch();
	int newpit = tempimage->GetPitch();
	int bitCount = binaryimage->GetBPP()/8;
	int newbitCount = tempimage->GetBPP()/8;
	for(int cx = 1; cx < width - 1; cx++)
		for(int cy = 1; cy < height - 1; cy++)
		{
			for(int m = 0; m < 3; m++)
                for(int n = 0; n < 3; n++)
                {
					color[m * 3 + n] = *(pData + (cy-1 + n)*pit + (cx-1 + m)*bitCount);
                }
			for(int m =0 ;m < 9; m++)
            {
                value[m] = (color[m])&& binarykernel[m];
            }
			int templevel = 255;
            if((value[0] || value[1] || value[2] || value[3] || value[4] && value[5] || value[6] || value[8] || value[8]) == 0)
                templevel = 0;
			*(newpData + cy*newpit + cx*newbitCount) = templevel;
		}
	for(int cx = 0; cx < width ; cx++)
		for(int cy = 0; cy < height ; cy++)
		{
			*(pData + cy*pit + cx*bitCount) = *(newpData + cy*newpit + cx*newbitCount);
		}
	delete tempimage, color, value;
}

void CMyMorphology::binaryErosion(CImage * binaryimage, int * binarykernel)
{
	int width = binaryimage->GetWidth();
	int height = binaryimage->GetHeight();
	CImage * tempimage = new CImage();
	tempimage->Create(width, height, 8);

	byte * color = new byte[9];
	bool * value = new bool[9];
	byte * pData, *newpData;
	pData = (byte*)binaryimage->GetBits();
	newpData = (byte*)tempimage->GetBits();
	int pit = binaryimage->GetPitch();
	int newpit = tempimage->GetPitch();
	int bitCount = binaryimage->GetBPP()/8;
	int newbitCount = tempimage->GetBPP()/8;

	for(int cx = 1; cx < width - 1; cx++)
		for(int cy = 1; cy < height - 1; cy++)
		{
			for(int m = 0; m < 3; m++)
                for(int n = 0; n < 3; n++)
                {
					color[m * 3 + n] = *(pData + (cy-1 + n)*pit + (cx-1 + m)*bitCount);
                }
			for(int m =0 ;m < 9; m++)
            {
				if(binarykernel[m] == 0)
                    value[m] = 1;
                else
                    value[m] = (color[m])&&binarykernel[m];
            }
			int templevel = 0;
			if((value[0]&&value[1]&& value[2] && value[3]&& value[4]&& value[5]&& value[6]&& value[7]&& value[8]) == 1)
                templevel = 255;

			*(newpData + cy*newpit + cx*newbitCount) = templevel;
		}
	for(int cx = 0; cx < width ; cx++)
		for(int cy = 0; cy < height ; cy++)
		{
			*(pData + cy*pit + cx*bitCount) = *(newpData + cy*newpit + cx*newbitCount);
		}
	delete tempimage, color, value;
}

void CMyMorphology::binaryClosing(CImage * binaryimage, int * binarykernel)
{
	this->binaryDilation(binaryimage, binarykernel);
	this->binaryErosion(binaryimage, binarykernel);
}

void CMyMorphology::binaryOpening(CImage * binaryimage, int * binarykernel)
{
	this->binaryErosion(binaryimage, binarykernel);
	this->binaryDilation(binaryimage, binarykernel);
	
}

int * CMyMorphology::binarykernel()
{
	int * binarykernel = new int[9];
	for(int i = 0; i < 9 ; i++)
		binarykernel[i] = 1;
	return binarykernel;
}
/*==============================================================
函数:	binaryDelete
功能:   删除图片当中的零碎点（《=3个邻接点，delete）
参数:   


--------------------------------------------------------------*/
void CMyMorphology::binaryDelete(CImage * binaryimage, int * binarykernel)
{
	int width = binaryimage->GetWidth();
	int height = binaryimage->GetHeight();
	CImage * tempimage = new CImage();
	tempimage->Create(width, height, 8);

	byte * color = new byte[9];
	bool * value = new bool[9];
	byte * pData, *newpData;
	pData = (byte*)binaryimage->GetBits();
	newpData = (byte*)tempimage->GetBits();
	int pit = binaryimage->GetPitch();
	int newpit = tempimage->GetPitch();
	int bitCount = binaryimage->GetBPP()/8;
	int newbitCount = tempimage->GetBPP()/8;

	for(int cx = 1; cx < width - 1; cx++)
		for(int cy = 1; cy < height - 1; cy++)
		{
			for(int m = 0; m < 3; m++)
                for(int n = 0; n < 3; n++)
                {
					color[m * 3 + n] = *(pData + (cy-1 + n)*pit + (cx-1 + m)*bitCount);
				}

			int templevel = 0;
			int nums = 0;
			for(int m =0 ;m < 9; m++)
            {
				if(binarykernel[m] == 0)
                    value[m] = 1;
                else
                    value[m] = (color[m])&&binarykernel[m];
				if(value[m] == 1)
					nums++;
            }
			if(nums > 2)
                templevel = 255;

			*(newpData + cy*newpit + cx*newbitCount) = templevel;
		}
	for(int cx = 0; cx < width ; cx++)
		for(int cy = 0; cy < height ; cy++)
		{
			*(pData + cy*pit + cx*bitCount) = *(newpData + cy*newpit + cx*newbitCount);
		}
	delete tempimage, color, value;
}