/*
* 寻找公共串的递归与非递归办法
*/

#include <iostream>
#include <assert.h>
#include <iomanip>
#include <algorithm>
using namespace std;

const int xlen = 7;
const int ylen = 6;
int sum = 0;//用来测试事件复杂度的全局变量

int **GetArray(int row, int col)//开辟二维数组
{
	int **s = (int**)malloc(sizeof(int)* row);
	assert(s != NULL);

	for (int i = 0; i < row; i++)
	{
		s[i] = (int*)malloc(sizeof(int)* col);
		assert(s[i] != NULL);
		memset(s[i], 0, sizeof(int)*col);
	}
	return s;
}

void printArray(int** s, int row, int col) //输出二维数组
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << setw(4) << s[i][j];
		}
		cout << endl;
	}
}

void ShowTrack(char* X, int** s, int row, int col)
{
	if (row <= 0 || col <= 0) return;
	if (s[row][col] == 1)
	{
		cout << X[row];
		ShowTrack(X, s, row - 1, col - 1);
	}
	else if (s[row][col] == 2)
	{
		ShowTrack(X, s, row - 1, col);
	}
	else
	{
		ShowTrack(X, s, row, col - 1);
	}
}

int GetLength1(char* X, char* Y, int row, int col, int ** c, int** s)//得到公共串长度和公共序列
{
	sum += 1;
	if (row <= 0 || col <= 0) return 0;
	if (c[row][col] > 0) return c[row][col]; //避免重复计算
	if (X[row] == Y[col])
	{		
		c[row][col] = GetLength1(X, Y, row-1,col-1, c, s) + 1;
		s[row][col] = 1;
	}
	else
	{
		int len1 = GetLength1(X, Y, row - 1, col, c, s);
		int len2 = GetLength1(X, Y, row, col-1, c, s);
		c[row][col] = max(len1, len2);
		if (len1 > len2)
		{
			s[row][col] = 2;
		}
		else
		{
			s[row][col] = 3;
		}
	}
	return c[row][col];
}

int GetLength2(char* X, char* Y, int row, int col, int ** c)//只得到公共串长度
{
	for (int i = 0; i < row; i++) c[i][0] = 0;
	for (int i = 0; i < col; i++) c[0][col] = 0;
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			if (X[i] == Y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else
			{
				c[i][j] = max(c[i - 1][j], c[i][j - 1]);
			}
		}
	}
	return c[row][col];
}

int  main()
{
	char X[xlen + 2] = "#ABCBDAB";
	char Y[ylen + 2] = "#BDCABA";
	int** c = GetArray(xlen+1, ylen+1);
	int** s = GetArray(xlen+1, ylen+1);
/*
	int length = GetLength1(X, Y, xlen, ylen, c, s);
	cout << "length: " << length << endl;

	ShowTrack(X, s, xlen, ylen);
	cout << endl;

	cout << "c: " << endl;
	printArray(c, xlen+1, ylen+1);

	cout << endl << "s: " << endl;
	printArray(s, xlen+1, ylen+1);

	cout << "sum: " << sum << endl;
*/
	int length = GetLength2(X, Y, xlen, ylen, c);
	cout << "length: " << length << endl;

	cout << "c: " << endl;
	printArray(c, xlen + 1, ylen + 1);

	return 0;
}