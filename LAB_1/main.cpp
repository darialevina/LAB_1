#include "main.h"
#include "stdio.h"
#include "stdlib.h"

#define LINE_LEN 128

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

const char* inputPath  = "inputA.txt";
const char* outputPath = "output.txt";
#define MAX_RECORDS 1024
int data[MAX_RECORDS];

int main() {
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

	getchar();
	return 0;
}