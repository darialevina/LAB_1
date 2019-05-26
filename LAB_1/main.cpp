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

	int testDataA[] = { -3,  2,  1,  0,   1,  2,  3, };
	int testDataB[] = { 7,  6,  5,  4,   3,  2,  1, -10, -4 };
	int testDataC[] = { 3, 56, 18, -7, 247,  0, -1, };
	int testDataD[] = { 0xDEADBEEF, };
	int testDataE[] = { 1,  2,  3 };
	int testDataF[] = { 7,  8,  7,  8,   7,  8,  7,   8, 7, 8, 7, 8, 7, 8 };

	sort(testDataA, sizeof(testDataA) / sizeof(int)); printf("TEST A : %s.\n", isAscending(testDataA, sizeof(testDataA) / sizeof(int)) ? "OK" : "FAIL");
	sort(testDataB, sizeof(testDataB) / sizeof(int)); printf("TEST B : %s.\n", isAscending(testDataB, sizeof(testDataB) / sizeof(int)) ? "OK" : "FAIL");
	sort(testDataC, sizeof(testDataC) / sizeof(int)); printf("TEST C : %s.\n", isAscending(testDataC, sizeof(testDataC) / sizeof(int)) ? "OK" : "FAIL");
	sort(testDataD, sizeof(testDataD) / sizeof(int)); printf("TEST D : %s.\n", isAscending(testDataD, sizeof(testDataD) / sizeof(int)) ? "OK" : "FAIL");
	sort(testDataE, sizeof(testDataE) / sizeof(int)); printf("TEST E : %s.\n", isAscending(testDataE, sizeof(testDataE) / sizeof(int)) ? "OK" : "FAIL");
	sort(testDataF, sizeof(testDataF) / sizeof(int)); printf("TEST F : %s.\n", isAscending(testDataF, sizeof(testDataF) / sizeof(int)) ? "OK" : "FAIL");

	printf("Testing OK\n");

	getchar();
	return 0;
}