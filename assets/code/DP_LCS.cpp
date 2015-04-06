#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int MaxSub(int a[], int n)
{ 
	if (n <= 0)
		return 0;

	int *F = new int[n], maxSum = 0;
	F[0] = a[0];
	maxSum = a[0];

	for (int i = 1; i < n; ++i)
	{
		F[i] = F[i - 1] > 0 ? F[i - 1] + a[i] : a[i];
		if (maxSum < F[i])
			maxSum = F[i];
	}

	delete []F;
	return maxSum;
}

int LongestCommonSubstring(string str1, string str2)
{
	int m = str1.length(), n = str2.length();
	if (m == 0 || n == 0)
		return 0;

	int maxLen = 0;
	vector<vector<int> > F(m+1, vector<int>(n+1));
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			F[i][j] = str1[i - 1] == str2[j - 1] ? F[i - 1][j - 1] + 1 : 0;
			if (maxLen < F[i][j])
				maxLen = F[i][j];
		}
	}

	return maxLen;
}

int LongestCommonSubsequence(string str1, string str2)
{
	int m = str1.length(), n = str2.length();
	if (m == 0 || n == 0)
		return 0;

	vector<vector<int> > F(m + 1, vector<int>(n + 1));
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (str1[i - 1] == str2[j - 1])
			{
				F[i][j] = F[i - 1][j - 1] + 1;
			}
			else
			{
				F[i][j] = max(F[i][j - 1], F[i - 1][j]);
			}
		}
	}

	return F[m][n];
}

int LIS_ori(int a[], int n)
{
	if (n <= 0)
		return 0;
	
	// F[i]:以`a[i]`结尾的最长递增子序列的长度
	int *F = new int[n], maxLen = 1;
	for (int i = 0; i < n; ++i)
		F[i] = 1;

	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (a[i] > a[j] && F[i] < F[j] + 1)
				F[i] = F[j] + 1;
			if (maxLen < F[i])
				maxLen = F[i];
		}
	}

	delete[]F;
	return maxLen;
}

int LIS_ex(int a[], int n)
{
	if (n <= 0)
		return 0;

	// F[i]: 长度为i的递增子序列中的最小的最后一个元素
	int *F = new int[n], len = 0;
	F[len] = a[0];

	for (int i = 1, j = 1; i < n; ++i)
	{
		if (F[len] > a[i]) // 二分查找
		{
			int low = 0, high = len, mid = 0;
			while (low <= high)
			{
				mid = (low + high) >> 1;
				if (F[mid] < a[i] && (len == mid || F[mid + 1] >= a[i]))
					break;
				else if (F[mid] > a[i])
					high = mid - 1;
				else
					low = mid + 1;
			}
			
			j = mid + 1;
		}
		else if (F[len] < a[i])
			j = ++len;
		else
			continue;
		F[j] = a[i];
	}

	return len + 1;
}

int EditDistance(string str1, string str2)
{
	int m = str1.length(), n = str2.length();

	vector<vector<int> > F(m + 1, vector<int>(n + 1));
	// initialize
	for (int i = 0; i <= m; ++i)
		F[i][0] = i;
	for (int j = 0; j <= n; ++j)
		F[0][j] = j;

	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (str1[i - 1] == str2[j - 1])
			{
				F[i][j] = F[i - 1][j - 1];
			}
			else
			{
				F[i][j] = min(F[i-1][j-1]+1, min(F[i][j-1]+1, F[i-1][j]+1));
			}
		}
	}

	return F[m][n];
}

int main()
{
	// Maximum Subarray
	int a[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	cout << "test MaxSub\t" << MaxSub(a, 9) << endl;

	// Longest Common Substring
	string str1 = "ADE", str2 = "ABCDE";
	cout << "test LongestCommonSubstring\t" << LongestCommonSubstring(str1, str2) << endl;

	// Longest Common Subsequence
	cout << "test LongestCommonSubsequence\t" << LongestCommonSubsequence(str1, str2) << endl;

	// Longest Increasing Subsequence
	int b[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	cout << "test LongestIncreasingSubsequence\t" << LIS_ex(b, 16) << endl;

	// Edit Distance
	string s1 = "kitten", s2 = "sitting";
	cout << "test EditDistance\t" << EditDistance(s1, s2) << endl;

	getchar();
	return 0;
}