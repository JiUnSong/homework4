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
/////////////////////////////////////			�Լ� ���� �κ�
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
	int matrix_row[2], matrix_column[2], i;		// ��� A, B�� ���� ��� ��, for���� ���� ���� i
	int **matrix[2];		// ��� A, B
	int **matrix_sum;		// ��� A + B
	int **matrix_sub;		// ��� A - B
	int **matrix_t;			// ��� A�� ��ġ���
	int **matrix_axt;		// ��� A�� A��ġ����� ��
	printf("------������    2019038028-------\n\n");

	for (i = 0; i < 2; i++) {									// ��� ���� ũ�⸦ �Է��ϰ� ����, ������ �����ϴ� for��
		printf("%d�� ����� ��� ���� �Է��Ͻÿ�: ", i + 1);		// ����ڿ��� ����� ũ�⸦ �Է��϶�� ��¹�
		scanf("%d %d", &matrix_row[i], &matrix_column[i]);		//����ڰ� ����� ũ�⸦ �Է�
		matrix[i] = create_matrix(matrix_row[i], matrix_column[i]);		// ��� ����
		if (**matrix[i] == -1)		//���� ��� ������ �ȵǾ��ٸ� ���α׷� ����
			break;
		else
			fill_data(matrix[i], matrix_row[i], matrix_column[i]);		// ��Ŀ� ������ ����
		printf("----matrix_%d----\n", i+1);							// 1��, 2�� ��� ���
		print_matrix(matrix[i], matrix_row[i], matrix_column[i]);	// 1��, 2�� ��� ���
		printf("--------------------\n");
	}
	if (matrix_row[0] == matrix_row[1] && matrix_column[0] == matrix_column[1]) {		// sum�� sub�� �ϱ����� if��
		matrix_sum = create_matrix(matrix_row[0], matrix_column[0]);		// sum��� ����
		matrix_sub = create_matrix(matrix_row[0], matrix_column[0]);		// sub��� ����
		addition_matrix(matrix[0], matrix[1], matrix_sum, matrix_row[0], matrix_column[0]);		// sum��Ŀ� ������
		printf("----sum_matrix----\n");
		print_matrix(matrix_sum, matrix_row[0], matrix_column[0]);			// sum����� �� ���
		printf("--------------------\n");
		subtraction_matrix(matrix[0], matrix[1], matrix_sub, matrix_row[0], matrix_column[0]);	// sub ��Ŀ� ������
		printf("----sub_matrix----\n");
		print_matrix(matrix_sub, matrix_row[0], matrix_column[0]);			// sub����� �� ���
		printf("--------------------\n");
		free_matrix(matrix_sum, matrix_row[0], matrix_column[0]);			//sum �����Ҵ� ����
		free_matrix(matrix_sub, matrix_row[0], matrix_column[0]);			//sub �����Ҵ� ����
	}
	if (matrix_row[0] == matrix_column[0]) {							// ��ġ��� ����, ������� if��
		matrix_t = create_matrix(matrix_row[0], matrix_column[0]);		// ��ġ��� ����
		transpose_matrix(matrix[0], matrix_t, matrix_row[0], matrix_column[0]);		// ��ġ��� �� ����
		printf("----matrix_t----\n");
		print_matrix(matrix_t, matrix_row[0], matrix_column[0]);		// ��ġ���  ���
		printf("--------------------\n");
	}
	else {								// ��ġ��� ����, ������� if��
		matrix_t = create_matrix(matrix_column[0], matrix_row[0]);	// ��ġ��� ����
		transpose_matrix(matrix[0], matrix_t, matrix_row[0], matrix_column[0]);		// ��ġ��� �� ����
		printf("----matrix_t----\n");
		print_matrix(matrix_t, matrix_column[0], matrix_row[0]);		// ��ġ���  ���
		printf("--------------------\n");
	}
	matrix_axt = create_matrix(matrix_row[0], matrix_row[0]);	// ��� �� ����
	multiply_matrix(matrix[0], matrix_t, matrix_axt, matrix_row[0], matrix_column[0]);		// ��� �� �� ����

	printf("----matrix_axt----\n");
	print_matrix(matrix_axt, matrix_row[0], matrix_row[0]);		// ������ �� ���
	printf("--------------------\n");

	for(i = 0; i < 2; i++)						// matrix_a, b ����
		free_matrix(matrix[i], matrix_row[i], matrix_column[i]);
	return 0;			// 0���� ��ȯ
}

int** create_matrix(int row, int col)		// ��� ���� �Լ�
{
	int **real_matrix, i;			// ���� ����

	if (row <= 0 || col <= 0) {		// ���� ��� ���� ũ�Ⱑ ������
		printf("Check the sizes of row and col!\n");		// ũ�� üũ�϶�� ��¹�
		return -1;		// -1����
	}

	real_matrix = malloc(row * sizeof(int*));		// 2���� �迭 �����Ҵ�
	for (i = 0; i < row; i++)
		real_matrix[i] = malloc(col * sizeof(int));

	if (real_matrix == NULL) {		// �迭�� ���������,
		printf("�ٽ� �����Ͻÿ�.");		// �ٽ� �����϶�� ��¹�
		return -1;
	}
	return real_matrix;		// ��� ����
}

int fill_data(int **matrix, int row, int col)		// ����� ���� ä��� �Լ�
{
	int a, b;
	srand((unsigned)time(NULL));		// �ð��������ִ� ��ġ

	for (a = 0; a < row; a++) {			// ��Ŀ� 0���� 20���� ������ ����
		for (b = 0; b < col; b++) {
			matrix[a][b] = rand() % 20;
		}
	}
	return matrix;		// ��� ����
}
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col) {		// �� ����� ���� ���ϴ� �Լ�
	int a, i, j;

	for(i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];			// ����� ���� �����ϴ� for��

	return matrix_sum;		// ��� ����
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col) {		//�� ����� ���� ���ϴ� �Լ�
	int a, i, j;
	for (i = 0; i < row; i++)					//����� ���� �����ϴ� for��
		for (j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];

	return matrix_sub;		// ��� ����
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col)		// ��ġ����� ���ϴ� �Լ�
{
	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_t[j][i] = matrix[i][j];			// ��ġ����� �˰������� ����

	return matrix_t;		// ��� ����
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col) {		// ����� ���� ���ϴ� �Լ�
	int i, j, k, sum;
	for(i = 0; i < row; i++)						// ����� �� �˰����� ����
		for (j = 0; j < col; j++) {
			sum = 0;		// sum  = 0 �ʱ�ȭ
			for(k = 0; k < col; k++)
			sum += matrix_a[i][k] * matrix_t[k][j];
			matrix_axt[i][j] = sum;
		}
	return matrix_axt;		// ��� ����
}

void print_matrix(int **matrix, int row, int col) {			// ��� ��� �Լ�
	int a, b;
	for (a = 0; a < row; a++) {					// ����� ����ϴ� for��
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
