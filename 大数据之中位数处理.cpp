#define _CRT_SECURE_NO_WARNINGS  //����fopen�����ľ��� 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
//����500M���ڴ棬����10G�����ݵ���λ��

#define NUM_SIZE (1024ll*1024*1024/4*10)  //10G��������
#define ITEM_SIZE (1024*1024/4*500)       //������ʹ�õ��ڴ�500M��������������
#define ITEM_RANGE 10736763               //ÿ����ƽ�������ݿ�ȣ�32767*32767/100+1 ȡ��

void QuickSort(int *arr,int len);         //��������
void HeapSort(int *arr,int len);          //������

//ͳ�ƶ������ļ�path���ֽ���
long long FileSize(const char *path)
{
	FILE *fr = fopen(path,"rb");
	assert(fr != NULL);

	fseek(fr,0,SEEK_END); 
	long long count = ftell(fr);
	
	fclose(fr);
	return count;
}

//���������
void CreateBigFile(const char *path)
{
	FILE *fw = fopen(path,"wb");//����������
	assert(fw != NULL);

	int tmp;

	for(long long i=0;i<NUM_SIZE;i++)
	{
		tmp = rand()*rand();
		fwrite(&tmp,sizeof(int),1,fw);
	}
	fclose(fw);
}

//��Ҫ����λ���������е����ְ��ηֳ�100��//ʵ��Windows 7���ļ�����509��֮�����ٴ��µ��ļ�
//Ȼ����ĳһ���ֶκ������ҵ���λ��
int Division(char *path)
{
#define DIV_NUM 100
	char pathArr[DIV_NUM][10];//���100���ļ���

	int *buf = (int *)malloc(ITEM_SIZE*sizeof(int));//���������ʱ��Դ�ļ��ж�ȡ����

	FILE *fw[DIV_NUM]; //�ļ�ָ������

	long long i;
	for(i=0;i<DIV_NUM;i++)//�����ļ�����
	{
		sprintf(pathArr[i],"%d.txt",i);
	}
	
	for(i=0;i<DIV_NUM;i++)
	{
		assert((fw[i]=fopen(pathArr[i],"wb"))!=NULL);//�򿪳ɹ�
	}

	FILE *fr = fopen(path,"rb"); //��Դ�ļ�
	assert(fr  != NULL);

	int len = 0;//��ȡ���ݵĳ���
	int index;
	while((len=fread(buf,sizeof(int),ITEM_SIZE,fr))>0)//��ԭ�ļ��ж�ȡ���ݣ�Ȼ�󱣴浽������100���ļ���
	{
		for(int i=0;i<len;i++)
		{
			index = buf[i]/ITEM_RANGE;
			fwrite(&buf[i],sizeof(int),1,fw[index]);  //�����ֱ��浽��Ӧ���ļ���
		}
	}

	for(i=0;i<DIV_NUM;i++)
	{
		fclose(fw[i]);
	}
	fclose(fr);
	

	long long mid =  NUM_SIZE/2;//��λ��
	long long count = 0;//��ǰ�ֶ��ļ����ֽ���

	for(i=0;i<DIV_NUM;i++)//�ȳ�����λ��λ�����ڵķֶ��ļ���Ȼ���ڷֶ��ļ����ҵ�����λ��
	{
		count += FileSize(pathArr[i]); 
		if(count >= mid*sizeof(int))  //��λ����i���ļ���
		{
			break;
		}
	}

	long long tmp = mid - (count-FileSize(pathArr[i]))/sizeof(int);//������λ���ڵ�i���ļ��еĵڼ���(����С��)����
	 
	//todo�����i�ŷֶ��ļ��Ĵ�Сû�г����ڴ�������ֱ����������������ƻ���Ҫ�����ֶΡ�
	//������費����
	fr = fopen(pathArr[i],"rb");
	assert(fr != NULL);
	len = fread(buf,sizeof(int),ITEM_SIZE,fr);
	fclose(fr);

	HeapSort(buf,len);
	
	int num = buf[tmp];

	free(buf);

	return num;
}

//��������Ļ��ֺ���
static int Partition(int *arr,int low,int high)
{
	int tmp = arr[low];

	while(low < high)
	{
		while(low<high && arr[high]>=tmp)//�Ӻ���ǰ�ұȻ�׼С������
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

		while(low<high && arr[low]<=tmp)//��ǰ�����ұȻ�׼�������
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

	if(low+1 < par)//��������������
	{
		Quick(arr,low,par-1);
	}
	if(par+1 < high)
	{
		Quick(arr,par+1,high);
	}
}

//��������
void QuickSort(int *arr,int len)
{
	Quick(arr,0,len-1);
}

//һ�ε�������
static void HeapAdjust(int *arr,int start,int end)
{//O(logn),O(1),
	int tmp = arr[start];
	int parent = start;

	for(int i=2*parent+1;i<=end;i=2*i+1)
	{
		if((i+1<=end) && (arr[i]<arr[i+1]))
		{
			++i;
		}//iһ�������Һ��ӽϴ�ֵ���±�

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

void HeapSort(int *arr,int len)//O(nlogn),O(1),���ȶ�
{
	//��һ���������
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

		HeapAdjust(arr,0,len-i-1-1);//�Ѿ���������ݲ��������
	}
}

//��ȫ�����ݶ����ڴ棬������λ��
//��֤�����ֶεķ����Ƿ���ȷ
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
	int tmp = arr[len/2]; // ��λ��
	free(arr);

	return tmp;
}

int main()
{
	char *path  = "big.txt";
	//printf("%d\n",Mid1(path));
	clock_t c1 = clock();
	CreateBigFile(path);//����10�ڸ����ִ����Ҫ300��
	clock_t c2 = clock();
	printf("����10�ڸ����ֵ�ʱ��Ϊ%d����\n",c2-c1);//�����Ҫ300��
	int num = Division(path);//���300������
	printf("%d\n",num);
	c1 = clock();
	printf("��ȡ10�ڸ����ֵ���λ��ʱ��Ϊ%d����\n",c1-c2);
	
	return 0;
}
