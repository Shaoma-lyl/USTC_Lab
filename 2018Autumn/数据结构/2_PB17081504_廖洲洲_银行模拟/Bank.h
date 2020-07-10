#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<process.h>

#define OK 1
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<process.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0


typedef struct QElemType { 	//�˿�
	int ArriveTime;			//����ʱ��
	int Duration;			//����ҵ������ʱ��
	struct QElemType *next;
}QElemType;

typedef struct {        //���д���
	QElemType *head;
	QElemType *tail;
}LinkQueue;

typedef struct Event {    //�¼�
	int OccurTime;       //�¼�����ʱ��
	int NType;          //�¼����ͣ�0��ʾ�����¼���1��4��ʾ�ô��ڵĹ˿��뿪
	struct Event *next;
}Event, ElemType;

typedef struct EventList {       //�¼���
	ElemType *head;
	ElemType *tail;
}EventList;




Event NewEvent(int occurT, int nType);
//����OccurTime��NTypeֵ���������¼�
int InitList(EventList *L);
//��ʼ���¼�����
int OrderInsert(EventList *L, Event e);
//���¼�e������ʱ��˳�������������L��
int ListEmpty(EventList *L);
//�ж�����L�Ƿ�Ϊ�գ�Ϊ�շ���TRUE�����򷵻�FALSE
int DelFirst(EventList *L, ElemType *e);
//����L��Ϊ�գ�ɾ�����׽�㣬��e���أ�������OK�����򷵻�ERROR
int ListTraverse(EventList *L);
//��������
int InitQueue(LinkQueue *Q);
//��ʼ������Q
int EmptyQueue(LinkQueue *Q);
//������QΪ�գ�����TRUE�����򷵻�FALSE
int DelQueue(LinkQueue *Q, QElemType *e);
//������Q��Ϊ�գ��׽����ӣ���e���أ�������OK�����򷵻�ERROR
int EnQueue(LinkQueue *Q, QElemType e);
//���e���Q
int Length(LinkQueue Q);
//���ض���Q�ĳ��ȣ���Ԫ�ظ���
int GetHead(LinkQueue *Q, QElemType *e);
//������Q��Ϊ�գ���e�������׽�㣬������OK,���򷵻�ERROR
int QueueTraverse(LinkQueue *Q);
//��������Q


int Min(int a[], int n);
//���س���Ϊn������a��һ����Сֵ���±꣬��1��ʼ
int ShortestQueue();
//��ȡ��̶��еı��
void OpenForDay();
//��ʼ������
void Arrive();
//�˿ʹﵽ�¼�
void Leave();
//�˿��뿪�¼�
void PrintEventList();
//����¼�����
void PrintQueue();
//��ӡ��ǰ����
//----ȫ�ֱ���-----//
EventList ev;
Event en;
LinkQueue q[5];
QElemType customer;
int TotalTime, Num;
int CloseTime;//�ر�ʱ�䣬��Ӫҵʱ�䳤��


