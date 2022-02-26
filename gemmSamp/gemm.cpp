// gemm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "utils.h"
#include "timer.h"
#include <iostream>
#include <fstream>

//#define A( i, j ) a[ (i)*lda + (j) ]
//#define B( i, j ) b[ (i)*ldb + (j) ]
//#define C( i, j ) c[ (i)*ldc + (j) ]
// gemm C = A * B + C
// A:m*k B:k*n C:m*n

#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]

/* Routine for computing C = A * B + C */

extern void MY_MMult(int m, int n, int k, double *a, int lda,
	double *b, int ldb,
	double *c, int ldc);


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

void printMyMat(int m, int n, double *a, int lda, string name) {
	ofstream outFile;
	outFile.open(name, ios::out);
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < lda; j++)
		{
			outFile << a[i*lda + j]<<";";
		}
		outFile << "\n";
	}
	outFile.close();
}

#include <sstream>
#include <iomanip>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
	std::ostringstream out;
	out << std::setprecision(n) << a_value;
	return out.str();
}
template <typename T>
std::string to_string_with_precision2(const T a_value, const int n = 3)
{
	return std::to_string(a_value).substr(0, std::to_string(a_value).find(".") + n + 1);
}
//

int main()
{
	//int m = 100, n = 50, k = 20;
	//double* a = new double[m*n];
	//double* b = new double[n*k];
	//double* c = new double[m*k];
	//getDataRandom(m*n, a);
	//getDataRandom(n*k, b);
	//getDataRandom(m*k, c);
	//time_start("matrix");
	//MY_MMult(m, n, k, a, m, b, n, c, m);
	//time_cost("matrix");
 //   std::cout << "Hello World!\n";
	//system("pause");
	//return 0;

	int
		p,
		m, n, k,
		lda, ldb, ldc,
		rep;

	double
		dtime, dtime_best,
		gflops,
		diff;

	double
		*a, *b, *c, *cref, *cold;


	printf("MY_MMult = [\n");

	ofstream outFile;
	outFile.open("4_9.csv", ios::out);
	//outFile <<"size;time;flops\n";
	string line_one("matSize;");
	string line_time("time;");
	string line_glops("gflops;");
	for (p = PFIRST; p <= PLAST; p += PINC) {
		line_one += std::to_string(p) + ";";
		m = (M == -1 ? p : M);
		n = (N == -1 ? p : N);
		k = (K == -1 ? p : K);

		gflops = 2.0 * m * n * k * 1.0e-09;

		lda = (LDA == -1 ? m : LDA);
		ldb = (LDB == -1 ? k : LDB);
		ldc = (LDC == -1 ? m : LDC);

		/* Allocate space for the matrices */
		/* Note: I create an extra column in A to make sure that
		   prefetching beyond the matrix does not cause a segfault */
		a = (double *)malloc(lda * (k ) * sizeof(double));
		memset(a, 0, lda * (k) * sizeof(double));
		b = (double *)malloc(ldb * n * sizeof(double));
		memset(b, 0, ldb * (n) * sizeof(double));
		c = (double *)malloc(ldc * n * sizeof(double));
		cold = (double *)malloc(ldc * n * sizeof(double));
		cref = (double *)malloc(ldc * n * sizeof(double));

		/* Generate random matrices A, B, Cold */
		random_matrix(m, k, a, lda);
		//printMyMat(m, k, a, lda, string("a.csv"));
		random_matrix(k, n, b, ldb);
		random_matrix(m, n, cold, ldc);

		copy_matrix(m, n, cold, ldc, cref, ldc);

		/* Run the reference implementation so the answers can be compared */
		REF_MMult(m, n, k, a, lda, b, ldb, cref, ldc);
		//printMyMat(m, k, a, lda, string("a+.csv"));

		string name = "matrix_" + to_string(m)+"*"+ to_string(n) +"X"+  to_string(n) + "*" + to_string(k);
		Test::Timer timer(name);
		//m_n * n_k = m_k 
		/* Time the "optimized" implementation */
		for (rep = 0; rep < NREPEATS; rep++) {
			copy_matrix(m, n, cold, ldc, c, ldc);

			timer.Start();

			MY_MMult(m, n, k, a, lda, b, ldb, c, ldc);

			timer.Stop();
			
		}


		diff = compare_matrices(m, n, c, ldc, cref, ldc);
		timer.Print();
		dtime_best = timer.GetMin()/1000; //s
		printf("		size=%d, glops=%le , diff=%0.4f\n", p, gflops / dtime_best, diff);
		printf("------------------------------------------------------------\n");
		//outFile << p << ";"<< timer.GetAvr() << ";" << gflops / dtime_best<<std::endl;
		line_time += (to_string_with_precision2(timer.GetAvr(), 2)+";");
		line_glops += (to_string_with_precision2(gflops / dtime_best) + ";");
		//printf("%d %le %le \n", p, gflops / dtime_best, diff);
		//fflush(stdout);

		free(a);
		free(b);
		free(c);
		free(cold);
		free(cref);
	}
	outFile << line_one << std::endl;
	outFile << line_time << std::endl;
	outFile << line_glops << std::endl;
	outFile.close();
	printf("];\n");

	//exit(0);
	system("pause");
	return 0;
}


int var_test() {
	int w =256,  h = 256, c = 64;
	float* src = new float[w*h*c];
	getDataRandom(w*h*c, src);

	int len = 100;

	Test::Timer time("timer");

	string time_name = "old";
	time_start(time_name);
	time.Start();
	{
		
		for (size_t j = 0; j < len ; j++)
		{
			float sum1 = 0.0f;
			for (size_t i = 0; i < w*h*c; i++) {
				float temp = src[i];
				sum1 += temp;
			}
			float mean1 = sum1 / (w*h*c);
			float sum2 = 0.0f;
			for (size_t i = 0; i < w*h*c; i++)
			{
				float temp = src[i];
				//sum2 += pow((temp - mean1), 2);
			}
			float varia = sum2 / (w*h*c);
		}
	}
	time_cost(time_name);
	time.Stop();
	time.Print();
	time.Reset();
	time.Start();
	time_name = "new";
	time_start(time_name);
	{

		for (size_t j = 0; j < len; j++)
		{
			float sum1 = 0.0f;
			float sum2 = 0.0f;
			for (size_t i = 0; i < w*h*c; i++) {
				float temp = src[i];
				sum1 += temp;
				//sum2 += pow(temp, 2);
			}
			float mean1 = sum1 / (w*h*c);
			float mean2 = sum2 / (w*h*c);

			float varia = mean2 - mean1 * mean1;
		}


	}
	time_cost(time_name);
	time.Stop();
	time.Print();
	system("pause");
	return 0;

}
