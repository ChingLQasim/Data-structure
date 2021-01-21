#include<iostream>
using namespace std;
#define OK 0
#define TRUE 1
#define FALSE 0
int jud = 0;
typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;
typedef struct LNode
{
	BiTNode* ptr;
	struct LNode* next;
}LNode, * QueuePtr;
typedef struct LinkQueue
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
BiTNode* btn;
int InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = new LNode;
	Q.front->ptr = new BiTNode;
	if (Q.front == NULL)
	{
		cout << "Init fall!" << endl;
		exit(-1);
	}
	Q.front->next = NULL;
	return OK;
}
int DestroyQueue(LinkQueue& Q)
{
	LNode* p;
	while (Q.front->next != NULL)
	{
		p = Q.front->next;
		Q.front->next = p->next;
		delete p->ptr;
		delete p;
	}
	delete Q.front->ptr;
	delete Q.front;
	Q.front = NULL;
	Q.rear = NULL;
	return OK;
}
int EnQueue(LinkQueue& Q, BiTNode* e)
{
	LNode* pNew = new LNode;
	pNew->ptr = new BiTNode;
	pNew->ptr = e;
	Q.rear->next = pNew;
	Q.rear = pNew;
	Q.rear->next = NULL;
	return OK;
}
int DeQueue(LinkQueue& Q, char& e)
{
	if (Q.front->next == NULL)
	{
		return -1;
	}
	if (Q.front == Q.rear)
	{
		cout << "Queue is empty!" << endl;
		return OK;
	}
	LNode* p;
	p = Q.front->next;
	e = p->ptr->data;
	Q.front->next = p->next;
	if (Q.rear == p)
	{
		Q.rear = Q.front;
	}
	return OK;
}
bool QueueEmpty(LinkQueue Q)
{
	if (Q.front->next == NULL)
	{
		return TRUE;
	}
	if (Q.front == Q.rear)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void DestroyBiTree(BiTree& T)
{
	if (T)
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
int BiTreeEmpty(BiTree T)
{
	if (T == NULL)
		return 1;
	else
		return 0;

}
int BiTreeDepth(BiTree T)
{
	LinkQueue Q;
	char e;
	InitQueue(Q);
	EnQueue(Q, T);
	int num=0;
	while (!QueueEmpty(Q))
	{
		if (Q.front->next->ptr->lchild != NULL)
		{
			num++;
			EnQueue(Q, Q.front->next->ptr->lchild);
		}
		if (Q.front->next->ptr->rchild != NULL)
		{
			num++;
			EnQueue(Q, Q.front->next->ptr->rchild);
		}
		if (Q.front->next->ptr->rchild != NULL && Q.front->next->ptr->lchild != NULL)
		{
			num--;
		}
		DeQueue(Q, e);
	}
	DestroyQueue(Q);
	return num;
}

int LevelOrderTraverse(BiTree T)
{
	LinkQueue Q;
	char e;
	InitQueue(Q);
	EnQueue(Q, T);
	while (!QueueEmpty(Q))
	{
		if (Q.front->next->ptr->lchild != NULL)
		{
			EnQueue(Q, Q.front->next->ptr->lchild);
		}
		if (Q.front->next->ptr->rchild != NULL)
		{
			EnQueue(Q, Q.front->next->ptr->rchild);
		}
		DeQueue(Q, e);
		jud++;
	}
	DestroyQueue(Q);
	return 0;
}
int main()
{
	for(int i=0;i<2;i++)
	{
		int sum = 0;
		BiTree T;
		cout << "请输入二叉树元素：" << endl;
		CreateBiTree(T);
		cin.ignore();
		cout << "树的高度：";
		cout << BiTreeDepth(T) << endl;
		for (int i = 1; i <= BiTreeDepth(T); i++)
		{
			if (i == 1)
			{
				sum = 1;
			}
			else
			{
				sum = sum + (i - 1) * 2;
			}
		}
		cout << "树的节点应该有：" << sum << "个" << endl;
		LevelOrderTraverse(T);
		cout << "实际树的节点有" << jud << endl;
		if (jud == sum)
			cout << "是完全二叉树！" << endl;
		else
			cout << "不是完全二叉树！" << endl;
		DestroyBiTree(T);
		jud = 0;
	}
	return 0;
}















