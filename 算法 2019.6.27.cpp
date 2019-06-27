#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<windows.h>
#include<limits.h>
#include<queue>
#include<stack>
#include<map>
#include<iomanip>
using namespace std;

const int xlen = 7;
const int ylen = 6;
int ** Get2Array(int row,int col)
{
	int **s = (int**)malloc(sizeof(int*)*row);
	for(int i = 0;i<row;++i)
	{
		s[i] = (int *)malloc(sizeof(int)*col);
		memset(s[i],0,sizeof(int)*col);
	}
	return s;
}
void Print2Array(int **s,int row,int col)
{
	for(int i = 0;i<row;++i)
	{
		for(int j = 0;j<col;++j)
		{
			cout<<setw(4)<<s[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}
int num = 0;
int LCSLength(char *X,char *Y,int m,int n,int **c,int **s)
{
	num+=1;
	if(m <= 0 || n <= 0) return 0;
	if(c[m][n] > 0) return c[m][n];
	if(X[m] == Y[n])
	{
		c[m][n] = LCSLength(X,Y,m-1,n-1,c,s) + 1;
		s[m][n] = 1; // 
	}
	else
	{
		int len1 = LCSLength(X,Y,m-1,n,c,s);
		int len2 = LCSLength(X,Y,m,n-1,c,s);
		if(len1 > len2)
		{
			s[m][n] = 2;
			c[m][n] = len1;
		}
		else
		{
			s[m][n] = 3;
			c[m][n] = len2;
		}
	}
	return c[m][n];
}
void BackTrack(char *X,int **s,int m,int n)
{
	if(m <= 0 || n <= 0) return ;
	if(s[m][n] == 1)
	{
		BackTrack(X,s,m-1,n-1);
		cout<<X[m];
	}else if(s[m][n] == 2)
	{
		BackTrack(X,s,m-1,n);
	}else 
	{
		BackTrack(X,s,m,n-1);
	}
}

int LCSLength2(char *X,char *Y,int m,int n,int **c,int **s)
{
	for(int i = 0;i<=m;++i) c[i][0] = 0;
	for(int i = 0;i<=n;++i) c[0][i] = 0;
	for(int i = 1;i<=m;++i)
	{
		for(int j = 1;j<=n;++j)
		{
			if(X[i] == Y[j])
			{
				c[i][j] = c[i-1][j-1] + 1;
			}else 
			{
				c[i][j] = c[i-1][j] > c[i][j-1]? c[i-1][j]:c[i][j-1];
			}
		}
		Print2Array(c,m+1,n+1);
	}
	return c[m][n];
}
int main()
{
	char X[xlen+2] ={"#ABCBDAB"};
	char Y[ylen+2] ={"#BDCABA"};
	int **c = Get2Array(xlen+1,ylen+1);
	int **s = Get2Array(xlen+1,ylen+1);
	int maxlen = LCSLength2(X,Y,xlen,ylen,c,s);

	cout<<maxlen<<endl;
	Print2Array(c,xlen+1,ylen+1);
	Print2Array(s,xlen+1,ylen+1);

	//BackTrack(X,s,xlen,ylen);
	cout<<endl;
	cout<<num<<endl;
	return 0;
}
#if 0

// 1) 
template<class Type>
void Print(Type *ar,int n)
{
	for(int i = 0;i<n;++i)
	{
		cout<<ar[i]<<" ";
	}
	cout<<endl;
}
template<class Type>
void Copy(Type *di,Type *si,int left,int right)
{
	for(int i = left;i<=right; ++i)
	{
		di[i] = si[i];
	}
}
template<class Type>
void Merge(Type *di,Type *si,int left,int m , int right)
{
	int i = left, j = m+1;
	int k = i;
	while(i <= m && j <= right)
	{
		di[k++] = si[i] < si[j]? si[i++]:si[j++];
	}

	while(i <= m )
	{
		di[k++] = si[i++];
	}

	while(j <= right)
	{
		di[k++] = si[j++];
	}
}
template<class Type>
void PassMerge(Type *br,Type *ar,int left,int right)
{
	if(left < right)// left = 1   right = 2
	{
		int m = (right - left)/2 + left;
		PassMerge(br,ar,left,m);
		PassMerge(br,ar,m+1,right);
		Merge(br,ar,left,m,right);
		Copy(ar,br,left,right);
	}
}
template<class Type>
void MergeSort(Type *ar,int n)
{
	Type *br = new Type[n];
	PassMerge(br,ar,0,n-1);
	delete []br;
}
template<class Type>
void NicePassMerge(Type *di,Type *si,int s,int n)
{
	int i = 0;
	cout<<s<<endl;
	for(i = 0; i+2*s-1 <= n-1; i+=2*s)
	{
		Merge(di,si,i,i+s-1,i+2*s-1);
		cout<<i<<" "<<i+s-1<<" "<<i+2*s-1<<endl;
	}
	if(n-1 > i+s-1)
	{
		Merge(di,si,i,i+s-1,n-1);
		cout<<i<<" "<<i+s-1<<" "<<n-1<<endl;
	}
	else
	{
		for(int j = i;j<n;++j)
		{
			di[j] = si[j];
		}
	}

}
template<class Type>
void NiceMergeSort(Type *ar,int n)
{
	Type *br = new Type[n];
	int s = 1;
	while(s < n)
	{
		NicePassMerge(br,ar,s,n);// 1
		s+=s; // 2
		NicePassMerge(ar,br,s,n);// 2
		s+=s; // 4
	}

	delete []br;
}
int main()
{
	int ar[]={56,23,45,78,90,100,89,12,67,34,50};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	NiceMergeSort(ar,n);
	Print(ar,n);
	return 0;
}



template<class Type>
int Partition(Type *ar,int left,int right)
{
	int i = left, j = right;
	Type tmp = ar[i];
	while(i<j)
	{
		while(i<j && ar[j] > tmp) --j;
		if(i<j) ar[i] = ar[j];
		while(i<j && ar[i] <= tmp) ++i;
		if(i<j) ar[j] = ar[i];
	}
	ar[i] = tmp;
	return i;
}
template<class Type>
int RandPartition(Type *ar,int left, int right)
{
	srand(time(NULL));
	int rindex = rand()%( right - left + 1) + left;
	swap(ar[left],ar[rindex]);

	return Partition(ar,left,right);
}
template<class Type>
void Pass(Type *ar,int left,int right)
{
	if(left < right)
	{
		int mid = Partition(ar,left,right);
		Pass(ar,left,mid-1);
		Pass(ar,mid+1,right);
	}
}
template<class Type>
void NicePass(Type *ar,int left,int right)
{
	if(left >= right) return ;
	stack<int> s;
	s.push(left);
	s.push(right);
	while(!s.empty())
	{
		right = s.top(); s.pop();
		left = s.top(); s.pop();
		int mid = Partition(ar,left,right);
		if(left < mid-1)
		{
			s.push(left);
			s.push(mid-1);
		}
		if(mid+1 < right)
		{
			s.push(mid+1);
			s.push(right);
		}
	}
}

template<class Type>
void QNicePass(Type *ar,int left,int right)
{
	if(left >= right) return ;
	queue<int> s;
	s.push(left);
	s.push(right);
	while(!s.empty())
	{
		left = s.front(); s.pop();
		right = s.front(); s.pop();
		int mid = Partition(ar,left,right);
		if(left < mid-1)
		{
			s.push(left);
			s.push(mid-1);
		}
		if(mid+1 < right)
		{
			s.push(mid+1);
			s.push(right);
		}
	}
}
template<class Type>
void QuickSort(Type *ar,int n)
{
	QNicePass(ar,0,n-1);
}
template<class Type>
const Type & Select_K(Type *ar,int left,int right,int k)
{
	if(left == right && k == 1) return ar[left];
	int pos = Partition(ar,left,right);
	int j = pos - left + 1;
	if(k <= j) return Select_K(ar,left,pos,k);
	else return Select_K(ar,pos+1,right,k - j);
}
template<class Type>
const Type & Select_K_Min(Type *ar,int n,int k)
{
	return Select_K(ar,0,n-1,k);
}
int main()
{
	int ar[]={56,23,45,78,90,100,89,12,67,34};
	int n = sizeof(ar)/sizeof(ar[0]);
	for(int k = 1;k<=n;++k)
	{
		cout<<k<<" => "<<Select_K_Min(ar,n,k)<<endl;
	}

	return 0;

}

#define BOARDSIZE  8
typedef int Array[BOARDSIZE][BOARDSIZE];

void Print2Array(Array ar)
{
	for(int i = 0;i<BOARDSIZE;++i)
	{
		for(int j = 0;j<BOARDSIZE;++j)
		{
			cout<<setw(3)<<ar[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}
int tile = 1;
void ChessBoard(Array ar,int tr,int tc,int dr,int dc,int size)
{
	if(size <= 1) return ;
	Print2Array(ar);
	int s = size/2;
	int t = tile++;
	if(dr < tr + s && dc < tc + s)
	{
		ChessBoard(ar,tr,tc,dr,dc,s);
	}
	else
	{
		ar[tr+s-1][tc+s-1] = t;
		ChessBoard(ar,tr,tc,tr+s-1,tc+s-1,s);
	}

	if(dr < tr+s && dc >= tc + s)
	{
		ChessBoard(ar,tr,tc+s,dr,dc,s);
	}
	else
	{
		ar[tr+s-1][tc+s] = t;
		ChessBoard(ar,tr,tc+s,tr+s-1,tc+s,s);
	}

	if(dr >= tr + s && dc >= tc+s)
	{
		ChessBoard(ar,tr+s,tc+s,dr,dc,s);
	}
	else
	{
		ar[tr+s][tc+s] = t;
		ChessBoard(ar,tr+s,tc+s,tr+s,tc+s,s);
	}

	if(dr >= tr+s && dc < tc + s)
	{
		ChessBoard(ar,tr+s,tc,dr,dc,s);
	}
	else
	{
		ar[tr+s][tc+s-1] = t;
		ChessBoard(ar,tr+s,tc,tr+s,tc+s-1,s);
	}
}
int main()
{
	Array ar={0};
	int dr = 2,dc = 3;
	ar[dr][dc] = -1;
	ChessBoard(ar,0,0,dr,dc,BOARDSIZE);
	Print2Array(ar);

	return 0;
}


//B_ B+
#define M 5
#define MAXELEM (M-1) // 4  // 1   // 2
#define MINELEM (M/2) // 2 
typedef char KeyType;
typedef struct {} Record;
typedef struct
{
	KeyType key;
	Record *recptr;
}ElemType;  // key_value
struct BNode
{
	int num;
	BNode *parent;
	ElemType data[M+1];   // 0// 1 < 2 < 3 < 4 < 5
	BNode    *sub[M+1];  //    0   1   2   3   4   5 
};
typedef struct 
{
	BNode *pnode;
	int index;
	bool tag;  // true; false
}Result;

typedef struct
{
	BNode *root;
	int cursize;
}BTree;

Result FindValue(BTree &bt,KeyType kx)
{
	BNode *p = bt.root;
	Result res ={NULL,-1,false};
	while(p != NULL)
	{
		p->data[0].key = kx;
		int i = p->num;
		while(kx < p->data[i].key) --i;
		res.pnode = p;
		res.index = i;
		if(i > 0 && p->data[i].key == kx)
		{
			res.tag = true;
			break;
		}
		if(p->sub[i] == NULL)
		{
			res.tag = false;
			break;
		}
		p = p->sub[i];
	}
	return res;
}
//////////////////////////////////////////////
// B+
#define M 5
#define BRCHMAX (M-1)    // 1   // 2
#define BRCHMIN  (M/2) // 2 

#define LEAFMAX (M)     // 5
#define LEAFMIN (M/2+1) // 3
typedef enum{LEAF = 0 , BRCH = 1} NodeType;
typedef char KeyType;
typedef struct {} Record;
struct BNode
{
	NodeType utype; // LEAF // BRCH
	int num;
	BNode *parent;
	KeyTyp key[M+1];
	union
	{
		struct
		{
			Record recptr[M+1];
			BNode *prev,BNode *next;
		};
		BNode    *sub[M+1];  //    0   1   2   3   4   5 
	};
};
typedef struct 
{
	BNode *pnode;
	int index;
	bool tag;  // true; false
}Result;

typedef struct
{
	BNode *root;
	int cursize;
}BTree;


template<class KeyType>
class RBTree
{
private:
	typedef enum{RED = 0, BLACK = 1} ColorType;
	typedef struct rb_node
	{
		rb_node *leftchild;
		rb_node *parent;
		rb_node *rightchild;
		ColorType color;
		KeyType key;
	}rb_node;

private:
	rb_node *head;
	int cursize;
	static rb_node *nil;
	static int ref;

	static rb_node *Buynode(rb_node *pa=NULL,ColorType color = RED)
	{
		rb_node *s =(rb_node*)malloc(sizeof(rb_node));
		if(NULL == s) exit(1);
		memset(s,0,sizeof(rb_node));
		s->parent = pa;
		s->color = color;
		return s;
	}
	static void Freenode(rb_node *p)
	{
		free(p);
	}

	void RotateLeft(rb_node *ptr)
	{
		rb_node * newroor = ptr->rightchild;
		newroot->parent = ptr->parent; // 1
		ptr->rightchild = newroot->leftchild;
		if(newroot->leftchild != NULL)
		{
			newroot->leftchild->parent = ptr;
		}
		newroot->leftchild = ptr;
		if(ptr->parent == head) // ptr => root;
		{
			head->parent = newroot;
		}
		else // ptr != root;
		{
			if(ptr = ptr->parent->leftchild)
			{
				ptr->parent->leftchild = newroot;
			}
			else
			{
				ptr->parent->rightchild = newroot;
			}
		}
		ptr->parent = newroot;
	}

	void RotateRight(rb_node *ptr)
	{
		rb_node *newroot = ptr->leftchild;
		newroot->parent = ptr->parent; // 1
		ptr->leftchild = newroot->rightchild;
		if(newroot->rightchild != NULL)
		{
			newroot->rightchild->parent = ptr;
		}
		newroot->rightchild = ptr;
		if(ptr->parent == head) // root;
		{
			head->parent = newroot;
		}else
		{
			if(ptr->parent->rightchild == ptr)
			{
				ptr->parent->rightchild = newroot;
			}
			else
			{
				ptr->parent->leftchild = newroot;
			}
		}
		ptr->parent = newroot;//3
	}
	void Adjust(rb_node *ptr)
	{
		rb_node *_X = ptr;
		rb_node *_Y = NULL;
		for(; _X->parent != head && _X->parent->color == RED; )
		{
			if(_X->parent->parent->rightchild == _X->parent) // right
			{
				_Y = _X->parent->parent->leftchild;
				if(_Y->color == RED)
				{
					_Y->color = BLACK;
					_X->parent->color = BLACK;
					_X->parent->parent->color = RED;
					_X = _X->parent->parent;
				}
				else
				{
					if(_X->parent->leftchild == _X)
					{
						_X = _X->parent;
						RotateRight(_X);
					}
					_X->parent->color = BLACK;
					_X->parent->parent->color = RED;
					RotateLeft(_X->parent->parent);
				}
			}
			else // left
			{

			}
		}
		head->parent->color = BLACK;
	}
public:
	RBTree():head(NULL),cursize(0)
	{
		if(ref == 0)
		{
			nil = Buynode(NULL,BLACK);
		}
		ref+=1;
		head = Buynode(nil);
		head->leftchild = nil;
		head->rightchild = nil;
	}
	~RBTree()
	{
		ref-=1;
		if(ref == 0)
		{
			Freenode(nil);
			nil = NULL;
		}
		//Clear();
		Freenode(head);
		head = NULL;
	}
	bool Insert(const KeyType &kx)
	{
		rb_node *pa = head;
		rb_node *p = head->parent; // root;
		while(p != nil && p->key != kx)
		{
			pa = p;
			p = kx < p->key ? p->leftchild:p->rightchild;
		}
		if(p != nil && p->key == kx) return false;

		p = Buynode(pa); // parent , color
		p->key = kx;
		p->leftchild = nil;
		p->rightchild = nil;
		if(pa == head)
		{
			pa->parent = pa->leftchild =pa->rightchild = p;
		}
		else
		{
			if(p->key < pa->key)
			{
				pa->leftchild = p;
				if(p->key < head->leftchild->key)
				{
					head->leftchild = p;
				}
			}
			else
			{
				pa->righchild = p;
				if(p->key > head->rightchild->key)
				{
					head->rightchild = p;
				}
			}
		}

		Adjust(p);
		cursize+=1;
		return true;
	}
};

template<class KeyType>
typename RBTree<KeyType>::rb_node * RBTree<KeyType>::nil = NULL;

template<class KeyType>
int RBTree<KeyType>::ref = 0;

int main()
{
	RBTree<int> myt;

	return 0;
}


template<class KeyType>
class AVLTree
{
private:
	struct AVLNode 
	{
		AVLNode *leftchild;
		AVLNode *parent;
		AVLNode *rightchild;
		int balance; // -1 0 1 
		KeyType key;
	};
private:
	AVLNode *head;
	int cursize;

	static AVLNode * Buynode(AVLNode *pa = NULL,
		AVLNode *left = NULL,AVLNode *right = NULL)
	{
		AVLNode *s = (AVLNode*)malloc(sizeof(AVLNode));
		if(NULL == s) exit(1);
		memset(s,0,sizeof(AVLNode));
		s->parent = pa;
		s->leftchild = left;
		s->rightchild = right;
		return s;
	}
	static void Freenode(AVLNode *p)
	{
		free(p);
	}

	void RotateLeft(AVLNode *ptr)
	{
		AVLNode * newroor = ptr->rightchild;
		newroot->parent = ptr->parent; // 1
		ptr->rightchild = newroot->leftchild;
		if(newroot->leftchild != NULL)
		{
			newroot->leftchild->parent = ptr;
		}
		newroot->leftchild = ptr;
		if(ptr->parent == head) // ptr => root;
		{
			head->parent = newroot;
		}
		else // ptr != root;
		{
			if(ptr = ptr->parent->leftchild)
			{
				ptr->parent->leftchild = newroot;
			}
			else
			{
				ptr->parent->rightchild = newroot;
			}
		}
		ptr->parent = newroot;
	}

	void RotateRight(AVLNode *ptr)
	{
		AVLNode *newroot = ptr->leftchild;
		newroot->parent = ptr->parent; // 1
		ptr->leftchild = newroot->rightchild;
		if(newroot->rightchild != NULL)
		{
			newroot->rightchild->parent = ptr;
		}
		newroot->rightchild = ptr;
		if(ptr->parent == head) // root;
		{
			head->parent = newroot;
		}else
		{
			if(ptr->parent->rightchild == ptr)
			{
				ptr->parent->rightchild = newroot;
			}
			else
			{
				ptr->parent->leftchild = newroot;
			}
		}
		ptr->parent = newroot;//3
	}

	void LeftBalance(AVLNode *ptr)
	{

	}
	void RightBalance(AVLNode *ptr)
	{
		AVLNode *rightsub = ptr->rightchild, *leftsub = NULL;
		switch(rightsub->balance)
		{
		case 0: cout<<"balance right "<<endl; break;
		case 1:
			ptr->balance = 0;
			rightsub->balance = 0;
			RotateLeft(ptr);
			break;
		case -1:
			leftsub = rightsub->leftchild;
			switch(leftsub->balance)
			{
			case 0: 
				ptr->balance = 0;
				rightsub->balance = 0;
				break;
			case 1: 
				ptr->balance = -1;
				rightsub->balance  = 0;
				break;
			case -1:
				ptr->balance = 0;
				rightsub->balance = 1;
				break;
			}
			leftsub->balance = 0;
			RotateRight(rightsub);
			RotateLeft(ptr);
			break;
		}
	}
	void Adjust_Tree(AVLNode *ptr)
	{
		AVLNode *_X = ptr;
		AVLNode *_Y = ptr->parent;
		int taller = 1;
		for(;taller == 1 && _Y != head; )
		{
			if(_Y->leftchild == _X)
			{
				switch(_Y->balance)
				{
				case 0: _Y->balance = -1; break;
				case 1: _Y->balance = 0; taller = 0; break;
				case -1:
					LeftBalance(_Y);
					taller = 0;
					break;
				}
			}
			else // _X parent right
			{
				switch(_Y->balance)
				{
				case 0: _Y->balance = 1; break;
				case -1: _Y->balance = 0; taller = 0; break;
				case 1: 
					RightBalance(_Y);
					taller = 0;
					break;
				}
			}
			_X = _Y;
			_Y = _Y->parent;
		}
	}
public:
	AVLTree():head(Buynode()),cursize(0) {}
	~AVLTree() {}

	bool InsertItem(const KeyType &kx)
	{
		AVLNode *pa = head; //
		AVLNode *p = head->parent;
		while(p != NULL && p->key != kx)
		{
			pa = p;
			p = kx < p->key? p->leftchild:p->rightchild;
		}
		if(p != NULL && p->key == kx) return false;
		p = Buynode(pa);
		p->balance = 0;
		p->leftchild = p->rightchild = NULL;
		if(pa == head)
		{
			head->parent = p;
			head->leftchild = head->rightchild = p;
		}
		else
		{
			if(p->key < pa->key)
			{
				pa->leftchild = p;
				if(p->key < head->leftchild->key)
				{
					head->leftchild = p;
				}
			}
			else
			{
				pa->rightchild = p;
				if(p->key > head->rightchild->key)
				{
					head->righthcild = p;
				}
			}
			Adjust_Tree(p);
		}
		return true;
	}
};

int main()
{
	AVLTree<int>  myt;

}

// avl // br
typedef int KeyType;
struct AVLNode
{
	AVLNode *leftchild;
	AVLNode *parent;
	AVLNode *rightchild;
	int balance; // -1,0,1; // |Depth(right)-Depth(left)| <= 1
	KeyType key;
};
typedef struct
{
	AVLNode *head;
	int cursize;
}AVLTree;
AVLNode * Buynode(AVLNode *pa=NULL,AVLNode *left = NULL,AVLNode *right = NULL)
{
	AVLNode *s = (AVLNode*)malloc(sizeof(AVLNode));
	if(NULL == s) exit(1);
	s->leftchild = left;
	s->parent = pa;
	s->rightchild = right;
	s->balance = 0;
	return 0;
}
void Freenode(AVLNode *p)
{
	free(p);
}
//////////////////////////////////////////////////////////
void RotateLeft(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *newroot = ptr->rightchild;
	newroot->parent = ptr->parent;//1
	ptr->rightchild = newroot->leftchild;
	if(newroot->leftchild != NULL)
	{
		newroot->leftchild->parent = ptr; // 2
	}
	newroot->leftchild = ptr;
	if(ptr->parent == myt.head)
	{
		myt.head = newroot;
	}else
	{
		if(ptr->parent->leftchild == ptr)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}
	ptr->parent = newroot; // 3
}

void RotateRight(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *newroot = ptr->leftchild;
	newroot->parent = ptr->parent; //1
	ptr->leftchild = newroot->rightchild;
	if(newroot->rightchild != NULL)
	{
		newroot->rightchild->parent = ptr;
	}
	newroot->rightchild = ptr;
	if(ptr->parent == myt.head)
	{
		myt.head->parent = newroot;
	}else 
	{
		if(ptr->parent->leftchild == ptr)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}
	ptr->parent = newroot; // 3
}
void LeftBalance(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *leftsub = ptr->leftchild, *rightsub = NULL;
	switch(leftsub->balance)
	{
	case 0: cout<<"left balance"<<endl; break;
	case -1: 
		ptr->balance = 0;
		leftsub->balance = 0;
		RotateRight(myt,ptr);
		break;
	case 1: 
		rightsub = leftsub->rightchild;
		switch(rightsub->balance)
		{
		case 0: break;
		case 1: break;
		case -1: break;
		}
		RotateLeft(myt,leftsub);
		RotateRight(myt,ptr);
		break;
	}
}

void RightBalance(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *rightsub = ptr->rightchild, *leftsub = NULL;
	switch(rightsub->balance)
	{
	case 0: cout<<"right ready balance "<<endl; break;
	case 1:
		ptr->balance = 0;
		rightsub->balance = 0;
		RotateLeft(myt,ptr);
		break;
	case -1:
		leftsub = rightsub->leftchild;
		switch(leftsub->balance)
		{
		case 0:
			ptr->balance = 0;
			rightsub->balance = 0;
			break;
		case 1: 
			ptr->balance = -1;
			rightsub->balance = 0;
			break;
		case -1:
			ptr->balance = 0;
			rightsub->balance = 1;
			break;
		}
		leftsub->balance = 0;
		RotateRight(myt,rightsub);
		RotateLeft(myt,ptr);
		break;
	}
}
void AdjustTree(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *pa = ptr->parent;
	for(; ;)
	{
		if(pa->leftchild == ptr) // left
		{
			switch(pa->balance)
			{
			case 0: pa->balance = -1; break;
			case 1: pa->balance = 0; break;
			case -1: 
				LeftBalance(myt,pa);
				break;
			}
		}
		else
		{ 
			switch(pa->balance)
			{
			case 0: pa->balance = 1; break;
			case -1: pa->balance = 0; break;
			case 1: 
				RightBalance(myt,pa);
				break;
			}
		}
		ptr = pa;
		pa = pa->parent;
	}
}
bool InsertItem(AVLTree &myt,KeyType kx)
{
	AVLNode *pa = myt.head;        // head
	AVLNode *p = myt.head->parent; // root
	while(p != NULL && p->key != kx)
	{
		pa = p;
		p = kx < p->key? p->leftchild:p->rightchild;
	}
	if(p != NULL && p->key == kx) return false;
	p = Buynode(pa);
	if(pa == myt.head)
	{
		myt.head->parent = p;
		myt.head->leftchild = p;
		myt.head->rightchild = p;
	}
	else
	{
		if(p->key < pa->key)
		{
			pa->leftchild = p;
			if(p->key < myt.head->leftchild->key)
			{
				myt.head->leftchild = p;
			}
		}
		else
		{
			pa->rightchild = p;
			if(p->key > myt.head->rightchild->key)
			{
				myt.head->rightchild = p;
			}
		}
		AdjustTree(myt,p);
	}
	myt.cursize+=1;
	return true;
}
int main()
{
	AVLTree myt;
}

template<class KeyType>
class BSTree
{
private:
	struct BstNode
	{
		BstNode *leftchild;
		BstNode *parent;
		BstNode *rightchild;
		KeyType key;
	};
private:
	BstNode *head;
	int cursize;

	static BstNode * Buynode(BstNode *pa=NULL,BstNode *left = NULL,BstNode *right = NULL)
	{
		BstNode *s = (BstNode*)malloc(sizeof(BstNode));
		if(NULL == s) exit(1);
		s->leftchild = left;
		s->parent = pa;
		s->rightchild = right;
		return s;
	}
	static void Freenode(BstNode *p)
	{
		free(p);
	}

	static void InOrder(BstNode *p)
	{
		if(p != NULL)
		{
			InOrder(p->leftchild);
			cout<<p->key<<" ";
			InOrder(p->rightchild);
		}
	}
	 BstNode * First(BstNode *ptr)
	{
		while(ptr != NULL && ptr->leftchild != NULL)
		{
			ptr = ptr->leftchild;
		}
		return ptr;
	}
	BstNode * Next(BstNode *ptr)
	{
		if(ptr == NULL) return NULL;
		if(ptr->rightchild != NULL)
		{
			return First(ptr->rightchild);
		}else
		{
			BstNode *pa = ptr->parent;
			while(pa != head && ptr != pa->leftchild)
			{
				ptr = pa;
				pa = pa->parent;
			}
			if(pa == head)
			{
				pa = NULL;
			}
			return pa;
		}
	}
	bool InsertItem(BstNode *&ptr,BstNode *pa ,const KeyType &kx)
	{
		bool res = false;
		if(ptr == NULL)
		{
			ptr = Buynode(pa);
			ptr->key = kx;
			if(cursize == 0)
			{
				head->parent = ptr;
				head->leftchild = ptr;
				head->rightchild = ptr;
			}
			else
			{
				if(ptr->key > head->rightchild->key)
				{
					head->rightchild = ptr;
				}
				if(ptr->key < head->leftchild->key)
				{
					head->leftchild = ptr;
				}
			}
			cursize+=1;
			res = true;
		}else if(kx < ptr->key)
		{
			res = InsertItem(ptr->leftchild,ptr,kx);
		}else if(kx > ptr->key)
		{
			res =InsertItem(ptr->rightchild,ptr,kx);
		}
		return res;
	}
	bool RemoveItem(BstNode *&ptr,const KeyType &kx)
	{
		bool res = false;
		if(NULL == ptr) return res;
		if(kx < ptr->key)
		{
			res = RemoveItem(ptr->leftchild,kx);
		}else if(kx > ptr->key)
		{
			res = RemoveItem(ptr->rightchild,kx);
		}else if(ptr->leftchild != NULL && ptr->rightchild != NULL)
		{
			BstNode * nt = Next(ptr);
			ptr->key = nt->key;
			res = RemoveItem(ptr->rightchild,nt->key);
		}else
		{// leaf // brch;// root;
			BstNode *child = ptr->leftchild != NULL? 
				ptr->leftchild:ptr->rightchild;
			if(child != NULL) child->parent = ptr->parent;
			BstNode *q = ptr;
			ptr = child;
			Freenode(q);
			cursize-=1;
			res = true;
		}
		return res;
	}
public:
	BSTree():head(Buynode()),cursize(0){}
	~BSTree()
	{
	}

	bool InsertItem(const KeyType &kx)
	{
		return InsertItem(head->parent,head,kx);
	}
	void InOrder() const
	{
		InOrder(head->parent);
		cout<<endl;
	}
	bool RemoveItem(const KeyType &kx)
	{
		return RemoveItem(head->parent,kx);
	}
	begin();
	end();
	class const_iterator
	{
	public:
		const_iterator();
		operator*() const;
		operator->() const;
		operator++();
		operator++(int);
		operator--();
		operator--(int);
		operator==();
		operator!=();

	protected:

		BstNode *_Ptr;
	};
	class iterator : public const_iterator
	{
	};

};
int main()
{
	int ar[]={53,17,78,9,45,65,87,23,81,94,88,9,53,87};
	int n = sizeof(ar)/sizeof(ar[0]);
	int kx;
	BSTree<int> myt;
	for(int i = 0;i<n;++i)
	{
		cout<<myt.InsertItem(ar[i]);
	}
	cout<<endl;
	
	BSTree<int>::iterator it = myt.begin();
	for(; it != myt.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	return 0;
}


typedef int ElemType;
typedef struct BstNode
{
	BstNode *leftchild;
	BstNode *parent;
	BstNode *rightchild;
	ElemType data;
}BstNode;
typedef struct 
{
	BstNode *head;
	int cursize;
}BSTree;


BstNode *Buynode(BstNode *pa = NULL,BstNode *left = NULL,BstNode *right=NULL)
{
	BstNode *s = (BstNode*)malloc(sizeof(BstNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BstNode));
	s->leftchild = left;
	s->parent = pa;
	s->rightchild = right;
	return s;
}
void Freenode(BstNode *p)
{
	free(p);
}

void InitBSTree(BSTree &bt)
{
	bt.head = Buynode();
	bt.cursize = 0;
}

bool InsertItem(BSTree &bt,ElemType x)
{
	BstNode *pa = bt.head;
	BstNode *p = bt.head->parent; // root;
	while(p != NULL && p->data != x)
	{
		pa = p;
		p = x > p->data ? p->rightchild:p->leftchild;
	}
	if(p != NULL && p->data == x) return false;
	p = Buynode(pa);
	p->data = x;
	if(pa == bt.head)
	{
		pa->parent = p;
		pa->leftchild = p;
		pa->rightchild = p;
	}
	else
	{
		if(p->data < pa->data)
		{
			pa->leftchild = p;
			if(p->data < bt.head->leftchild->data)
			{
				bt.head->leftchild = p;
			}
		}
		else
		{
			pa->rightchild = p;
			if(p->data > bt.head->rightchild->data)
			{
				bt.head->rightchild = p;
			}
		}
	}
	bt.cursize +=1;
	return true;
}
void InOrder(BstNode *p)
{
	if(p != NULL)
	{
		InOrder(p->leftchild);
		cout<<p->data<<" ";
		InOrder(p->rightchild);
	}
}
void InOrder(BSTree &bt)
{
	InOrder(bt.head->parent);
}
BstNode * FindValue(BSTree &bt,ElemType x)
{
	BstNode *p = bt.head->parent; // root;
	while(p != NULL && p->data != x)
	{
		p = x > p->data ? p->rightchild:p->leftchild;
	}
	return p;
}
BstNode * Search(BstNode *p,ElemType x)
{
	if(p == NULL || p->data == x) return p;
	else if(x < p->data) return Search(p->leftchild,x);
	else return Search(p->rightchild,x);
}
BstNode * SearchValue(BSTree &bt,ElemType x)
{
	return Search(bt.head->parent,x);
}
BstNode * First(BstNode *ptr)
{
	while(ptr != NULL && ptr->leftchild != NULL)
	{
		ptr = ptr->leftchild;
	}
	return ptr;
}
BstNode * Next(BSTree &bt,BstNode *ptr)
{
	if(ptr == NULL || ptr == bt.head) return NULL;
	if(ptr->rightchild != NULL)
	{
		return First(ptr->rightchild);
	}
	else
	{
		BstNode *pa = ptr->parent;
		while(pa != bt.head && pa->leftchild != ptr)
		{
			ptr = pa;
			pa = pa->parent;
		}
		if(pa == bt.head)
		{
			pa = NULL;
		}
		return pa;
	}
}
void NiceInOrder(BSTree &bt)
{
	for(BstNode *p = First(bt.head->parent);
		               p != NULL; p = Next(bt,p))
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
}
int GetSize(BSTree &bt) { return bt.cursize;}
int Empty(BSTree &bt) { return GetSize(bt) == 0;}

bool RemoveItem(BSTree &bt,ElemType x)
{
	if(Empty(bt)) return false;
	BstNode *p = FindValue(bt,x);
	if(NULL == p) return false;

	if(p->leftchild != NULL && p->rightchild != NULL)
	{
		BstNode *nt = Next(bt,p);
		p->data = nt->data;
		p = nt;
	}
	BstNode *pa = p->parent;
	////////////////////////////////
	BstNode * child = p->leftchild != NULL? p->leftchild:p->rightchild;
	if(child != NULL) child->parent = pa;
	if(pa == bt.head)
	{
		pa->parent = child;
	}
	else
	{
		if(p == pa->leftchild)
		{
			pa->leftchild = child;
		}
		else
		{
			pa->rightchild = child;
		}
	}
	Freenode(p);
	bt.cursize-=1;
	return true;
}
int main()
{
	int ar[]={53,17,78,9,45,65,87,23,81,94,88};
	int n = sizeof(ar)/sizeof(ar[0]);
	int x;
	BSTree myt;
	InitBSTree(myt);
	for(int i = 0;i<n;++i)
	{
		InsertItem(myt,ar[i]);
	}
	InOrder(myt);
	cout<<endl;
	NiceInOrder(myt);
	while(cin>>x , x != -1)
	{
		RemoveItem(myt,x);
		NiceInOrder(myt);
	}
	return 0;
}



typedef char ElemType;
#define END '#'
typedef enum{LINK = 0,THREAD = 1} PointerTag;
typedef struct BiThrNode // binarytreenode
{
	BiThrNode *leftchild;
	BiThrNode *rightchild;
	PointerTag Ltag, Rtag;
	ElemType data;
}BiThrNode,*BinaryThreadTree;

BiThrNode *Buynode()
{
	BiThrNode *s = (BiThrNode*)malloc(sizeof(BiThrNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BiThrNode));
	return s;
}
void Freenode(BiThrNode *p)
{
	free(p);
}


BiThrNode * CreateTree2(ElemType *&str)
{
	BiThrNode *s = NULL;
	if(*str != END)
	{
		s = Buynode();
		s->data = *str;
		s->leftchild = CreateTree2(++str);
		s->rightchild = CreateTree2(++str);
	}
	return s;
}
void InOrder(BiThrNode *p)
{
	if(p != NULL)
	{
		InOrder(p->leftchild);
		cout<<p->data<<" ";
		InOrder(p->rightchild);
	}
}
void MakeThread(BiThrNode *p,BiThrNode *&ptr)
{
	if(p != NULL)
	{
		MakeThread(p->leftchild,ptr);
		if(p->leftchild == NULL)
		{
			p->leftchild = ptr;
			p->Ltag = THREAD;
		}
		if(ptr != NULL && ptr->rightchild == NULL)
		{
			ptr->rightchild = p;
			ptr->Rtag = THREAD;
		}
		ptr = p;
		MakeThread(p->rightchild,ptr);

	}
}
void MakeThreadTree(BiThrNode *p)
{
	BiThrNode *ptr = NULL;
	MakeThread(p,ptr);
	ptr->rightchild = NULL;
	ptr->Rtag = THREAD;
}

BiThrNode * First(BiThrNode *ptr)
{
	while(ptr != NULL && ptr->Ltag != THREAD)
	{
		ptr = ptr->leftchild;
	}
	return ptr;
}
BiThrNode * Next(BiThrNode *ptr)
{
	if(NULL == ptr) return NULL;
	if(ptr->Rtag == THREAD)
	{
		return ptr->rightchild;
	}
	else
	{
		return First(ptr->rightchild);
	}
}
BiThrNode *Last(BiThrNode *ptr)
{
	while(ptr != NULL && ptr->Rtag != THREAD)
	{
		ptr = ptr->rightchild;
	}
	return ptr;
}
BiThrNode *Prev(BiThrNode *ptr)
{
	if(NULL == ptr) return NULL;
	if(ptr->Ltag == THREAD)
	{
		return ptr->leftchild;
	}
	else
	{
		return Last(ptr->leftchild);
	}
}
void InOrderThread(BiThrNode *ptr)
{
	for(BiThrNode *p = First(ptr); p != NULL; p = Next(p))
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
}
void ResInOrderThread(BiThrNode *ptr)
{
	for(BiThrNode *p = Last(ptr); p != NULL; p = Prev(p))
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
}
int main()
{
	ElemType *ar="ABC##DE##F##G#H##";
	BinaryThreadTree root =NULL;
	root = CreateTree2(ar);

	InOrder(root);
	cout<<endl;
	MakeThreadTree(root);
	InOrderThread(root);
	ResInOrderThread(root);
	return 0;
}

typedef int ElemType;
#define END -1

typedef struct BtNode // binarytreenode
{
	BtNode *leftchild;
	BtNode *rightchild;
	ElemType data;
}BtNode,*BinaryTree;

BtNode *Buynode()
{
	BtNode *s = (BtNode*)malloc(sizeof(BtNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BtNode));
	return s;
}
void Freenode(BtNode *p)
{
	free(p);
}
void PreOrder(BtNode *p)
{
	if(p != NULL)
	{
		cout<<p->data<<" ";
		PreOrder(p->leftchild);
		PreOrder(p->rightchild);
	}
}
void InOrder(BtNode *p)
{
	if(p != NULL)
	{
		InOrder(p->leftchild);
		cout<<p->data<<" ";
		InOrder(p->rightchild);
	}
}

void PastOrder(BtNode *p)
{
	if(p != NULL)
	{
		PastOrder(p->leftchild);
		PastOrder(p->rightchild);
		cout<<p->data<<" ";
	}
}


BtNode * CreateTree2(ElemType *&str)
{
	BtNode *s = NULL;
	if(*str != END)
	{
		s = Buynode();
		s->data = *str;
		s->leftchild = CreateTree2(++str);
		s->rightchild = CreateTree2(++str);
	}
	return s;
}
int GetSize(BtNode *ptr)
{
	if(ptr == NULL) return 0;
	else return GetSize(ptr->leftchild) + GetSize(ptr->rightchild) + 1;
}
int Depth(BtNode *ptr)
{
	if(ptr == NULL) return 0;
	else return max(Depth(ptr->leftchild),Depth(ptr->rightchild)) + 1;
}


BtNode * FindValue(BtNode *ptr,ElemType x)
{
	if(ptr == NULL || ptr->data == x) 
	{
		return ptr;
	}
	else
	{
		BtNode *p = FindValue(ptr->leftchild,x);
		if(NULL == p)
		{
			p = FindValue(ptr->rightchild,x);
		}
		return p;
	}
}
BtNode * Parent(BtNode *ptr,BtNode *child)
{
	if(ptr == NULL || ptr->leftchild == child 
		|| ptr->rightchild == child)
	{
		return ptr;
	}
	else
	{
		BtNode *p = Parent(ptr->leftchild,child);
		if(NULL == p)
		{
			p = Parent(ptr->rightchild,child);
		}
		return p;
	}
}
BtNode * FindParent(BtNode *ptr,BtNode *child)
{
	if(NULL == ptr || child == NULL || ptr == child)
	{
		return NULL;
	}
	else
	{
		return Parent(ptr,child);
	}
}

//BtNode * FindNearParent(BtNode *ptr,BtNode *child1,BtNode *child2)
void NiceInOrder(BtNode *ptr)
{
	if(NULL == ptr) return ;
	stack<BtNode *> st;
	
	while(!st.empty() || ptr != NULL)
	{
		while(ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftchild;
		}
		ptr = st.top(); st.pop();
		cout<<ptr->data<<" ";
		ptr = ptr->rightchild;
	}
	cout<<endl;
}

void NicePreOrder(BtNode *ptr)
{
	if(NULL == ptr) return ;
	stack<BtNode *> st;
	st.push(ptr);
	while(!st.empty())
	{
		ptr = st.top(); st.pop();
		cout<<ptr->data<<" ";
		if(ptr->rightchild != NULL)
		{
			st.push(ptr->rightchild);
		}
		if(ptr->leftchild != NULL)
		{
			st.push(ptr->leftchild);
		}
	}
	cout<<endl;

}


void NicePastOrder(BtNode *ptr)
{
	if(NULL == ptr) return ;
	BtNode *tag = NULL;
	stack<BtNode *> st;
	while(!st.empty() || ptr != NULL)
	{
		while(ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftchild;
		}
		ptr = st.top(); st.pop();
		if(ptr->rightchild == NULL || ptr->rightchild == tag)
		{
			cout<<ptr->data<<" ";
			tag = ptr;
			ptr = NULL;
		}else
		{
			st.push(ptr);
			ptr = ptr->rightchild;
		}
	}
	cout<<endl;
}
//////////////////////////////////////////////
struct StkNode
{
	BtNode *pnode;
	int popnum;
public:
	StkNode(BtNode *p = NULL):pnode(p),popnum(0) {}
};

void StkNiceInOrder(BtNode *ptr)
{
	if(ptr == NULL) return ;
	stack<StkNode> st;
	st.push(StkNode(ptr));
	while(!st.empty())
	{
		StkNode node = st.top(); st.pop();
		if(++node.popnum == 2)
		{
			cout<<node.pnode->data<<" ";
			if(node.pnode->rightchild != NULL)
			{
				st.push(StkNode(node.pnode->rightchild));
			}
		}
		else
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode(node.pnode->leftchild));
			}
		}
	}
	cout<<endl;
}
void StkNicePastOrder(BtNode *ptr)
{
	if(ptr == NULL) return ;
	stack<StkNode> st;
	st.push(StkNode(ptr));
	while(!st.empty())
	{
		StkNode node = st.top(); st.pop();
		if(++node.popnum == 3)
		{
			cout<<node.pnode->data<<" ";
		}
		else
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode(node.pnode->leftchild));
			}else if(node.popnum == 2  && node.pnode->rightchild != NULL)
			{
				st.push(StkNode(node.pnode->rightchild));
			}
		}
	}
	cout<<endl;
}
void PrintLevel_K(BtNode *ptr, int k)
{
	if(ptr != NULL && k == 0)
	{
		cout<<ptr->data<<" ";
	}else if(ptr != NULL)
	{
		PrintLevel_K(ptr->leftchild,k-1);
		PrintLevel_K(ptr->rightchild ,k-1);
	}
}


void NiceLevelOrder(BtNode *ptr)
{
	if(NULL == ptr) return ;
	queue<BtNode *> qu;
	qu.push(ptr);
	while(!qu.empty())
	{
		BtNode *p = qu.front(); qu.pop();
		cout<<p->data<<" ";
		if(p->leftchild != NULL)
		{
			qu.push(p->leftchild);
		}
		if(p->rightchild != NULL)
		{
			qu.push(p->rightchild);
		}
	}
	cout<<endl;
}
void LevelOrder(BtNode *ptr)
{
	int n = Depth(ptr);
	for(int i = 0;i<n;++i)
	{
		PrintLevel_K(ptr,i);
	}
	cout<<endl;
}
bool Is_F_btree(BtNode *p)
{
	return (p == NULL) || (Is_F_btree(p->leftchild) && Is_F_btree(p->rightchild)
		&& (Depth(p->leftchild) == Depth(p->rightchild)) );

}
bool Is_Full_BinaryTree(BtNode *ptr)
{
	bool tag = true;
	int n = 1;
	queue<BtNode *> qu;
	qu.push(ptr);
	while(!qu.empty())
	{
		int i = 0;
		for(;i<n && !qu.empty();++i)
		{
			BtNode *p = qu.front(); qu.pop();
			if(p->leftchild != NULL)
			{
				qu.push(p->leftchild);
			}
			if(p->rightchild != NULL)
			{
				qu.push(p->rightchild);
			}
		}
		if(i<n) 
		{
			tag = false;
			break;
		}
		n+=n;
	}
	return tag;
}
bool Is_Comp_BinaryTree(BtNode *ptr)
{
	bool res = true;
	if(NULL == ptr) return true;
	queue<BtNode *> qu;
	qu.push(ptr);
	while(1) // while(!qu.empty())
	{
		ptr = qu.front();qu.pop();
		if(NULL == ptr) break;
		qu.push(ptr->leftchild);
		qu.push(ptr->rightchild);
	}
	while(!qu.empty())
	{
		ptr = qu.front(); qu.pop();
		if(ptr != NULL)
		{
			res = false;
			break;
		}
	}
	return res;
}
void PrintVal(BtNode *ptr,vector<int> &vec,int total)
{
	if(ptr != NULL)
	{
		vec.push_back(ptr->data);
		PrintVal(ptr->leftchild,vec,total);	
		PrintVal(ptr->rightchild,vec,total);
		if(ptr->leftchild == NULL && ptr->rightchild == NULL)
		{
			int sum = 0;
			int n = vec.size();
			for(int i = 0;i<n;++i)
			{
				sum +=vec[i];
			}
			if(sum == total)
			{
				for(int i = 0;i<n;++i)
				{
					cout<<vec[i]<<" ";
				}
				cout<<total<<endl;
			}
		}
		vec.pop_back();
	
	}

}
//bool Is_BST;
//bool Is_Balance_BinaryTree;
int main()
{
	BinaryTree root = NULL;
	int ar[]={10,5,4,-1,-1,7,-1,-1,12,-1,-1,};

	int *p = ar;
	root = CreateTree2(p);
	StkNiceInOrder(root);
	vector<int> vec;
	PrintVal(root,vec,22);

	return 0;
}
int main()
{
	BinaryTree root = NULL;
	char *str = "ABC##DE##F##G#H##";
	root = CreateTree2(str);
	StkNiceInOrder(root);
	StkNicePastOrder(root);

	return 0;
}

typedef int ElemType;
typedef struct BtNode // binarytreenode
{
	BtNode *leftchild;
	BtNode *rightchild;
	ElemType data;
}BtNode,*BinaryTree;


void PreOrder(BtNode *p)
{
	if(p != NULL)
	{
		cout<<p->data<<" ";
		PreOrder(p->leftchild);
		PreOrder(p->rightchild);
	}
}
void InOrder(BtNode *p)
{
	if(p != NULL)
	{
		InOrder(p->leftchild);
		cout<<p->data<<" ";
		InOrder(p->rightchild);
	}
}

void PastOrder(BtNode *p)
{
	if(p != NULL)
	{
		PastOrder(p->leftchild);
		PastOrder(p->rightchild);
		cout<<p->data<<" ";
	}
}
BtNode *Buynode()
{
	BtNode *s = (BtNode*)malloc(sizeof(BtNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BtNode));
	return s;
}
void Freenode(BtNode *p)
{
	free(p);
}
BtNode * CreateTree1()
{
	BtNode *s = NULL;
	ElemType item;
	cin>>item;
	if(item != '#')
	{
		s = Buynode();
		s->data = item;
		s->leftchild = CreateTree1();
		s->rightchild = CreateTree1();
	}
	return s;
}
BtNode * CreateTree2(ElemType *&str)
{
	BtNode *s = NULL;
	if(*str != '#')
	{
		s = Buynode();
		s->data = *str;
		s->leftchild = CreateTree2(++str);
		s->rightchild = CreateTree2(++str);
	}
	return s;
}
// 1) ps is;=> tree;
// 2) is ls => tree;
// LevelOrder;
// Size;
// Level;
//
int  FindPos(ElemType *is,ElemType x,int n)
{
	int pos = -1;
	for(int i = 0;i<n;++i)
	{
		if(x == is[i])
		{
			pos = i;
			break;
		}
	}
	return pos;
}
BtNode * CreatePI(ElemType *ps,ElemType *is,int n)
{
	BtNode *s = NULL;
	if(n > 0)
	{
		s = Buynode();
		s->data = ps[0];// s->data = *ps;
		int pos = FindPos(is,ps[0],n);
		if(pos == -1) exit(1);
		s->leftchild = CreatePI(ps+1,is,pos);
		s->rightchild = CreatePI(ps+1+pos,is+1+pos,n - pos - 1);
	}
	return s;
}
BtNode * CreateTreePI(ElemType *ps,ElemType *is,int n)
{
	if(NULL == ps || NULL == is || n < 1)
		return NULL;
	else
		return CreatePI(ps,is,n);
}
BtNode * CreateIL(ElemType *is,ElemType *ls,int n)
{
	BtNode *s = NULL;
	if(n > 0)
	{
		s = Buynode();
		s->data = ls[n-1];
		int pos = FindPos(is,ls[n-1],n);
		if(pos == -1) exit(1);
		s->leftchild = CreateIL(is,ls,pos);
		s->rightchild = CreateIL(is+pos+1,ls+pos,n - pos - 1);
	}
	return s;
}
BtNode * CreateTreeIL(ElemType *is,ElemType *ls,int n)
{
	if(NULL == is || NULL == ls || n < 1) 
		return NULL;
	else
		return CreateIL(is,ls,n);
}
void CreateTree4(BtNode *&ptr,ElemType *&str)
{
	if(NULL == str || *str == '#')
	{
		ptr = NULL;
	}
	else
	{
		ptr = Buynode();
		ptr->data = *str;
		CreateTree4(ptr->leftchild,++str);
		CreateTree4(ptr->rightchild,++str);
	}
}

void ArrayInOrder(int *ar,int i,int n)
{
	if(i<n) // p != NULL
	{
		ArrayInOrder(ar,i*2+1,n); // p->leftchild;
		cout<<ar[i]<<" ";
		ArrayInOrder(ar,i*2+2,n); // p->rightchild;
	}
}
BtNode *  CreateArray(int *ar,int i,int n)
{
	BtNode *s = NULL;
	if(i<n)
	{
		s = Buynode();
		
		s->leftchild = CreateArray(ar,i*2+1,n);
		s->rightchild = CreateArray(ar,i*2+2,n);
		s->data = ar[i];
	}
	return s;
}
void Link_Array(BtNode *ptr,int * br,int i)
{
	if(ptr != NULL)
	{
		br[i] = ptr->data;
		Link_Array(ptr->leftchild,br,i*2+1);
		Link_Array(ptr->rightchild,br,i*2+2);
	}
}
BtNode * BinaryCreate(int *ar,int left,int right)
{
	BtNode *s = NULL;
	if(left <= right)
	{
		int mid = (right - left + 1)/2 + left;
		s = Buynode();
		s->data = ar[mid];
		s->leftchild = BinaryCreate(ar,left,mid-1);
		s->rightchild = BinaryCreate(ar,mid+1,right);
	}
	return s;
}
BtNode * BinaryCreate(int *ar,int n)
{
	if(NULL == ar || n < 1) return NULL;
	else return BinaryCreate(ar,0,n-1);
}

int main()
{
	int ar[]={12,23,34,45,56,67,78,85,90,100};
	int n =sizeof(ar)/sizeof(ar[0]);
	BinaryTree root = NULL;

	root = BinaryCreate(ar,n);
	return 0;
}

int main()
{
	BinaryTree root = NULL;
	int ar[]={31,23,12,66,94,5,17,70,62,49,55,88};
	const int n = sizeof(ar)/sizeof(ar[0]);
	int br[n];
	ArrayInOrder(ar,0,n);
	cout<<endl;
    root = CreateArray(ar,0,n);
	InOrder(root);
	cout<<endl;
	Link_Array(root,br,0);
	return 0;

}


int main()
{
    char *str="ABC##DE##F##G#H##";
    BinaryTree root = NULL;
    CreateTree4(root,str);
	return 0;
}

int main()
{
	char *ps = "ABCDEFGH";
	char *is = "CBEDFAGH";
	char *ls = "CEFDBHGA";
	int n = strlen(ps); // n = sizeof(ps);//
	BinaryTree root = NULL;
	//root = CreateTreePI(ps,is,n);
	root = CreateTreeIL(is,ls,n);
	PreOrder(root);
	cout<<endl;
	InOrder(root);
	cout<<endl;
	PastOrder(root);
	cout<<endl;
	return 0;
}
int main()
{
	char *ps = "ABCDEFGH";
	char *is = "CBEDFAGH";
	char *ls = "CEFDBHGA";

	BinaryTree root = NULL;
	char *str="ABC##DE##F##G#H##";
	//root = CreateTree1();
	root = CreateTree2(str);
	PreOrder(root);
	cout<<endl;
	InOrder(root);
	cout<<endl;
	PastOrder(root);
	cout<<endl;
	return 0;
}



int fun(int n)
{
	if(n <=1)
		return 1;
	else 
		return fun(n-1)*n;
}


template<class Type>
struct PrintInt
{
	void operator()(const Type &val) const
	{
		cout<<val<<" ";
	}
};

int main()
{
	vector<int> ivec;
	for(int i = 0;i<10;++i)
	{
		ivec.push_back(rand()%100);
	}
	for_each(ivec.begin(),ivec.end(),PrintInt<int>());

	std::partition
	return 0;
}


typedef struct 
{
	int first;
	int second;
	int diff;
}DiffPair;

template<class Type>
int Parition(Type *ar,int left,int right)
{
	Type tmp = ar[left];
	int i = left , j = right;
	while(i<j)
	{
		while(i<j && ar[j] >= tmp) --j;
		if(i<j){ ar[i] = ar[j];}
		while(i<j && ar[i] <= tmp) ++i;
		if(i<j) { ar[j] = ar[i];}
	}
	ar[i] = tmp;
	return i;
}
template<class Type>
int RandParition(Type *ar,int left,int right)
{
	srand(time(NULL));
	Sleep(300);
	int rindex = (rand()%(right - left + 1)) + left; 
	swap(ar[rindex],ar[left]);
	return Parition(ar,left,right);
}
template<class Type>
Type SelectK(Type *ar,int left,int right,int k)
{
	if(left == right && k == 1) return ar[left];
	int index = Parition(ar,left,right);
	int pos = index - left + 1;
	if(k <= pos) return SelectK(ar,left,index,k);
	else return SelectK(ar,index+1,right,k - pos);
}
template<class Type>
Type SelectK_Min(Type *ar,int n,int k)
{
	return SelectK(ar,0,n-1,k);
}

int MaxS(int *br,int left,int right)
{
	int max = br[left];
	for(int i = left + 1; i<=right; ++i)
	{
		if(max < br[i])
		{
			max = br[i];
		}
	}
	return max;
}
int MinS(int *br,int left,int right)
{
	int min = br[left];
	for(int i = left + 1; i<=right; ++i)
	{
		if(min > br[i])
		{
			min = br[i];
		}
	}
	return min;
}
//INT_MAX
int Min(int d1,int d2,int d3)
{
	return min(d1,min(d2,d3));
}
DiffPair Spair(int *br,int left,int right)
{
	DiffPair dip = {-1,-1,INT_MAX};
	if(right - left <= 0)
	{
		return dip;
	}
	int mid = (right - left + 1)/2;
	int pos = left + mid -1;
	SelectK(br,left,right,mid);
	DiffPair d1 = Spair(br,left,pos); // s1;
	DiffPair d2 = Spair(br,pos+1,right);// s2

	int maxs1 = MaxS(br,left,pos); //s1;
	int mins2 = MinS(br,pos+1,right); //s2;

	if(mins2 - maxs1 <= d1.diff && mins2 - maxs1 <= d2.diff)
	{
		dip.diff = mins2 - maxs1;
		dip.first = mins2;
		dip.second = maxs1;
	}
	if(d2.diff <=d1.diff && d2.diff <= mins2 - maxs1)
	{
		dip =  d2;
	}
	if(d1.diff <= d2.diff && d1.diff <= mins2 - maxs1)
	{
		dip =  d1;
	}
	
	return dip;
}
DiffPair Spair(int *br,int n)
{
	DiffPair dip={-1,-1,INT_MAX};
	if(NULL != br && n >=2) 
	{
		dip =  Spair(br,0,n-1);
	}
	return dip;
}
int main()
{
	int ar[]={56,23,12,89,78,45,99,100,65,32,20,55};
	int n = sizeof(ar)/sizeof(ar[0]);

	DiffPair dip = Spair(ar,n);


	cout<<dip.first<<" : "<<dip.second<<" => "<<dip.diff<<endl;
	return 0;
}



int main()
{
	vector<int> ivec;
	for(int i= 0;i<10;++i)
	{
		srand(time(NULL));
		Sleep(300);
		ivec.push_back(rand()%100);
	}
	vector<int>::iterator it = ivec.begin();
	for(; it != ivec.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	return 0;
}


template<class Type>
int Parition(Type *ar,int left,int right)
{
	Type tmp = ar[left];
	int i = left , j = right;
	while(i<j)
	{
		while(i<j && ar[j] >= tmp) --j;
		if(i<j){ ar[i] = ar[j];}
		while(i<j && ar[i] <= tmp) ++i;
		if(i<j) { ar[j] = ar[i];}
	}
	ar[i] = tmp;
	return i;
}
template<class Type>
int RandParition(Type *ar,int left,int right)
{
	srand(time(NULL));
	Sleep(300);
	int rindex = (rand()%(right - left + 1)) + left; 
	swap(ar[rindex],ar[left]);
	return Parition(ar,left,right);
}
template<class Type>
Type SelectK(Type *ar,int left,int right,int k)
{
	if(left == right && k == 1) return ar[left];
	int index = RandParition(ar,left,right);
	int pos = index - left + 1;
	if(k <= pos) return SelectK(ar,left,index,k);
	else return SelectK(ar,index+1,right,k - pos);
}
template<class Type>
Type SelectK_Min(Type *ar,int n,int k)
{
	return SelectK(ar,0,n-1,k);
}
int main()
{
	int ar[]={56,34,89,90,45,23,18,78,67,100};
	int n = sizeof(ar)/sizeof(ar[0]);
	for(int k = 1; k<=n;++k)
	{
		int x = SelectK_Min(ar,n,k);
		cout<<k<<" => "<<x<<endl;
	}
	return 0;

}
template<class Type>
void Select2Max(Type *ar,int n)
{
	if(NULL == ar || n < 2) return ;
	Type max1 = ar[0]>ar[1]? ar[0]:ar[1];
	Type max2 = ar[0]>ar[1]? ar[1]:ar[0];
	for(int i = 2;i<n;++i)
	{
		if(ar[i] > max1)
		{
			max2 = max1;
			max1 = ar[i];
		}else if(ar[i] > max2)
		{
			max2 = ar[i];
		}
	}
	cout<<max1<<" "<<max2<<endl;
}



void fun(int *ar,int *br,int i,int n)
{
	if(i == n)
	{
		for(int j = 0;j<n;++j)
		{
			if(br[j])
			{
				cout<<ar[j]<<" ";
			}
		}
		cout<<endl;
	}
	else
	{
		br[i] = 1;
		fun(ar,br,i+1,n); // left
		br[i] = 0;
		fun(ar,br,i+1,n); // right
	}
}
int main()
{
	int ar[]={1,2,3};
	int br[]={0,0,0};
	fun(ar,br,0,3);
	return 0;
}

void Perm(int *br,int k,int m)
{
	if(k == m)
	{
		for(int i = 0;i<=m;++i)
		{
			cout<<br[i]<<" ";
		}
		cout<<endl;
	}
	else
	{
		for(int j = k;j<=m;++j)
		{
			swap(br[j],br[k]);
			Perm(br,k+1,m);
			swap(br[j],br[k]);
		}
	}
}

int main()
{
	int ar[]={1,2,3};
	int n = sizeof(ar)/sizeof(ar[0]);
	Perm(ar,0,n-1);//n

	return 0;
}


int fac(unsigned int n ,unsigned int a,unsigned int b)
{
	if(n <= 2) return a;
	else return fac(n-1,a+b,a);
}

int fac(unsigned int n)
{
	int a = 1, b = 1;
	return fac(n ,a,b);
}


// input_iterator_tag;
//


template<class _II>
void PrintArray(_II _F ,_II _L)
{
	for(; _F != _L;++_F)
	{
		cout<<*_F<<"  ";
	}
	cout<<endl;
}
template<class Type>
int FindValue(vector<Type> &ibr,Type val)
{
	int left = 0, right = ibr.size();
	int pos = -1;
	while(left <= right)
	{  
		int mid = (right - left + 1)/2 + left;
		if(val < ibr[mid])
		{
			right = mid -1;
		}else if(val > ibr[mid])
		{
			left = mid + 1;
		}else
		{
			while(mid > left && val == ibr[mid-1]) --mid;
			pos = mid;
			break;
		}
	}
	return pos;
}
int main()
{
	int ar[]={12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar)/sizeof(ar[0]);
	vector<int> iar(ar,ar+n);
	PrintArray(iar.begin(),iar.end());
	int pos = FindValue(iar,23);

	return 0;
}
// 12 12 12 12 12 23 34 45 56 56 56 56 56 67 78 89 90 100
int SearchValue(int br[],int left,int right,int val)
{
	int pos = -1;
	int mid = (right - left + 1)/2 + left;
	if(val < br[mid])
	{
		pos = SearchValue(br,left,mid-1,val);
	}else if(val > br[mid])
	{
		pos = SearchValue(br,mid+1,right,val);
	}else
	{
		while(mid > left && br[mid-1] == val) --mid;
		pos = mid;
	}
	return pos;
}
int FindValue(int br[],int n,int val)
{
	if(NULL == br || n < 1) return -1;
	return SearchValue(br,0,n-1,val);
}
int main()
{
	int ar[]={12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar)/sizeof(ar[0]);
	vector<int> iar(ar,ar+n);
	PrintArray(iar.begin(),iar.end());

	return 0;
}


// 1 2 3 4
// 1 1 2 3 5

int FindValue(int br[],int n,int val)
{ // 0 1 2 3 4   n-1
    if(NULL == br || n < 1) return -1;
	int left = 0, right = n-1;
	int pos = -1;
	while(left <= right)
	{  
		// int mid = (left + right) / 2;
		int mid = (right - left + 1)/2 + left;
		if(val < br[mid])
		{
			right = mid -1;
		}else if(val > br[mid])
		{
			left = mid + 1;
		}else
		{
			while(mid > left && val == br[mid-1]) --mid;
			pos = mid;
			break;
		}
	}
	return pos;
}
template<class _Con>
void PrintArray(const _Con &ibr)
{
	typename _Con::const_iterator it = ibr.begin();
	for(; it != ibr.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
void PrintArray(const vector<int> &ibr)
{
	vector<int>::const_iterator it = ibr.begin();
	for(; it != ibr.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
int num = 0;
int fac(unsigned int n)
{
	++num;
	if(n <= 2) return 1;
	else return fac(n-1) + fac(n-2);
}
int fun(unsigned int n)
{
	int a = 1 , b = 1 , c = 1;
	for(int i = 3;i<=n;++i)
	{
		c = a+b;
		b = a;
		a = c;
	}
	return c;
}
int main()
{
	int n ,sum;
	cin>>n;
	sum = fac(n);
	cout<<num<<endl;
}

int fac(unsigned int n)
{
	if(n <= 1) return 1;
	else return fac(n-1) *n;
}

int fun(unsigned int n)
{
	int sum = 1;
	for(int i = 1;i<=n;++i)
	{
		sum = sum *i;
	}
	return sum;
}
int main()
{
	int n,sum;
	cin>>n;
	sum = fun(n);
}
#endif
