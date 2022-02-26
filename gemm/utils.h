#ifndef _UTILS_H_

#include <set>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <algorithm >
#include <time.h>
#include <map>
#include <unordered_map>
using namespace std;
//time_t   g_begin, g_end;
//double g_duration = 0.0, total = 0.0;



void time_start(string key);
void time_cost(string key);
void getDataRandom(int size, float* pData);
void getDataRandom(int size, double* pData);

#endif // !_UTILS_H_