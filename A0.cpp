#include <iostream>
#include "omp.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	
	int numberOfWords = 0;
	if (argc >= 1) {
        string inputString = argv[1];
		
		for (int i = 0; inputString[i] != '\0'; i++) {
			char current = inputString[i];
			char next = inputString[i+1];

			if (isalpha(current) && (next == ' ' || next == '\t' || next == '\n' || i == (inputString.size() - 1))) {
				numberOfWords++;
			}
		}
		cout << numberOfWords << endl;
    }
    else {
        cout << "No arguments!" << endl;
        exit(0);
    }
    return 0;
	

}