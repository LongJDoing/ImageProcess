#pragma once
// ��ά��C-means ��ISOData ����
#include<vector>
using namespace std;

typedef struct float_center
{
	float center_x;
	float center_y;
}AA;
class CISOData
{
public:
	CISOData(void);
	~CISOData(void);
public:
	bool	m_bShowClass;		//��־���c-mean�������ʾ����
	bool	m_bShowISOClass;	//��־���ISODATA�������ʾ����
    int     m_ClusterCenterNum;  //c-means�洢������������������������ĳ�ʼ������������

	int		m_ISO_c;			//ISODATA������ ��Ԥ������
	int		m_ISO_Nc;			//ISODATA������ �ĳ�ʼ�������ĸ���
	int		m_ISO_l;			//ISODATA������ ��ÿ�ε������Ժϲ������������
	int		m_ISO_i;			//ISODATA������ �����������������
	int		m_ISO_theta_n;		//ISODATA������ ��ÿһ�����������ģʽ��Ŀ,�����ڴ���������Ϊһ����������
	float	m_ISO_theta_s;		//ISODATA������ �����ڸ����������׼�������
	float	m_ISO_theta_d;		//ISODATA������ ���������ļ���С���������

	float	m_k_split;			//ISODATA������ �����ʱ����������ĵ�ϵ�� 0<=k<=1
	float	m_averdist;			//ISODATA������ �����������ĵ�ƽ������

public:
	int m_DataNum;              //���ݵ�ĸ���
	vector<CPoint> DataPoint;	//�洢���ݵ�
    vector<AA> ClusterCenter;//�洢ÿ�������
  
	vector< vector <CPoint>  > c_meanClass;//�洢c��ֵ����ķ�����
	vector< vector <CPoint>  > ISOClass;//�洢Isodata����ķ�����
public:
	void OnGenerateData(int *, int *);
	void OnCMean();
	void InitCenter(int CenterNum, int type =0);
	void ClusteringPoint(int centernum,int type = 0);//ȷ���������ĺ󰴾ͽ�ԭ�򽫸���ֵ�����ȥ
	void CalcuCenter(int CenterIntex,float &Center_x,float &Center_y,int type=0);

	void OnIsodata();
	float CalAverDist(int CenterNum);//�������ƽ������
	bool ISOSplit();//����
	void GetMaxStandDevi(int CenterNum,int &xORy/*out*/,float &StandDev/*out*/);//�õ�����ı�׼��������������
	void ISOMerge();//�ϲ�

};

