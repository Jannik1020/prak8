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

int maxDigitAmount(Currency curr[], int buySell){ // buy 0 sell 1
	int data_len = sizeof(data)/sizeof(Currency);

	int count = 1;
	for(int i = 0; i< data_len; i++){
		int digits;
		if(buySell == 0){
			digits = abs((int) curr[i].buy);
		}
		else if(buySell == 1) {
			digits = abs((int) curr[i].sell);
		}
		else{
			return -1;
		}
		
		digits = (digits == 0 )? 1 : log10(digits)+1;
		if(digits > count) count = digits;
	}

	return count;
}

int digitAmount(double num) {
	int digits = abs((int) num);
	return (digits == 0)? 1 : 1+ log10(digits);
}

void printStringCol(int max_chars, char string[]) {
	int whitespaces = max_chars - strlen(string);
	printf(" %s%*c|", string, whitespaces, ' ');
}

void printNumCol(int max_digits, double num){
	int whitespaces = max_digits - digitAmount(num);
	printf("%*c%f |", whitespaces+1, ' ', num);
}

void printRow(Currency * row, int max_digits_buy, int max_digits_sell){
	printStringCol(32, row->country_name);
	printStringCol(4, row->country_code);
	printStringCol(4, row->currency_code);
	printNumCol(max_digits_buy, row->buy);
	printNumCol(max_digits_sell, row->sell);
	printf("\n");
}

int compareByCountryName(const void *a, const void *b) {
    return strcmp(((Currency *)a)->country_name, ((Currency *)b)->country_name);
}

int main(){
	int data_len = sizeof(data)/sizeof(Currency);

	qsort(data, data_len, sizeof(Currency), compareByCountryName);

	for(int i = 0; i < data_len; i++) {
		printRow(&data[i], maxDigitAmount(data, 0), maxDigitAmount(data, 1));
	}
}