#include<iostream>
using namespace std;
#define OK 0
#define TRUE 1
#define FALSE 0
typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;
BiTNode* btn;
void DestroyBiTree(BiTree& T)
{
	if (T!=NULL)
	{
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		delete T;
		T = NULL;
	}
}
int CreateBiTree(BiTree& T)//基于先序遍历创建二叉树
{
	char input;
	cin >> input;
	if (input == '$')
	{
		return 0;
	}
	if (input == '#')
	{
		T = NULL;
	}
	else
	{
		T = new BiTNode;
		T->data = input;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}
int PreOrderTraverse(BiTree T)
{
	if (T != NULL)
	{
		cout << T->data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	return 0;
}
BiTNode* Search(BiTree &T, char e)
{
	if (T != NULL)
	{
		if (T->data == e)
		{
			btn = T;
			return btn;
		}
		Search(T->lchild, e);
		Search(T->rchild, e);
	}
	return btn;
}
BiTNode* Parent(BiTree T, BiTNode* cur_p)
{
	if (cur_p == T)
	{
		return NULL;
	}
	if (T->lchild == cur_p || T->rchild == cur_p)
	{
		return T;
	}
	else
	{
		Parent(T->lchild, cur_p);
		Parent(T->rchild, cur_p);
	}
}
int Deletect(BiTree& T, char e)
{
	while (1)
	{
		btn = NULL;
		bool lr=0;
		BiTNode* temp=NULL,*cur_p=NULL;
		temp = Search(T, e);
		cur_p=Parent(T,temp);
		if (temp == NULL)
		{
			break;
		}
		if (cur_p->lchild == temp)
		{
			lr = 1;
		}
		DestroyBiTree(temp);
		if (lr == 1)
		{
			cur_p->lchild = NULL;
		}
	}
	return 0;
}
int main()
{
	BiTree T;
	cout << "请输入二叉树元素：" << endl;
	CreateBiTree(T);
	Deletect(T, 'X');
	PreOrderTraverse(T);
	DestroyBiTree(T);
	return 0;
}















