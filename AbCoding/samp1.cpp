#include <set>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <algorithm >
#include <vector>

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


void backtrace(string digits, vector<string>&results, vector<vector<string>>& maps) {
	if (digits.size() == 0) {
		results.push_back("");
		return;
	}
	int num = digits[0] - '0';
	digits.erase(0, 1);
	vector<string> part_results;
	backtrace(digits, part_results, maps);
	for (auto head : maps[num]) {
		for (auto temp : part_results) {
			results.push_back(head + temp);
		}
	}
}

vector<string> letterCombinations(string digits) {
	vector<vector<string>> maps;
	maps.push_back({ "" });//0
	maps.push_back({ "" });//1
	maps.push_back({ "a","b", "c" });//2
	maps.push_back({ "d","e","f" });
	maps.push_back({ "g","h","i" });
	maps.push_back({ "j","k","l" });
	maps.push_back({ "m","n","o" });
	maps.push_back({ "p","q","r","s" });
	maps.push_back({ "t","u","v" });
	maps.push_back({ "w","x","y","z" });

	vector<string> results;
	if (digits.size() == 0) {
		return results;
	}

	backtrace(digits, results, maps);
	return results;
}


int main() {
	int len = 10;
	//vector<vector<int> > dp(len, vector<int>(len));

	////string huiwen("abdsnjfshdfjkdsfjksdfdnsjkfdnskfndsjkfndsjkfndsjkfnddhjkfbdsjkfbdskfbdsjkfbdsjkfbdsjkfbdskfbdskjfbdskjfbbbbbbbbbbbbbbbbbbbbbbbdshfbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbuuuuuuuuuuuuuudsadbaskjdbaskjbdajkbdsjakdsjakdsajkdbasjkdbasjkdbsakjdbsakjbdsakjdbaskjsjkfndsjfndsjkfndskjfndsjkfndsjkfnsdb");
	////time_start("huiwen");
	////string result = longestPalindrome(huiwen);
	////time_cost("huiwen");

	//vector<int> coins{ 1, 2, 5 };
	//int amount = 11;

	//coinChange(coins, amount);

	letterCombinations("23");


	system("pause");
	return 0;
}