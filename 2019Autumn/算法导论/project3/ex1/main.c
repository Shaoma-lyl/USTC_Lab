#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *s1;
char *s2;
int **c;//c��һ����ά���飬�洢LCS�ĳ���
int **b;//b��һ����ά���飬�洢����cʱ��ѡ�������������Ž�
int m;//s1�ĳ���
int n;//s2�ĳ���

void Generate_Str(char *s,int len){
    s[0]='0';
    s[len]='\0';
    int flag;
    for(int i=1;i<len;i++){
        flag=rand()%3;
        if(flag==0){
            s[i] = rand()%26 +'a';
        }
        else if(flag==1){
            s[i] = rand()%26 +'A';
        }
        else{
            s[i] = rand()%10 +'0';
        }
    }
}
int LCS_LENGTH(){//�Ե����ϼ���LCS�ĳ��ȣ�����b��������������Ž�
    int i,j;
    for(i=1;i<=m;i++)//��ʼ��
        c[i][0]=0;
    for(j=0;j<=n;j++)
        c[0][j]=0;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++){
            if(s1[i]==s2[j]){//��s1 s2����ַ���ͬ���������ַ�������LCS��һ���ַ���LCS���ȼ�1
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=0;//Z(k-1)��s1(i-1) s2(j-1)��LCS
            }
            else if(c[i-1][j]>=c[i][j-1]){//��s1(i-1) s2(j)��LCS����s1(i) s2(j-1)
                c[i][j]=c[i-1][j];
                b[i][j]=1;//��¼Z��s1(i-1) s2(j)��LCS
            }
            else{
                c[i][j]=c[i][j-1];
                b[i][j]=2;
            }
        }
    return 1;

}
void PRINT_LCS(int i,int j){
    if(i==0||j==0)
        return ;
    if(b[i][j]==0){
        PRINT_LCS(i-1,j-1);
        printf("%c",s1[i]);
    }
    else if(b[i][j]==1)
        PRINT_LCS(i-1,j);
    else
        PRINT_LCS(i,j-1);
    return ;
}

int main() {
    int i;
    printf("Please input the length of s1:\nm=");
    scanf("%d",&m);
    printf("Please input the length of s2:\nn=");
    scanf("%d",&n);
    s1=(char *)malloc((m+2)*sizeof(char));
    s2=(char *)malloc((n+2)* sizeof(char));
    srand(time(NULL));
    Generate_Str(s1,m+1);
    Generate_Str(s2,n+1);
    printf("s1:\n%s\n",s1+1);
    printf("s2:\n%s\n",s2+1);
    c=(int **)malloc((m+1)*sizeof(int *));
    for(i=0;i<m+1;i++)
        c[i]=(int *)malloc((n+1)* sizeof(int));
    b=(int **)malloc((m+1)*sizeof(int *));
    for(i=0;i<m+1;i++)
        b[i]=(int *)malloc((n+1)* sizeof(int));
    printf("LSC:\n");
    LCS_LENGTH();
    PRINT_LCS(m,n);
}