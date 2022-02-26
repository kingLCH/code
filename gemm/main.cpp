#include <set>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <algorithm >

using namespace std;
typedef std::map<int, std::string> mapStudent_t;



#include <stdio.h>
#define f(a,b) a##b
#define g(a)   #a
#define h(a) g(a)

#define REGISTER_OPTIMIZE_PASS(pass_name)                                                                              \
    TnnOptimizePassRegister<TnnOptimize##pass_name##Pass> g_tnn_optimize_##pass_name##_pass_(#pass_name)

int main_str()
{
	printf("%s\n", h(f(1, 2)));
	printf("%s\n", g(f(1, 2)));
	printf("%s\n", g(REGISTER_OPTIMIZE_PASS(FuseShuffleChannel)));
	printf("%s\n", h(REGISTER_OPTIMIZE_PASS(FuseShuffleChannel)));
	return 0;
}


int main_map() {
	mapStudent_t mapStudent;

	mapStudent.insert(std::pair<int, std::string>(1, "zhao"));
	mapStudent.insert(std::pair<int, std::string>(2, "qian"));
	mapStudent.insert(std::pair<int, std::string>(3, "sun"));
	mapStudent[1000] = "liu";

	mapStudent_t::iterator iter;
	iter = mapStudent.find(1000);
	if (iter != mapStudent.end()){
		cout << "Find it, the relative value is: " << iter->second << endl;
	}else{
		cout << "Can not find the relative value." << endl;
		//cout << "Find it, the relative value is: " << iter->second << endl;
	}
	iter = mapStudent.end();
	cout << "Find it, the relative value is: " << iter->second << endl;
	return 0;
}

int main_set()
{

	// begin/end:返回指向第一个元素的迭代/返回指向最后一个元素之后的迭代器，不是最后一个元素
		int myints[] = { 75, 23, 65, 42, 13 };
		std::string str[] = { "b", "c", "f", "g", "e", "d", "a" };
		std::set<int> myset(myints, myints + 5);
		std::set<std::string> mystr(str, str + 7);
		mystr.insert("a");

		std::cout << "mystr contains:";
		for (auto& iter : mystr) {
				std::cout << ' ' << iter;
		}
		std::cout << "\n";

		myset.insert(100);
		std::cout << "myset contains:";
		for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
			std::cout << ' ' << *it;

		std::cout << '\n';

		return 0;
}


#include <immintrin.h>
void sinx(int N, int terms, float* x, float* sinx)
{
	float three_fact = 6; // 3!
	for (int i = 0; i < N; i += 8)
	{
		__m256 origx = _mm256_load_ps(&x[i]);
		__m256 value = origx;
		__m256 numer = _mm256_mul_ps(origx, _mm256_mul_ps(origx, origx));
		__m256 denom = _mm256_broadcast_ss(&three_fact);
		float sign = -1.f;
		for (int j = 1; j <= terms; j++)
		{
			// value += sign * numer / denom
			__m256 tmp = _mm256_div_ps(_mm256_mul_ps(_mm256_broadcast_ss(&sign), numer), denom);
			value = _mm256_add_ps(value, tmp);
			numer = _mm256_mul_ps(numer, _mm256_mul_ps(origx, origx));
			float fenmu = (2 * j + 2) * (2 * j + 3);
			denom = _mm256_mul_ps(denom, _mm256_broadcast_ss(&fenmu));
			sign *= -1;
		}
		_mm256_store_ps(&sinx[i], value);
	}
}

#include <omp.h>
#define MNN_CONCURRENCY_BEGIN(__iter__, __num__) \
    __pragma(omp parallel for) for (int __iter__ = 0; __iter__ < __num__; __iter__++) {
#define MNN_CONCURRENCY_END() }
#define MNN_CONCURRENCY_BEGIN_CONDITION(__iter__, __num__, __condition__) \
    int __iter__ = 0;                                                     \
    __pragma(omp parallel for if(__condition__))                          \
    for (; __iter__ < __num__; __iter__++) {

 #include <string>
 #include <unordered_set>
 using namespace std;
int lengthOfLongestSubstring(string s) {
	std::cout << "input: " << s << std::endl;
	unordered_set<char> str;
	int size = s.size();
	if (size <= 0)
	{
		return 0;
	}

	int maxLen = 0, i = 0, j = 0;
	while (i < size)
	{
		if (str.find(s[i]) == str.end()){
			str.insert(s[i]);
			i++;
			maxLen = std::max(maxLen, (int)str.size());
		}
		else {
			str.erase(s[j]);
			j++;
		}
	}
	return maxLen;
}

void printf_vec(vector<int> num) {
	for (size_t ii = 0; ii < num.size(); ii++)
	{
		std::cout << num[ii] << "\t";
	}
	std::cout << "\n";
}
/*
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	vector<int> temp;
	int i = 0, j = 0;
	printf_vec(nums1);
	printf_vec(nums2);
	while (i < m && j < n)
	{
		if (nums2[j] > nums1[i])
		{
			temp.push_back(nums1[i++]);
		}
		else {
			temp.push_back(nums2[j++]);
		}
		printf_vec(temp);
	}
	if (i==m && j < n)
	{
		while (j<n)
		{
			temp.push_back(nums2[j++]);
		}
		printf_vec(temp);
	}
	if (j == n  && i < m)
	{
		while (i < m)
		{
			temp.push_back(nums1[i++]);
		}
		printf_vec(temp);
	}
	nums1 = temp;
}*/

//void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
//	//vector<int> temp;
//	int i = 0, j = 0;
//	printf_vec(nums1);
//	printf_vec(nums2);
//	int endl = m - 1;
//	while (i < m && j < n)
//	{
//		if (nums2[j] > nums1[i])
//		{
//			temp.push_back(nums1[i++]);
//		}
//		else {
//			temp.push_back(nums2[j++]);
//		}
//		printf_vec(temp);
//	}
//	if (i == m && j < n)
//	{
//		while (j < n)
//		{
//			temp.push_back(nums2[j++]);
//		}
//		printf_vec(temp);
//	}
//	if (j == n && i < m)
//	{
//		while (i < m)
//		{
//			temp.push_back(nums1[i++]);
//		}
//		printf_vec(temp);
//	}
//	nums1 = temp;
//}

int main() {
	//main_set();
	float test = 66666;
	__m256 temp = _mm256_broadcast_ss(&test);
	__m128 temp128 = _mm_broadcast_ss(&test);
	__m128i tempi = _mm_castps_si128(temp128);

	__m128d x;

	//lengthOfLongestSubstring(string("pwwkew"));
	vector<int> nums1{ 1, 3, 5, 0, 0, 0 };
	vector<int> nums2{ 2,4,6 };
	//merge(nums1, 3, nums2, 3);

	system("pause");
	return 0;
}