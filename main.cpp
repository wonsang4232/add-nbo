#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

uint16_t read_nbo(char* filename) {

	FILE* fp = fopen(filename, "rb");
	
	if(fp == NULL) {
		printf("file does not exists!!\n");
		exit(0);
	}

	fseek(fp, 0, SEEK_END);
	int file_size = ftell(fp);

	if(file_size != 4) {
		printf("File size of %s is not 4 !!\n", filename);
		exit(0);
	}

	char buffer[4] = {0, };
	uint16_t result = 0x0;

	fclose(fp);

	fp = fopen(filename, "rb");

	fread(buffer, 1, 4, fp);

	for(int i = 0; i < 4; i ++) {
		result += buffer[i] << ((3 - i) * 8);
	}

	fclose(fp);

	return result;
}

int main(int argc, char* argv[]){
	char* filename1 = argv[1];
	char* filename2 = argv[2];

	uint16_t res1 = read_nbo(filename1);
	uint16_t res2 = read_nbo(filename2);

	uint16_t sum = res1 + res2;

	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", res1, res1, res2, res2, sum, sum);

	return 0;
}
