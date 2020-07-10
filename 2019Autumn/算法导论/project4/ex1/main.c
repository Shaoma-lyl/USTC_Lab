#include <stdio.h>
#include <stdlib.h>
int min_time=999999;//�������������ʱ��
int *best_scheduler;//best_scheduler��һ�����飬��ʾ��i�������ɻ���best_scheduler[i]ִ��
int n;//��������
int k;//��������
int *time;//time��һ�����飬time[i]��ʾ�����������i����ʱ��
int *x;//x�������ڴ洢��ǰ·��

int time_scheduler(int m){//ִ����������ʱ��
    int i,max=0;
    int *machine_time;//ÿ̨���������ѵ�ʱ�䣬��������ʱ��ֵ��Ϊ�����ʱ��
    machine_time=(int *)malloc((k+1)* sizeof(int));
    for(i=1;i<=k;i++)
        machine_time[i]=0;
    for(i=1;i<=m;i++){
        machine_time[x[i]]=machine_time[x[i]]+time[i];
    }//���������i����ʱ��ӵ��������i�Ļ����Ļ���ʱ����
    for(i=1;i<=k;i++){//�ҳ���������ʱ������ֵ����Ϊ��ʱ��
        if(machine_time[i]>max)
            max=machine_time[i];
    }
    return max;
}

void Backtrack(int t){//�Ӽ����Ļ��ݷ������������ĵ�t�㣬��i��Ľ��ֵx[i]��ʾ��i�������ɻ���x[i]ִ��
    //�ɵ�t�����t+1����չ��ȷ��x[t]��ֵ
    int i;
    if(t>n){//˵���ǵ�ǰ�����Ž⣬���ýⱣ������
        min_time=time_scheduler(n);//��ǰ�����������ʱ��
        for(i=1;i<=n;i++)
            best_scheduler[i]=x[i];
    }
    else{
        for(i=1;i<=k;i++){//��ÿ�����񣬶���k�ַ��䷽��
            x[t]=i;
            if(time_scheduler(t)<min_time)//�����ǰ·����ʱ���Ѿ���������Сʱ�䣬������ǰ��
                Backtrack(t+1);//����һ����չ
        }
    }
}

int main(){
    int i;

    printf("����������������\n");
    scanf("%d",&n);
    printf("���������������\n");
    scanf("%d",&k);
    best_scheduler=(int *)malloc((n+1)* sizeof(int));
    time=(int *)malloc((n+1)* sizeof(int));
    x=(int *)malloc((n+1)* sizeof(int));
    printf("�������������ִ��ʱ�䣺\n");
    for(i=1;i<=n;i++)
        scanf("%d",&time[i]);
    printf("��������%d,��������%d\n������ʱ�䣺",n,k);
    for(i=1;i<=n;i++)
        printf("%d\t",time[i]);


    Backtrack(1);//�ӵ�һ�㿪ʼ���Ӽ��������㷨

    printf("\n���������ȣ�\n");
    printf("����\t");
    for(i=1;i<=n;i++)
        printf("%d\t",i);
    printf("\n����\t");
    for(i=1;i<=n;i++)
        printf("%d\t",best_scheduler[i]);
    printf("\n���ʱ�䣺%d",min_time);
}