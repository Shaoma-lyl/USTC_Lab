#include <stdio.h>
#include <stdlib.h>
int MAX=999999999;
int *row;//稀疏矩阵的行偏移数组，row[i]表示第i行第一个元素在非0元素中的偏移量，则row[i+1]-row[i]为该行中的非0数
int *column;//对矩阵中的非0元素从左往右从上往下记录其列位置，colum[row[i]]即第i行第一个非0元素的列位置
// 我们的偏移量都是从0开始计算的
//由于我们只有两个点之间是否有边的信息，故矩阵非0即1，则不用存储值数组了
int *adj;//存储一个节点的相邻节点
int r=-1;//记录矩阵的最大行列号(从0计），即row矩阵的大小减2
int edge=-1;//记录矩阵的最大边号(从0计），即column矩阵的大小减1
struct node{
    int color;//白色0，灰色1 3，黑色2 4
    int d;
    int pi;
};
struct QNode{
    int data;
    struct QNode *next;
};//队列节点
struct QueueLink{
    struct QNode *front;
    struct QNode *rear;
};
struct QueueLink *Q1,*Q2;//队列
struct node *G;//节点数组，存储每个节点的相关信息
void creat_CSR(){//处理上三角矩阵
    row=(int *)malloc(100* sizeof(int));//初始化100，以后动态增加
    column=(int *)malloc(500* sizeof(int));//初始化500，以后动态增加
    int u,v,oldu=0;int i;
    row[0]=0;
    FILE *fp;
    if((fp=fopen("E:\\alg project\\project5\\facebook_combined.txt","r"))==NULL){
        printf("Cannot open this file!");
        exit(0);
    }
    while(feof(fp)==0){//当文件记录指针未到文件结尾
        fscanf(fp,"%d%d",&u,&v);
        //printf("%d %d\n",u,v);
        if(v>r)//保存最大列数，即行数
            r=v;
        if((r+2)> sizeof(row)){//所需空间不足，扩充加100
            row=(int *)realloc(row,(r+2+100)* sizeof(int));
        }
        edge++;
        //printf("@%d@",edge);
        if((edge+1)> sizeof(column)){
            column=(int *)realloc(column,(edge+1+200)*sizeof(int));
        }
        column[edge]=v;
        if(u!=oldu){//若u更新了,更新偏移量，因为是第一次输入u，故该(u,v)对的偏移量edge就是该行第一个非0元素的偏移量
            row[u]=edge;
            for(i=u-1;i>oldu;i--)//如果有行i的元素都是0，则row[i+1]-row[i]=0,即row[i]=row[i+1]
                row[i]=row[i+1];
        }
        oldu=u;
    }
    row[r+1]=edge+1;//最后在矩阵末尾补上矩阵元素总数
    for(i=r;i>u;i--){//最后没有元素的行偏移为矩阵元素总数
        row[i]=row[r+1];
    }
    adj=(int *)malloc((r+1)* sizeof(int));//r+1位存储了其相邻节点个数
   // printf("row offsets:");
    /*for(i=0;i<=r+1;i++){
        printf("%d ",row[i]);
    }
    printf("\ncolumn indices:");
    for(i=0;i<=edge;i++){
        printf("%d ",column[i]);
    }*/

}
int search_CSR(int u,int v){//在压缩矩阵中查找(u,v),若存在边，返回1，不存在返回0
    if(u==v)
        return 0;
    int tmp,i;
    if(u>v){
        tmp=u;
        u=v;
        v=tmp;
    }//令u始终大于v
    if(v>column[row[u+1]-1])
        return 0;//如果比该行最后一个非0元素列号都大，说明不存在，减少比较次数
    for(i=row[u];i<row[u+1];i++){//在该行非0元素间查询，若有相同的列索引，说明存在该非零矩阵元素
        if(column[i]==v)
            return 1;
        if(column[i]>v)
            return 0;//由于对于该行非0元素列索引来说，其是递增的
        // 当当前的索引号都比v大，则后面的也比v大，故无该元素
    }
    return 0;
}

void Adj(int s){//s点求与其相邻的点
    int i,j;
    adj[r+1]=row[s+1]-row[s];
    for(i=0;i<adj[r+1];i++)
        adj[i]=column[row[s]+i];//这只能求出上三角的相邻边
    for(j=0;j<=s;j++){//对下三角
        if(search_CSR(s,j)){
            adj[r+1]=adj[r+1]+1;
            adj[i]=j;
            //printf("*%d*",j);
            i++;
        }
    }
}

int InitQueue(struct QueueLink *Q){
    Q->front=Q->rear=(struct QNode*)malloc(sizeof(struct QNode));
    if(!Q->front)
        exit(0);
    Q->front->next=NULL;
    return 1;
}
int EnQueue(struct QueueLink *Q,int e){
    struct QNode *p;
    p=(struct QNode*)malloc(sizeof(struct QNode));
    p->data=e;
    p->next=NULL;
    Q->rear->next=p;
    Q->rear=p;
    return 1;
}
int DeQueue(struct QueueLink *Q){//从列表从出队
    if(Q->rear==Q->front)
        exit(0);
    struct QNode *p;
    p=Q->front->next;
    int e=p->data;
    Q->front->next=p->next;
    if(Q->rear==p)
        Q->rear=Q->front;
    free(p);
    return e;
}
int EmptyQueue(struct QueueLink *Q){
    if(Q->front==Q->rear)
        return 1;
    return 0;
}

int BFS2(int s,int f,int *m,int *n){//以s为源，f为终点进行双向广度优先搜索,返回两节点距离，和交界点节点
    int i,u,v,min=MAX,flag=0;
    G=(struct node *)malloc((r+1)* sizeof(struct node));
    Q1=(struct QueueLink*)malloc(sizeof(struct QueueLink));
    Q2=(struct QueueLink*)malloc(sizeof(struct QueueLink));
    for(i=0;i<=r;i++){
        G[i].color=0;//0为白色，1、3分别为队列1、2的灰色，2、4分别为队列1、2的黑色
        G[i].d=MAX;
        G[i].pi=-1;
    }
    G[s].color=1;G[f].color=3;
    G[s].d=0;G[f].d=0;
    G[s].pi=-1;G[f].pi=-1;
    InitQueue(Q1);//构造队列
    InitQueue(Q2);
    EnQueue(Q1,s);
    EnQueue(Q2,f);
    while(!EmptyQueue(Q1) || !EmptyQueue(Q2)){//当队列不空
        if(!EmptyQueue(Q1)) {
            //printf("@Q1@");
            u = DeQueue(Q1);
            Adj(u);//找出u的相邻点
            for (i = 0; i < adj[r + 1]; i++) {//对每个相邻点进行检测
                v = adj[i];
                if (G[v].color == 0) {//未被发现
                    G[v].color = 1;//已发现但未处理
                    G[v].d = G[u].d + 1;
                    G[v].pi = u;
                    EnQueue(Q1, v);
                   // printf("Q1En");
                }
                else if(G[v].color==3||G[v].color==4){//v节点被队列2发现过，相交了，该输出
                    //由于两个队列间的交界面可能有多个节点（如教材上图的（0->7)，故需要在该交界面上取最小的路径
                    flag=1;
                    if(G[u].d+G[v].d+1<min){
                        min=G[u].d+G[v].d+1;
                        *m=u;*n=v;
                    }
                }
            }
            if(flag)
                return min;
            G[u].color = 2;//处理结束
        }
        if(!EmptyQueue(Q2)) {
            //printf("@Q2@");
            u = DeQueue(Q2);
            Adj(u);//找出u的相邻点
           // printf("Q2(%d,%d)",u,adj[r+1]);
            for (i = 0; i < adj[r + 1]; i++) {//对每个相邻点进行检测
                v = adj[i];
                if (G[v].color == 0) {//未被发现
                    G[v].color = 3;//已发现但未处理
                    G[v].d = G[u].d + 1;
                    G[v].pi = u;
                    EnQueue(Q2, v);
                   // printf("Q1En");
                }
                else if(G[v].color==1||G[v].color==2){//v节点被队列2发现过，相交了，输出
                    flag=1;
                    if(G[u].d+G[v].d+1<min){
                        min=G[u].d+G[v].d+1;
                        *m=v;*n=u;
                    }
                }
            }
            if(flag)
                return min;
            G[u].color = 4;//处理结束
        }
    }
    return 0;
}
void print(int m){
    if(m==-1)
        return;
    print(G[m].pi);
    printf("%d->",m);
}
int main() {
    int i,j,s,f,m,n,d;
    printf("Inputting from file.... \n");
    creat_CSR();
    /*for(i=0;i<=r;i++){
        printf("\n");
        for(j=0;j<=r;j++)
            printf("%d ",search_CSR(i,j));
    }*/
    printf("Please input two nodes:");
    scanf("%d %d",&s,&f);
    d=BFS2(s,f,&m,&n);
    //for(i=0;i<=r;i++){
    //    printf("node%d:d=%d,pi=%d\n",i,G[i].d,G[i].pi);
    //}
    printf("Distance:%d\n",d);
    print(m);
    do{
        if(n==f)
            printf("%d",n);
        else
            printf("%d->",n);
        n=G[n].pi;
    }while (n!=-1);
}
