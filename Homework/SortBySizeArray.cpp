#include <stdio.h>
int DataNumber = 8;
int data[8] = {12,23,98,45,11,92,56,79};
void sort(int list[], int size);
int main(void) {
	printf("기존 배열: [");
	for (int i = 0; i < DataNumber; i++) {
		if(i!=DataNumber-1)
			printf("%d,", data[i]);
		else
			printf("%d]", data[i]);
	}
	printf("\n");
	sort(data, DataNumber);
	printf("정렬후 배열: [");
	for (int i = 0; i < DataNumber; i++) {
		if (i != DataNumber - 1)
			printf("%d,", data[i]);
		else
			printf("%d]", data[i]);
	}

}
void sort(int list[], int size) {
	size--;
	while (size != 0) {
		for (int i = 0; i < size; i++) {
			if (list[i] > list[i + 1]) {
				int temp = 0;
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
			}
		}
		size--;
	}
}