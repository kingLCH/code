#include "utils.h"

unordered_map<string, time_t> timeCosts;
void time_start(string key) {
	timeCosts[key] = clock();
}
void time_cost(string key) {
	if (timeCosts.find(key) != timeCosts.end())
	{
		time_t   begin = timeCosts[key];
		time_t 	end = clock();
		double duration = double(end - begin);//  CLOCKS_PER_SEC 检测识别耗时
		printf("%s forward time: %f ms.\n ", key.c_str(), duration);
	}
	else
	{
		printf("no key in %s\n", key.c_str());
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