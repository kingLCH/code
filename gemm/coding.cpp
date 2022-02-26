#include <set>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <algorithm >
#include "utils.h"

using namespace std;


bool isHuiwen(string s) {
	bool ishuiwen = false;
	int i = 0, j = s.size() - 1;
	while (i <= j)
	{
		if (s[i++] == s[j--]) {
			ishuiwen = true;
		}
		else {
			ishuiwen = false;
			break;
		}
	}
	return ishuiwen;
}
string longestPalindrome(string s) {
	int size = s.size();

	int maxLen = 0;
	string maxStr(s);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 1; j + i <= size; j++)
		{
			string temp = s.substr(i, j);
			if (isHuiwen(temp) && temp.size() > maxLen) {
				maxStr = temp;
				maxLen = temp.size();
			}
		}

	}
	return maxStr;
}

int coinChange(vector<int>& coins, int amount) {
	if (amount <= 0)  return 0;
	vector<int> dp(amount + 1, INT32_MAX);
	dp[0] = 0;

	for (size_t i = 1; i <= amount; i++)
	{
		for (size_t j = 0; j < coins.size(); j++)
		{
			if (i >= coins[j]) {
				dp[i] = min(dp[i], dp[i - coins[j]] + 1);
			}
		}
	}
	return dp[amount] != INTMAX_MAX ? dp[amount] : -1;
}

int main0110() {
	int len = 10;
	vector<vector<int> > dp(len, vector<int>(len));

	//string huiwen("abdsnjfshdfjkdsfjksdfdnsjkfdnskfndsjkfndsjkfndsjkfnddhjkfbdsjkfbdskfbdsjkfbdsjkfbdsjkfbdskfbdskjfbdskjfbbbbbbbbbbbbbbbbbbbbbbbdshfbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbuuuuuuuuuuuuuudsadbaskjdbaskjbdajkbdsjakdsjakdsajkdbasjkdbasjkdbsakjdbsakjbdsakjdbaskjsjkfndsjfndsjkfndskjfndsjkfndsjkfnsdb");
	//time_start("huiwen");
	//string result = longestPalindrome(huiwen);
	//time_cost("huiwen");

	vector<int> coins{ 1, 2, 5 };
	int amount = 11;

	coinChange(coins, amount);

	system("pause");
	return 0;
}