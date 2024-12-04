#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	char country_name[31];
	char country_code[4];
	char currency_code[4];
	double buy;
	double sell;
} Currency;

Currency data[] = {
	#include "waehrung.dat"
};

void printStringCol(int max_chars, char string[]) {
	int whitespaces = max_chars - strlen(string);
	printf(" %s%*c|", string, whitespaces, ' ');
}
void printNumCol(double num){
	printf("%10.6f |", num);
}

void printRow(Currency * row){
	printStringCol(32, row->country_name);
	printStringCol(4, row->country_code);
	printStringCol(4, row->currency_code);
	printNumCol(row->buy);
	printNumCol(row->sell);
	printf("\n");
}

int compareByCountryName(const void *a, const void *b) {
    return strcmp(((Currency *)a)->country_name, ((Currency *)b)->country_name);
}

int main(){
	int data_len = sizeof(data)/sizeof(Currency);

	qsort(data, data_len, sizeof(Currency), compareByCountryName);

	for(int i = 0; i < data_len; i++) {
		printRow(&data[i]);
	}
}