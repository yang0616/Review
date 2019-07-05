#include <iostream>
#include <stack>
using namespace std;

typedef struct BiNode  //����������Ľڵ�ṹ
{
	char data;
	struct BiNode* lchild;
	struct BiNode* rchild;
}BiNode, *PNode;

void CreateTree(PNode &root) //����������
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

void PreOrder(PNode root) //�ݹ�--��������������������ң�
{
	if (root == NULL)
		return;
	cout << root->data << " ";
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}

void InOrder(PNode root) //�ݹ�--�������������������ң�
{
	if (root == NULL)
		return;
	InOrder(root->lchild);
	cout << root->data << " ";
	InOrder(root->rchild);
}

void PostOrder(PNode root)//�ݹ�--������������������Ҹ���
{
	if (root == NULL)
		return;
	PostOrder(root->lchild);
	PostOrder(root->rchild);
	cout << root->data << " ";
}

void PreTraverse(PNode root) //�ǵݹ�--�������������
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

void InTraverse(PNode root) //�ǵݹ�--�������������
{
	if (root == NULL)
		return;

	PNode p;
	stack<PNode> sta;
	sta.push(root);

	while (!sta.empty())
	{
		while ((p = sta.top()) && p) //�ȱ���ջ�н�������
		{
			sta.push(p->lchild); 
		}
		sta.pop();

		if (!sta.empty())
		{
			p = sta.top();
			sta.pop();
			cout << p->data << " ";//��ʱ����Ѿ���������
			sta.push(p->rchild); //���Һ��ӷŽ�ջ�У����Һ��ӽ����������
		}


	}
}

int main()
{
	PNode root = NULL;
	cout << "please input data: ";
	CreateTree(root);

	cout << "�ݹ����������";
	PreOrder(root);
	cout << endl;

	cout << "�ǵݹ����������";
	PreTraverse(root);
	cout << endl;

	//InOrder(root);
	//cout << endl;

	//PostOrder(root);
	//cout << endl;
	return 0;
}
// ABC##DE##F##G#H##