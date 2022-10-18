#include <iostream>
#include "omp.h"
#include <time.h>
#include <stdexcept>
using namespace std;

double getTimeOfMultipl(int numOfThreads, int size, int **a, int **b) {
	omp_set_dynamic(0);
	int rslt[size][size];
	double time = omp_get_wtime();
	#pragma omp parallel for num_threads(numOfThreads)
    for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			for (int j = 0; j < size; j++)
				rslt[x][y] += a[x][j] * b[j][y];
	return omp_get_wtime() - time;
}

void randomInitMatrix(int size, int** matrix) {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			matrix[x][y] = 1 + rand() % 100;
		}
	}
}

void printMatrix(int size, int** matrix) {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) 
			printf("%-5d",matrix[x][y]);
   		cout<<'\n';
	}
}

int main(int argc, char *argv[]) {

	srand(time(NULL));
	if (argc >= 1) {
        const int N = atoi(argv[1]); // matrix size
		if (N <= 0) throw invalid_argument("Matrix dimension must be positive!");
		// Initialize matrices
		int **a = new int*[N];
		int **b = new int*[N];
		for (int i = 0; i <N; i++)
		{
			a[i] = new int[N] {};
			b[i] = new int[N] {};
		}

		// Fill matrices with random numbers
		cout << "[INFO] Randomizing...\n";
		randomInitMatrix(N, a);
		randomInitMatrix(N, b);
		cout << "[INFO] Matrices created\n";

		// cout << "First matrix:\n"; printMatrix(N, a);
		// cout << "Second matrix:\n"; printMatrix(N, b);

		printf("%-5s\t%-10s\t%-10s\n", "Threads", "Time (s)", "Efficiency, %");
		int numOfThreads;
		double t1 = getTimeOfMultipl(1, N, a, b);
		for (int numOfThreads = 1; numOfThreads <= 10; numOfThreads++)
		{
			double time = getTimeOfMultipl(numOfThreads, N, a, b);
			double efficiency = t1 / time;
			printf("%-5d\t%-10.4f\t%-10.2f\n", numOfThreads, time, efficiency * 100);
		}		
    }
    else {
        cout << "No arguments!" << endl;
        exit(0);
    }
    return 0;
	

}