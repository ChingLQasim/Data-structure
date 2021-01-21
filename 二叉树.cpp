#include<iostream>
using namespace std;
#define OK 0
#define TRUE 1
#define FALSE 0
typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;
typedef struct LNode
{
	BiTNode *ptr;
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
int EnQueue(LinkQueue& Q, BiTNode *e)
{
	LNode* pNew = new LNode;
	pNew->ptr = new BiTNode;
	pNew->ptr = e;
	Q.rear->next = pNew;
	Q.rear = pNew;
	Q.rear->next = NULL;
	return OK;
}
int DeQueue(LinkQueue& Q, char & e)
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
int CreateBiTree(BiTree &T)//基于先序遍历创建二叉树
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
	return 0;
}
BiTNode* Search(BiTree T, char e)
{
	if (T != NULL)
	{
		if (T->data == e)
		{
			btn = T;
			return btn;
		}
		Search(T->lchild,e);
		Search(T->rchild,e);
	}
	return btn;
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
	int left=0, right=0;
	if (T != NULL)
	{
		left++;
		left = BiTreeDepth(T->lchild);
		right++;
		right = BiTreeDepth(T->rchild);
	}
	if (left < right * 2)
	{
		return right+1;
	}
	return left-right+1;
}
int Root(BiTree T, char& e)
{
	if (T == NULL)
	{
		cout << "Binary Tree does not exit!";
		return -1;
	}
	e = T->data;
	return 0;
}
int Value(BiTree T, BiTNode* cur_p, char& e)
{
	e = cur_p->data;
	return 0;
}
BiTNode *Parent(BiTree T, BiTNode* cur_p)
{
	if (cur_p == T)
	{
		cout << "Ancestor does not have parent!"<<endl;
		return NULL;
	}
	if (T->lchild == cur_p||T->rchild==cur_p)
	{
		return T;
	}
	else
	{
		Parent(T->lchild, cur_p);
		Parent(T->rchild, cur_p);
	}
}
BiTNode *LeftChild(BiTree T, BiTNode* cur_p)
{
	return cur_p->lchild;
}
BiTNode *RightChild(BiTree T, BiTNode* cur_p)
{
	return cur_p->rchild;
}
BiTNode *LeftBrother(BiTree T, BiTNode* cur_p)
{
	if (T == cur_p)
	{
		cout << "Ancestor does not have brother!"<<endl;
		return NULL;
	}
	if (cur_p == T->rchild)
	{
		if (T->lchild == NULL)
		{
			cout << "He does not have a leftbrother!" << endl;
			return NULL;
		}
		else
		{
			return T->lchild;
		}
	}
	else
	{
		LeftBrother(T->lchild, cur_p);
		LeftBrother(T->rchild, cur_p);
	}
}
BiTNode *RightBrother(BiTree T, BiTNode* cur_p)
{
	if (T == cur_p)
	{
		cout << "Ancestor does not have brother!" << endl;
		return NULL;
	}
	if (cur_p == T->lchild)
	{
		if (T->rchild == NULL)
		{
			cout << "He does not have a rightbrother!" << endl;
			return NULL;
		}
		else
		{
			return T->rchild;
		}
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
int InOrderTraverse(BiTree T)
{
	if (T != NULL)
	{
		InOrderTraverse(T->lchild);
		cout << T->data;
		InOrderTraverse(T->rchild);
	}
	return 0;
}
int PostOrderTraverse(BiTree T)
{
	if (T != NULL)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->data;
	}
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
	cout << "中序遍历：";
	InOrderTraverse(T);
	cout << endl;
	cout << "后序遍历：";
	PostOrderTraverse(T);
	cout << endl;
	cout << "层次遍历：";
	LevelOrderTraverse(T);
	cout << endl;
	cout << "树的高度：";
	cout<<BiTreeDepth(T)<<endl;
	BiTNode *cur_p=Search(T, 'B');
	cout << cur_p->data<<endl;
	if (cur_p != NULL)
	{
		DeleteChild(T, cur_p, 0);
	}
	PreOrderTraverse(T);
	DestroyBiTree(T);
	return 0;
}















