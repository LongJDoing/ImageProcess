
// ImageCalculateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageCalculate.h"
#include "ImageCalculateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CImageCalculateDlg 对话框




CImageCalculateDlg::CImageCalculateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageCalculateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pConnectComponentLabel = new CConnectComponentLabel();
	m_pCalculate = new CCalculate();
	
	
	m_labelIndex = 0;
	m_MaxArea = 0;
	m_MaxlabelIndex = 0;
	b_input = FALSE;
	b_input2 = FALSE;
//	m_pImage = NULL;
}

void CImageCalculateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageCalculateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INPUT, &CImageCalculateDlg::OnInput)
	ON_BN_CLICKED(IDC_LABEL, &CImageCalculateDlg::OndLabel)
	ON_BN_CLICKED(IDC_MEAN, &CImageCalculateDlg::OnMean)
	ON_BN_CLICKED(IDC_Area, &CImageCalculateDlg::OnArea)
	ON_BN_CLICKED(IDC_VARIANCE, &CImageCalculateDlg::OnVariance)
END_MESSAGE_MAP()


// CImageCalculateDlg 消息处理程序

BOOL CImageCalculateDlg::OnInitDialog()
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

void CImageCalculateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CImageCalculateDlg::OnPaint()
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
HCURSOR CImageCalculateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageCalculateDlg::OnInput()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_labelIndex == 0)
		{MessageBox(_T("Input QualityMap_1"));	b_input = TRUE;}
	else
		{b_input2 = TRUE;}
	CString strFilter;
	CSimpleArray<GUID>aguidFileTypes;
	HRESULT hResult;
	m_pImage = new CImage();
	hResult = m_pImage->GetExporterFilterString(strFilter,aguidFileTypes,_T("All image Files"));

	strFilter =_T("JPEG (*.jpg)|*.jpg|BMP (*.bmp)|*.bmp|GIF (*.gif)|*.gif|PNG (*.png)|*.png||");
	if(FAILED(hResult))
	{
		MessageBox(_T("Failed！"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);//多选模式
	if(dlg.DoModal()!=IDOK)     //判断是否获得图片
	{ 
		return;
	}
	CString m_path = dlg.GetPathName();
	if(m_path=="")   //判断图片路径是否存在
	{
		return;
	}
	
	hResult = m_pImage->Load(m_path);   //将外部图像文件装载到CImage对象中
	if(FAILED(hResult))
	{
		MessageBox(_T("Failed"));
		return;
	}
	OnShow(m_pImage);
	return;
}

void CImageCalculateDlg::OnShow(CImage *Image)
{
	CRect rect;
	CRect rectSrc;
	//选择需要显示的图像
	if(!Image->IsNull())	
	{
		int cx = Image->GetWidth();
		int cy = Image->GetHeight();

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

//==================利用质量图1产生掩膜图，用来做标记========================

void CImageCalculateDlg::OndLabel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!b_input)
	{   
		MessageBox(_T("Failed:Complete the Prior Step!"));
		return;
	}
	int m_Width = m_pImage->GetWidth() - 10;
	int m_Height = m_pImage->GetHeight() - 10;
	
	COLORREF m_Pixel;
	byte r;
	unsigned char * bitmap = new unsigned char[m_Width * m_Height];
    labelmap = new int[m_Width * m_Height];
	for(int i = 0; i < m_Width * m_Height; i++)
	{
		bitmap[i] = 0;
		labelmap[i] = 0;
	}
	for(int cy = 5; cy < m_Height ; cy++)
		for(int cx = 5; cx < m_Width ; cx++)
		{
			m_Pixel = m_pImage->GetPixel(cx, cy);
			r = GetRValue(m_Pixel);
			if(r < 125)
				r = 0;
			else
				r = 255;
			bitmap[cx + cy * m_Width] = r;
		}

	m_labelIndex = m_pConnectComponentLabel->ConnectedComponentLabeling(bitmap, m_Width, m_Height, labelmap);

	//**************************测试图片效果程序***************************

	/*CImage *tempImage = new CImage();
	tempImage->Create(m_Width, m_Height, 24);
	CString stmp;
	stmp.Format("%d", m_labelIndex);
	MessageBox(stmp);

	for(int i = 0; i < m_Width * m_Height; i++)
	{
		switch(labelmap[i])
		{
		case 0:
			tempImage->SetPixelRGB(i%m_Width, i/m_Width, 0, 0, 0);
			break;
		case 1:
			tempImage->SetPixelRGB(i%m_Width, i/m_Width, 255, 0, 0);
			break;
		case 2:
		    tempImage->SetPixelRGB(i%m_Width, i/m_Width, 0, 255, 0);
			break;
		case 3:
			tempImage->SetPixelRGB(i%m_Width, i/m_Width, 0, 0, 255);
			break;
		default:
			tempImage->SetPixelRGB(i%m_Width, i/m_Width, 100, 50, 0);
			break;
		}
	}
	OnShow(tempImage);*/
	
	//*********************************************************************************
}

void CImageCalculateDlg::OnArea()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!b_input||m_labelIndex==0)
	{   
		MessageBox(_T("Failed:Complete the Prior Step!"));
		return;
	}
	int m_Width = m_pImage->GetWidth() - 10;
	int m_Height = m_pImage->GetHeight() - 10;
	int *m_area = new int[m_labelIndex];
	for(int i = 0; i < m_labelIndex; i++)
		m_area[i] = 0;
	for(int j = 0; j < m_labelIndex; j++)
	{
		m_area[j] = m_pCalculate->CalculateArea(labelmap, m_Width, m_Height, j+1);
	}
	m_MaxArea = 0;
	for(int i = 0; i < m_labelIndex; i++)
		if(m_MaxArea < m_area[i])
		{
			m_MaxArea = m_area[i];
			m_MaxlabelIndex = i+1;
		}
// *************************************测试程序*********************************
	CString stmp;
	stmp.Format("%d", m_MaxArea);
	MessageBox(stmp);
	CImage *TemplateImage = new CImage();
	TemplateImage->Create(m_Width, m_Height, 24);
	for(int i = 0; i < m_Width * m_Height; i++)
	{
		if(m_MaxlabelIndex == labelmap[i])
		{
			TemplateImage->SetPixelRGB(i%m_Width, i/m_Width, 255, 0, 0);
		}
	}

	OnShow(TemplateImage);
//*****************************************************************************
	delete m_area;
}

//利用质量图1的结果求出质量图2的均值和方差
void CImageCalculateDlg::OnMean()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!b_input||m_labelIndex==0)
	{   
		MessageBox(_T("Failed:Complete the Prior Step!"));
		return;
	}
	if(!b_input2)
	{
		MessageBox(_T("Input QualityMap_2"));
		return;
	}
	int m_Width = m_pImage->GetWidth() - 10;
	int m_Height = m_pImage->GetHeight() - 10;
	
	COLORREF m_Pixel;
	byte r;
	unsigned char * bitmap = new unsigned char[m_Width * m_Height];

	for(int i = 0; i < m_Width * m_Height; i++)
	{
		bitmap[i] = 0;
	}
	for(int cy = 5; cy < m_Height ; cy++)
		for(int cx = 5; cx < m_Width ; cx++)
		{
			m_Pixel = m_pImage->GetPixel(cx, cy);
			r = GetRValue(m_Pixel);
			if(r < 125)
				r = 0;
			else
				r = 255;
			bitmap[cx + cy * m_Width] = r;
		}
	double m_Mean = m_pCalculate->CalculateMean(bitmap, labelmap, m_Width, m_Height, m_MaxArea, m_MaxlabelIndex);
	CString stmp;
	stmp.Format("%f", m_Mean);
	MessageBox(stmp);

}

void CImageCalculateDlg::OnVariance()
{
	// TODO: 在此添加控件通知处理程序代码
	int m_Width = m_pImage->GetWidth() - 10;
	int m_Height = m_pImage->GetHeight() - 10;
	
	COLORREF m_Pixel;
	byte r;
	unsigned char * bitmap = new unsigned char[m_Width * m_Height];

	for(int i = 0; i < m_Width * m_Height; i++)
	{
		bitmap[i] = 0;
	}
	for(int cy = 5; cy < m_Height ; cy++)
		for(int cx = 5; cx < m_Width ; cx++)
		{
			m_Pixel = m_pImage->GetPixel(cx, cy);
			r = GetRValue(m_Pixel);
			if(r < 125)
				r = 0;
			else
				r = 255;
			bitmap[cx + cy * m_Width] = r;
		}
		
	double m_Variance = m_pCalculate->CalculateVariance(bitmap, labelmap, m_Width, m_Height, m_MaxArea, m_MaxlabelIndex);
	CString stmp;
	stmp.Format("%f", m_Variance);
	MessageBox(stmp);
}
