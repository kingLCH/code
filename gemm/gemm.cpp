// gemm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "utils.h"

//#define A( i, j ) a[ (i)*lda + (j) ]
//#define B( i, j ) b[ (i)*ldb + (j) ]
//#define C( i, j ) c[ (i)*ldc + (j) ]
// gemm C = A * B + C

#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]

/* Routine for computing C = A * B + C */

//void MY_MMult(int m, int n, int k, double *a, int lda,
//	double *b, int ldb,
//	double *c, int ldc)
//{
//	int i, j, p;
//
//	for (i = 0; i < m; i++) {        /* Loop over the rows of C */
//		for (j = 0; j < n; j++) {        /* Loop over the columns of C */
//			for (p = 0; p < k; p++) {        /* Update C( i,j ) with the inner
//							 product of the ith row of A and
//							 the jth column of B */
//				C(i, j) = C(i, j) + A(i, p) * B(p, j);
//			}
//		}
//	}
//}

int main10220()
{
	int m = 100, n = 50, k = 20;
	double* a = new double[m*n];
	double* b = new double[n*k];
	double* c = new double[m*k];

	getDataRandom(m*n, a);
	getDataRandom(n*k, b);
	getDataRandom(m*k, c);

	time_start("matrix");
	//MY_MMult(m, n, k, a, m, b, n, c, m);
	time_cost("matrix");

    std::cout << "Hello World!\n";
	system("pause");
	return 0;
}

