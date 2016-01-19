
// IMageProcessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IMageProcess.h"
#include "IMageProcessDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


RGBQUAD colorTable[256];
RGBQUAD mycolorTable[10];
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIMageProcessDlg 对话框




CIMageProcessDlg::CIMageProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIMageProcessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_mymorphology = new CMyMorphology();
	m_pImg = new CImage();
	m_pConnectComponentLabel = new CConnectComponentLabel();
	//m_pImg = NULL;
	labelmap = NULL;
	m_myimageopreate = new CImageOperate();
	for(int i=0; i<256; i++)
	{
		RGBQUAD index;
		index.rgbBlue = index.rgbGreen = index.rgbRed = i;
		colorTable[i] = index;
	}
	for(int i=0; i<10; i++)
	{
		RGBQUAD index;
		index.rgbBlue = i*22;
		index.rgbGreen = i+10;
		index.rgbRed = i + 100;
		
		mycolorTable[i] = index;
	}
	m_kmeans = new CK_Means();
	m_isodata = new CISOData();
	m_myslopecluster = new CMySlopeCluster();
	m_leastquadraticfiter = new CLeastQuadraticFiter();
	CFile m_File1;
	m_File1.Remove("result.txt"); //删除上一次存储的图片位置
	m_File1.Open("result.txt",CFile::modeWrite|CFile::modeCreate);//重新创建该文件
	m_File1.Close();

}

void CIMageProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIMageProcessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PROCESS1, &CIMageProcessDlg::OnProcess1)
	ON_BN_CLICKED(IDC_PROCESS2, &CIMageProcessDlg::OnProcess2)
	ON_BN_CLICKED(IDC_PROCESS3, &CIMageProcessDlg::OnProcess3)
	ON_BN_CLICKED(IDC_PROCESS4, &CIMageProcessDlg::OnProcess4)
	ON_BN_CLICKED(IDC_PROCESS5, &CIMageProcessDlg::OnProcess5)
	ON_BN_CLICKED(IDC_PROCESS7, &CIMageProcessDlg::OnProcess7)
END_MESSAGE_MAP()


// CIMageProcessDlg 消息处理程序

BOOL CIMageProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIMageProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIMageProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIMageProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//===============目的是制作一张掩模图==================
void CIMageProcessDlg::OnShow(CImage * Image)
{
	CRect rect;
	//选择需要显示的图像
	if(!Image->IsNull())	
	{
		int cx = Image->GetWidth();
		int cy = Image->GetHeight();
		CRect rectSrc;
		CWnd *pWnd=GetDlgItem(IDC_PICTURE);//获得pictrue控件窗口的句柄  
			
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rectSrc = CRect(CPoint(0, 0), CPoint(cx, cy));
		pWnd->MoveWindow(rect, TRUE);//将窗口移动到Picture控件表示的矩形区域  					
		pWnd->GetClientRect(&rect);//获得pictrue控件所在的矩形区域 

		CDC *pDC=pWnd->GetDC();//获得pictrue控件的DC  
		Image->Draw(pDC->m_hDC, rect, rectSrc); //将图片画到Picture控件表示的矩形区域 

		ReleaseDC(pDC);//释放picture控件的DC  
	}
	
	return;
}

void CIMageProcessDlg::OnProcess1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString path = "image\\";
	CString filename;
	filename = path + "temp2.bmp";
	CImage *image = new CImage();
	image->Load(filename);
	m_Width = image->GetWidth();
	m_Height = image->GetHeight();
	//将图像都转换为8为索引图
	m_pImg->Create(m_Width, m_Height, 8);
	byte * pData, * oldpData;
	oldpData = (byte*)image->GetBits();
	pData = (byte *)m_pImg->GetBits();
	int pit = m_pImg->GetPitch();
	int oldpit = image->GetPitch();
	int bitCount = m_pImg->GetBPP()/8;
	int oldbitCount = image->GetBPP()/8;
	for(int cy = 0; cy < m_Height; cy++)
		for(int cx = 0; cx < m_Width; cx++)
		{
			*(pData + cy*pit + cx*bitCount) = *(oldpData + cy*oldpit + cx*oldbitCount);
		}
	delete image;
	for(int cy = 0; cy < m_Height; cy++)
		for(int cx = 0; cx < m_Width; cx++)
		{
			byte r = *(pData + cy*pit + cx*bitCount);
			if((r > 200)||(r < 80))
				*(pData + cy*pit + cx*bitCount) = 255;
			else
				*(pData + cy*pit + cx*bitCount) = 0;
		}
	m_pImg->SetColorTable(0, 256, colorTable);
	OnShow(m_pImg);
}



void CIMageProcessDlg::OnProcess2()
{
	// TODO: 在此添加控件通知处理程序代码
	int * binarykernel;
	binarykernel  = m_mymorphology->binarykernel();
	m_mymorphology->binaryClosing(m_pImg, binarykernel);
	m_mymorphology->binaryOpening(m_pImg, binarykernel);
	delete binarykernel;
	OnShow(m_pImg);
}



void CIMageProcessDlg::OnProcess3()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char * bitmap = new unsigned char[m_Width * m_Height];
	byte r;
    labelmap = new int[m_Width * m_Height];
	byte * pData = (byte*)m_pImg->GetBits();
	int pit = m_pImg->GetPitch();
	int bitCount = m_pImg->GetBPP()/8;
	for(int i = 0; i < m_Width * m_Height; i++)
	{
		r = *(pData + i/m_Width*pit + i%m_Width*bitCount);
		bitmap[i] = r;
		labelmap[i] = 0;
	}
	int m_labelIndex = m_pConnectComponentLabel->ConnectedComponentLabeling(bitmap, m_Width, m_Height, labelmap);
	//CImage * bimage = new CImage();
	//bimage->Create(m_Width, m_Height, 24);
	//for(int i = 0 ;i < m_Width*m_Height; i++)
	//{
	//	switch(labelmap[i])
	//	{
	//	case 0:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 0,0,0);
	//		break;
	//	case 1:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 255,0,0);
	//		break;
	//	case 2:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 0,255,0);
	//		break;
	//	case 3:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 0,0,255);
	//		break;
	//	case 4:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 124,124,0);
	//		break;
	//	case 5:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 0,124,0);
	//		break;
	//	case 6:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 0,124,124);
	//		break;
	//	case 7:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 0,34,124);
	//		break;
	//	default:
	//		bimage->SetPixelRGB(i%m_Width, i/m_Width, 80,30,0);
	//		break;
	//	}
	//}
	//OnShow(bimage);
	//delete bimage;
	int max, temp, maxIndex;
	max  = 0;
	maxIndex = 1;
	for(int j = 1; j <= m_labelIndex; j++)
	{
		temp = 0;
		for(int i = 0; i < m_Width * m_Height; i++)
		{
			if(labelmap[i] == j)
				temp++;
		}
		if(max < temp)
		{
			max = temp;
			maxIndex = j;
		}
		
	}
	for(int i = 0; i < m_Width * m_Height; i++)
	{
		if(labelmap[i] == maxIndex)
		{
			labelmap[i] = INTEREST;
			*(pData + i/m_Width*pit + i%m_Width*bitCount) = 255;
		}
		else
		{
			labelmap[i] = 0;
			*(pData + i/m_Width*pit + i%m_Width*bitCount) = 0;
		}
	}
	m_pImg->SetColorTable(0, 256, colorTable);
	OnShow(m_pImg);
	delete bitmap, m_pImg;
	m_pImg = NULL;
	bitmap = NULL;
}
// ===============完成掩模图的制作=================

#if 0
//================查找线算法===============
void CIMageProcessDlg::OnProcess4()
{
	// TODO: 在此添加控件通知处理程序代码
	ofstream fout("result.txt", ios::out|ios::in|ios::ate);
	m_pImg = new CImage();
	m_pImg->Create(m_Width, m_Height, 8);
	CString path = "image\\";
	CString filename;
	filename = path + "temp2.bmp";
	CImage * image = new CImage();
	image->Load(filename);
	//将图像都转换为8为索引图
	byte * pData, * oldpData;
	oldpData = (byte*)image->GetBits();
	pData = (byte *)m_pImg->GetBits();
	int pit = m_pImg->GetPitch();
	int oldpit = image->GetPitch();
	int bitCount = m_pImg->GetBPP()/8;
	int oldbitCount = image->GetBPP()/8;
	for(int cy = 0; cy < m_Height; cy++)
		for(int cx = 0; cx < m_Width; cx++)
		{
			*(pData + cy*pit + cx*bitCount) = *(oldpData + cy*oldpit + cx*oldbitCount);
		}
	delete image;
	image = NULL;
	//图像二值化,计算需要需要处理的图像
	int * m_hisArr;
	m_hisArr = new int[256];
	for(int i = 0; i < 256; i++)
	{
		m_hisArr[i] = 0;
	}
	m_myimageopreate->calhistogram(m_pImg, m_hisArr);
#if 0
	int otsuthreshold;
	otsuthreshold = m_myimageopreate->calotsuThreshold(m_hisArr);
	m_myimageopreate->ToBinary(image, otsuthreshold);
	image->Save("checkerboardbinary.bmp");
#endif

#if 1
	int entropythreshold;
	entropythreshold = m_myimageopreate->calentropyThreshold(m_hisArr);
	m_myimageopreate->ToBinary(m_pImg, entropythreshold);
	//image->Save("checkerboardbinary3.bmp");
#endif
	delete m_hisArr;
	m_hisArr = NULL;

	int * binarykernel;
	binarykernel  = m_mymorphology->binarykernel();
	m_mymorphology->binaryClosing(m_pImg, binarykernel);
	m_mymorphology->binaryOpening(m_pImg, binarykernel);
	//delete binarykernel;
	//======================================================
	m_pImg->SetColorTable(0, 256, colorTable);
	//OnShow(m_pImg);
	Queue * queue = NULL;
	queue = new Queue();
	queue->first = NULL;
	queue->last = NULL;
    image = new CImage();
	image->Create(m_Width, m_Height, 8);
	oldpData = (byte*)image->GetBits();
	oldpit = image->GetPitch();
	oldbitCount = image->GetBPP()/8;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			*(oldpData + oldpit*cy + oldbitCount*cx) = 0;
		}
	// 找到黑白的变化，我简单的需要两个循环
	for(int cy = 0; cy < m_Height; cy++)
	{
		int index = 0;
		int nwhitepoints = 0;
		int nblackpoints = 0;
		int pointx = 0;
		int pointy = 0;
		for(int cx = 0; cx < m_Width; cx++)
		{
			if(labelmap[cx + cy*m_Width] == INTEREST)
			{
				byte r = *(pData + cy*pit + cx*bitCount);
				if(r == 255)
				{
					nwhitepoints++;
					nblackpoints = 0;
					pointx = cx;
					pointy = cy;
				}
				else
				{
					nblackpoints++;
				}
				if((nblackpoints >= NBLACK)&&((nwhitepoints >= NWHITE)))
				{
					nwhitepoints = 0;
					//PushQueue(queue, pointx+pointy*m_Width);
					*(oldpData + oldpit*pointy + oldbitCount*pointx) = 255;
					//	OnShow(m_pImg);
					index++;
				}
			}
		}
	}
	// 2
	for(int cy = 0; cy < m_Height; cy++)
	{
		int index = 0;
		int nwhitepoints = 0;
		int nblackpoints = 0;
		int pointx = 0;
		int pointy = 0;
		for(int cx = 0; cx < m_Width; cx++)
		{
			if(labelmap[cx + cy*m_Width] == INTEREST)
			{
				byte r = *(pData + cy*pit + cx*bitCount);
				if(r == 255)
				{
					nwhitepoints++;
				}
				else
				{
					nblackpoints++;
					nwhitepoints = 0;
					pointx = cx;
					pointy = cy;
				}
				if((nblackpoints >= NBLACK)&&((nwhitepoints >= NWHITE)))
				{
					nblackpoints = 0;
					//PushQueue(queue, pointx+pointy*m_Width);
					*(oldpData + oldpit*pointy + oldbitCount*pointx) = 255;
					//	OnShow(m_pImg);
					index++;
				}
			}
		}
	}
	image->SetColorTable(0, 256, colorTable);
	//OnShow(image);
	//image->Save("2.bmp");
#if 1
	// ====================除噪过程，消除一些零碎点=============
	CImage * copyimage = new CImage();
	copyimage->Create(m_Width, m_Height, 8);
	pData = (byte*)copyimage->GetBits();
	pit = copyimage->GetPitch();
	bitCount = copyimage->GetBPP()/8;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			*(pData + cy*pit + cx*bitCount) = *(oldpData + cy*oldpit + cx*oldbitCount);
		}
	m_mymorphology->binaryDelete(copyimage, binarykernel);
//	OnShow(copyimage);
	delete binarykernel;
	//MessageBox("Next...");
	int allnums = 0;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			if((*(pData + cy*pit + cx*bitCount) == 255)&&(*(oldpData + cy*oldpit + cx*oldbitCount) == 255))
			{
				*(oldpData + cy*oldpit + cx*oldbitCount) = 255;
				allnums++;
			}
			else
				*(oldpData + cy*oldpit + cx*oldbitCount) = 0;
		}
	delete copyimage;
	copyimage = 0;
	//OnShow(image);
#endif
	//=====================================================================
	// ========================赋值过程===============================
#if 1
	int ** inputRealX = new int*[2];
	for(int i = 0; i < 2; i++)
		inputRealX[i] = new int[allnums];
	int ** tempX = new int*[2];
	for(int i = 0; i < 2; i++)
		tempX[i] = new int[allnums];

	int i = 0;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			if(*(oldpData + cy*oldpit + cx*oldbitCount) == 255)
			{
				inputRealX[0][i] = tempX[0][i] = cx;
				inputRealX[1][i] = tempX[1][i] = cy;
				fout << inputRealX[0][i] <<" ";
				i++;
			}
		}
#endif
//================================================================

// ====================分类过程，将点进行分类=====================
#if 0 // C-means 方法，结果不准确
	int Flag = 1;
	m_kmeans->InitData(inputRealX[0], allnums, 9);
	while(Flag)
	{
		m_kmeans->UpdateCluster();
		m_kmeans->UpdateCenter();
		if(m_kmeans->IsEqual(m_kmeans->Center,m_kmeans->CenterCopy))
			Flag = 0;
		else
			m_kmeans->CopyCenter();
	}
	int ** result;
	result = m_kmeans->ReturnData();
	int * Top;
	Top = m_kmeans->Top;
#endif
#if 1 // 使用ISOData算法，进行分类
	m_isodata->m_DataNum = allnums;
	int * yy = new int[allnums];
	for(int i = 0; i < allnums; i++)
		yy[i] = 0;
	m_isodata->OnGenerateData(inputRealX[0], yy);
	//预先初始化ISOdata的一些值
	m_isodata->m_ISO_c = 9; //预期类数
	m_isodata->m_ISO_Nc = 9; // 初始聚类中心个数
	m_isodata->m_ISO_l = 2; // 每次迭代可以合并的类的最多对数
	m_isodata->m_ISO_i = 400; // 允许的最多迭代次数
	m_isodata->m_ISO_theta_n = 20; // 每一类允许的最少模式数目
	m_isodata->m_ISO_theta_s =  0.4; // 类内各分量距离标准差的上限,标准差大于这个值就会分裂
	m_isodata->m_ISO_theta_d = 1; // 两类中心间最小距离的下限，小于这个值就会合并
	m_isodata->m_k_split = 0.5;  //类分裂时候计算新中心的系数
	m_isodata->OnIsodata();
	// 利用这里的C-means
//	m_isodata->m_ClusterCenterNum = 9;
	//m_isodata->OnCMean();
	vector<vector <CPoint> > ISOClass;
	ISOClass = m_isodata->ISOClass;
	//vector<vector <CPoint> > c_meanClass;
	//c_meanClass = m_isodata->c_meanClass;
	CImage * myimage = new CImage();
	myimage->Create(m_Width, m_Height, 24);
	byte *mypData = (byte*)myimage->GetBits();
	int mypit = myimage->GetPitch();
	int mybitCount = myimage->GetBPP()/8;
	//for( int i = 0; i < m_isodata->m_ISO_Nc; i++)
	//{
	//	for(int j = 0; j < ISOClass[i].size(); j++)
	//	{
	//		int x = ISOClass[i].at(j).x ;
	//		int y = ISOClass[i].at(j).y;
	//	//	*(mypData + y*mypit + x*mybitCount) = i*225/9;
	//	//	*(mypData + y*mypit + x*mybitCount+1) = 100;
	//	//	*(mypData + y*mypit + x*mybitCount+2) = i*i*i*225/729 ;
	//	}
	//	OnShow(myimage);
	//	MessageBox("next...");
	//}
	///*myimage->SetColorTable(0, 10, mycolorTable);*/
	//OnShow(myimage);
	//myimage->Save("5.bmp");


#endif
	//========================================================
	//=====================最小二乘估计直线过程===============
#if 1
	
//	double c[9][2];
	double *ey = new double[9];
	for(int i = 0; i < m_isodata->m_ISO_Nc; i++)
	{
		int * x = new int[ISOClass[i].size()];
		int * y = new int[ISOClass[i].size()];
		ey[i] = 0;
		for(int j = 0; j < ISOClass[i].size(); j++)
		{
			for(int fi = 0; fi < allnums; fi++)
				if(ISOClass[i].at(j).x == inputRealX[0][fi])
					{
						inputRealX[0][fi] = 0;
						x[j] = ISOClass[i].at(j).x;
						y[j] = inputRealX[1][fi];
						//ey[i] += x[j];
						*(mypData + y[j]*mypit + x[j]*mybitCount) = i*225/9;
						*(mypData + y[j]*mypit + x[j]*mybitCount+1) = 100;
			            *(mypData + y[j]*mypit + x[j]*mybitCount+2) = i*i*i*225/729 ;
						break;
					}
			 			//fout << linepoints[j].x << " "<< linepoints[j].y << endl; 
		}
		OnShow(myimage);
		MessageBox("next..");

	//	m_leastquadraticfiter->LeastQuadraticFiter(x, y, c[i], Top[i], 2);
	//	CString stmp;
	//	double pan;
	//	if(!::_isnan(atan(c[i][0]))) // NAN
	//	{
	//		pan = 180.0/PI*(atan(c[i][0]));
	//		if(pan < 0)
	//			pan = 180 + pan;
	//	}
	//	else
	//	{
	//		pan = 90.0;
	//		
	//	}
	//	ey[i] /= Top[i];
	//	c[i][1] = ey[i]; 
	//	c[i][0] = pan;
	//	/*stmp.Format("%f, %f", pan, c[i][1]);
	//	MessageBox(stmp);*/
	//	delete x, y;
	//	x = 0;
	//	y = 0;
	}
	//delete ey;
#endif
	//===================================================
	//====================计算斜率的均值，从而获得9条直线=======
#if 0
	// 这里直接利用斜率来带入方程，没有进行优化
	filename = path + "temp2.bmp";
	CImage * tempimage = new CImage();
	tempimage->Load(filename);
	CImage * resultImg = new CImage();
	resultImg->Create(m_Width, m_Height, 24);
	pData = (byte*)tempimage->GetBits();
	pit = tempimage->GetPitch();
	bitCount = tempimage->GetBPP()/8;

	byte * repData = (byte *)resultImg->GetBits();
	int repit = resultImg->GetPitch();
	int rebitCount = resultImg->GetBPP()/8;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{	
			*(repData + repit*cy + rebitCount*cx) = *(pData + pit*cy + bitCount*cx);
			*(repData + repit*cy + rebitCount*cx +1) = *(pData + pit*cy + bitCount*cx);
			*(repData + repit*cy + rebitCount*cx +2) = *(pData + pit*cy + bitCount*cx);
		}

	double ek = 0;
	for(int i = 0; i < 9; i++)
		ek += c[i][0] / 9;
	for(int cy = 0; cy < m_Height; cy++)
		for(int i = 0; i < 9; i++)
		{
			//int x = (cy-c[i][1]) / tan(ek*PI/180.0);
			//if((x < m_Width)&&(x > 0))
			int x = c[i][1];
			{
				*(repData + repit*cy + rebitCount*x) = 0;
				*(repData + repit*cy + rebitCount*x +1) = 255;
				*(repData + repit*cy + rebitCount*x +2) = 0;
			}
		}
	OnShow(resultImg);
	resultImg->Save("4.bmp");
#endif
	//出栈，对找到的点进行一个分类
	/*int m = m_Width / NWHITE;
	int n = m_Height / NWHITE;
	int * xClassifyIn = new int[m];
	int * yClassifyIn = new int[n];
	for(int i = 0; i < m; i++)
		xClassifyIn[i] = 0;
	for(int i = 0; i < n; i++)
		yClassifyIn[i] = 0;*/
	//int PopData = PopQueue(queue); 
	//// 对横坐标的点进行分类
	
	
	
		/*delete image;
	image = NULL;*/
	/*int Max = 0;
	for(int i = 0; i < m; i++)
		Max = (Max < xClassifyIn[i]) ? xClassifyIn[i] : Max;
	CImage * lineImg = new CImage();
	lineImg->Create(m+20, Max+10, 8);
	byte * linepData;
	linepData = (byte*)lineImg->GetBits();
	int linepit = lineImg->GetPitch();
	int linebitCount = lineImg->GetBPP()/8;
	int j = 0;
	for(int cx = 10; cx < m + 10; cx++)
	{
		for(int cy = 0; cy < xClassifyIn[j]; cy++)
		{
			*(linepData + (Max+5-cy)*linepit + cx*linebitCount) = 255;
		}
		j++;
	}
	lineImg->SetColorTable(0, 256, colorTable);
	OnShow(lineImg);
	lineImg->Save("line.bmp");*/
	// 对于捕获的64个分类的点，进行挑选，选择合适数目的分类
	//int num_x = 0;
	//for(int i = 0; i < m; i++)
	//	if(xClassifyIn[i] > 50)
	//		/*num_x++;*/
	//	{
	//		num_x = i; 
	//		for(int cx = NWHITE*(num_x); cx < NWHITE*(num_x+1) - 1; cx++)
	//			for(int cy = 0; cy < m_Height; cy++)
	//			{
	//				*(oldpData + oldpit*cy + oldbitCount*cx) = 0;
	//				*(oldpData + oldpit*cy + oldbitCount*cx +1) = 255;
	//				*(oldpData + oldpit*cy + oldbitCount*cy +2) = 0;
	//			}
	//		OnShow(image);
	//		CString xtmp;
	//		xtmp.Format("%d", num_x++);
	//		MessageBox(xtmp);
	//	}
	//	image->Save("error.bmp");
}
#endif

void CIMageProcessDlg::OnProcess4()
{
	ofstream fout("result.txt", ios::out|ios::in|ios::ate);
		
	CString path = "image\\";
	CString filename;
	filename = path + "temp2.bmp";
	CImage * image = new CImage();
	image->Load(filename);
	m_Width = image->GetWidth();
	m_Height = image->GetHeight();
	m_pImg = new CImage();
	m_pImg->Create(m_Width, m_Height, 8);

	//将图像都转换为8为索引图
	byte * inpData,* pData;
	inpData = (byte*)image->GetBits();
	pData = (byte *)m_pImg->GetBits();
	int pit = m_pImg->GetPitch();
	int inpit = image->GetPitch();
	int bitCount = m_pImg->GetBPP()/8;
	int inbitCount = image->GetBPP()/8;
	for(int cy = 0; cy < m_Height; cy++)
		for(int cx = 0; cx < m_Width; cx++)
		{
			*(pData + cy*pit + cx*bitCount) = *(inpData + cy*inpit + cx*inbitCount);
		}
	delete image;
	image = NULL;
	//图像二值化,计算需要需要处理的图像
	int * m_hisArr;
	m_hisArr = new int[256];
	for(int i = 0; i < 256; i++)
	{
		m_hisArr[i] = 0;
	}
	m_myimageopreate->calhistogram(m_pImg, m_hisArr);
#if 0
	int otsuthreshold;
	otsuthreshold = m_myimageopreate->calotsuThreshold(m_hisArr);
	m_myimageopreate->ToBinary(image, otsuthreshold);
	image->Save("checkerboardbinary.bmp");
#endif

#if 1
	int entropythreshold;
	entropythreshold = m_myimageopreate->calentropyThreshold(m_hisArr);
	m_myimageopreate->ToBinary(m_pImg, entropythreshold);
	//image->Save("checkerboardbinary3.bmp");
#endif
	delete m_hisArr;
	m_hisArr = NULL;

	int * binarykernel;
	binarykernel  = m_mymorphology->binarykernel();
	m_mymorphology->binaryClosing(m_pImg, binarykernel);
	m_mymorphology->binaryOpening(m_pImg, binarykernel);
	//delete binarykernel;
	//======================================================
	m_pImg->SetColorTable(0, 256, colorTable);
//	OnShow(m_pImg);

	CImage * Vimage = new CImage();
	Vimage->Create(m_Width, m_Height, 8);
	byte *vpData = (byte*)Vimage->GetBits();
	int vpit = Vimage->GetPitch();
	int vbitCount = Vimage->GetBPP()/8;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			*(vpData + vpit*cy + vbitCount*cx) = 0;
		}
	// 找到黑白的变化，我简单的需要两个循环
	for(int cy = 0; cy < m_Height; cy++)
	{
		int index = 0;
		int nwhitepoints = 0;
		int nblackpoints = 0;
		int pointx = 0;
		int pointy = 0;
		for(int cx = 0; cx < m_Width; cx++)
		{
			if(labelmap[cx + cy*m_Width] == INTEREST)
			{
				byte r = *(pData + cy*pit + cx*bitCount);
				if(r == 255)
				{
					nwhitepoints++;
					nblackpoints = 0;
					pointx = cx;
					pointy = cy;
				}
				else
				{
					nblackpoints++;
				}
				if((nblackpoints >= NBLACK)&&((nwhitepoints >= NWHITE)))
				{
					nwhitepoints = 0;
					//PushQueue(queue, pointx+pointy*m_Width);
					*(vpData + vpit*pointy + vbitCount*pointx) = 255;
					//	OnShow(m_pImg);
					index++;
				}
			}
		}
	}
	// 2
	for(int cy = 0; cy < m_Height; cy++)
	{
		int index = 0;
		int nwhitepoints = 0;
		int nblackpoints = 0;
		int pointx = 0;
		int pointy = 0;
		for(int cx = 0; cx < m_Width; cx++)
		{
			if(labelmap[cx + cy*m_Width] == INTEREST)
			{
				byte r = *(pData + cy*pit + cx*bitCount);
				if(r == 255)
				{
					nwhitepoints++;
				}
				else
				{
					nblackpoints++;
					nwhitepoints = 0;
					pointx = cx;
					pointy = cy;
				}
				if((nblackpoints >= NBLACK)&&((nwhitepoints >= NWHITE)))
				{
					nblackpoints = 0;
					//PushQueue(queue, pointx+pointy*m_Width);
					*(vpData + vpit*pointy + vbitCount*pointx) = 255;
					//	OnShow(m_pImg);
					index++;
				}
			}
		}
	}
	Vimage->SetColorTable(0, 256, colorTable);
	//OnShow(Vimage);
#if 1
	// ====================除噪过程，消除一些零碎点=============
	CImage * copyimage = new CImage();
	copyimage->Create(m_Width, m_Height, 8);
	byte *copData = (byte*)copyimage->GetBits();
	int copit = copyimage->GetPitch();
	int cobitCount = copyimage->GetBPP()/8;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			*(copData + cy*copit + cx*cobitCount) = *(vpData + cy*vpit + cx*vbitCount);
		}
	m_mymorphology->binaryDelete(copyimage, binarykernel);
//	OnShow(copyimage);
	//delete binarykernel;
	//MessageBox("Next...");
	int allnums = 0;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			if((*(copData + cy*copit + cx*cobitCount) == 255)&&(*(vpData + cy*vpit + cx*vbitCount) == 255))
			{
				*(vpData + cy*vpit + cx*vbitCount) = 255;
				allnums++;
			}
			else
				*(vpData + cy*vpit + cx*vbitCount) = 0;
		}
	delete copyimage;
	copyimage = 0;
	//OnShow(image);
	Vimage->Save("image\\V.bmp");
#endif
	// 水平方向的线
	CImage * Himage = new CImage();
	Himage->Create(m_Width, m_Height, 8);
	byte *hpData = (byte*)Himage->GetBits();
	int hpit = Himage->GetPitch();
	int hbitCount = Himage->GetBPP()/8;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			*(hpData + hpit*cy + hbitCount*cx) = 0;
		}
	// 找到黑白的变化，我简单的需要两个循环
	for(int cx = 0; cx < m_Width; cx++)
	{
		int index = 0;
		int nwhitepoints = 0;
		int nblackpoints = 0;
		int pointx = 0;
		int pointy = 0;
		for(int cy = 0; cy < m_Height; cy++)
		{
			if(labelmap[cx + cy*m_Width] == INTEREST)
			{
				byte r = *(pData + cy*pit + cx*bitCount);
				if(r == 255)
				{
					nwhitepoints++;
					nblackpoints = 0;
					pointx = cx;
					pointy = cy;
				}
				else
				{
					nblackpoints++;
				}
				if((nblackpoints >= NBLACK)&&((nwhitepoints >= NWHITE)))
				{
					nwhitepoints = 0;
					//PushQueue(queue, pointx+pointy*m_Width);
					*(hpData + hpit*pointy + hbitCount*pointx) = 255;
					//	OnShow(m_pImg);
					index++;
				}
			}
		}
	}
	// 2
	for(int cx = 0; cx < m_Width; cx++)
	{
		int index = 0;
		int nwhitepoints = 0;
		int nblackpoints = 0;
		int pointx = 0;
		int pointy = 0;
		for(int cy = 0; cy < m_Height; cy++)
		{
			if(labelmap[cx + cy*m_Width] == INTEREST)
			{
				byte r = *(pData + cy*pit + cx*bitCount);
				if(r == 255)
				{
					nwhitepoints++;
				}
				else
				{
					nblackpoints++;
					nwhitepoints = 0;
					pointx = cx;
					pointy = cy;
				}
				if((nblackpoints >= NBLACK)&&((nwhitepoints >= NWHITE)))
				{
					nblackpoints = 0;
					//PushQueue(queue, pointx+pointy*m_Width);
					*(hpData + hpit*pointy + hbitCount*pointx) = 255;
					//	OnShow(m_pImg);
					index++;
				}
			}
		}
	}
	/*Himage->SetColorTable(0, 256, colorTable);
	OnShow(Himage);*/
#if 1
	// ====================除噪过程，消除一些零碎点=============
	copyimage = new CImage();
	copyimage->Create(m_Width, m_Height, 8);
	pData = (byte*)copyimage->GetBits();
	pit = copyimage->GetPitch();
	bitCount = copyimage->GetBPP()/8;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			*(pData + cy*pit + cx*bitCount) = *(hpData + cy*hpit + cx*hbitCount);
		}
	m_mymorphology->binaryDelete(copyimage, binarykernel);
//	OnShow(copyimage);
	delete binarykernel;
	//MessageBox("Next...");
//	int allnums = 0;
	for(int cx = 0; cx < m_Width; cx++)
		for(int cy = 0; cy < m_Height; cy++)
		{
			if((*(pData + cy*pit + cx*bitCount) == 255)&&(*(hpData + cy*hpit + cx*hbitCount) == 255))
			{
				*(hpData + cy*hpit + cx*hbitCount) = 255;
				allnums++;
			}
			else
				*(hpData + cy*hpit + cx*hbitCount) = 0;
		}
	delete copyimage;
	copyimage = 0;
	//OnShow(image);
	Himage->SetColorTable(0, 256, colorTable);
	Himage->Save("image\\H.bmp");
#endif

}
/*==============================================================
函数:	
功能:   对上面找到的数据点进行一个分类,并且画线
参数:   垂直线

--------------------------------------------------------------*/

void CIMageProcessDlg::OnProcess5()
{
	// TODO: 在此添加控件通知处理程序代码
	ofstream fout1("result1.txt", ios::out|ios::in|ios::ate);

	CString path = "image\\";
	CString filename;
	filename = path + "V.bmp";
	CImage * inImg = new CImage();
	inImg->Load(filename);
	OnShow(inImg);
	int width = inImg->GetWidth();
	int height = inImg->GetHeight();
	CImage * TpImg = new CImage();
	TpImg->Create(width, height, 8);

	byte * inPdata, * tpPdata;
	inPdata = (byte*)inImg->GetBits();
	tpPdata = (byte*)TpImg->GetBits();
	int inpit = inImg->GetPitch();
	int tppit = TpImg->GetPitch();
	int inbit = inImg->GetBPP()/8;
	int tpbit = TpImg->GetBPP()/8;
	// step 1. 找到最长一条直线
#if 1
	unsigned char * bitmap = new unsigned char[width * height];
	byte r;
    int * tplabelmap = new int[width * height];
	int m_allnums = 0; // 找到所有的点的个数
	for(int cx = 0; cx < width; cx++)
		for(int cy = 0; cy < height; cy++)
		{
			r = *(inPdata + inpit*cy + inbit*cx);
			*(tpPdata + tppit*cy + tpbit*cx) = r;
			bitmap[cx + cy*width] = r;
			tplabelmap[cx + cy*width] =0;	
			if(r == 255)
				m_allnums++;
		}
	int m_labelIndex = m_pConnectComponentLabel->ConnectedComponentLabeling(bitmap, width, height, tplabelmap);
	int max, temp, maxIndex;
	max  = 0;
	maxIndex = 1;
	for(int j = 1; j <= m_labelIndex; j++)
	{
		temp = 0;
		for(int i = 0; i < width * height; i++)
		{
			if(tplabelmap[i] == j)
				temp++;
		}
		if(max < temp)
		{
			max = temp;
			maxIndex = j;
		}
		
	}
	int initLinenum = 0;
	for(int i = 0; i < width * height; i++)
	{
		if(tplabelmap[i] == maxIndex)
		{
			tplabelmap[i] = INTEREST;
		//	*(tpPdata + tppit*(i/width) + tpbit*(i%width)) = 255;
			initLinenum++;
		}
		else
		{
			tplabelmap[i] = 0;
		//	*(tpPdata + (i/width)*tppit + (i%width)*tpbit) = 0;
		}
	}

//	TpImg->SetColorTable(0, 256, colorTable);
//	OnShow(TpImg);
	int * initx, * inity ;
	//double * coff;
	initx = new int[initLinenum];
	inity = new int[initLinenum];
	//coff = new double[2];
	//coff[0] = coff[1] = 0;
	double coff[2];
	for(int i = 0,  m = 0; i < width * height; i++)
	{
		if(tplabelmap[i] == INTEREST)
		{
			initx[m] = i%width;
			inity[m] = i/width;
			fout1 << initx[m] <<" " << inity[m] <<endl;
			m++;
		}
	}
	m_leastquadraticfiter->LeastQuadraticFiter(initx, inity, coff, initLinenum, 2);
	CString stmp;
	double pan;
	if(!::_isnan(atan(coff[1]))) // NAN coff[1] ==k
	{
		pan = 180.0/PI*(atan(coff[1]));
		if(pan < 0)
			pan = 180 + pan;
	}
	else
	{
		pan = 90.0;
			
	}
	
//	stmp.Format("%f, %f", coff[1], coff[0]);
//	MessageBox(stmp);
	delete bitmap, inImg ,tplabelmap,initx, inity;
	inImg = NULL; bitmap = NULL; tplabelmap = NULL; 
	initx = NULL; inity = NULL;
#endif
	// 以该直线的斜率作为输入，来对点进行分类， >>pan=====
#if 1
	int * inx, * iny;
	inx = new int[m_allnums];
	iny = new int[m_allnums];
	int i = 0;
	for(int cx = 0; cx < width; cx++)
		for(int cy = 0; cy < height; cy++)
		{
			r = *(tpPdata + tppit*cy + tpbit*cx);	
			if(r == 255)
			{
				inx[i] = cx;
				iny[i] = cy;
				i++;
			}
		}
    m_myslopecluster->m_DataNum = m_allnums;
	m_myslopecluster->m_ClusterNum = 9;
	m_myslopecluster->m_initSlope = pan;
	m_myslopecluster->OnGenerateData(inx, iny);

	int indexx = 0;
	int maxnums, indexcy;
	maxnums = 0; 
	for(int cy = 0; cy < height; cy++)
	{
		int nums = 0;
		for(int cx = 0; cx < width; cx++)
		{
			
			r = *(tpPdata + tppit*cy + tpbit*cx);	
			if(r == 255)
			{
				nums++;;
			}
		}
		if(maxnums < nums)
		{
			indexcy = cy;
			maxnums = nums;
		}
	}
	int * x0, * y0;
	x0 = new int[maxnums];
	y0 = new int[maxnums];
	i = 0;
	for(int cx = 0; cx < width; cx++)
	{
		r = *(tpPdata + tppit*indexcy + tpbit*cx);	
		if(r == 255)
		{
			x0[i] = cx;
			y0[i] = indexcy;
			i++;
		}
	}
	m_myslopecluster->m_ClusterNum = maxnums;
	m_myslopecluster->OnSlope(x0, y0, true);
	delete x0, y0, inx, iny;
	x0 = 0; y0 = 0;
	inx = 0; iny = 0;
	vector<vector <CPoint> > sclopeClass;
	sclopeClass = m_myslopecluster->SlopeClass;
	CImage * myimage = new CImage();
	myimage->Create(width, height, 24);
	byte *mypData = (byte*)myimage->GetBits();
	int mypit = myimage->GetPitch();
	int mybitCount = myimage->GetBPP()/8;
	
	for(int i = 0; i < maxnums; i++)
	{		
		for(int j = 0; j < sclopeClass[i].size(); j++)
		{
			int x = sclopeClass[i].at(j).x ;
			int y = sclopeClass[i].at(j).y;

			*(mypData + y*mypit + x*mybitCount) = i*225/9;
			*(mypData + y*mypit + x*mybitCount+1) = 100;
			*(mypData + y*mypit + x*mybitCount+2) = i*i*i*225/729 ;		
		}
		OnShow(myimage);
		MessageBox("next..");
	}
	//OnShow(myimage);
	//myimage->Save("6.bmp");
	/*delete myimage;
	myimage = NULL;*/
#endif
	//对点完成分类之后，分别计算这几条直线的斜率
#if 1
	double ** allcoff;
	allcoff = new double*[maxnums];
	for(int i = 0; i < maxnums; i++)
		allcoff[i] = new double[2];
	double meank = 0;
	vector<CPoint> meanpoints;
	if(!meanpoints.empty())
		meanpoints.clear();
	for(int i = 0; i < maxnums; i++)
	{	
		int *x, *y;
		CPoint meanpoint;
		meanpoint.x = meanpoint.y = 0;
		x = new int[sclopeClass[i].size()];
		y = new int[sclopeClass[i].size()];
		
		for(int j = 0; j < sclopeClass[i].size(); j++)
		{
			int tempx = sclopeClass[i].at(j).x;
			int tempy = sclopeClass[i].at(j).y;
			x[j] = tempx;
			y[j] = tempy;
			meanpoint.x += tempx ;
			meanpoint.y += tempy ;
		}
		meanpoint.x /= sclopeClass[i].size();
		meanpoint.y /= sclopeClass[i].size();
		meanpoints.push_back(meanpoint);
		m_leastquadraticfiter->LeastQuadraticFiter(x, y, allcoff[i], sclopeClass[i].size(), 2);
		delete x, y;
		x = NULL; y = NULL;
		//CString stmp;
		double pan;
		if(!::_isnan(atan(allcoff[i][1]))) // NAN
		{
			pan = 180.0/PI*(atan(allcoff[i][1]));
			if(pan < 0)
				pan = 180 + pan;
		}
		else
		{
			pan = 90.0;
			
		}
		//allcoff[i][0] = pan;
	//	meank += pan / maxnums;
		//stmp.Format("%f, %f",allcoff[i][0] , allcoff[i][1]);
		
		//MessageBox(stmp);
	}
	for(int cy = 0; cy < height; cy++)
	{
		for(int i = 0; i < maxnums; i++)
		{
			double x = (cy - meanpoints.at(i).y) / allcoff[i][1] + meanpoints.at(i).x;
//			double x = (cy + allcoff[i][1]) / (tan(PI*allcoff[i][0]/180.0));
		//	double x = (cy - allcoff[i][0]) / allcoff[i][1]; // y = kx + b; k = allcoff[i][1], b = allcoff[i][0] 不知道为什么这里会出错
			if((x >=0)&&(x <= width))
			{
				*(mypData + cy*mypit + int(x)*mybitCount) = 0;
				*(mypData + cy*mypit + int(x)*mybitCount+1) = 255;
				*(mypData + cy*mypit + int(x)*mybitCount+2) = 0 ;
			}
		}
	}
	for(int i = 0; i < maxnums; i++)
		delete []allcoff[i];
	delete []allcoff;
	OnShow(myimage);
	myimage->Save("7.bmp");
#endif
}

/*==============================================================
函数:	
功能:   对上面找到的数据点进行一个分类,并且画线
参数:   水平线

--------------------------------------------------------------*/

void CIMageProcessDlg::OnProcess7()
{
	// TODO: 在此添加控件通知处理程序代码
	ofstream fout1("result1.txt", ios::out|ios::in|ios::ate);
	CString path = "image\\";
	CString filename;
	filename = path + "H.bmp";
	CImage * inImg = new CImage();
	inImg->Load(filename);
	//OnShow(inImg);
	int width = inImg->GetWidth();
	int height = inImg->GetHeight();
	CImage * TpImg = new CImage();
	TpImg->Create(width, height, 8);

	byte * inPdata, * tpPdata;
	inPdata = (byte*)inImg->GetBits();
	tpPdata = (byte*)TpImg->GetBits();
	int inpit = inImg->GetPitch();
	int tppit = TpImg->GetPitch();
	int inbit = inImg->GetBPP()/8;
	int tpbit = TpImg->GetBPP()/8;

	// step 1. 找到最长一条直线
#if 1
	unsigned char * bitmap = new unsigned char[width * height];
	byte r;
    int * tplabelmap = new int[width * height];
	int m_allnums = 0; // 找到所有的点的个数
	for(int cx = 0; cx < width; cx++)
		for(int cy = 0; cy < height; cy++)
		{
			r = *(inPdata + inpit*cy + inbit*cx);
			*(tpPdata + tppit*cy + tpbit*cx) = r;
			bitmap[cx + cy*width] = r;
			tplabelmap[cx + cy*width] =0;	
			if(r == 255)
				m_allnums++;
		}
	int m_labelIndex = m_pConnectComponentLabel->ConnectedComponentLabeling(bitmap, width, height, tplabelmap);
	int max, temp, maxIndex;
	max  = 0;
	maxIndex = 1;
	for(int j = 1; j <= m_labelIndex; j++)
	{
		temp = 0;
		for(int i = 0; i < width * height; i++)
		{
			if(tplabelmap[i] == j)
				temp++;
		}
		if(max < temp)
		{
			max = temp;
			maxIndex = j;
		}
		
	}
	int initLinenum = 0;
	for(int i = 0; i < width * height; i++)
	{
		if(tplabelmap[i] == maxIndex)
		{
			tplabelmap[i] = INTEREST;
		//	*(tpPdata + tppit*(i/width) + tpbit*(i%width)) = 255;
			initLinenum++;
		}
		else
		{
			tplabelmap[i] = 0;
		//	*(tpPdata + (i/width)*tppit + (i%width)*tpbit) = 0;
		}
	}

	//TpImg->SetColorTable(0, 256, colorTable);
	//OnShow(TpImg);
	int * initx, * inity ;
	//double * coff;
	initx = new int[initLinenum];
	inity = new int[initLinenum];
	//coff = new double[2];
	//coff[0] = coff[1] = 0;
	double coff[2];
	for(int i = 0,  m = 0; i < width * height; i++)
	{
		if(tplabelmap[i] == INTEREST)
		{
			initx[m] = i%width;
			inity[m] = i/width;
			m++;
		}
	}
	m_leastquadraticfiter->LeastQuadraticFiter(initx, inity, coff, initLinenum, 2);
	CString stmp;
	double pan;
	if(!::_isnan(atan(coff[1]))) // NAN
	{
		pan = 180.0/PI*(atan(coff[1]));
		if(pan < 0)
			pan = 180 + pan;
	}
	else
	{
		pan = 90.0;
			
	}
	
	//stmp.Format("%f, %f", coff[1], coff[0]);
	//MessageBox(stmp);
	delete bitmap, inImg ,tplabelmap,initx, inity;
	inImg = NULL; bitmap = NULL; tplabelmap = NULL; 
	initx = NULL; inity = NULL;
#endif
		// 以该直线的斜率作为输入，来对点进行分类， >>pan=====
#if 1
	int * inx, * iny;
	inx = new int[m_allnums];
	iny = new int[m_allnums];
	int i = 0;
	//TpImg->SetColorTable(0, 256, colorTable);
	//OnShow(TpImg);
	for(int cy = 0; cy < height; cy++)
		for(int cx = 0; cx < width; cx++)
		{
			r = *(tpPdata + tppit*cy + tpbit*cx);	
			if(r == 255)
			{
				inx[i] = cx;
				iny[i] = cy;
				i++;
			}
		}
    m_myslopecluster->m_DataNum = m_allnums;
	m_myslopecluster->m_ClusterNum = 8;
	m_myslopecluster->m_initSlope = -0.13063144517504857;
	m_myslopecluster->OnGenerateData(inx, iny);

	int indecy = 0;
	int maxnums, indexcx;
	maxnums = 0; 
	for(int cx = 0; cx < width; cx++)
	{
		int nums = 0;
		for(int cy = 0; cy < height; cy++)
		{
			
			r = *(tpPdata + tppit*cy + tpbit*cx);	
			if(r == 255)
			{
				nums++;
			}
		}
		if(maxnums < nums)
		{
			indexcx = cx;
			maxnums = nums;
		}
	}
	int * x0, * y0;
	x0 = new int[maxnums];
	y0 = new int[maxnums];
	i = 0;
	for(int cy = 0; cy < height; cy++)
	{
		r = *(tpPdata + tppit*cy + tpbit*indexcx);	
		if(r == 255)
		{
			x0[i] = indexcx;
			y0[i] = cy;
			i++;
		}
	}
	m_myslopecluster->m_ClusterNum = maxnums;
	m_myslopecluster->OnSlope(x0, y0, false);
//	m_myslopecluster->OnSlope(x0, y0, false);
	delete x0, y0, inx, iny;
	x0 = 0; y0 = 0;
	inx = 0; iny = 0;
	vector<vector <CPoint> > sclopeClass;
	sclopeClass = m_myslopecluster->SlopeClass;
	CImage * myimage = new CImage();
	myimage->Create(width, height, 24);
	byte *mypData = (byte*)myimage->GetBits();
	int mypit = myimage->GetPitch();
	int mybitCount = myimage->GetBPP()/8;
	
	for(int i = 0; i < maxnums; i++)
	{		
		for(int j = 0; j < sclopeClass[i].size(); j++)
		{
			int x = sclopeClass[i].at(j).x ;
			int y = sclopeClass[i].at(j).y;

			*(mypData + y*mypit + x*mybitCount) = i*225/9;
			*(mypData + y*mypit + x*mybitCount+1) = 100;
			*(mypData + y*mypit + x*mybitCount+2) = i*i*i*225/729 ;		
		}
		OnShow(myimage);
		MessageBox("next..");
		}
	//OnShow(myimage);
	//myimage->Save("6.bmp");
	/*delete myimage;
	myimage = NULL;*/
#endif
	//对点完成分类之后，分别计算这几条直线的斜率
#if 1
	double ** allcoff;
	allcoff = new double*[maxnums];
	for(int i = 0; i < maxnums; i++)
		allcoff[i] = new double[2];
	double meank = 0;
	vector<CPoint> meanpoints;
	if(!meanpoints.empty())
		meanpoints.clear();
	for(int i = 0; i < maxnums; i++)
	{	
		int *x, *y;
		CPoint meanpoint;
		meanpoint.x = meanpoint.y = 0;
		x = new int[sclopeClass[i].size()];
		y = new int[sclopeClass[i].size()];
		
		for(int j = 0; j < sclopeClass[i].size(); j++)
		{
			int tempx = sclopeClass[i].at(j).x;
			int tempy = sclopeClass[i].at(j).y;
			x[j] = tempx;
			y[j] = tempy;
			meanpoint.x += tempx ;
			meanpoint.y += tempy ;
			fout1 << tempx <<" " << tempy <<endl;
		}
		fout1 << endl;
		meanpoint.x /= sclopeClass[i].size();
		meanpoint.y /= sclopeClass[i].size();
		meanpoints.push_back(meanpoint);
		m_leastquadraticfiter->LeastQuadraticFiter(x, y, allcoff[i], sclopeClass[i].size(), 2);
		delete x, y;
		x = NULL; y = NULL;
		//CString stmp;
		double pan;
		if(!::_isnan(atan(allcoff[i][1]))) // NAN
		{
			pan = 180.0/PI*(atan(allcoff[i][1]));
			if(pan < 0)
				pan = 180 + pan;
		}
		else
		{
			pan = 90.0;
			
		}
		meank += allcoff[i][1] / maxnums;
		//stmp.Format("%f, %f",allcoff[i][0] , allcoff[i][1]);
		
		//MessageBox(stmp);
	}
	double fad = meank; 
	for(int cx = 0; cx < width; cx++)
	{
		for(int i = 0; i < maxnums; i++)
		{
			double y = meanpoints.at(i).y + allcoff[i][1]*(cx - meanpoints.at(i).x);
//			double x = (cy + allcoff[i][1]) / (tan(PI*allcoff[i][0]/180.0));
		//	double x = (cy - allcoff[i][0]) / allcoff[i][1]; // y = kx + b; k = allcoff[i][1], b = allcoff[i][0] 不知道为什么这里会出错
			if((y >=0)&&(y <= height))
			{
				*(mypData + int(y)*mypit + int(cx)*mybitCount) = 0;
				*(mypData + int(y)*mypit + int(cx)*mybitCount+1) = 255;
				*(mypData + int(y)*mypit + int(cx)*mybitCount+2) = 0 ;
			}
		}
	}
	OnShow(myimage);
	myimage->Save("8.bmp");
#endif
}
