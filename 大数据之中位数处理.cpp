#define _CRT_SECURE_NO_WARNINGS  //消除fopen函数的警告 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
//利用500M的内存，计算10G的数据的中位数

#define NUM_SIZE (1024ll*1024*1024/4*10)  //10G的数据量
#define ITEM_SIZE (1024*1024/4*500)       //单次能使用的内存500M，操作的数据量
#define ITEM_RANGE 10736763               //每个段平均的数据宽度，32767*32767/100+1 取整

void QuickSort(int *arr,int len);         //快速排序
void HeapSort(int *arr,int len);          //堆排序

//统计二进制文件path的字节数
long long FileSize(const char *path)
{
	FILE *fr = fopen(path,"rb");
	assert(fr != NULL);

	fseek(fr,0,SEEK_END); 
	long long count = ftell(fr);
	
	fclose(fr);
	return count;
}

//产生随机数
void CreateBigFile(const char *path)
{
	FILE *fw = fopen(path,"wb");//二进制数据
	assert(fw != NULL);

	int tmp;

	for(long long i=0;i<NUM_SIZE;i++)
	{
		tmp = rand()*rand();
		fwrite(&tmp,sizeof(int),1,fw);
	}
	fclose(fw);
}

//需要找中位数，则将所有的数字按段分成100段//实测Windows 7打开文件超过509个之后不能再打开新的文件
//然后在某一个分段函数中找到中位数
int Division(char *path)
{
#define DIV_NUM 100
	char pathArr[DIV_NUM][10];//存放100个文件名

	int *buf = (int *)malloc(ITEM_SIZE*sizeof(int));//用来存放临时从源文件中读取的数

	FILE *fw[DIV_NUM]; //文件指针数组

	long long i;
	for(i=0;i<DIV_NUM;i++)//生成文件名称
	{
		sprintf(pathArr[i],"%d.txt",i);
	}
	
	for(i=0;i<DIV_NUM;i++)
	{
		assert((fw[i]=fopen(pathArr[i],"wb"))!=NULL);//打开成功
	}

	FILE *fr = fopen(path,"rb"); //打开源文件
	assert(fr  != NULL);

	int len = 0;//读取数据的长度
	int index;
	while((len=fread(buf,sizeof(int),ITEM_SIZE,fr))>0)//从原文件中读取数据，然后保存到其它的100个文件中
	{
		for(int i=0;i<len;i++)
		{
			index = buf[i]/ITEM_RANGE;
			fwrite(&buf[i],sizeof(int),1,fw[index]);  //将数字保存到对应的文件中
		}
	}

	for(i=0;i<DIV_NUM;i++)
	{
		fclose(fw[i]);
	}
	fclose(fr);
	

	long long mid =  NUM_SIZE/2;//中位数
	long long count = 0;//当前分段文件的字节数

	for(i=0;i<DIV_NUM;i++)//先初步定位中位数所在的分段文件，然后在分段文件中找到该中位数
	{
		count += FileSize(pathArr[i]); 
		if(count >= mid*sizeof(int))  //中位数在i号文件中
		{
			break;
		}
	}

	long long tmp = mid - (count-FileSize(pathArr[i]))/sizeof(int);//计算中位数在第i个文件中的第几个(按大小算)数字
	 
	//todo如果第i号分段文件的大小没有超过内存限制则直接排序，如果超过限制还需要继续分段。
	//这里假设不超过
	fr = fopen(pathArr[i],"rb");
	assert(fr != NULL);
	len = fread(buf,sizeof(int),ITEM_SIZE,fr);
	fclose(fr);

	HeapSort(buf,len);
	
	int num = buf[tmp];

	free(buf);

	return num;
}

//快速排序的划分函数
static int Partition(int *arr,int low,int high)
{
	int tmp = arr[low];

	while(low < high)
	{
		while(low<high && arr[high]>=tmp)//从后往前找比基准小的数据
		{
			high--;
		}
		if(low == high)
		{
			break;
		}
		else
		{
			arr[low] = arr[high];//************
		}

		while(low<high && arr[low]<=tmp)//从前往后找比基准大的数字
		{
			low++;
		}
		if(arr[low] > tmp)
		{
			arr[high] = arr[low];//***********
		}
		else
		{
			break;
		}
	}

	arr[low] = tmp;

	return low;
}

static void Quick(int *arr,int low,int high)
{
	int par = Partition(arr,low,high);

	if(low+1 < par)//至少有两个数据
	{
		Quick(arr,low,par-1);
	}
	if(par+1 < high)
	{
		Quick(arr,par+1,high);
	}
}

//快速排序
void QuickSort(int *arr,int len)
{
	Quick(arr,0,len-1);
}

//一次调整过程
static void HeapAdjust(int *arr,int start,int end)
{//O(logn),O(1),
	int tmp = arr[start];
	int parent = start;

	for(int i=2*parent+1;i<=end;i=2*i+1)
	{
		if((i+1<=end) && (arr[i]<arr[i+1]))
		{
			++i;
		}//i一定是左右孩子较大值的下标

		if(tmp < arr[i])
		{
			arr[parent] = arr[i];
			parent = i;
		}
		else
		{
			//arr[parent] = tmp;
			//return ;
			break;
		}
	}
	arr[parent] = tmp;
}

void HeapSort(int *arr,int len)//O(nlogn),O(1),不稳定
{
	//第一个建大根堆
	int i;
	int tmp;
	for(i=(len-1-1)/2;i>=0;i--)//O(nlogn)
	{
		HeapAdjust(arr,i,len-1);
	}

	for(i=0;i<len-1;i++)//O(nlogn)
	{
		tmp = arr[0];
		arr[0] = arr[len-1-i];
		arr[len-1-i] = tmp;

		HeapAdjust(arr,0,len-i-1-1);//已经有序的数据不参与调整
	}
}

//将全部数据读到内存，计算中位数
//验证上述分段的方法是否正确
int Mid1(const char *path)
{
	//int *arr = (int *)malloc(NUM_SIZE*sizeof(int));
	int *arr = NULL;
	assert(arr != NULL);
	FILE *fr = fopen(path,"rb");
	assert(fr != NULL);
	int len = fread(arr,sizeof(int),NUM_SIZE,fr);
	fclose(fr);

	HeapSort(arr,len);
	int tmp = arr[len/2]; // 中位数
	free(arr);

	return tmp;
}

int main()
{
	char *path  = "big.txt";
	//printf("%d\n",Mid1(path));
	clock_t c1 = clock();
	CreateBigFile(path);//产生10亿个数字大概需要300秒
	clock_t c2 = clock();
	printf("产生10亿个数字的时间为%d毫米\n",c2-c1);//大概需要300秒
	int num = Division(path);//大概300秒左右
	printf("%d\n",num);
	c1 = clock();
	printf("获取10亿个数字的中位数时间为%d毫米\n",c1-c2);
	
	return 0;
}
