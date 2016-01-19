
#include "queue.h"

#pragma once
 
class CConnectComponentLabel
{
public:
	CConnectComponentLabel(void);
	~CConnectComponentLabel(void);
	void PushQueue(Queue *, int );
	int PopQueue(Queue *);
	void SearchNeighbor(unsigned char *, int ,int , int *, int , int , Queue *);
	int ConnectedComponentLabeling(unsigned char*, int ,int , int *);
};