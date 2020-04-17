/*
 ============================================================================
 Name        : homework4.c
 Author      : Ji Un Song
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/////////////////////////////////////			함수 선언 부분
int** create_matrix(int row, int col);
int fill_data(int **matrix, int row, int col);
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col);
void print_matrix(int **matrix, int row, int col);
int free_matrix(int **matrix, int row, int col);
/////////////////////////////////////////////
int main(void)
{
	int matrix_row[2], matrix_column[2], i;		// 행렬 A, B의 각각 행과 열, for문에 쓰일 변수 i
	int **matrix[2];		// 행렬 A, B
	int **matrix_sum;		// 행렬 A + B
	int **matrix_sub;		// 행렬 A - B
	int **matrix_t;			// 행렬 A의 전치행렬
	int **matrix_axt;		// 행렬 A와 A전치행렬의 곱
	printf("------송지운    2019038028-------\n\n");

	for (i = 0; i < 2; i++) {									// 행과 열의 크기를 입력하고 생성, 랜덤값 대입하는 for문
		printf("%d번 행렬의 행과 열을 입력하시오: ", i + 1);		// 사용자에게 행렬의 크기를 입력하라는 출력문
		scanf("%d %d", &matrix_row[i], &matrix_column[i]);		//사용자가 행렬의 크기를 입력
		matrix[i] = create_matrix(matrix_row[i], matrix_column[i]);		// 행렬 생성
		if (**matrix[i] == -1)		//만약 행렬 생성이 안되었다면 프로그램 종료
			break;
		else
			fill_data(matrix[i], matrix_row[i], matrix_column[i]);		// 행렬에 랜덤값 대입
		printf("----matrix_%d----\n", i+1);							// 1번, 2번 행렬 출력
		print_matrix(matrix[i], matrix_row[i], matrix_column[i]);	// 1번, 2번 행렬 출력
		printf("--------------------\n");
	}
	if (matrix_row[0] == matrix_row[1] && matrix_column[0] == matrix_column[1]) {		// sum과 sub을 하기위한 if문
		matrix_sum = create_matrix(matrix_row[0], matrix_column[0]);		// sum행렬 생성
		matrix_sub = create_matrix(matrix_row[0], matrix_column[0]);		// sub행렬 생성
		addition_matrix(matrix[0], matrix[1], matrix_sum, matrix_row[0], matrix_column[0]);		// sum행렬에 값대입
		printf("----sum_matrix----\n");
		print_matrix(matrix_sum, matrix_row[0], matrix_column[0]);			// sum행렬의 값 출력
		printf("--------------------\n");
		subtraction_matrix(matrix[0], matrix[1], matrix_sub, matrix_row[0], matrix_column[0]);	// sub 행렬에 값대입
		printf("----sub_matrix----\n");
		print_matrix(matrix_sub, matrix_row[0], matrix_column[0]);			// sub행렬의 값 출력
		printf("--------------------\n");
		free_matrix(matrix_sum, matrix_row[0], matrix_column[0]);			//sum 동적할당 해지
		free_matrix(matrix_sub, matrix_row[0], matrix_column[0]);			//sub 동적할당 해지
	}
	if (matrix_row[0] == matrix_column[0]) {							// 전치행렬 생성, 출력위한 if문
		matrix_t = create_matrix(matrix_row[0], matrix_column[0]);		// 전치행렬 생성
		transpose_matrix(matrix[0], matrix_t, matrix_row[0], matrix_column[0]);		// 전치행렬 값 대입
		printf("----matrix_t----\n");
		print_matrix(matrix_t, matrix_row[0], matrix_column[0]);		// 전치행렬  출력
		printf("--------------------\n");
	}
	else {								// 전치행렬 생성, 출력위한 if문
		matrix_t = create_matrix(matrix_column[0], matrix_row[0]);	// 전치행렬 생성
		transpose_matrix(matrix[0], matrix_t, matrix_row[0], matrix_column[0]);		// 전치행렬 값 대입
		printf("----matrix_t----\n");
		print_matrix(matrix_t, matrix_column[0], matrix_row[0]);		// 전치행렬  출력
		printf("--------------------\n");
	}
	matrix_axt = create_matrix(matrix_row[0], matrix_row[0]);	// 행렬 곱 생성
	multiply_matrix(matrix[0], matrix_t, matrix_axt, matrix_row[0], matrix_column[0]);		// 행렬 곱 값 대입

	printf("----matrix_axt----\n");
	print_matrix(matrix_axt, matrix_row[0], matrix_row[0]);		// 곱셈한 값 출력
	printf("--------------------\n");

	for(i = 0; i < 2; i++)						// matrix_a, b 해제
		free_matrix(matrix[i], matrix_row[i], matrix_column[i]);
	return 0;			// 0값을 반환
}

int** create_matrix(int row, int col)		// 행렬 생성 함수
{
	int **real_matrix, i;			// 변수 선언

	if (row <= 0 || col <= 0) {		// 만약 행과 열의 크기가 음수면
		printf("Check the sizes of row and col!\n");		// 크기 체크하라는 출력문
		return -1;		// -1리턴
	}

	real_matrix = malloc(row * sizeof(int*));		// 2차원 배열 동적할당
	for (i = 0; i < row; i++)
		real_matrix[i] = malloc(col * sizeof(int));

	if (real_matrix == NULL) {		// 배열이 비어있으면,
		printf("다시 선언하시오.");		// 다시 선언하라는 출력문
		return -1;
	}
	return real_matrix;		// 행렬 리턴
}

int fill_data(int **matrix, int row, int col)		// 행렬의 값을 채우는 함수
{
	int a, b;
	srand((unsigned)time(NULL));		// 시간조절해주는 장치

	for (a = 0; a < row; a++) {			// 행렬에 0부터 20까지 랜덤값 대입
		for (b = 0; b < col; b++) {
			matrix[a][b] = rand() % 20;
		}
	}
	return matrix;		// 행렬 리턴
}
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col) {		// 두 행렬의 합을 구하는 함수
	int a, i, j;

	for(i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];			// 행렬의 합을 대입하는 for문

	return matrix_sum;		// 행렬 리턴
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col) {		//두 행렬의 차를 구하는 함수
	int a, i, j;
	for (i = 0; i < row; i++)					//행렬의 차를 대입하는 for문
		for (j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];

	return matrix_sub;		// 행렬 리턴
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col)		// 전치행렬을 구하는 함수
{
	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_t[j][i] = matrix[i][j];			// 전치행렬의 알고리즘으로 대입

	return matrix_t;		// 행렬 리턴
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col) {		// 행렬의 곱을 구하는 함수
	int i, j, k, sum;
	for(i = 0; i < row; i++)						// 행렬의 곱 알고리즘을 구현
		for (j = 0; j < col; j++) {
			sum = 0;		// sum  = 0 초기화
			for(k = 0; k < col; k++)
			sum += matrix_a[i][k] * matrix_t[k][j];
			matrix_axt[i][j] = sum;
		}
	return matrix_axt;		// 행렬 리턴
}

void print_matrix(int **matrix, int row, int col) {			// 행렬 출력 함수
	int a, b;
	for (a = 0; a < row; a++) {					// 행렬을 출력하는 for문
		for (b = 0; b < col; b++)
			printf("%d ", matrix[a][b]);
		printf("\n");
	}
}
int free_matrix(int **matrix, int row, int col) {
	int i;
	for (i = 0; i < row; i++)
		free(matrix[i]);
	free(matrix);
	if (matrix == NULL)
		return 1;
	else
		return -1;
}
