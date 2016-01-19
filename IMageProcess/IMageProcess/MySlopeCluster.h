#pragma once
#include <vector>
#include "DIdefine.h"

using namespace std;

class CMySlopeCluster
{
public:
	CMySlopeCluster(void);
	~CMySlopeCluster(void);
public:
	int m_DataNum; // ���ݵ�ĸ���
	int m_ClusterNum; // �洢��������������������ĳ�ʼ��������
	vector<CPoint> DataPoint;	//�洢���ݵ�
	vector<double> Slope;//�洢ÿһ���б��
	double m_initSlope; // ��Ϊ����ĳ�ʼб��,��ת�����Ƕ�

	vector< vector <CPoint>  > SlopeClass;//�洢Slope����ķ�����
	vector<CPoint> ClusterCenter; // �洢ÿ������ӵ㣬�õ�һֱ����
public:
	void OnGenerateData(int *, int *);
	void OnSlope(int * x0, int * y0, bool ); // x0 ,y0Ϊ����ĳ�ʼ���ӵ�
	void InitPoints(int * x0, int * y0,int clusternum);
	void ClusteringPoint(int centernum, bool);//ȷ���������ĺ�б�ʲ���С����ԭ�򽫸���ֵ�����ȥ
	void CalcuCenter(int CenterIntex,float &Center_x,float &Center_y); // ���³�ʼ���ӵ�
};

