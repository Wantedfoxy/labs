#include "BinTree.h"
#include <iostream>
#include <queue>
#include <ctime>


using namespace std;

Node* BinTree::Tree(int n, Node* p)// Построение идеально сбалансированного дерева с помощью рекурсии
{								  //  n - количество вершин, p - предок вершины дерева
	if (n == 0) return NULL;
	Node* q = new Node(rand() % 776);
	int nL, nR;
	nL = (n - 1) / 2; nR = n - nL -1;
	q->left = Tree(nL, q);
	q->right = Tree(nR, q);
	q->parent = p;
	return q;
}

BinTree::BinTree(int n)// n - количество вершин, при этом каждая из них генерируется случайным образом
{
	root = Tree(n, NULL);
}

int BinTree::Function(Node* root, int* Array,int m, int n)// Вспомогательная функция для BinTree
{
	if (root == 0) return m;
	root->key = Array[m];
	m++;
	m = Function(root->left, Array, m, n - 1);
	m = Function(root->right, Array, m, n - 1);
	return m;
}

BinTree::BinTree(int* a, int n)// a - массив вершин,  n - количество вершин
{
	Function(root, a, 0, n);
}

void BinTree::Copy(Node* q, Node* p, int f)// Функция копирования, q - корень, p - узел, к которому присоединяется копия
{										  //  При этом f отвечает за то, каким из двух потомков будет копируемое дерево
	if (q == NULL) return;				 //	  f = 0 => левый потомок
	Node* t = new Node(q->key);			//	  f = 1 => правый потомок
	t->parent = p;
	if (f == 0) p->left = t;
	else p->right = t;
	Copy(q->left, t, 0);
	Copy(q->right, t, 1);
}

BinTree::BinTree(const BinTree& T)
{
	if (T.root == NULL) root = NULL;
	else 
	{
		root = new Node(T.root->key);
		Copy(T.root->left, root, 0);
		Copy(T.root->right, root, 1);
	}
}

BinTree& BinTree::operator=(const BinTree& T)
{
	if (this != &T)
	{
		Clear();
		DelRoot();
		if (T.root == NULL) root = NULL;
		else
		{
			root = new Node(T.root->key);
			Copy(T.root->left, root, 0);
			Copy(T.root->right, root, 1);
		}
	}
		return *this;
}

BinTree::~BinTree()// Деструктор
{
	Clear();
	DelRoot();
}

void BinTree::Add(int k, Node* p)// Добавление узла с значением k в дерево с корнем p
{
	if (p == NULL)
		return;
	if (p->left == NULL)
	{
		Node* q = new Node(k);
		p->left = q;  q->parent = p;
		return;
	}
	if (p->right == NULL)
	{
		Node* q = new Node(k);
		p->right = q;  q->parent = p;
		return;
	}
	if (rand() % 2) Add(k, p->left);
	else Add(k, p->right);
}

void BinTree::Del(Node* p)// Удаление узла p
{
	if (p == root) 
	{ 
		DelRoot(); 
		return; 
	}
	Node* q = p->parent;
	//удаление листа
	if ((p->left == NULL) && (p->right == NULL))
	{
		if (q->left == p) q->left = NULL;
		else q->right = NULL;
		delete p;
		return;
	}
	//у p нет левой ветви
	if (p->left == NULL && p->right != NULL)
	{
		if (q->left == p) q->left = p->right;
		else q->right = p->right;
		p->right->parent = q;
		delete p;
		return;
	}
	//у p нет правой ветви
	if (p->left != NULL && p->right == NULL)
	{
		if (q->left == p) q->left = p->left;
		else q->right = p->left;
		p->left->parent = q;
		delete p;
		return;
	}

	//у p есть оба поддерева
	Node* t = p;
	while (t->left != 0) 
		t = t->left;
	//вырезаем t из дерева
	if (t->right == NULL)
		t->parent->left = NULL;
	else 
	{
		t->parent->left = t->right;
		t->right->parent = t->parent;
	}
	//заменяем p узлом t
	t->left = p->left;
	t->right = p->right;
	t->parent = q;

	if (q->left == p) q->left = t;
	else q->right = t;

	if (p->left != NULL)
		p->left->parent = t;

	p->right->parent = t;
	delete p;
	return;
}

void BinTree::DelRoot()// Удаление корня
{
	if ((root == NULL) || ((root->left == NULL) && (root->right == NULL)))
	{
		delete root;
		root = NULL;
		return;
	}
	if ((root->left != NULL) && (root->right == NULL))
	{
		Node* q = root;
		root = root->left;
		delete q;
		return;
	}
	if ((root->left == NULL) && (root->right != NULL))
	{
		Node* q = root;
		root = root->right;
		delete q;
		return;
	}
	if ((root->left != NULL) && (root->right != NULL))
	{
		Node* v = root;
		while (v->left != NULL)
			v = v->left;
		if (v->right == NULL)
			v->parent->left = NULL;
		else 
		{
			v->parent->left = v->right;
			v->right->parent = v->parent;
		}

		root->key = v->key;
		delete v;
		return;
	}
}

void BinTree::TreeTraversalLCR(Node* p)// Обход дерева с корнем p в глубину по принципу лево-корень-право
{
	if (p == NULL) return;
	TreeTraversalLCR(p->left);
	cout << p->key << ' ';
	TreeTraversalLCR(p->right);
}

void BinTree::TreeTraversalRCL(Node* p)// Обход дерева с корнем p в глубину по принципу право-корень-лево
{
	if (p == NULL) return;
	TreeTraversalRCL(p->right);
	std::cout << p->key << " ";
	TreeTraversalRCL(p->left);
}

void BinTree::TreeTraversalLRC(Node* p)// Обход дерева с корнем p в глубину по принципу лево-право-корень
{
	if (p == NULL) return;
	TreeTraversalLRC(p->left);
	TreeTraversalLRC(p->right);
	cout << p->key << ' ';
}

void BinTree::TreeTraversalRLC(Node* p)// Обход дерева с корнем p в глубину по принципу право-лево-корень
{
	if (p == NULL) return;
	TreeTraversalRLC(p->right);
	TreeTraversalRLC(p->left);
	cout << p->key << ' ';
}

void BinTree::TreeTraversalCLR(Node* p)// Обход дерева с корнем p в глубину по принципу корень-лево-право
{
	if (p == NULL) return;
	cout << p->key << " ";
	TreeTraversalCLR(p->left);
	TreeTraversalCLR(p->right);
}

void BinTree::WidthTraversal(Node* p)// Обход дерева с корнем p в ширину
{
	if (p == NULL) return;
	queue <Node*> Q;
	Q.push(p);			 // добавляет элемент в конец queue
	while (Q.size() != 0) // Пока очередь не пуста
	{
		Node* z = Q.front(); //Возвращает ссылку на первый элемент в начале
		Q.pop();			  // Удаляет элемент из начала
		cout << z->key << " ";
		if (z->left) Q.push(z->left);
		if (z->right) Q.push(z->right);
	}
}

Node* BinTree::FindKey(int k, Node* p)// Поиск вершины с значением k в дереве с корнем p
{
	if (p == NULL) return NULL;
	if (p->key == k) return p;
	Node* FindLeft = FindKey(k, p->left);
	Node* FindRight = FindKey(k, p->right);
	if (FindLeft != NULL)
		return FindLeft;
	if (FindRight != NULL)
		return FindRight;
}

Node* BinTree::FindMax(Node* p)// Поиск наибольшей вершины в дереве с корнем p
{
	if (p == NULL) return NULL;
	if ((p->left == NULL) && (p->right == NULL)) return p;
	Node* LMax = FindMax(p->left), * RMax = FindMax(p->right), * Max = p;
	if ((LMax!=NULL) && (Max->key < LMax->key))
		Max = LMax;
	if ((RMax!=NULL)&& (Max->key < RMax->key))
		Max = RMax;
	return Max;
}

Node* BinTree::FindMin(Node* p)// Поиск наименьшей вершины в дереве с корнем p
{
	if (p == NULL) return NULL;
	if ((p->left == NULL) && (p->right == NULL)) return p;
	Node* LMin = FindMin(p->left), * RMin = FindMin(p->right), * Min = p;
	if (LMin!=NULL && Min->key > LMin->key)
		Min = LMin;
	if (RMin!=NULL && Min->key > RMin->key)
		Min = RMin;
	return Min;
}

int BinTree::FindHight(Node* p)// Поиск высоты дерева с корнем p
{
	if (p == NULL) return 0;
	if ((p->left == NULL) && (p->right == NULL)) return 1;
	int HightL = 0, HightR = 0;
	if (p->left != NULL) HightL = FindHight(p->left);
	if (p->right != NULL) HightR = FindHight(p->right);
	int Hight;
	if (HightL > HightR)
		Hight = HightL;
	else Hight = HightR;
	return Hight + 1;
}

int BinTree::Count(Node* p)// Подсчет количества вершин в дереве с корнем p
{
	if (p == NULL) return 0;
	if ((p->left == NULL) && (p->right == NULL)) return 1;
	int CountL = 0, CountR = 0;
	if (p->left != NULL) CountL = Count(p->left);
	if (p->right != NULL) CountR = Count(p->right);
	return CountL + CountR + 1;
}

void BinTree::Clear()// Удаление дерева (корень остается)
{
	if (root == NULL) return;
	while (root->right != 0)
		Del(root->right);
	while (root->left != 0)
		Del(root->left);
}

void BinTree::PrintTree(Node* p, int k)// Вывод дерева на консоль
{
	if (p == NULL) return;
	PrintTree(p->right, k + 6);
	for (int i = 0; i < k; i++) cout << ' ';
	cout << p->key << endl;
	PrintTree(p->left, k + 6);
}