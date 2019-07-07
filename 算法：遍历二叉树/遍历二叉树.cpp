#include <iostream>
#include <stack>
using namespace std;

typedef struct BiNode  //定义二叉树的节点结构
{
	char data;
	struct BiNode* lchild;
	struct BiNode* rchild;
}BiNode, *PNode;

void CreateTree(PNode &root) //创建二叉树
{
	char ch; cin >> ch;
	if (ch == '#')
	{
		root = NULL;
	}
	else
	{
		root = new BiNode();
		root->data = ch;
		CreateTree(root->lchild);
		CreateTree(root->rchild);
	}
}

void PreOrder(PNode root) //递归--二叉树先序遍历（根左右）
{
	if (root == NULL)
		return;
	cout << root->data << " ";
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}

void InOrder(PNode root) //递归--二叉树中序遍历（左根右）
{
	if (root == NULL)
		return;
	InOrder(root->lchild);
	cout << root->data << " ";
	InOrder(root->rchild);
}

void PostOrder(PNode root)//递归--二叉树后序遍历（左右根）
{
	if (root == NULL)
		return;
	PostOrder(root->lchild);
	PostOrder(root->rchild);
	cout << root->data << " ";
}

void PreTraverse(PNode root) //非递归--二叉树先序遍历
{
	if (root == NULL)
		return;

	PNode p;
	stack<PNode> sta;
	sta.push(root);

	while (!sta.empty())
	{
		p = sta.top();
		sta.pop();

		while (p)
		{
			cout << p->data << " ";
			if (p->rchild)
			{
				sta.push(p->rchild);
			}
			p = p->lchild;
		}
	}
}

void InTraverse(PNode root) //非递归--二叉树中序遍历
{
	if (root == NULL)
		return;

	PNode p;
	stack<PNode> sta;
	sta.push(root);

	while (!sta.empty())
	{
		while ((p = sta.top()) && p) //先遍历栈中结点的左孩子
		{
			sta.push(p->lchild); 
		}
		sta.pop();

		if (!sta.empty())
		{
			p = sta.top();
			sta.pop();
			cout << p->data << " ";//此时左边已经遍历完了
			sta.push(p->rchild); //把右孩子放进栈中，对右孩子进行中序遍历
		}


	}
}

void PostTraverse(PNode root) //非递归--二叉树后续遍历
{
	typedef struct Data
	{
		int flag;
		PNode node;
	}Data;

	int flag;
	Data data;
	PNode p = root;
	stack<Data> sta;

	while (p || !sta.empty())
	{
		while (p)
		{
			data.node = p;
			data.flag = 0;
			sta.push(data);
			p = p->lchild;
		}

		data = sta.top();
		sta.pop();

		p = data.node;
		flag = data.flag;

		if (flag == 0)
		{
			data.node = p;
			data.flag = 1;
			sta.push(data);
			p = p->rchild;
		}
		else
		{
			cout << p->data << " ";
			p = NULL;
		}
	}
}


int main()
{
	PNode root = NULL;
	cout << "please input data: ";
	CreateTree(root);

	cout << "递归先序遍历：";
	PreOrder(root);
	cout << endl;

	cout << "非递归先序遍历：";
	PreTraverse(root);
	cout << endl;

	cout << "递归中序遍历：";
	InOrder(root);
	cout << endl;

	cout << "非递归中序遍历：";
	InTraverse(root);
	cout << endl;

	cout << "递归后续遍历：";
	PostOrder(root);
	cout << endl;

	cout << "非递归后续遍历：";
	PostTraverse(root);
	cout << endl;
	return 0;
}
// ABC##DE##F##G#H##
