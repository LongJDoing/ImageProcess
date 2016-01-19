
// ImageCalculateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageCalculate.h"
#include "ImageCalculateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CImageCalculateDlg �Ի���




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


// CImageCalculateDlg ��Ϣ�������

BOOL CImageCalculateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CImageCalculateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CImageCalculateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageCalculateDlg::OnInput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("Failed��"));
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);//��ѡģʽ
	if(dlg.DoModal()!=IDOK)     //�ж��Ƿ���ͼƬ
	{ 
		return;
	}
	CString m_path = dlg.GetPathName();
	if(m_path=="")   //�ж�ͼƬ·���Ƿ����
	{
		return;
	}
	
	hResult = m_pImage->Load(m_path);   //���ⲿͼ���ļ�װ�ص�CImage������
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
	//ѡ����Ҫ��ʾ��ͼ��
	if(!Image->IsNull())	
	{
		int cx = Image->GetWidth();
		int cy = Image->GetHeight();

		CWnd *pWnd=GetDlgItem(IDC_PICTURE);//���pictrue�ؼ����ڵľ��  
			
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rectSrc = CRect(CPoint(0, 0), CPoint(cx, cy));
		pWnd->MoveWindow(rect, TRUE);//�������ƶ���Picture�ؼ���ʾ�ľ�������  					
		pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ������� 

		CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC  
		Image->Draw(pDC->m_hDC, rect, rectSrc); //��ͼƬ����Picture�ؼ���ʾ�ľ������� 

		ReleaseDC(pDC);//�ͷ�picture�ؼ���DC  
	}
	
	return;
}

//==================��������ͼ1������Ĥͼ�����������========================

void CImageCalculateDlg::OndLabel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	//**************************����ͼƬЧ������***************************

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
// *************************************���Գ���*********************************
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

//��������ͼ1�Ľ���������ͼ2�ľ�ֵ�ͷ���
void CImageCalculateDlg::OnMean()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
