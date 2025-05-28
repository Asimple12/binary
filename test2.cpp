#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<Windows.h>
#define MaxWindow 10//�������ֵ
long long primary(int a, int b, int m, unsigned long long int result) {//ֱ�ӽ���ģ�ݼ���
	result = pow(a, b);
	result = result % m;
	printf("%llu\n", result);
	return result;
}
long long binary(int a, int b, int m, long long result) {//��ͨ�Ķ�����ģ���㷨
	if (b == 0) return 1;
	result = 1;
	while (b > 0) {
		if (b & 1) result = (result * a) % m;
		a = (a * a) % m;
		b >>= 1;
	}
	printf("%lld\n", result);
	return result;
}
long long SildeWindow(int a, int b, int m, long long result) {//���������㷨
	long long num[10] = {};
	for (int p = 0; p < 10; p++) {
		num[p] = -1;
	}
	long long i = 0;
	long long t = 0;
	long long k = MaxWindow;//�������ֵ
	while (b > 0) {//��bת��Ϊ������
		num[i] = b % 2;
		b = b / 2;
		i++;
	}
	t = i;//b������λ��
	//Ԥ����
	long long G[1024] = { 0 };
	G[0] = 1; G[1] = a; G[2] = a * a;
	long long h = 0;
	h = pow(2, k - 1);
	for (int j = 3; j <= h - 1; j++) {
		G[j] = G[j - 1] * a;
	}
	result = 1;
	i = i - 1;
	while (i >= 0) {
		if (num[i] == 0) {
			result = (result * result) % m;
			i = i - 1;//�����ȡ����Ϊ������Ķ�����Ϊ����
		}
		else {
			long long B[MaxWindow] = { -1,-1,};
			for (int p = 0; p < MaxWindow; p++) {
				B[p] = -1;
			}
			long long f = 0;
			int flag = 0;//����Ƿ��ȡ��1���߶�ȡ����
			for (int w = i; w >= 0 && f <= MaxWindow - 1 && flag < 2; w--) {//����1���ߵ��ڴ������ֵ�����޶�����ʱֹͣ
				B[f] = num[w];
				if (num[w] == 1)flag++;//��ȡ������1��flagΪ2
				f++;
			}
			long long l = f;//��ǰ��ȡ���г���
			f = f - 1;
			long long E = 0;
			while (f >= 0) {
				E = E * 2 + B[f];
				f--;
			}
			result = pow(result, (pow(2, l)));
			result = result % m;
			result *= G[E];
			result = result % m;
			i -= l;
		}
	}
	printf("%lld\n", result);
	return result;
}
int main() {
	int a1 = 6;
	int b1 = 25;
	int m1 = 13;
	long long result1 = 0;
	LARGE_INTEGER start_time, end_time, freq;
	double elapsed_time1, elapsed_time2, elapsed_time3;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);

	primary(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time1 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("����ִ��ʱ�䣺%.9fs\n", elapsed_time1);


	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);


	binary(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time2 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("����ִ��ʱ�䣺%.9fs\n", elapsed_time2);


	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);


	SildeWindow(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time3 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("����ִ��ʱ�䣺%.9fs\n", elapsed_time3);

	return 0;
}
