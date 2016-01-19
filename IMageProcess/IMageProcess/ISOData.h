#pragma once
// 二维的C-means 及ISOData 聚类
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
	bool	m_bShowClass;		//标志完成c-mean聚类后显示新类
	bool	m_bShowISOClass;	//标志完成ISODATA聚类后显示新类
    int     m_ClusterCenterNum;  //c-means存储聚类中心数（参数设置输入的初始聚类中心数）

	int		m_ISO_c;			//ISODATA聚类中 的预期类数
	int		m_ISO_Nc;			//ISODATA聚类中 的初始聚类中心个数
	int		m_ISO_l;			//ISODATA聚类中 的每次迭代可以合并的类的最多对数
	int		m_ISO_i;			//ISODATA聚类中 的允许的最多迭代次数
	int		m_ISO_theta_n;		//ISODATA聚类中 的每一类允许的最少模式数目,若少于次数，不作为一个独立聚类
	float	m_ISO_theta_s;		//ISODATA聚类中 的类内各分量距离标准差的上限
	float	m_ISO_theta_d;		//ISODATA聚类中 的两类中心间最小距离的下限

	float	m_k_split;			//ISODATA聚类中 类分裂时候计算新中心的系数 0<=k<=1
	float	m_averdist;			//ISODATA聚类中 样本距其中心的平均距离

public:
	int m_DataNum;              //数据点的个数
	vector<CPoint> DataPoint;	//存储数据点
    vector<AA> ClusterCenter;//存储每类的中心
  
	vector< vector <CPoint>  > c_meanClass;//存储c均值聚类的分类结果
	vector< vector <CPoint>  > ISOClass;//存储Isodata聚类的分类结果
public:
	void OnGenerateData(int *, int *);
	void OnCMean();
	void InitCenter(int CenterNum, int type =0);
	void ClusteringPoint(int centernum,int type = 0);//确定聚类中心后按就近原则将各点分到各类去
	void CalcuCenter(int CenterIntex,float &Center_x,float &Center_y,int type=0);

	void OnIsodata();
	float CalAverDist(int CenterNum);//计算各类平均距离
	bool ISOSplit();//分裂
	void GetMaxStandDevi(int CenterNum,int &xORy/*out*/,float &StandDev/*out*/);//得到各类的标准差向量的最大分量
	void ISOMerge();//合并

};

