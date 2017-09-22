// pi_finder_thread.cpp	   ->   estimates the Pi number.

#include "stdafx.h"
#include <conio.h>
#include <windows.h>
#include <time.h>

double random()
{
	//srand(time(NULL)); // no good when their time is the same
	return (double)rand() / (double)((unsigned)RAND_MAX + 1);
	// needs #include <stdlib.h>  or #include <windows.h>
}

//#define BATCH_SIZE 1000000000	// takes time, about 60 secs.
#define BATCH_SIZE	 10000000

struct ThreadParams 
{
	long int inCircle;
};

DWORD WINAPI MyThreadFunc(LPVOID lpParameter)
{
	ThreadParams* tp = (ThreadParams*) lpParameter; 

	long int inCircleCount = 0;                        

	for (int i = 0; i < BATCH_SIZE / 4 ; i++) 
	{
		double x = random();
		double y = random();
		if (x*x + y*y < 1)
			inCircleCount++;
	}
	
	tp->inCircle = inCircleCount;
	printf(" number of inCircles: %ld\n", inCircleCount);
	printf("thread finished\n");
	return 0;
}

int main()
{
	ThreadParams tp1, tp2, tp3, tp4;

	tp1.inCircle = 0;
	tp2.inCircle = 0;
	tp3.inCircle = 0;
	tp4.inCircle = 0;

	CreateThread(NULL, 0, &MyThreadFunc, &tp1, 0, NULL);
	CreateThread(NULL, 0, &MyThreadFunc, &tp2, 0, NULL);
	CreateThread(NULL, 0, &MyThreadFunc, &tp3, 0, NULL);
	CreateThread(NULL, 0, &MyThreadFunc, &tp4, 0, NULL);

	_getch(); 
	//// instead of '_getch();' we can also use a bigger time_consuming process, the joker:
	//long int joker = 0;
	//for (int i = 0; i < BATCH_SIZE ; i++) 
	//{
	//	double x = random();
	//	double y = random();
	//	if (x*x + y*y < 1)
	//		joker++;
	//}
	//printf("\nthe Joker is %ld\n", joker); // indicates that probably the other four processes has already finished!

	long long int sum = (long long int) tp1.inCircle + tp2.inCircle + tp3.inCircle + tp4.inCircle;
	printf("\nthe sum of all inCircles is %lld\n", sum);

	double estimateForPi = 4 * ((double) sum / BATCH_SIZE);
	printf("\ntherefore the 'estimate For Pi' is %lf\n", estimateForPi);

	_getch();
	return 0;           
}