#include "StdAfx.h"
#include "ISOData.h"


CISOData::CISOData(void)
{
	m_bShowClass = false;
	m_bShowISOClass = false;
}


CISOData::~CISOData(void)
{
	if(!DataPoint.empty())
	{
		DataPoint.clear();
	}
	if(!ISOClass.empty())
	{
		ISOClass.clear();
	}
	if(!c_meanClass.empty())
	{
		c_meanClass.clear();
	}
	if(!ClusterCenter.empty())
	{
		ClusterCenter.clear();
	}
}

void CISOData::OnGenerateData(int * x, int * y)
{
	// ���������ݵ����
	for(int i = 0; i < m_DataNum; i++)
	{
		CPoint ptTemp(x[i], y[i]);
		DataPoint.push_back(ptTemp); // ѹ������
	}
	m_bShowClass = false;
 	m_bShowISOClass = false;

}

void CISOData::OnCMean()
{
	if(!c_meanClass.empty())
		c_meanClass.clear();
	// ��Ԥ��֪��C-means������
	srand((unsigned)time(NULL));
	
	c_meanClass.resize(m_ClusterCenterNum);
	InitCenter(m_ClusterCenterNum);

	int max_iter = 50; //����������
	//�������
	int j ;
	for(j = 0; j < max_iter; j++)
	{
		//�����ݵ����
		ClusteringPoint(m_ClusterCenterNum);
		bool bFlagContinue = false; //��־�Ƿ����ѭ��

		//����ÿ��������ĵ�,���Ƿ��ԭ���ĵ����,����ֹͣ,���������
		for(int i = 0; i < m_ClusterCenterNum; i++)
		{
			float newCenter_x, newCenter_y;
			CalcuCenter(i,newCenter_x, newCenter_y);
			float old_x, old_y;
			old_x = ClusterCenter.at(i).center_x;
			old_y = ClusterCenter.at(i).center_y;
			//���������������������ı�,��ı�bFlagContinue,��Ϊtrue����ѭ��
			if (newCenter_x != old_x || newCenter_y != old_y)
			{
				bFlagContinue = true;
				ClusterCenter.at(i).center_x=newCenter_x;
				ClusterCenter.at(i).center_y=newCenter_y;
			}
		}
		//����CENTER��ȫ����
		if(!bFlagContinue)
			break;
	}
	int m_nIterTime = j + 1;
	CString str;
	str.Format(_T("����%d��") , m_nIterTime);
	AfxMessageBox(str,0);

	m_bShowClass = true;

	
}

void CISOData::InitCenter(int CenterNum, int type/*=0*/)
{
	int i , j, index;
	int *centerIndex = new int[CenterNum];
	if(!ClusterCenter.empty())
		ClusterCenter.clear();
	srand((unsigned)time(NULL));
	//	srand(1);//for test
	
	//��ʼ�����������CENTER
	// ͨ���ҵ�index�����ҵ�����Դ����ʼ������
	for(i = 0; i < CenterNum; ++i)
	{
		//���ܳ����ظ�
		while(1)
		{
			index = rand() % m_DataNum;
			
			//��һ��
			if(i == 0)
				break;
			
			//���ǵ�һ���ж������ظ�
			for(j = 0; j < i; ++j)
			{
				if(centerIndex[j] == index)
					break;					
			}
			//û���ظ�
			if(j == i)
			{
				break;		
			}	
		}
		AA point;
		point.center_x = DataPoint.at(index).x;
		point.center_y = DataPoint.at(index).y;
		ClusterCenter.push_back(point);
	}
	delete []centerIndex;
}

void CISOData::ClusteringPoint(int centernum, int type/*=0*/)
{
	int j ,k;
	//�����һ�η�����
    if (type==0)  //Cmeans
	{
		for(j = 0; j < centernum; j++)
		{
			if(!c_meanClass[j].empty())
				c_meanClass[j].clear();
		}
	}
	else    //isodata
	{
		ISOClass.resize(centernum);
		for(j = 0; j < centernum; j++)
		{
			if(!ISOClass[j].empty())
				ISOClass[j].clear();
		}
	}
	//�����ݵ����,ѭ��ÿ����
	for(j = 0; j < m_DataNum; ++j)
	{
		int		dist, distOld;
		int		classflag = 0;
		CPoint ptTemp = DataPoint[j];
		//ѭ��ÿ����,�ж���������
		for( k = 0; k < centernum; ++k)
		{
			float centerTemp_x, centerTemp_y;
			centerTemp_x=ClusterCenter.at(k).center_x;
            centerTemp_y=ClusterCenter.at(k).center_y;
			//û�п�����������һ����
			dist = (centerTemp_x - ptTemp.x) * (centerTemp_x - ptTemp.x) + (centerTemp_y - ptTemp.y) * (centerTemp_y - ptTemp.y);
			if(k == 0)
			{
				distOld = dist;
			}
			else
			{			
				if(dist < distOld)
				{	
					distOld = dist;
					classflag = k;
				}
			}			
		}
		//���ڵ�classflag ��
		if (type==0)
		{
		    c_meanClass[classflag].push_back(ptTemp);
		} 
		else
		{
		    ISOClass[classflag].push_back(ptTemp);
		}

	}
}

void CISOData::CalcuCenter(int CenterIntex,float &Center_x,float &Center_y,int type/*=0*/)
{
// 	if(c_meanClass[CenterIntex].empty()) //empty
// 	{
// 		x = -1;
// 		y = -1;
// 	}
	
	int i;
	int dataSize ;
	if (type==0)//cmeans
	{
		dataSize=c_meanClass[CenterIntex].size();
	} 
	else  //ISODATA
	{
		dataSize=ISOClass[CenterIntex].size();
	}
	float x_aver = 0; //�µ����ĵ������
	float y_aver = 0;
	
	for(i =0; i < dataSize; ++i)
	{
		if (type==0)
		{
			x_aver += c_meanClass[CenterIntex].at(i).x;
		    y_aver += c_meanClass[CenterIntex].at(i).y;
		} 
		else
		{
			x_aver += ISOClass[CenterIntex].at(i).x;
		    y_aver += ISOClass[CenterIntex].at(i).y;
		}

	}
	
	Center_x = x_aver / dataSize;
	Center_y = y_aver / dataSize;	
}

void CISOData::OnIsodata()
{
	if(!ISOClass.empty())
		ISOClass.clear();

	// ��Ҫ��ʼ��ǰ����߸�������ֵ
	srand((unsigned)time(NULL));
	int i, j;
	ISOClass.resize(m_ISO_Nc); // ���ٸ�����
	InitCenter(m_ISO_Nc, 1);

	j = 0;
	do {
		bool bFlagContinue = true;
		//�����ݵ����
//MessageBox(_T("11"));		
		ClusteringPoint(m_ISO_Nc,1);
//MessageBox(_T("12"));
		for(i = 0; i <m_ISO_Nc; ++i)
		{
			if(ISOClass[i].size() < m_ISO_theta_n)
			{
				//ȡ������,����Ŀ�Լ� .bFlagContinue= false ���·���
				//ISOClass.erase(ISOClass.begin() + i);
				ClusterCenter.erase(ClusterCenter.begin()+i);
				m_ISO_Nc--;
				bFlagContinue = false;
			}
		}
		
		if(!bFlagContinue)
		{
			//++j;			//��Ҫ?
			continue;
		}
		
		m_averdist = 0;	//ƽ����ľ���
		
//MessageBox(_T("21"));
        for(i = 0; i< m_ISO_Nc; ++i)
		{
			m_averdist += CalAverDist(i);
		}
//MessageBox(_T("22"));
		m_averdist = m_averdist / m_ISO_Nc;

		if( (m_ISO_Nc < m_ISO_c/2) || (m_ISO_Nc< 2*m_ISO_c && (j%2==0)) )
		{
//MessageBox(_T("31"));
			bFlagContinue = !ISOSplit();
//MessageBox(_T("32"));

		}
		
		if(!bFlagContinue)
		{
			++j;
			continue;
		}
		
//MessageBox(_T("41"));
		ISOMerge();
//MessageBox(_T("42"));
		++j;
	}  while (j <m_ISO_i);
//MessageBox(_T("5"));	
	CString str;
	int tempNum = ISOClass.size();
	str.Format(_T("�ֳ�%d ��"), tempNum);
	AfxMessageBox(str, 0);
	
	m_bShowISOClass = true;
	
}

float CISOData::CalAverDist(int CenterNum)
{
	if(ISOClass[CenterNum].empty()) //empty
	{
		return 0;
	}
	
	int i;
	int dataSize = ISOClass[CenterNum].size();//��ǰ�����е�ĸ���
	int x,y;
	float dist = 0;
	float newCenter_x, newCenter_y;
	newCenter_x = newCenter_y = 0.f;
	//��������µľ�������
	CalcuCenter(CenterNum,newCenter_x, newCenter_y,1);
	ClusterCenter.at(CenterNum).center_x=newCenter_x;
	ClusterCenter.at(CenterNum).center_y=newCenter_y;

	for(i =0; i < dataSize; ++i)
	{
		x = ISOClass[CenterNum].at(i).x;
		y = ISOClass[CenterNum].at(i).y;
		dist += sqrt((float)((x-newCenter_x) * (x-newCenter_x) + (y-newCenter_y) * (y-newCenter_y)));
	}
	
	dist = dist/ dataSize;
	m_averdist = dist;
	
	return m_averdist;
}

bool CISOData::ISOSplit()
{
	int i,xORy;
	float maxTheta = 0.f;
	xORy = 0;
	bool bSplit = false;

	int PreNc=m_ISO_Nc;
	
	for(i = 0; i < PreNc; ++i)
	{
//MessageBox(_T("01"));
		GetMaxStandDevi(i,xORy, maxTheta);
//MessageBox(_T("02"));
		if(maxTheta > m_ISO_theta_s)
		{
			if( (m_ISO_Nc <= m_ISO_c/2) ||
				((CalAverDist(i) > m_averdist) && ( ISOClass[i].size() > 2*(m_ISO_theta_n+1)) ) )
			{
				//����
				float oldCenter_x=ClusterCenter.at(i).center_x;
	        	float oldCenter_y=ClusterCenter.at(i).center_y;

				float newCenter_x,newCenter_y, newClassCenter_x,newClassCenter_y;
				if(xORy == 0)
				{
					newCenter_x = oldCenter_x + m_k_split * maxTheta;
					newClassCenter_x = oldCenter_x - m_k_split * maxTheta;
					newCenter_y = newClassCenter_y = oldCenter_y;
				}
				else
				{
					newCenter_y = oldCenter_y + m_k_split * maxTheta;
					newClassCenter_y = oldCenter_y - m_k_split * maxTheta;
					newCenter_x = newClassCenter_x = oldCenter_x;
				}
				ClusterCenter.at(i).center_x=newCenter_x;
	            ClusterCenter.at(i).center_y=newCenter_y;
				

				AA point;
				point.center_x=newClassCenter_x;
				point.center_y=newClassCenter_y;
	        	ClusterCenter.push_back(point);
				m_ISO_Nc++;
				bSplit =true;
				
			}
		}
		
	}
	
	return bSplit; //if split
}

void CISOData::GetMaxStandDevi(int CenterNum,int &xORy/*out*/,float &StandDev/*out*/)
{
	if(ISOClass[CenterNum].empty()) //empty
	{
		xORy = -1;
		StandDev = 0;
		return ;
	}
	
	int i;
	int dataSize = ISOClass[CenterNum].size();//��ǰ�����е�ĸ���
	int x,y;
	float dev_x = 0;
	float dev_y = 0;
	
	for(i =0; i < dataSize; ++i)
	{
		x = ISOClass[CenterNum].at(i).x;
		y = ISOClass[CenterNum].at(i).y;
		float m_center_x=ClusterCenter.at(CenterNum).center_x;
		float m_center_y=ClusterCenter.at(CenterNum).center_y;
		dev_x += (x-m_center_x) * (x-m_center_x);
		dev_y += (y-m_center_y) * (y-m_center_y);
	}
	
	dev_x = sqrt(dev_x / dataSize);
	dev_y =	sqrt(dev_y / dataSize);
	
	xORy = dev_x >= dev_y ? 0 : 1;
	StandDev = dev_x >= dev_y ? dev_x: dev_y;
	
}

void CISOData::ISOMerge()
{
	if(m_ISO_Nc == 1)
	{
		return;
	}
	
	int i,m,n;
	float temp,minDist;
	int index1,index2;
	
	for(i = 0; i < m_ISO_l; ++i) //���Ժϲ���������
	{
		if (m_ISO_l > 1)
		{
			ClusteringPoint(m_ISO_Nc,1);
		}
		//�ҳ���С����
		minDist = 0;
		for(m = 0; m < m_ISO_Nc-1; ++m)
		{
			for(n = m+1; n < m_ISO_Nc; ++n)
			{
				float pt1_x,pt1_y,pt2_x,pt2_y;
				CalcuCenter(m,pt1_x, pt1_y,1);
				CalcuCenter(n,pt2_x, pt2_y,1);
				temp = (pt1_x - pt2_x)*(pt1_x - pt2_x) + (pt1_y - pt2_y)*(pt1_y - pt2_y);
				if (m == 0 && n ==1)
				{
					minDist = temp;
					index1 = 0;
					index2 = 1;
				}
				else if(temp < minDist)
				{
					minDist = temp;
					index1 = m;
					index2 = n;
				}
			}
		}
		
		if(minDist >= m_ISO_theta_d)
			break;
		//����ϲ�
		float oldCenter1_x=ClusterCenter.at(index1).center_x;
	    float oldCenter1_y=ClusterCenter.at(index1).center_y;
		float oldCenter2_x=ClusterCenter.at(index2).center_x;
	    float oldCenter2_y=ClusterCenter.at(index2).center_y;
		int size1,size2;
		
		size1 = ISOClass[index1].size();
		size2 = ISOClass[index2].size();
		
		float newCenter_x,newCenter_y;
		
		newCenter_x = (oldCenter1_x * size1 + oldCenter2_x * size2) / (size1 +size2);
		newCenter_y = (oldCenter1_y * size1 + oldCenter2_y * size2) / (size1 +size2);

		ClusterCenter.at(index1).center_x=newCenter_x;
	    ClusterCenter.at(index1).center_y=newCenter_y;
		
		ClusterCenter.erase(ClusterCenter.begin() + index2);
		m_ISO_Nc--;
		
	}
	
}