#ifndef QUEUE_H
#define  QUEUE_H

typedef struct QNode
{
	int data;
	struct QNode *next;
}QNode;

typedef struct Queue
{
	struct QNode* first;
	struct QNode* last;
}Queue;

#endif