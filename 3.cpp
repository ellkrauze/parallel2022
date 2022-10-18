#include <iostream>
#include "omp.h"
#include <string>
#include <vector>
using namespace std;

int f()
{ 
    static int i;
    return ++i;
}

void printVector(vector<int> V) {
	cout << "Vector:\n";
	for (int i = 0; i < V.size(); i++) {
		cout << V[i] << " ";
	}
	cout << endl;
}

int findMaxElement(vector<int> V, int numOfThreads) {
	int max_element = V[0];
	omp_set_dynamic(0);
	#pragma omp parallel for num_threads(numOfThreads) reduction(max:max_element) 
		
	for (int i = 0; i < V.size(); i++)
		max_element = max_element > V[i] ? max_element : V[i];
	
	return max_element;
}


int main(int argc, char *argv[]) {
	
	int numberOfWords = 0;
	if (argc >= 1) {
        int N = atoi(argv[1]); // vector size

		// Fill the vector with random values
		srand(time(0));
		vector<int> V(N, 0);
		generate(V.begin(), V.end(), []() {
			return rand() % 1000;
		}); 
		// printVector(V);

		printf("%-5s\t%-10s\n", "Threads", "Time (s)");
		int numOfThreads;
		for (int numOfThreads = 1; numOfThreads <= 10; numOfThreads++)
		{
			double time = omp_get_wtime();
			int max_element = findMaxElement(V, numOfThreads);
			printf("%-5d\t%-10f\n", numOfThreads, omp_get_wtime() - time);
		}		
    }
    else {
        cout << "No arguments!" << endl;
        exit(0);
    }
    return 0;
	

}