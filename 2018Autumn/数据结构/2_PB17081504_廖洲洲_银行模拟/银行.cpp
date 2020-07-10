#include"Bank.h"

int main()
{
	printf("����������ģ��ʱ�䣺\n");
	scanf("%d",&CloseTime);
	//�����Ŷ�ģ��
    OpenForDay();
    srand((unsigned)time(NULL));
    while(!ListEmpty(&ev)){
        DelFirst(&ev,&en);
        printf("**********�¼�**********\n");
        if(en.NType==0)
            Arrive();
        else
            Leave();
        PrintQueue();
        PrintEventList();
    }
    printf("\n�˿Ͷ�����ʱ����ʱ��: %d min,�˿�ƽ������ʱ��: %g min.\n",TotalTime,(float)TotalTime/Num);
	system("pause");
}


void OpenForDay(){
    //��ʼ������
    int i;
    TotalTime=0;    Num=0;
    InitList(&ev);//��ʼ���¼�����
    en.OccurTime=0;
    en.NType=0;
    OrderInsert(&ev,en);
    for(i=1;i<=4;i++)
        InitQueue(&q[i]);//��ʼ���ĸ����ڶ���
}//OpenForDay

void Arrive(){
    //�˿͵����¼�
    int durtime,Nexttime,i,t;
    QElemType e;
    Num++;
    Nexttime=rand()%5+1;   //���ʱ����5������
    durtime=rand()%30+1;    //����ҵ��ʱ����30������
    t=en.OccurTime+Nexttime;
    if( en.OccurTime<CloseTime){//������δ����
        printf("�˿͵���ʱ��:%d,�ù˿Ͱ���ҵ������ʱ��:%d,��һλ�˿͵���ʱ����:%d|\n",en.OccurTime,durtime,Nexttime);//��һλ�˿ʹﵽʱ��
        OrderInsert(&ev,NewEvent(t,0));
        i=ShortestQueue();//��̶���
        e.ArriveTime=en.OccurTime;
        e.Duration=durtime;
        EnQueue(&q[i],e);
        if(Length(q[i])==1)
            OrderInsert(&ev,NewEvent(en.OccurTime+durtime,i));
    }else{
        printf("һλ�˿͵���:%d�������в��ٽ���ҵ������ˣ�\n",en.OccurTime);
        Num--;
    }
}

void Leave(){
    //�˿��뿪�¼�
    int i=en.NType;
    DelQueue(&q[i],&customer);
    printf("һλ�˿��뿪������ʱ��:%d\n",en.OccurTime);//����˿��뿪ʱ��
    TotalTime+=en.OccurTime-customer.ArriveTime;
    if(!EmptyQueue(&q[i])){
        GetHead(&q[i],&customer);
        OrderInsert(&ev,NewEvent(en.OccurTime+customer.Duration,i));
    }
}





void PrintQueue(){
    //��ӡ��ǰ����
    int i;
    for(i=1;i<=4;i++){
        printf("���� %d �� %d ���˿�:",i,Length(q[i]));
        QueueTraverse(&q[i]);
    }
    printf("\n");
}

void PrintEventList(){
    //����¼�����
    printf("�¼���:(ʱ��,����)\n");
    ListTraverse(&ev);
}
int Min(int a[],int n){
    //���س���Ϊn������a��һ����Сֵ���±꣬��0��ʼ
    int i,tmp,ind=0;
    tmp=a[0];
    for(i=1;i<n;i++){
        if(a[i]<tmp){
            tmp=a[i];
            ind=i;
        }
    }
    return ind;
}

int ShortestQueue(){
    //��ȡ��̶��еı��
    int i,a[4];
    for(i=1;i<=4;i++){
        a[i-1]=Length(q[i]);
        //printf("��%d�ĳ���Ϊ%d\n",i,Length(q[i]));
    }
    return Min(a,4)+1;//���д�1��ʼ���
}




int OrderInsert(EventList *L,Event e){
    //���¼�e������ʱ��˳�������������L��
    ElemType *p,*q,*n;
    n=(ElemType *)malloc(sizeof(ElemType));
    if(!n){
        printf("����ռ�ʧ��\n");
        exit(0);
    }
    *n=e;
    if(TRUE==ListEmpty(L)){//����Ϊ��
       L->head->next=n;
       L->tail=n;
       n->next=NULL;
       return OK;
    }
    q=L->head;
    p=L->head->next;
    while(p){//������������
        if(p->OccurTime>=n->OccurTime)
            break;
        q=p;
        p=p->next;
    }
    q->next=n;
    n->next=p;
    if(!p)//����λ��Ϊ����β��
        L->tail=n;
    return OK;
}

int ListEmpty(EventList *L){
    //�ж�����L�Ƿ�Ϊ�գ�Ϊ�շ���TRUE�����򷵻�FALSE
    if((L->head==L->tail)&&(L->head!=NULL))
        return TRUE;
    else
        return FALSE;
}

int DelFirst(EventList *L,ElemType *e){
    //����L��Ϊ�գ�ɾ�����׽�㣬��e���أ�������OK�����򷵻�ERROR
    ElemType *p=L->head->next;
    if(!p)
        return ERROR;
    L->head->next=p->next;
    *e=*p;
    free(p);
    if(L->head->next==NULL)
        L->tail=L->head;
    return OK;
}

int ListTraverse(EventList *L){
    //��������
    Event *p=L->head->next;
    if(!p){
        printf("�¼���Ϊ�գ�\n");
        return ERROR;
    }
   
    while(p!=NULL){
    
        printf("(%d,%d)\n",p->OccurTime,p->NType);
        p=p->next;
       
   		 }

    printf("\n");
    return OK;
}

int InitQueue(LinkQueue *Q){
    //��ʼ������Q
    Q->head=Q->tail=(QElemType *)malloc(sizeof(QElemType));
    if(!Q->head){
        printf("����ռ�ʧ��\n");
        exit(0);
    }
    Q->head->next=NULL;
    return OK;
}



int Length(LinkQueue Q){
    //���ض���Q�ĳ��ȣ���Ԫ�ظ���
    int count=0;
    QElemType *p=Q.head->next;
    while(p){
        p=p->next;
        count++;
    }
    return count;
}

int GetHead(LinkQueue *Q,QElemType *e){
    //������Q��Ϊ�գ���e�������׽�㣬������OK,���򷵻�ERROR
    if(EmptyQueue(Q))
        return ERROR;
    *e=*(Q->head->next);
        return OK;
}

int DelQueue(LinkQueue *Q,QElemType *e){
    //������Q��Ϊ�գ��׽����ӣ���e���أ�������OK�����򷵻�ERROR
    QElemType *p=Q->head->next;
    if(!p)
        return ERROR;
    *e=*p;
    Q->head->next=p->next;//��������ָ��
    free(p);
    if(!Q->head->next)//�ӿ�
        Q->tail=Q->head;
    return OK;
}


int QueueTraverse(LinkQueue *Q){
    //��������Q
    QElemType *p=Q->head->next;
    if(!p){
        printf("--��.\n");
        return ERROR;
    }
    while(p){
        printf("(%d,%d) ",p->ArriveTime,p->Duration);
        p=p->next;
    }
    printf("\n");
    return OK;
}
int EmptyQueue(LinkQueue *Q){
    //������QΪ�գ�����TRUE�����򷵻�FALSE
    if(Q->head==Q->tail&&Q->head!=NULL)
        return TRUE;
    else
        return FALSE;
}
int EnQueue(LinkQueue *Q,QElemType e){
    //���e���Q
    QElemType *p=(QElemType *)malloc(sizeof(QElemType));
    if(!p){
        printf("����ռ�ʧ��\n");
        exit(0);
    }
    *p=e;
    p->next=NULL;
    Q->tail->next=p;//�����β
    Q->tail=p;//�޸Ķ�βָ��
    return OK;
}
Event NewEvent(int occurT,int nType){
    //����OccurTime��NTypeֵ���������¼�
    Event e;
    e.OccurTime=occurT;
    e.NType=nType;
    return e;
}

int InitList(EventList *L){
    //��ʼ���¼�����
    L->head=L->tail=(ElemType *)malloc(sizeof(ElemType));
    if(!L->head){
        printf("����ռ�ʧ��\n");
        exit(0);
    }
    L->head->next=NULL;
    return OK;
}
