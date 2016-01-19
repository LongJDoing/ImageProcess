#include "StdAfx.h"
#include "K_Means.h"
#include <math.h>
#include <fstream>
#include <iostream>
using namespace std;
CK_Means::CK_Means(void)
{
}


CK_Means::~CK_Means(void)
{
	delete CenterIndex;
	CenterIndex = 0;
	delete Center;
	Center = 0;
	delete AllData;
	AllData = 0;
	for(int i = 0; i < K; i++)
		delete []Cluster[i];
	delete []Cluster;
	Cluster = 0;
	delete Top;
	Top = 0;
}
void CK_Means::CreateRandomArray(int n, int k,int * center)
{
    int i=0;
    int j=0;    
    srand( (unsigned)time( NULL ) );
    for( i=0;i<k;++i)
    {
        int a=rand()%n;
        
        for(j=0;j<i;j++)
        {
            if(center[j]==a)
            {
                break;
            }
        }
        if(j>=i)
        {
            center[i]=a;
        }
        else
        {
            i--;
            
        }
    }     
}

int CK_Means::GetIndex(double value,double * center)
{
    int i=0;
    int index=i;
    double min=fabs(value-center[i]);
    for(i=0;i<K;i++)
    {
        if(fabs(value-center[i])<min)
        {
             index=i;
             min=fabs(value-center[i]);
        }
    }
    return index;
}
void CK_Means::CopyCenter()
{
    int i=0;
    for(i=0;i<K;i++)
    {
        CenterCopy[i]=Center[i];
    }
}

void CK_Means::InitCenter()
{
    int i=0;
    CreateRandomArray(N,K,CenterIndex);
    for(i=0;i<K;i++)
    {
        Center[i]=AllData[CenterIndex[i]];
    }
    CopyCenter();
}

void CK_Means::AddToCluster(int index,double value)
{
    Cluster[index][Top[index]++]=value;
} 


void CK_Means::UpdateCluster()
{    
    int i=0;
    int tindex;
    
    for(i=0;i<K;i++)
    {
        Top[i]=0;
    }
    for(i=0;i<N;i++)
    {
        tindex=GetIndex(AllData[i],Center);
        AddToCluster(tindex,AllData[i]);       
    }
}

void CK_Means::UpdateCenter()
{
    int i=0;
    int j=0;
    double sum=0;
    for(i=0;i<K;i++)
    {
        sum=0;    
        
        for(j=0;j<Top[i];j++)
         {
             sum+=Cluster[i][j];
         }
        if(Top[i]>0)
        {
           Center[i]=sum/Top[i];
        }
    }
}

int CK_Means::IsEqual(double * center1 ,double * center2)
{
    int i;
    for(i=0;i<K;i++)
    {
         if(fabs(double(center1[i]!=center2[i])))
         {
             return FALSE;
         }
    }
    return TRUE;
}


void CK_Means::InitData(int * inputdata, int a, int k)
{
    int i=0;
    N = a;
    K = k;
	if(K>N)
    {
        AfxMessageBox("Error", 0);
    }
    Center = new double[k];
    CenterIndex = new int[k];
    CenterCopy = new double[k]; 
    Top= new int[k];
    AllData = new double[N];
    Cluster = new double*[K];
   
    for(i=0;i<K;i++)
    {
        Cluster[i] = new double[N];
        Top[i]=0;
    }
    for(i=0;i<N;i++)
    {
        AllData[i] = inputdata[i];
    }
    InitCenter();    
    UpdateCluster();   
}

int ** CK_Means::ReturnData()
{
	int ** ClusterData = new int*[K];
	for(int i = 0; i < K; i++)
		ClusterData[i] = new int[N];
	for(int i = 0; i < K; i++)
		for(int j = 0; j < N; j++)
		{
			ClusterData[i][j]= Cluster[i][j];
		}
		this->Print();
	return ClusterData;
}

void CK_Means::Print()
{
	ofstream fout("result.txt", ios::out|ios::in|ios::ate);
    int i,j;
    fout << "--------------------------------------------" << endl;
    for(i=0;i<K;i++)
    {
		fout <<endl;
        fout<<"µÚ"<<i<<"ÖÐÐÄ£º"<< Center[i] << endl;
        for(j=0;j<Top[i];j++)
        {
            fout << Cluster[i][j] << " ";
        }           
    }     
}