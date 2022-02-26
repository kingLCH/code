#include "utils.h"

unordered_map<string, time_t> timeCosts;
void time_start(string key) {
	timeCosts[key] = clock();
}
double time_cost(string key) {
	if (timeCosts.find(key) != timeCosts.end())
	{
		time_t   begin = timeCosts[key];
		time_t 	end = clock();
		double duration = double(end - begin);//  CLOCKS_PER_SEC 检测识别耗时
		printf("%s forward time: %f ms.\n ", key.c_str(), duration);
		return duration;
	}
	else
	{
		printf("no key in %s\n", key.c_str());
		return 0.0;
	}
}
void getDataRandom(int size, float* pData) {
	//cv::Mat randMat(int rows, int cols, int type)
	srand(time(0));
	for (int i = 0; i < size; i++) {
		pData[i] = (rand() % 255) / double(RAND_MAX);
	}
}
void getDataRandom(int size, double* pData) {
	//cv::Mat randMat(int rows, int cols, int type)
	srand(time(0));
	for (int i = 0; i < size; i++) {
		pData[i] = (rand() % 255) / double(RAND_MAX);
	}
}
void random_matrix(int m, int n, double *a, int lda)
{
	#define A( i,j ) a[ (j)*lda + (i) ]

	//double drand48();
	int i, j;

	for (j = 0; j < n; j++){
		for (i = 0; i < m; i++){
			double temp = 2.0 * (rand() % 255) / (255.f) - 1.0;
			A(i, j) = temp;
		}
	}
}

void copy_matrix(int m, int n, double *a, int lda, double *b, int ldb)
{
#define A( i, j ) a[ (j)*lda + (i) ]
#define B( i, j ) b[ (j)*ldb + (i) ]
	int i, j;

	for (j = 0; j < n; j++)
		for (i = 0; i < m; i++)
			B(i, j) = A(i, j);
}
void REF_MMult(int m, int n, int k, double *a, int lda,
	double *b, int ldb,
	double *c, int ldc)
{
#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]

	int i, j, p;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			for (p = 0; p < k; p++) {
				C(i, j) = C(i, j) + A(i, p) * B(p, j);
			}
		}
	}
}

double compare_matrices(int m, int n, double *a, int lda, double *b, int ldb)
{
#define A( i, j ) a[ (j)*lda + (i) ]
#define B( i, j ) b[ (j)*ldb + (i) ]
#define abs( x ) ( (x) < 0.0 ? -(x) : (x) )

	int i, j;
	double max_diff = 0.0, diff;

	for (j = 0; j < n; j++)
		for (i = 0; i < m; i++) {
			diff = abs(A(i, j) - B(i, j));
			max_diff = (diff > max_diff ? diff : max_diff);
		}

	return max_diff;
}