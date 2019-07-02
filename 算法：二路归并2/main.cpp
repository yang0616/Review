#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <iterator>
#include <time.h>
#include <string>
#include <math.h>
#include <utility>
#include <algorithm>
using namespace std;

template<class Type>
void Print(Type* ar, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << ar[i] << " ";
	}
	cout << endl;
}

template<class Type>
void Merge(Type* br, Type* ar, int part, int left, int right)
{
	int i = left, j = part + 1, index = i;
	while (i <= part && j <= right)
	{
		br[index++] = ar[i] < ar[j] ? ar[i++] : ar[j++];
	}

	while (i <= part)
	{
		br[index++] = ar[i++];
	}

	while (j <= right)
	{
		br[index++] = ar[j++];
	}
}

template<class Type> //二路归并递归
void Copy(Type* des, Type* sou, int left, int right)
{
	for (int i = left; i <= right; i++)
	{
		des[i] = sou[i];
	}
}

template<class Type>
void PassMerge(Type* br, Type* ar, int left, int right)
{
	if (left < right)
	{
		int part = (right - left) / 2 + left;
		PassMerge(br, ar, left, part);
		PassMerge(br, ar, part + 1, right);
		Merge(br, ar, part, left, right);
		Copy(ar, br, left, right);
	}
}

template<class Type>
void MergeSort(Type* ar, int len)
{
	Type* br = new Type[len];
	PassMerge(br, ar, 0, len - 1);
	delete []br;
}

template<class Type>//二路归并非递归
void NicePassMerge(Type* des, Type* sou, int width, int len)
{
	int i = 0;
	for (; i + 2 * width - 1 <= len - 1; i += 2 * width)
	{
		Merge(des, sou, i + width - 1, i, i + 2 * width - 1);
	}

	if (len - 1 > i + width - 1)//处理剩余的元素不足的情况
	{
		Merge(des, sou, i + width - 1, i, len - 1);
	}
	else
	{
		for (int j = i; j < len; j++)
		{
			des[j] = sou[j];
		}
	}
}

template<class Type>
void NiceMergeSort(Type* ar, int len)
{
	Type* br = new Type[len];
	int width = 1;
	while (width < len)
	{
		NicePassMerge(br, ar, width, len);
		width += width;
		NicePassMerge(ar, br, width, len);
		width += width;
	}
	delete []br;
}

int main()
{
	int ar[] = { 43, 6, 8, 74, 68, 16, 3, 7, 26, 2, 33 };
	int len = sizeof(ar) / sizeof(ar[0]);
	Print(ar, len);
	//MergeSort(ar, len);
	NiceMergeSort(ar, len);
	Print(ar, len);
	return 0;
}
