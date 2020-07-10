#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>

#define N 256				//С�����
#define G 6.67e-11			//������������
#define M 10000				//С������
#define Cycle 500000			//�ܵ���������ÿ����ʱ��=TotalTime/Cycle
#define CycleTime 0.01		//ÿ���ڵ�ʱ��

struct ball {
	double ax, ay;			//���ٶ�
	double vx, vy;			//�ٶ�
	double px, py;			//λ��
};

void compute_force(int index, ball *ballList) {
	//������Ϊindex��С�����ܵ��ļ��ٶ�
	//��ʼ�����ٶ�Ϊ0���ٱ�������С�򣬼����µļ��ٶ�
	double px, py;
	double dx, dy,d;
	px = ballList[index].px;
	py = ballList[index].py;
	ballList[index].ax = 0;
	ballList[index].ay = 0;
	for (int i = 0; i < N; i++) {
		if (i != index) {
			dx = ballList[i].px - px;
			dy = ballList[i].py - py;
			d = sqrt(dx*dx + dy*dy);
			if (d < 0.001) {
				//�����������С��ʹ��1cm��Ϊ�������
				d = 0.001;
				dx = 0.001*dx / d;
				dy = 0.001*dy / d;
			}
			ballList[index].ax += G*M*dx / (d*d*d);
			ballList[index].ay += G*M*dy / (d*d*d);
		}
	}
}

void compute_velocities(int index, ball * ballList) {
	//����ÿ��С����ٶ�
	ballList[index].vx += ballList[index].ax*CycleTime;
	ballList[index].vy += ballList[index].ay*CycleTime;
}

void compute_positions(int index, ball * ballList) {
	//����ÿ��С���λ��
	double oldVx, oldVy;
	//����ɵ��ٶ�ֵ
	oldVx = ballList[index].vx;
	oldVy = ballList[index].vy;
	compute_velocities(index, ballList);
	ballList[index].px += (oldVx + ballList[index].vx)*CycleTime / 2.0;
	ballList[index].py += (oldVy + ballList[index].vy)*CycleTime / 2.0;
}


int main(int argc, char ** argv) {
	ball ballList[N];
	int i, j;
	int rank, size,partition,low,high;
	double startTime, endTime;
	
	//��ʼ��С��
	int temp = int(sqrt(N));
	int index;
	for (i = 0; i < temp; i++) {
		for (j = 0; j < temp; j++) {
			index = i*temp + j;
			ballList[index].px = j*0.01;
			ballList[index].py = i*0.01;
			ballList[index].ax = 0;
			ballList[index].ay = 0;
			ballList[index].vx = 0;
			ballList[index].vy = 0;
		}
	}
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	startTime = MPI_Wtime();
	//ÿ�����ڼ���С���λ�ã����ڽ���ʱ���������̹㲥�����̸����С��λ��
	partition = N / size;//�����С�����
	low = rank*partition;//�����С�����С���
	high = (rank + 1)*partition - 1;//�����С��������
	//printf("$$$$$$$$$$$$$$\n");
	//for (j = 0; j < N; j++) {
	//	printf("rank %d,ball %d,(%f,%f)\n", rank, j, ballList[j].px, ballList[j].py);
	//}
	//printf("$$$$$$$$$$$$$$\n");
	for (i = 0; i < Cycle; i++) {
		for (j = low; j <= high; j++) {
			//���ȸ��¸���С���ڵ�ǰλ���ܵ���������������ٶ�
			compute_force(j, ballList);
		}
		for (j = low; j <= high; j++) {
			//���������С���µ�λ��
			compute_positions(j, ballList);
		}
		//ÿ�����̹㲥�Լ������С����Ϣ��ʵ��������ͬ��
		//printf("#############\n");
		//for (j = 0; j < N; j++) {
		//	printf("rank %d,ball %d,(%f,%f)\n", rank, j, ballList[j].px, ballList[j].py);
		//}
		//printf("#############\n");
		for (j = 0; j < size; j++) {
			//ÿ�����̹㲥�Լ������С����Ϣ��ʵ��������ͬ��
			MPI_Bcast(&ballList[j*partition], sizeof(ball)*partition, MPI_BYTE, j, MPI_COMM_WORLD);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
	//printf("***************\n");
	//for (j = 0; j < N; j++) {
	//	printf("rank %d,ball %d,(%f,%f)\n", rank, j, ballList[j].px, ballList[j].py);
	//}
	//printf("***************\n");
	endTime = MPI_Wtime();
	if (rank == 0) {
		printf("����ʱ��:%f\n", endTime - startTime);
		/*printf("������λ��\n");
		for (i = 0; i < temp; i++) {
			for (j = 0; j < temp; j++) {
				index = i*temp + j;
				printf("\t(%.2f,%.2f)", ballList[index].px, ballList[index].py);
			}
			printf("\n");
		}*/
	}
	MPI_Finalize();
	return 0;
}