#include "main.h"
#include "stdio.h"
#include "stdlib.h"

const int LINE_LEN = 128;

int readData(const char* filepath, int* data, int maxRecords) {
	FILE* file = fopen(filepath, "r");
	if (file == NULL) { return 0; }

	char line[LINE_LEN];
	int numRecords = 0;

	while (fgets(line, LINE_LEN, file) != NULL &&
		numRecords < maxRecords) {
		*data = atoi(line);
		data++;
		numRecords++;
	}

	fclose(file);
	return numRecords;
}

int writeData(const char* filepath, int* data, int len) {
	FILE* file = fopen(filepath, "w");
	if (file == NULL) { return 1; }

	for (int i = 0; i < len; i++) {
		if (fprintf(file, "%i\n", *data) < 0) { return 1; };
		data++;
	}

	fclose(file);
	return 0;
}

// this is NOT a bubble/insertion sort!
void sort(int* data, int len) {
	for (int i = 0; i < len; i++) {
		int* min = data + i;

		for (int k = i; k < len; k++) {
			if (*(data + k) < *min) { min = data + k; }
		}

		int tmp = *(data + i);
		*(data + i) = *min;
		*min = tmp;
	}
}

int isAscending(int* data, int len) {
	for (int i = 1; i < len; i++) {
		if (data[i] < data[i - 1]) { return 0; }
	}

	return 1;
}

const char* inputPath = "inputA.txt";
const char* outputPath = "output.txt";
const int MAX_RECORDS = 1024;

int main() {

	int* data = new int[MAX_RECORDS];

	printf("LAB 1\n");
	printf("Reading file...\n");

	int numRecords = readData(inputPath, data, MAX_RECORDS);

	if (!numRecords) {
		printf("No data.\n");
		getchar();
		return 0;
	}

	printf("Reading file OK\n");

	printf("Sorting data...\n");
	sort(data, numRecords);
	printf("Sorting data OK\n");

	printf("Writing file...\n");

	if (writeData(outputPath, data, numRecords)) {
		printf("Writing failed.\n");
		getchar();
		return 0;
	}
	printf("Writing file OK\n");

	delete[] data;

	// *** *** ***

	printf("Testing... \n");

	int* testEmpty        = NULL;
	int  testOneItem   [] = { 0xDEADBEEF,                                };
	int  testDescending[] = { -3,  2,   1,  0,   1,       2,  3,         };
	int  testAscendng  [] = {  1,  2,   3,  4,   5,       6,  7          };
	int  testRandomA   [] = {  7,  6, 334,  4,   3,  231010,  1, -10, -4 };
	int  testRandomB   [] = {  3, 56,  18, -7, 247,       0, -1,         };
	int  testSame      [] = {  7,  7,   7,  7,   7,       7,  7          };

	sort(testEmpty     , 0                                   ); printf("Empty      : %s.\n", isAscending(testEmpty     , 0                                   ) ? "OK" : "FAIL");
	sort(testOneItem   , sizeof(testOneItem   ) / sizeof(int)); printf("One Item   : %s.\n", isAscending(testOneItem   , sizeof(testOneItem   ) / sizeof(int)) ? "OK" : "FAIL");
	sort(testDescending, sizeof(testDescending) / sizeof(int)); printf("Descending : %s.\n", isAscending(testDescending, sizeof(testDescending) / sizeof(int)) ? "OK" : "FAIL");
	sort(testAscendng  , sizeof(testAscendng  ) / sizeof(int)); printf("Ascendng   : %s.\n", isAscending(testAscendng  , sizeof(testAscendng  ) / sizeof(int)) ? "OK" : "FAIL");
	sort(testRandomA   , sizeof(testRandomA   ) / sizeof(int)); printf("RandomA    : %s.\n", isAscending(testRandomA   , sizeof(testRandomA   ) / sizeof(int)) ? "OK" : "FAIL");
	sort(testRandomB   , sizeof(testRandomB   ) / sizeof(int)); printf("RandomB    : %s.\n", isAscending(testRandomB   , sizeof(testRandomB   ) / sizeof(int)) ? "OK" : "FAIL");
	sort(testSame      , sizeof(testSame      ) / sizeof(int)); printf("Same       : %s.\n", isAscending(testSame      , sizeof(testSame      ) / sizeof(int)) ? "OK" : "FAIL");

	printf("Testing OK\n");

	getchar();
	return 0;
}