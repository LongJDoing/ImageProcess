
// DicomReadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DicomRead.h"
#include "DicomReadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#pragma comment( lib, "wsock32.lib" )
#pragma comment( lib, "odbc32.lib" )
#pragma comment( lib, "odbccp32.lib" )

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


// CDicomReadDlg 对话框




CDicomReadDlg::CDicomReadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDicomReadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_page1 = new CPage1();
	m_page2 = new CPage2();

	m_pPDU			= NULL;
	m_pDICOMData			= NULL;
	m_pImage = NULL;

	m_nWindowCenter = 0;
	m_nWindowWidth =0;
	m_szPhotoMetric = "";

	m_pStoreData = NULL;
	m_pData = NULL;

	m_bFlag = TRUE;

	m_path = "";
}

void CDicomReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABMAIN, m_tabMain); // tab 
}

BEGIN_MESSAGE_MAP(CDicomReadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABMAIN, &CDicomReadDlg::OnTcnSelchangeTabmain)
	ON_COMMAND(ID_FILE_OPEN, &CDicomReadDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CDicomReadDlg::OnFileSave)
	ON_COMMAND(ID_FILE_DUMP, &CDicomReadDlg::OnFileDump)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()


// CDicomReadDlg 消息处理程序

BOOL CDicomReadDlg::OnInitDialog()
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

	 //添加选项卡
	 m_tabMain.InsertItem(0,_T("Information"));//“ ”可更改，是sheet页的名字；

	 //关联对话框,并且将IDC_TABMAIN控件设为父窗口
	// m_page1->Create(IDD_DIALOG1, GetDlgItem(IDC_TABMAIN));
	 	 //创建页面  
	m_page1->Create(IDD_DIALOG1,&m_tabMain);  
	m_page2->Create(IDD_DIALOG2,&m_tabMain);  
	 //获得IDC_tabMain客户区大小
	 CRect rs;
	 m_tabMain.GetClientRect(&rs);



	 //调整子对话框在父窗口中的位置，可以改动数值，使子窗体的大小合适；
	 rs.top += 20;
	 rs.bottom -= 5;
	 rs.left += 5;
	 rs.right -= 5;

	 //设置子对话框尺寸并移动到指定位置
	 m_page1->MoveWindow(&rs);
	 m_page2->MoveWindow(&rs);

	  //分别设置隐藏和显示
	 m_page1->ShowWindow(true);
	 m_page2->ShowWindow(false);

	 //设置默认的选项卡
	m_tabMain.SetCurSel(0);

	m_pDC =GetDlgItem(IDC_STATIC)->GetWindowDC(); // 得picture控件pdc
	GetDlgItem(IDC_STATIC)->GetClientRect(&m_rect); // 得picture控件的大小
	

	m_menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_menu);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDicomReadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDicomReadDlg::OnPaint()
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
HCURSOR CDicomReadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDicomReadDlg::OnTcnSelchangeTabmain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int CurSel = m_tabMain.GetCurSel();
	 switch(CurSel)
	 {
	 case 0:
		  m_page1->ShowWindow(true);
		  m_page2->ShowWindow(false);
		  break;
	 case 1:
		  m_page1->ShowWindow(false);
		  m_page2->ShowWindow(true);
		  break;
	 default:;
	 } 
	*pResult = 0;
}


void CDicomReadDlg::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	
	CString strFilter;
	CSimpleArray<GUID>aguidFileTypes;
	HRESULT hResult;
	////获取CImage支持的图像的文件的过滤字符串

	m_pImage = new CImage();

	hResult = m_pImage->GetExporterFilterString(strFilter,aguidFileTypes,_T("All image Files"));

	strFilter = "DICOM图像文件|*.dcm|位图文件|*.bmp|JPEG图像文件|*.jpg|\GIF图像文件|*.gif|PNG图像文件|*.png|";


	if(FAILED(hResult))
	{
		MessageBox(_T("Failed！"));
		return;
	}
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);

	m_spRtc = new RTC(TRUE,"dicom-dict.txt");

	if(dlg.DoModal()!=IDOK)     //判断是否获得图片
	{ 
		return;
	}

	m_path = dlg.GetPathName(); //获得图片路径

	if(m_path=="")        //判断图片路径是否存在
	{
		return;
	}

	
	m_Ext = dlg.GetFileExt();

	char *sz;
	sz= m_path.GetBuffer(0);

	if (m_Ext == _T("dcm"))
	{
		if(m_pPDU == NULL)
			m_pPDU = new PDU_Service;
		m_pDICOMData = m_pPDU->LoadDICOMDataObject((m_path.GetBuffer(0)));
	   Initialization();
	   ShowImage();
	   m_page1->ShowDicomInfo(sz);
	} 
	else
	{
		m_pImage->Destroy();
		hResult = m_pImage->Load(m_path);   //将外部图像文件装载到CImage对象中
		if(FAILED(hResult))
		{
			MessageBox(_T("Failed"));
			return;
		}

		if(m_pImage)
		{
			m_pImage->Draw(m_pDC->m_hDC,m_rect);
		}
	}
}

void CDicomReadDlg::OnFileDump()
{
	// TODO: 在此添加命令处理程序代码
	dump();
}

// 读取
void CDicomReadDlg::Initialization()
{
	VR* pElement;
	char szText[128];
	UINT16  uiCol;
	UINT16  uiRow;
	UINT16 uiBitsAllocated;
	UINT16 uiBitsStored;
	UINT16 uiHighBit;
	UINT16 nSamplePerPixel;
	char cphotoMetric[128];

	memset(szText,0,128*sizeof(char));
	if (pElement = m_pDICOMData->GetVR(0x0028,0x1050))
	{
		memcpy(szText,pElement->Data,pElement->Length);
		m_nWindowCenter = atoi(szText);
	}

	memset(szText,0,128*sizeof(char));
	if (pElement = m_pDICOMData->GetVR(0x0028,0x1051))
	{
		memcpy(szText,pElement->Data,pElement->Length);
		m_nWindowWidth = atoi(szText);
	}
	
	memset(szText,0,128*sizeof(char));
	if (pElement = m_pDICOMData->GetVR(0x0010, 0x0010))
	{
		memcpy(szText,pElement->Data,pElement->Length);
		m_szPatientName = szText ;
	}
	memset(szText,0,128*sizeof(char));
	if (pElement = m_pDICOMData->GetVR(0x0010, 0x0040))
	{
		memcpy(szText,pElement->Data,pElement->Length);
		m_szPatientSex = szText ;
	}
	memset(szText,0,128*sizeof(char));
	if (pElement = m_pDICOMData->GetVR(0x0008, 0x0080))
	{
		memcpy(szText,pElement->Data,pElement->Length);
		m_szInstitutionName = szText ;
	}
	memset(szText,0,128*sizeof(char));
	if (pElement = m_pDICOMData->GetVR(0x0008, 0x1030))
	{
		memcpy(szText,pElement->Data,pElement->Length);
		m_szStudyDescription = szText ;
	}

    memset(cphotoMetric,0,128*sizeof(char));
	if (pElement = m_pDICOMData->GetVR(0x0028,0x0004))
	{
		memcpy(cphotoMetric,pElement->Data,pElement->Length);
		m_szPhotoMetric = cphotoMetric;
	}

	if (pElement = m_pDICOMData->GetVR(0x0028,0x0002))
	{
		nSamplePerPixel = *((UINT16*)(pElement->Data));
	}

	if (pElement = m_pDICOMData->GetVR(0x0028,0x0011))
	{
		uiCol = *((UINT16*)(pElement->Data));
		m_nCol = uiCol;
	}
	
	if (pElement = m_pDICOMData->GetVR(0x0028,0x0010))
	{
		uiRow = *((UINT16*)(pElement->Data));
		m_nRow = uiRow;
	}
	
	if (pElement = m_pDICOMData->GetVR(0x0028,0x0100))
	{
		uiBitsAllocated = *((UINT16*)(pElement->Data));
	}
	
	if (pElement = m_pDICOMData->GetVR(0x0028,0x0101))
	{
		uiBitsStored = *((UINT16*)(pElement->Data));
	}	

	if (pElement = m_pDICOMData->GetVR(0x0028,0x0102))
	{
		uiHighBit = *((UINT16*)(pElement->Data));
	}
	
	pElement = m_pDICOMData->GetVR(0x7FE0,0x0010);

    m_pStoreData = new int[m_nCol*m_nRow];
	m_pData = new int[m_nCol*m_nRow];
	int shift = uiHighBit + 1 - uiBitsStored;
	switch (uiBitsAllocated)
	{
	case 8:
		{
			UINT8 *pData = (UINT8 *)pElement->Data;
			for (int x = 0;x<(m_nCol*m_nRow);x++)
			{
				m_pStoreData[x] = pData[x] >> shift;
			}
			break;
		}
	case 16:
		{
			UINT16 *pData = (UINT16 *)pElement->Data;
			//int *pData = (int*)pElement->Data;  
			for (int x = 0;x<(m_nCol*m_nRow);x++)
			{
				m_pData[x] = m_pStoreData[x] = pData[x] >> shift;
			}
			//memcpy(m_pStoreData,pData,(pElement->Length)*2);
			break;
		}
		//C++没有24位指针
	default:
		{
			int *pData = (int *)pElement->Data;
			//int *pData = (int*)pElement->Data;  
			for (int x = 0;x<(m_nCol*m_nRow);x++)
			{
				m_pData[x] = m_pStoreData[x] = *(pData + x + shift);
			}
			//memcpy(m_pStoreData,pData,(pElement->Length)*2);
			break;
		}
		break;
	}
}

//显示的是DICOM的图像
void CDicomReadDlg::ShowImage()
{
	m_pImage = new CImage();

	int nBitsPerPixel,nBytesPerPixel;
	BYTE *pNewPixel;

	nBitsPerPixel = 24;
	//nBitsPerPixel = uiBitsAllocated;
	nBytesPerPixel = nBitsPerPixel/8;
	if(!m_pImage->IsNull())
		m_pImage->Destroy();//如果图像pNewImage非空，则清除原有图像（原位图）
	m_pImage->Create(m_nRow,m_nCol,nBitsPerPixel,0);


	for(int x = 0;x < m_nCol;x++)
		for(int y = 0;y < m_nRow;y++)
		{
			pNewPixel = (BYTE*)m_pImage->GetPixelAddress(x,y);
			*pNewPixel = *(pNewPixel+1) = *(pNewPixel+2) = GetPixelValue(y,x);
		}

	//InvalidateRect(&m_rect);

		if(m_pImage)
		{
			CRect rect((m_rect.left+m_rect.right-m_pImage->GetWidth())/2,(m_rect.top+m_rect.bottom-m_pImage->GetHeight())/2,(m_rect.left+m_rect.right+m_pImage->GetWidth())/2,(m_rect.top+m_rect.bottom+m_pImage->GetHeight())/2);
			m_rect.CopyRect(&rect);
			m_pImage->Draw(m_pDC->m_hDC,m_rect);

			CString str;
			m_pDC->SetBkMode(TRANSPARENT);///透明
			m_pDC->SetTextColor(RGB(58,110,165));
			m_pDC->SetTextAlign(TA_RIGHT);

			m_pDC->TextOut(m_rect.right-5,m_rect.top+10,m_szPatientName);
			m_pDC->TextOut(m_rect.right-5,m_rect.top+30,m_szPatientSex);
			m_pDC->TextOut(m_rect.right-5,m_rect.top+50,m_szInstitutionName);
			m_pDC->TextOut(m_rect.right-5,m_rect.top+70,m_szStudyDescription);


			m_pDC->SetTextAlign(TA_LEFT);
			str.Format("Window center:%d   width:%d",m_nWindowCenter,m_nWindowWidth);
			str = str + _T("    ");
			m_pDC->TextOut(m_rect.left+5,m_rect.bottom-20,str);
		}
}
void CDicomReadDlg::RestoreData()
{
	for (int x = 0;x<(m_nCol*m_nRow);x++)
	{
		m_pData[x] = m_pStoreData[x];
	}
}
int CDicomReadDlg::GetPixelValue(int i,int j)
{
	int nWH = m_nWindowCenter + m_nWindowWidth/2;
	int nWL = m_nWindowCenter - m_nWindowWidth/2;

	int nValue = m_pData[i*m_nCol+j];


	if ("MONOCHROME2 " == m_szPhotoMetric)
	{
		if ((nValue < nWH) && (nValue > nWL))
		{ 
			nValue = (nValue - nWL) * 255/(nWH - nWL);
		}
		else if (nValue > nWH)
		{
			nValue = 255;
		}
		else
		{
			nValue = 0;
		}
	} 
	else
	{
		if ((nValue < nWH) && (nValue > nWL))
		{ 
			nValue = (nWH -nValue) * 255/(nWH - nWL);
		}
		else if (nValue > nWH)
		{
			nValue = 0;
		}
		else
		{
			nValue = 255;
		}
	}

	return nValue;
}

void CDicomReadDlg::OnFileSave()
{
	if(!m_pImage)
	{
		MessageBox(_T("Did not open the picture file!"));
		return;
	}

	CString strFilter;
	/*strFilter = "DICOM图像文件|*.dcm|位图文件|*.bmp|JPEG图像文件|*.jpg|\GIF图像文件|*.gif|PNG图像文件|*.png|";*/
	strFilter = "位图文件|*.bmp|JPEG图像文件|*.jpg|\GIF图像文件|*.gif|PNG图像文件|*.png|DICOM图像文件|*.dcm|";
	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	if ( IDOK != dlg.DoModal())
		return;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	CString strExtension;

	strExtension = dlg.GetFileExt();
	strFileName = dlg.m_ofn.lpstrFile;
	if (dlg.m_ofn.nFileExtension == 0) 
	{
		switch (dlg.m_ofn.nFilterIndex)
		{

		case 1:strExtension = "bmp"; break;
		case 2:strExtension = "jpg";break;
		case 3:strExtension = "gif"; break;
		case 4:strExtension = "png"; break;
		case 5:strExtension = "dcm"; break;

			/*case 1:strExtension = "dcm"; break;
			case 2:strExtension = "bmp"; break;
			case 3:strExtension = "jpg";break;
			case 4:strExtension = "gif"; break;
			case 5:strExtension = "png"; break;*/

		default:break;
		}

		strFileName = strFileName + '.' + strExtension;
	}
	// 图像保存


	if (strExtension == "dcm")
	{
		char *sz;
		sz= strFileName.GetBuffer(0);

		if(m_pPDU == NULL) // we need to create a PDU
			m_pPDU = new PDU_Service;
		if(m_pPDU->SaveDICOMDataObject(sz, ACRNEMA_VR_DUMP, m_pDICOMData) == TRUE)
			return ;
		else
			MessageBox(_T("Failed")); ;
	} 
	else
	{
		HRESULT hResult = m_pImage->Save(strFileName);
		if (FAILED(hResult)) 
			MessageBox(_T("Failed")); 
	}
}
//导出信息到txt当中
BOOL CDicomReadDlg::dump()
{
	if(m_pPDU == NULL)
		m_pPDU = new PDU_Service;
	m_pDICOMData = m_pPDU->LoadDICOMDataObject((m_path.GetBuffer(0)));

	// BTX: if no data, print error
	if(m_pDICOMData == NULL)
	{
		//cout<<"Error: There is no data to be saved"<<endl;
		return false;
	}
	// ETX

	// BTX: dump information

	CString strFilter;
	strFilter = "文本文件|*.txt|DICOM图像文件|*.dcm|";
	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	if ( IDOK != dlg.DoModal())
		return false;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	CString strExtension;

	strExtension = dlg.GetFileExt();
	strFileName = dlg.m_ofn.lpstrFile;


	if (dlg.m_ofn.nFileExtension == 0) 
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
		default:strExtension = "txt";
				break;
		}

		strFileName = strFileName + '.' + strExtension;
	}

    RTC rtc;
	//if(m_pDICOMData->DumpElementsOneByOne(&rtc, strFileName.GetBuffer(0)) == TRUE)
	if(m_pDICOMData->DumpElementsOneByOne(m_spRtc, strFileName.GetBuffer(0)) == TRUE)
		return true;
	else
		return false;
	// ETX
}

void CDicomReadDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		CString str;
	CDC *pdc = GetDC();
	if (m_pDICOMData)
	{
		CWnd *pwnd=GetDlgItem(IDC_STATIC);
		this->ClientToScreen(&point);
		pwnd->ScreenToClient(&point);

		m_myPoint = CPoint(m_rect.left,m_rect.top);
		m_myPoint = point - m_myPoint;
		
		if (m_rect.PtInRect(point))
		{
			//InvalidateRect(&m_rect);
   //         m_pDC->SetBkMode(OPAQUE);///透明
			////m_pDC->SetBkColor(RGB(58,110,165));
			//m_pDC->SetTextColor(RGB(255,0,0));
			//int nGray = m_pStoreData[(m_myPoint.y)*m_nCol+m_myPoint.x];
			//str.Format("X:%d Y:%d V:%d",m_myPoint.x,m_myPoint.y,nGray);
			//str = str+_T("       ");
			//m_pDC->TextOut(m_rect.left+5,m_rect.bottom+20,str);	

			pdc->SetBkMode(OPAQUE);///透明
			//m_pDC->SetBkColor(RGB(58,110,165));
			pdc->SetTextColor(RGB(255,0,0));
			int nGray = m_pStoreData[(m_myPoint.y)*m_nCol+m_myPoint.x];
			str.Format("X:%d Y:%d V:%d",m_myPoint.x,m_myPoint.y,nGray);
			str = str+_T("       ");
			pdc->TextOut(m_rect.left+10,m_rect.bottom+20,str);
			GetDlgItem(IDC_STATIC)->SetFocus();
		}
		else
		{
			/*str = _T("                                                      ");
			m_pDC->TextOut(m_rect.left+5,m_rect.bottom+20,str);*/
			str = _T("                                                      ");
			pdc->TextOut(m_rect.left+10,m_rect.bottom+20,str);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDicomReadDlg::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_pDICOMData)
	{
		if (m_bFlag)
		{
			m_nWindowCenter += zDelta;
		}
		else
		{
			m_nWindowWidth += zDelta;
		}
		
		ShowImage();
	}
	CDialogEx::OnMouseHWheel(nFlags, zDelta, pt);
}
