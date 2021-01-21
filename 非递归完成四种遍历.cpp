#include<iostream>
using namespace std;
#define OK 0
#define TRUE 1
#define FALSE 0
#define STACKINITSIZE 256
#define STACKINCREMENT 128
typedef struct BiTNode
{
	char data;
	bool state = 0;
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
typedef struct SeqStack
{
	BiTNode * pBase;
	BiTNode * pTop;
}SeqStack;
int InitStack(SeqStack& S)
{
	S.pBase = new BiTNode[STACKINITSIZE];
	if (S.pBase == NULL)
	{
		return -1;
	}
	S.pTop = S.pBase;
	return OK;
}
int DestroyStack(SeqStack& S)
{
	if (S.pBase != NULL)
	{
		delete[]S.pBase;
		S.pBase = NULL;
	}
	S.pTop = NULL;
	return OK;
}
bool StackEmpty(SeqStack S)
{
	if (S.pBase == NULL)
	{
		return 1;
	}
	if (S.pBase == S.pTop)
	{
		return TRUE;
	}
	return FALSE;
}
int Push(SeqStack& S, BiTNode *e)
{
	*S.pTop = *e;
	S.pTop++;
	return OK;
}
int Pop(SeqStack& S,BiTree&node)
{
	if (S.pTop == S.pBase)
	{
		cout << "No stastic can be pop!" << endl;
		return -1;
	}
	S.pTop--;
	node = S.pTop;
	return OK;
}
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
///////////////////////////////////////////////////////////
int PreOrderTraverse(BiTree T)//（先序遍历）非递归
{
	SeqStack zhan;
	BiTNode* node=NULL;
	node = T;
	InitStack(zhan);
	Push(zhan, T);
	while (!StackEmpty(zhan))
	{
		if (node == T)
		{
			cout << T->data;
			T->state=1;
		}
		else
		{
			Push(zhan, node);
			cout << node->data;
			node->state = 1;
		}
		if (node->lchild != NULL)
		{
			node = node->lchild;
			continue;
		}
		else if(node->rchild!=NULL)
			{
				node = node->rchild;
				continue;
			}
		else
		{
			Pop(zhan,node);
			if (zhan.pBase == zhan.pTop)
			{
				break;
			}
			node = (zhan.pTop - 1)->rchild;
			while (node == NULL||node->state==1)
			{
				Pop(zhan,node);
				node = (zhan.pTop - 1)->rchild;
				if (StackEmpty(zhan))
				{
					break;
				}
			}
		}
	}
	DestroyStack(zhan);
	return 0;
}
int InOrderTraverse(BiTree T)
{
	SeqStack zhan;
	BiTNode* node = NULL;
	node = T;
	InitStack(zhan);
	Push(zhan, node);
	while (!StackEmpty(zhan))
	{
		if (node->lchild != NULL)
		{
			Push(zhan, node->lchild);
			node = node->lchild;
			node->state = 1;
			continue;
		}
		else if (node->rchild != NULL)
		{
			Push(zhan, node->rchild);
			node = node->rchild;
			node->state=1;
			continue;
		}
		else
		{
			Pop(zhan,node);
			cout << node->data;
			node = (zhan.pTop - 1);
			if (node->rchild!=NULL)
			{
				Pop(zhan, node);
				cout << node->data;
				node = node->rchild;
				Push(zhan,node);
				node->state = 1;
			}
			else
			{
				node = node->rchild;
			}
			while (node == NULL || node->state == 1)
			{
				
				if (StackEmpty(zhan))
				{
					break;
				}
				Pop(zhan,node);
				cout << node->data;
				node =node->rchild;
				if (StackEmpty(zhan)&&node!=NULL&&node->state==0)
				{
					Push(zhan, node);
					node->state = 1;
					break;
				}
			}
		}
	}
	DestroyStack(zhan);
	return 0;
}
int PostOrderTraverse(BiTree T)
{
	SeqStack zhan;
	BiTNode* node = NULL;
	node = T;
	InitStack(zhan);
	Push(zhan, node);
	while (!StackEmpty(zhan))
	{
		if (node->lchild != NULL&&node->lchild->state==0)
		{
			Push(zhan,node->lchild);
			node = node->lchild;
			node->state = 1;
			continue;
		}
		else if (node->rchild != NULL && node->rchild->state == 0)
		{
			Push(zhan, node->rchild);
			node = node->rchild;
			node->state = 1;
			continue;
		}
		else
		{
			Pop(zhan,node);
			cout << node->data;
			node = (zhan.pTop - 1);
		}
	}
	DestroyStack(zhan);
	return 0;
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
		cout << e;
	}
	DestroyQueue(Q);
	return 0;
}
int Assign(BiTree& T, BiTNode& cur_p, char value)//改变树中给定节点的值
{
	cur_p.data = value;
	return 0;
}
int InsertChild(BiTree& T, BiTNode* cur_p, bool LR, BiTree& c)
{
	if (LR == 0)
	{
		c->rchild = cur_p->lchild;
	}
	else
	{
		c->rchild = cur_p->rchild;
	}
	return 0;
}
int DeleteChild(BiTree& T, BiTNode* cur_p, bool LR)
{
	if (LR == 0)
	{
		DestroyBiTree(cur_p->lchild);
	}
	else
	{
		DestroyBiTree(cur_p->rchild);
	}
	return 0;
}
void reset(BiTree& T)
{
	LinkQueue Q;
	char e;
	InitQueue(Q);
	EnQueue(Q, T);
	while (!QueueEmpty(Q))
	{
		Q.front->next->ptr->state = 0;
		if (Q.front->next->ptr->lchild != NULL)
		{
			EnQueue(Q, Q.front->next->ptr->lchild);
		}
		if (Q.front->next->ptr->rchild != NULL)
		{
			EnQueue(Q, Q.front->next->ptr->rchild);
		}
		DeQueue(Q, e);
	}
	DestroyQueue(Q);
}
int main()
{
	BiTree T;
	cout << "请输入二叉树元素：" << endl;
	CreateBiTree(T);
	if (T == NULL)
	{
		cout << "Binary Tree does not exit!" << endl;
		exit(-1);
	}
	cout << "先序遍历：";
	PreOrderTraverse(T);
	cout << endl;
	reset(T);
	cout << "中序遍历：";
	InOrderTraverse(T);
	cout << endl;
	reset(T);
	cout << "后序遍历：";
	PostOrderTraverse(T);
	cout << endl;
	cout << "层次遍历：";
	LevelOrderTraverse(T);
	DestroyBiTree(T);
	return 0;
}















