#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<Windows.h>
#define MaxWindow 10//窗口最大值
long long primary(int a, int b, int m, unsigned long long int result) {//直接进行模幂计算
	result = pow(a, b);
	result = result % m;
	printf("%llu\n", result);
	return result;
}
long long binary(int a, int b, int m, long long result) {//普通的二进制模幂算法
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
long long SildeWindow(int a, int b, int m, long long result) {//滑动窗口算法
	long long num[10] = {};
	for (int p = 0; p < 10; p++) {
		num[p] = -1;
	}
	long long i = 0;
	long long t = 0;
	long long k = MaxWindow;//窗口最大值
	while (b > 0) {//将b转化为二进制
		num[i] = b % 2;
		b = b / 2;
		i++;
	}
	t = i;//b二进制位数
	//预计算
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
			i = i - 1;//倒序读取，因为数组里的二进制为倒序
		}
		else {
			long long B[MaxWindow] = { -1,-1,};
			for (int p = 0; p < MaxWindow; p++) {
				B[p] = -1;
			}
			long long f = 0;
			int flag = 0;//标记是否读取到1或者读取结束
			for (int w = i; w >= 0 && f <= MaxWindow - 1 && flag < 2; w--) {//读到1或者等于窗口最大值或者无二进制时停止
				B[f] = num[w];
				if (num[w] == 1)flag++;//读取到两次1，flag为2
				f++;
			}
			long long l = f;//当前截取序列长度
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
	printf("函数执行时间：%.9fs\n", elapsed_time1);


	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);


	binary(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time2 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("函数执行时间：%.9fs\n", elapsed_time2);


	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_time);


	SildeWindow(a1, b1, m1, result1);

	QueryPerformanceCounter(&end_time);
	elapsed_time3 = (end_time.QuadPart - start_time.QuadPart) / (double)freq.QuadPart;
	printf("函数执行时间：%.9fs\n", elapsed_time3);

	return 0;
}
