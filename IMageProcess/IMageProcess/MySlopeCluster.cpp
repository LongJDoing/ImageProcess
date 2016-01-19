#include "StdAfx.h"
#include "MySlopeCluster.h"


CMySlopeCluster::CMySlopeCluster(void)
{
}


CMySlopeCluster::~CMySlopeCluster(void)
{
	if(!DataPoint.empty())
	{
		DataPoint.clear();
	}
	if(!SlopeClass.empty())
	{
		SlopeClass.clear();
	}
}

void CMySlopeCluster::OnGenerateData(int * x, int * y)
{
	// 需输入数据点个数
	if(!DataPoint.empty())
		DataPoint.clear();
	for(int i = 0; i < m_DataNum; i++)
	{
		CPoint ptTemp(x[i], y[i]);
		DataPoint.push_back(ptTemp); // 压入数据
	}

}
void CMySlopeCluster::OnSlope(int * x0, int * y0, bool b_c)
{
	if(!SlopeClass.empty())
		SlopeClass.clear();

	SlopeClass.resize(m_ClusterNum);
	InitPoints(x0, y0, m_ClusterNum);

	this->ClusteringPoint(m_ClusterNum, b_c);
}

void CMySlopeCluster::InitPoints(int *x0, int * y0, int CenterNum)
{
	if(!ClusterCenter.empty())
		ClusterCenter.clear();
	for(int i = 0; i < CenterNum; ++i)
	{
		CPoint point;
		point.x = x0[i];
		point.y = y0[i];
		ClusterCenter.push_back(point);
	}
}

void CMySlopeCluster::ClusteringPoint(int centernum, bool b_c)
{
	//将数据点聚类,循环每个点
	for(int j = 0; j < m_DataNum; j++)
	{
		double atank, minatank, addtank;
		int classflg = 0;
		minatank = 10;
		CPoint ptTemp = DataPoint[j];
	//	int cok = 0;
		for(int k = 0; k < centernum; k++)
		{
			float center_x, center_y;
			CalcuCenter(k, center_x, center_y);
			//center_x = ClusterCenter.at(k).x;
			//center_y = ClusterCenter.at(k).y;
			double tank = (center_y - ptTemp.y)/(center_x - ptTemp.x);
			//计算斜率
			if(b_c)
			{
				if(!::_isnan(atan(tank))) // NAN
				{
					atank = 180.0/PI*(atan(tank));
					if(atank < 0)
						atank = 180+atank;
				}
				else
				{
					atank = 90.0;	
				}			
			}
			else
			{
				if(center_x == ptTemp.x)
					break;
				tank = (center_y - ptTemp.y)/(center_x - ptTemp.x);

				atank = tank;
			}
			double atemptank = (atank - m_initSlope)*(atank - m_initSlope);
			//minatank = atank;
			if(atemptank < minatank)
			{
				minatank = atemptank;
				classflg = k;
				addtank = atank;
			}
		}
		if(minatank == 10) // 排除一些点
			continue;
	//	cok++;
		if(!b_c)
		{
			m_initSlope += addtank;
			m_initSlope /= (2); // 不断的递归k
		}

		SlopeClass[classflg].push_back(ptTemp);
	}
}

void CMySlopeCluster::CalcuCenter(int CenterIntex, float &Center_x, float &Center_y)
{
	float x_aver = 0;
	float y_aver = 0;
//	int dataSize = SlopeClass[CenterIntex].size();
	//for(int i = 0; i < dataSize; i++)
	//{
	//	x_aver += SlopeClass[CenterIntex].at(i).x;
	//	y_aver += SlopeClass[CenterIntex].at(i).y;
	//}
	x_aver += ClusterCenter.at(CenterIntex).x;
	y_aver += ClusterCenter.at(CenterIntex).y;

//	Center_x = x_aver/(dataSize+1);
	//Center_y = y_aver/(dataSize+1);
	Center_x = x_aver;
	Center_y = y_aver;
}