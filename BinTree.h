#pragma once
#include<iostream>

using namespace std;

class Node
{
	int key;
	Node* left, *right, *parent;

public:
	Node(int k = 0, Node* L = NULL, Node* R = NULL, Node* P = NULL)
	{
		key = k; left = L; right = R; parent = P;
	}
	int GetKey() { return key; }

	friend class BinTree;
};


class BinTree
{
	Node* root;

	Node* Tree(int n, Node* p); //построение идеально сбалансированного дерева с n вершинами, p - предок вершины дерева

	void Copy(Node* q, Node* p, int f);
	//копирование дерева с корнем q, p - узел, к которому присоединяется копия
	//f=0 - копируемое дерево будет левым потомком для p;
	//f=1 - копируемое дерево будет правым потомком для p.

	int Function(Node* root, int* Array, int m, int n);

public:
	BinTree() { root = NULL; }
	BinTree(int n); 		//n - количество ключей, ключи случайны
	BinTree(int* a, int n);	//a - массив ключей,  n - количество ключей
							//потребуется вспомогательная ф-я
	BinTree(const BinTree&);
	BinTree& operator=(const BinTree&);
	~BinTree();

	void Add(int k, Node* p); 	//добавление узла с ключом k в дерево с корнем p
	void Del(Node* p); 		//удаление узла p
	void DelRoot(); 			//удаление корня

	void TreeTraversalLCR(Node* p); //обход дерева с корнем p, в глубину по принципу лево-корень-право, ключи выводятся на консоль
	void TreeTraversalRCL(Node* p);//обход дерева с корнем p, в глубину по принципу право-корень-лево, ключи выводятся на консоль
	void TreeTraversalLRC(Node* p); //обход дерева с корнем p, в глубину по принципу лево-право-корень, ключи выводятся на консоль
	void TreeTraversalRLC(Node* p);//обход дерева с корнем p, в глубину по принципу право-лево-корень, ключи выводятся на консоль
	void TreeTraversalCLR(Node* p);//обход дерева с корнем p, в глубину по принципу корень-лево-право, ключи выводятся на консоль
	void WidthTraversal(Node* p); //обход дерева с корнем p, в ширину

	Node* FindKey(int k, Node* p); //поиск узла с ключом k в дереве с корнем p
	Node* FindMax(Node* p); //поиск узла с max ключом в дереве с корнем p
	Node* FindMin(Node* p); //поиск узла с min ключом в дереве с корнем p
	int FindHight(Node* p); //поиск высоты дерева с корнем p
	int Count(Node* p); //нахождение количества узлов в дереве с корнем p

	Node* GetRoot() { return root; }
	void Clear(); 	//уничтожает все дерево, кроме корня

	void PrintTree(Node* p, int k); //вывод дерева на консоль, k - отступ от левой границы консоли
};
