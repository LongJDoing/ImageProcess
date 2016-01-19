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
	int m_DataNum; // 数据点的个数
	int m_ClusterNum; // 存储聚类数（参数设置输入的初始聚类数）
	vector<CPoint> DataPoint;	//存储数据点
	vector<double> Slope;//存储每一类的斜率
	double m_initSlope; // 作为输入的初始斜率,已转换到角度

	vector< vector <CPoint>  > SlopeClass;//存储Slope聚类的分类结果
	vector<CPoint> ClusterCenter; // 存储每类的种子点，该点一直不变
public:
	void OnGenerateData(int *, int *);
	void OnSlope(int * x0, int * y0, bool ); // x0 ,y0为输入的初始种子点
	void InitPoints(int * x0, int * y0,int clusternum);
	void ClusteringPoint(int centernum, bool);//确定聚类中心后按斜率差最小化的原则将各点分到各类去
	void CalcuCenter(int CenterIntex,float &Center_x,float &Center_y); // 更新初始种子点
};

