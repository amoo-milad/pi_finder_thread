// pi_finder_thread.cpp :  Estimates the Pi number.

#include "stdafx.h"
#include <conio.h>
#include <windows.h>

#define BATCH_SIZE	 10000000

double random();
DWORD WINAPI MyThreadFunc(LPVOID lpParameter);

struct ThreadParams 
{
	long long inCircle;
	int seed;
};

int main()
{
	ThreadParams tp1, tp2, tp3, tp4;
	//the initializing of "tpn.inCircle = 0;" are not necessary because they're gonna be written (and not read) in the Func. 

	tp1.seed = 1;
	tp2.seed = 2;
	tp3.seed = 3;
	tp4.seed = 4;

	DWORD thread_id1 = 0;
	HANDLE h1 = CreateThread(NULL, 0, &MyThreadFunc, &tp1, 0, &thread_id1);
	HANDLE h2 = CreateThread(NULL, 0, &MyThreadFunc, &tp2, 0, NULL);
	HANDLE h3 = CreateThread(NULL, 0, &MyThreadFunc, &tp3, 0, NULL);
	HANDLE h4 = CreateThread(NULL, 0, &MyThreadFunc, &tp4, 0, NULL);

	//WaitForSingleObject(h1, INFINITE);
	//WaitForSingleObject(h2, INFINITE); // and like this for all the 4 threads...

	HANDLE handles[] = {h1, h2, h3, h4};
	WaitForMultipleObjects(4, handles, TRUE, INFINITE);

	long long sum = ((long long) tp1.inCircle) + tp2.inCircle + tp3.inCircle + tp4.inCircle;
	printf("\nthe sum of all inCircles is %lld\n", sum);

	double estimateForPi = 4 * ((double) sum / BATCH_SIZE);
	printf("\ntherefore the 'estimate For Pi' is %lf\n", estimateForPi);

	_getch();
	return 0;           
}

double random()
{
	return (double)rand() / (double)((unsigned)RAND_MAX + 1);
	// rand functions need either #include <stdlib.h>  or #include <windows.h>
}

DWORD WINAPI MyThreadFunc(LPVOID lpParameter)
{
	ThreadParams* tp = (ThreadParams*) lpParameter; 

	long long inCircleCount = 0;                        

	srand(tp->seed);

	for (int i = 0; i < BATCH_SIZE / 4 ; i++) 
	{
		double x = random();
		double y = random();
		if (x*x + y*y <= 1.0)
			inCircleCount++;
	}
	
	tp->inCircle = inCircleCount;
	printf(" number of inCircles: %lld for seed %d\n", inCircleCount, tp->seed);
	printf("thread finished\n");
	return 0;
}
