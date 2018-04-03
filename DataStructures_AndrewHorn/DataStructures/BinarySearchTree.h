#pragma once

#include "BinarySearchNode.h"
#include "QueueList.h"

template<class T>
QueueList<T> _data;

template<class T>
static void Visit(BinarySearchNode<T> *node)
{
	_data<T>.Enqueue(node->GetDataCopy());
}

template<class T>
class BinarySearchTree
{
private:
	void(*_visit)(BinarySearchNode<T> *node);
	BinarySearchNode<T> *_root;

	void inOrder(BinarySearchNode<T>* node);
	void preOrder(BinarySearchNode<T> *node);
	void postOrder(BinarySearchNode<T> *node);
	void breadthFirst(BinarySearchNode<T> *node);
	void findNodeToDelete(const T &data);
	void deleteFromTree(BinarySearchNode<T> *parent, const T &data);
	void recursivePurge(BinarySearchNode<T> *node, BinarySearchNode<T> *parent);
	int max(int left, int right);
	void insert(const T &data, BinarySearchNode<T> *node);
	int height(BinarySearchNode<T> *node);
public:
	BinarySearchTree();
	BinarySearchTree(const T &data);
	BinarySearchTree(BinarySearchTree<T> &copy);
	~BinarySearchTree();

	void InOrder(void(*visit)(BinarySearchNode<T> *node));
	void InOrder();
	void PreOrder(void(*visit)(BinarySearchNode<T> *node));
	void PreOrder();
	void PostOrder(void(*visit)(BinarySearchNode<T> *node));
	void PostOrder();
	void BreadthFirst(void(*visit)(BinarySearchNode<T> *node));
	void BreadthFirst();

	void SetFunction(void(*visit)(BinarySearchNode<T> *node));
	void Insert(const T &data);
	void Delete(const T &data);
	void Purge();
	int Height();
};

template<class T>
inline BinarySearchTree<T>::BinarySearchTree()
	: _root(nullptr), _visit(nullptr) {}

template<class T>
inline BinarySearchTree<T>::BinarySearchTree(const T &data)
{
	_root = new BinarySearchNode<T>(data);
	_visit = nullptr;
}

template<class T>
inline BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T> &copy)
{
	_root = nullptr;
	_visit = nullptr;

	copy.BreadthFirst(Visit<T>);
	while (!_data<T>.isEmpty())
		Insert(_data<T>.Dequeue());
}

template<class T>
inline BinarySearchTree<T>::~BinarySearchTree() 
{ 
	if (_root != nullptr)
		Purge(); 
	_root = nullptr;
	_visit = nullptr;
}

template<class T>
inline void BinarySearchTree<T>::SetFunction(void(*visit)(BinarySearchNode<T> *node)) { _visit = visit; }

template<class T>
inline void BinarySearchTree<T>::InOrder(void(*visit)(BinarySearchNode<T> *node)) { _visit = visit; inOrder(_root); }

template<class T>
inline void BinarySearchTree<T>::InOrder() { inOrder(_root); }

template<class T>
inline void BinarySearchTree<T>::inOrder(BinarySearchNode<T> *node)
{
	if (node != nullptr)
	{
		if (node->GetLeft() != nullptr)
			inOrder(node->GetLeft());

		_visit(node);

		if (node->GetRight() != nullptr)
			inOrder(node->GetRight());
	}
}

template<class T>
inline void BinarySearchTree<T>::PreOrder(void(*visit)(BinarySearchNode<T> *node)) { _visit = visit; preOrder(_root); }

template<class T>
inline void BinarySearchTree<T>::PreOrder() { preOrder(_root); }

template<class T>
inline void BinarySearchTree<T>::preOrder(BinarySearchNode<T> *node)
{
	if (node != nullptr)
	{
		_visit(node);

		if (node->GetLeft() != nullptr)
			preOrder(node->GetLeft());

		if (node->GetRight() != nullptr)
			preOrder(node->GetRight());
	}
}

template<class T>
inline void BinarySearchTree<T>::PostOrder(void(*visit)(BinarySearchNode<T> *node)) { _visit = visit; postOrder(_root); }

template<class T>
inline void BinarySearchTree<T>::PostOrder() { postOrder(_root); }

template<class T>
inline void BinarySearchTree<T>::postOrder(BinarySearchNode<T> *node)
{
	if (node != nullptr)
	{
		if (node->GetLeft() != nullptr)
			postOrder(node->GetLeft());
		if (node->GetRight() != nullptr)
			postOrder(node->GetRight());
		_visit(node);
	}
}

template<class T>
inline void BinarySearchTree<T>::BreadthFirst(void(*visit)(BinarySearchNode<T> *node)) { _visit = visit; breadthFirst(_root); }

template<class T>
inline void BinarySearchTree<T>::BreadthFirst() { breadthFirst(_root); }

template<class T>
inline void BinarySearchTree<T>::breadthFirst(BinarySearchNode<T> *node)
{
	if (node != nullptr)
	{
		QueueList<BinarySearchNode<T>*> queue;
		BinarySearchNode<T> *nodePtr;
		queue.Enqueue(node);

		while (!queue.isEmpty())
		{
			nodePtr = queue.Dequeue();
			_visit(nodePtr);
			if (nodePtr->GetLeft() != nullptr)
				queue.Enqueue(nodePtr->GetLeft());
			if (nodePtr->GetRight() != nullptr)
				queue.Enqueue(nodePtr->GetRight());
		}
	}
}

template<class T>
inline void BinarySearchTree<T>::Insert(const T &data) { insert(data, _root); }

template<class T>
inline void BinarySearchTree<T>::insert(const T &data, BinarySearchNode<T> *node)
{
	BinarySearchNode<T> *current = node;
	if (_root != nullptr)
	{
		if (current != nullptr)
		{
			if (data < current->GetDataRef())
			{
				if (current->GetLeft() != nullptr)
					insert(data, current->GetLeft());
				else
					current->SetLeft(new BinarySearchNode<T>(data));
			}
			else if (data > current->GetDataRef())
			{
				if (current->GetRight() != nullptr)
					insert(data, current->GetRight());
				else
					current->SetRight(new BinarySearchNode<T>(data));
			}
		}
	}
	else
		_root = new BinarySearchNode<T>(data);
}

template<class T>
inline void BinarySearchTree<T>::Delete(const T &data)
{
	if (_root != nullptr)
		findNodeToDelete(data);
	else
		throw Exception("Cannot delete, tree is currently empty.");
}

template<class T>
inline void BinarySearchTree<T>::findNodeToDelete(const T &data)
{
	BinarySearchNode<T> *current = _root, *prev = _root;
	bool found = false;

	while (current != nullptr && !found)
	{
		if (current->GetDataRef() == data)
			found = true;
		else
		{
			prev = current;
			if (current->GetDataRef() > data)
				current = current->GetLeft();
			else
				current = current->GetRight();
		}
	}

	if (current == nullptr)
		throw Exception("Unable to delete, could not find a match.");

	else if (found)
	{
		if (current == _root)
			deleteFromTree(_root, data);
		else
			deleteFromTree(prev, data);
	}
}

template<class T>
inline void BinarySearchTree<T>::deleteFromTree(BinarySearchNode<T> *parent, const T &data)
{
	BinarySearchNode<T> *current = nullptr, *del = nullptr, *prev = nullptr;

	if (parent == nullptr)
		throw Exception("Error: Nullptr passed to deleteFromTree.");

	if (parent->GetDataRef() == data)
		del = parent;
	else if (parent->GetDataRef() > data)
		del = parent->GetLeft();
	else
		del = parent->GetRight();

	if (del->GetLeft() == nullptr && del->GetRight() == nullptr) // leaf
	{
		if (parent->GetDataRef() > data)
			parent->SetLeft(nullptr);
		else
			parent->SetRight(nullptr);
	}
	else if (del->GetLeft() != nullptr && del->GetRight() == nullptr) // has left
	{
		if (parent->GetDataRef() > data)
			parent->SetLeft(del->GetLeft());
		else
			parent->SetRight(del->GetLeft());
	}
	else if (del->GetLeft() == nullptr && del->GetRight() != nullptr) // has right
	{
		if (parent->GetDataRef() > data)
			parent->SetLeft(del->GetRight());
		else
			parent->SetRight(del->GetRight());
	}
	else // has both subtrees
	{
		current = del->GetLeft();
		while (current->GetRight() != nullptr)
		{
			prev = current;
			current = current->GetRight();
		}
		
		del->SetData(current->GetDataCopy());
		if (prev == nullptr)
			del->SetLeft(current->GetLeft());
		else
			prev->SetRight(current->GetLeft());

		del = current;
	}
	delete del;
}

template<class T>
inline void BinarySearchTree<T>::Purge()
{
	if (_root != nullptr)
		recursivePurge(_root, nullptr);
	else
		throw Exception("Cannot purge, tree is empty.");
}

template<class T>
inline void BinarySearchTree<T>::recursivePurge(BinarySearchNode<T> *node, BinarySearchNode<T> *parent)
{
	if (node != nullptr)
	{
		if (node->GetLeft() != nullptr)
			recursivePurge(node->GetLeft(), node);
		if (node->GetRight() != nullptr)
			recursivePurge(node->GetRight(), node);
		if (node->GetLeft() == nullptr && node->GetRight() == nullptr)
		{
			if (parent != nullptr)
			{
				if (parent->GetLeft() == node)
					parent->SetLeft(nullptr);
				else
					parent->SetRight(nullptr);
				delete node;
			}
			else
			{
				_root = nullptr;
				delete node;
			}
		}
	}
}

template<class T>
inline int BinarySearchTree<T>::Height()
{
	int _height = 0;
	if (_root != nullptr)
	{
		_height =  1 + max(height(_root->GetLeft()), height(_root->GetRight()));
	}
	
	return _height;
}

template<class T>
inline int BinarySearchTree<T>::height(BinarySearchNode<T> *root)
{
	int left = 0, right = 0;
	if (root != nullptr)
	{
		if (root->GetLeft() != nullptr)
			left = height(root->GetLeft());
		if (root->GetRight() != nullptr)
			right = height(root->GetRight());
		return 1 + max(left, right);
	}
	else
		return 0;
}

template<class T>
inline int BinarySearchTree<T>::max(int left, int right)
{
	return (left > right ? left : right);
}