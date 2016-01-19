#pragma once
// һάC-means ���� ������Ǻܺ�
class CK_Means
{
public:
	CK_Means(void);
	~CK_Means(void);
public:
	void CreateRandomArray(int n, int k,int * center);
	int GetIndex(double value,double * center);
	void CopyCenter();
	void InitCenter();
	void AddToCluster(int index,double value);
	void UpdateCluster();
    void UpdateCenter();
	int IsEqual(double * center1 ,double * center2);
	void InitData(int *, int , int );
	int ** ReturnData();
	void Print();
private:
	int N;//�������ݸ���
	int K; // ���ֵľ������
	int * CenterIndex;

	double * AllData;
	double ** Cluster;
	
public:
	double * Center;
	double * CenterCopy;
	int * Top;
};

