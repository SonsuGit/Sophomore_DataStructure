#include <stdio.h>
#include <string.h>
#define N_STUDENTS  4
void Nsort(struct student_info list[], int size);
void Hsort(struct student_info list[], int size);
void Wsort(struct student_info list[], int size);
void printArray(const char s[], struct student_info list[]);
typedef struct student_info {
	char    name[10];
	int     height;
	float   weight;
} student_info;

student_info students[N_STUDENTS] = {
	{"이순신", 172, 83.4},
	{"홍길동", 167, 72.5},
	{"김유신", 159, 70.8},
	{"유관순", 163, 58.4}
};
student_info temp;
int main(void) {
	printArray("초기 학생 정보", students);
	Hsort(students, N_STUDENTS);
	printArray("키 정렬 후 학생 정보", students);
	Wsort(students, N_STUDENTS);
	printArray("몸무게 정렬 후 학생 정보", students);
	Nsort(students, N_STUDENTS);
	printArray("이름 정렬 후 학생 정보", students);
}
void printArray(const char s[], struct student_info list[]) {
	printf("------------------------------\n");
	printf("[%s]\n",s);
	printf("------------------------------\n");
	for (int i = 0; i < N_STUDENTS; i++) {
		printf("[%d] %s: %d %f\n", i, list[i].name, list[i].height, list[i].weight);
	}
}
void Nsort(struct student_info list[], int size) {
	size--;
	while (size != 0) {
		for (int i = 0; i < size; i++) {
			if ((strcmp(list[i].name, list[i + 1].name)) > 0) {
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
			}
		}
		size--;
	}
}
void Hsort(struct student_info list[], int size) {
	size--;
	while (size != 0) {
		for (int i = 0; i < size; i++) {
			if ((list[i].height) > (list[i + 1].height)) {
				temp = list[i];
				list[i] = list[i+1];
				list[i + 1] = temp;
			}
		}
		size--;
	}
}
void Wsort(struct student_info list[], int size) {
	size--;
	while (size != 0) {
		for (int i = 0; i < size; i++) {
			if ((list[i].weight) > (list[i + 1].weight)) {
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
			}
		}
		size--;
	}
}
