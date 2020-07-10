#include"mpi.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CarNum 1000000
#define Cycle 300
#define v_max 15
#define p 0.4

struct car
{
	int v;//��ǰ�ٶ�
	int x;//��ǰ��ͷλ��
};

int carMove(car * thisCar, int preCarX,int carNum) {
	if (carNum == 0 && thisCar->v<v_max) {
		//��һ����d=������ٶȼ�һ
		thisCar->v += 1;
	}
	else if (carNum>0) {
		int d = preCarX - thisCar->x - 1;
		if (d > thisCar->v&&thisCar->v<v_max) {
			//d>v���ٶȼ�1 
			thisCar->v += 1;
		}
		else {
			//d<=v���ٶȽ���d
			thisCar->v = d;
		}
	}
	double newp = rand() / (RAND_MAX + 1.0);
	if (newp <= p&&thisCar->v >= 1) {
		thisCar->v = thisCar->v - 1;
	}
	thisCar->x += thisCar->v;
	return 1;
}

int main(int argc, char ** argv) {
	int i, j;
	double startTime, endTime;
	int rank, size,partition;
	car* carList;
	int preCarX;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	partition = CarNum / size;
	carList = (car *)malloc(sizeof(car)*(partition));
	startTime = MPI_Wtime();
	srand(time(NULL));
	MPI_Status status;
	for (i = 0; i < partition; i++) {
		carList[i].v = 0;
		carList[i].x = CarNum - (rank*partition + i);
	}
	//��ʼʱ��һ������ǰ��λ��
	preCarX = CarNum - (rank*partition - 1);
	for (j = 0; j < Cycle; j++) {
		if (j > 0&&rank>=1) {
			//���յ�һ��������һ������λ��
			MPI_Recv(&preCarX, 1, MPI_INT, rank - 1, (j-1) * 10 + rank-1, MPI_COMM_WORLD, &status);
		}
		for (i = partition-1; i >= 0; i--) {
			//���˶�
			if (i == 0) {
				carMove(&carList[i], preCarX, rank*partition + i);
			}
			else {
				carMove(&carList[i], carList[i - 1].x,rank*partition + i);
			}
		}
		if (rank < size - 1) {
			//����һ�����̷������һ������λ��
			MPI_Send(&(carList[partition - 1].x), 1, MPI_INT, rank + 1, j * 10 + rank, MPI_COMM_WORLD);
		}
	}
	endTime = MPI_Wtime();
	if (rank == 0) {
		printf("����ʱ�䣺%f\n", endTime - startTime);
	}
	MPI_Finalize();
	return 0;
}