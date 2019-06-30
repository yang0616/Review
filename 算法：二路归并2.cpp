#include <iostream>
using namespace std;

template<class Type>  //数组输出
void Print(Type* arr, int len)
{
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;
}

template<class Type> //将源数组中剩余的不成对元素复制到目的数组中
void Copy(Type* des, Type* sou, int left, int right)
{
	for (int i = left; i < right; i++)
		des[i] = sou[i];

}

template<class Type>
void Merge(Type* des, Type* sou, int left, int right, int width)
{
	int i = left, j = width + 1, k = i;
	while (i <= width && j <= right)
	{
		des[k++] = sou[i] < sou[j] ? sou[i++] : sou[j++];
	}

	while (i <= m)
	{
		des[k++] = sou[i++];
	}

	while (j <= right)
	{
		des[k++] = sou[j++];
	}
}

template<class Type>
void PassMerge(Type* br, Type* ar, int left, int right)
{
	if (left < right)
	{
		int m = (right - left) / 2 + left;
		PassMerge(br, ar, left, m);
		Merge(br, ar, left, right, m);
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

template<class Type>       //非递归
void NicePassMerge(Type* des, Type* sou, int s, int n)
{
	int i = 0;
	cout << s << endl;
	for (i = 0, i + 2 * s - 1 <= n - 1; i += 2 * s)
	{
		Merge(des, sou, i, i + s - 1, i + 2 * s - 1);
	}

	if (n - 1 > i + s - 1)
	{
		Merge(des, sou, i, i + s - 1, n - 1);
	}
	else
	{
		for (int j = i; j < n; j++)
		{
			des[j] = sou[j];
		}
	}
}

template<class Type>
void NiceMergeSort(Type* ar, int len)
{
	Type* br = new Type[len];
	int s = 1;
	while (s < n)
	{
		NiceMergeSort(br, ar, s, len);
		s += s;
		NiceMergeSort(ar, br, s, len);
		s += s;
	}
	delete[]br;
}


int main()
{

	return 0;
}