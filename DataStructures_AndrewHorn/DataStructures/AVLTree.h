#pragma once

#include "AVLNode.h"
#include "QueueList.h"

template<class T>
QueueList<T> _data;

template<class T>
static void Visit(AVLNode<T> *node)
{
	_data<T>.Enqueue(node->GetDataCopy());
}

template<class T>
class AVLTree
{
private:
	AVLNode<T> *_root;
	void(*_visit)(AVLNode<T> *node);

	void inOrder(AVLNode<T>* node);
	void preOrder(AVLNode<T> *node);
	void postOrder(AVLNode<T> *node);
	void breadthFirst(AVLNode<T> *node);
	void recursivePurge(AVLNode<T> *node, AVLNode<T> *parent);
	int max(int left, int right);
	int height(AVLNode<T> *node);

	void insertAVL(AVLNode<T> *&root, AVLNode<T> *node, const T &data, bool &taller);
	AVLNode<T>* rotateLeft(AVLNode<T> *node);
	AVLNode<T>* rotateRight(AVLNode<T> *node);
	AVLNode<T>* leftBalance(AVLNode<T> *node, bool &taller);
	AVLNode<T>* rightBalance(AVLNode<T> *node, bool &taller);
	AVLNode<T>* deleteAVL(AVLNode<T> *node, const T &key, bool &success);
	AVLNode<T>* deleteRightBalance(AVLNode<T> *node);
	AVLNode<T>* deleteLeftBalance(AVLNode<T> *node);
public:
	AVLTree();
	AVLTree(const T &data);
	AVLTree(AVLTree<T> &copy);
	~AVLTree();

	void InOrder(void(*visit)(AVLNode<T> *node));
	void InOrder();
	void PreOrder(void(*visit)(AVLNode<T> *node));
	void PreOrder();
	void PostOrder(void(*visit)(AVLNode<T> *node));
	void PostOrder();
	void BreadthFirst(void(*visit)(AVLNode<T> *node));
	void BreadthFirst();

	void SetFunction(void(*visit)(AVLNode<T> *node));
	void Purge();
	int Height();
	void Insert(const T &data);
	void Delete(const T &data);
};

template<class T>
inline AVLTree<T>::AVLTree()
	: _root(nullptr), _visit(nullptr) {}

template<class T>
inline AVLTree<T>::AVLTree(const T &data)
{
	_root = new AVLNode<T>(data);
	_visit = nullptr;
}

template<class T>
inline AVLTree<T>::AVLTree(AVLTree<T> &copy)
{
	_root = nullptr;
	_visit = nullptr;

	if (&copy != this)
	{
		copy.BreadthFirst(Visit);
		while (!_data<T>.isEmpty())
			Insert(_data<T>.Dequeue());
	}
}

template<class T>
inline AVLTree<T>::~AVLTree()
{

	Purge();
	_root = nullptr;
	_visit = nullptr;
}

template<class T>
inline void AVLTree<T>::SetFunction(void(*visit)(AVLNode<T> *node)) { _visit = visit; }

template<class T>
inline void AVLTree<T>::InOrder(void(*visit)(AVLNode<T> *node)) { _visit = visit; inOrder(_root); }

template<class T>
inline void AVLTree<T>::InOrder() { inOrder(_root); }

template<class T>
inline void AVLTree<T>::inOrder(AVLNode<T> *node)
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
inline void AVLTree<T>::Insert(const T &data)
{
	bool taller = false;
	if (_root != nullptr)
		insertAVL(_root, _root, data, taller);
	else
		_root = new AVLNode<T>(data);
}

template<class T>
inline void AVLTree<T>::insertAVL(AVLNode<T> *&root, AVLNode<T> *node, const T &data, bool &taller)
{
	if (node == nullptr)
	{
		node = new AVLNode<T>(data);
		taller = true;
		if (data < root->GetDataRef())
			root->SetLeft(node);
		else
			root->SetRight(node);
	}
	else if (data < node->GetDataRef()) // left subtree
	{
		insertAVL(node, node->GetLeft(), data, taller);
		if (taller) // left high
		{
			switch (node->GetBF())
			{
			case LH: root->SetLeft(leftBalance(node, taller)); // LL
				break;
			case EH: node->SetBF(LH);
				break;
			case RH: node->SetBF(EH);
				taller = false;
				break;
			}
		}
	}
	else if (data > node->GetDataRef()) // right subtree
	{
		insertAVL(node, node->GetRight(), data, taller);
		if (taller) // right high
		{
			switch (node->GetBF())
			{
			case LH: node->SetBF(EH);
				taller = false;
				break;
			case EH: node->SetBF(RH);
				break;
			case RH: root->SetRight(rightBalance(node, taller)); // RR
				break;
			}
		}
	}
}

template<class T>
inline void AVLTree<T>::PreOrder(void(*visit)(AVLNode<T> *node)) { _visit = visit; preOrder(_root); }

template<class T>
inline void AVLTree<T>::PreOrder() { preOrder(_root); }

template<class T>
inline void AVLTree<T>::preOrder(AVLNode<T> *node)
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
inline void AVLTree<T>::PostOrder(void(*visit)(AVLNode<T> *node)) { _visit = visit; postOrder(_root); }

template<class T>
inline void AVLTree<T>::PostOrder() { postOrder(_root); }

template<class T>
inline void AVLTree<T>::postOrder(AVLNode<T> *node)
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
inline void AVLTree<T>::BreadthFirst(void(*visit)(AVLNode<T> *node)) { _visit = visit; breadthFirst(_root); }

template<class T>
inline void AVLTree<T>::BreadthFirst() { breadthFirst(_root); }

template<class T>
inline void AVLTree<T>::breadthFirst(AVLNode<T> *node)
{
	if (node != nullptr)
	{
		QueueList<AVLNode<T>*> queue;
		AVLNode<T> *nodePtr;
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
inline AVLNode<T>* AVLTree<T>::leftBalance(AVLNode<T> *node, bool &taller)
{
	AVLNode<T>* newRoot = nullptr;
	if (node->GetBF() == LH && node->GetLeft()->GetBF() == LH)
	{
		newRoot = rotateRight(node);
		taller = false;
	}
	else
	{
		newRoot = rotateLeft(node->GetLeft());
		newRoot = rotateRight(node);
	}
	return newRoot;
}

template<class T>
inline AVLNode<T>* AVLTree<T>::rightBalance(AVLNode<T> *node, bool &taller)
{
	AVLNode<T> *newRoot = nullptr;
	if (node->GetBF() == RH && node->GetRight()->GetBF() == RH)
	{
		newRoot = rotateLeft(node);
		taller = false;
	}
	else
	{
		newRoot = rotateRight(node->GetRight());
		newRoot = rotateLeft(node);
	}
	return newRoot;
}

template<class T>
inline AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T> *node)
{
	AVLNode<T> *left = node->GetLeft();
	node->SetLeft(left->GetRight());
	left->SetRight(node);
	if (left->GetRight() != nullptr)
		node->SetBF(RH);
	else
		node->SetBF(EH);
	left->SetBF(EH);
	return left;
}

template<class T>
inline AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T> *node)
{
	AVLNode<T> *right = node->GetRight();
	node->SetRight(right->GetLeft());
	right->SetLeft(node);
	if (node->GetLeft() != nullptr)
		node->SetBF(LH);
	else
		node->SetBF(EH);
	right->SetBF(EH);
	return right;
}

template<class T>
inline void AVLTree<T>::Delete(const T &key)
{
	if (_root != nullptr)
	{
		bool success = false;
		deleteAVL(_root, key, success);
	}
}

template<class T>
inline AVLNode<T>* AVLTree<T>::deleteAVL(AVLNode<T> *node, const T &key, bool &success)
{
	if (node == nullptr)
	{
		success = false;
		return nullptr;
	}
	if (key < node->GetDataRef())
	{
		node->SetLeft(deleteAVL(node->GetLeft(), key, success));
		// if (tree shorter)
		//		set root to deleteRightBalance(root)
		if (success)
			node = deleteRightBalance(node);
	}
	else if (key > node->GetDataRef())
	{
		node->SetRight(deleteAVL(node->GetRight(), key, success));
		// if (tree shorter)
		//		set root to deleteLeftBalance(root)
		if (success)
			node = deleteLeftBalance(node);
	}
	else
	{

		AVLNode<T> *del = nullptr, *cur = nullptr, *prev = nullptr, *ret = nullptr;
		del = node;

		if (node->GetRight() == nullptr)
		{
			success = true;
			ret = node->GetLeft();
			delete del;
		}
		else if (node->GetLeft() == nullptr)
		{
			success = true;
			ret = node->GetRight();
			delete del;
		}
		else
		{
			cur = node->GetLeft();
			while (cur->GetRight() != nullptr)
			{
				prev = cur;
				cur = cur->GetRight();
			}
			node->SetData(cur->GetDataCopy());
			/*prev->SetRight(nullptr);
			delete cur;*/
			node->SetLeft(deleteAVL(cur, key, success));

			if (success)
				node = deleteRightBalance(node);
		}
		return ret;
	}
}

template<class T>
inline AVLNode<T>* AVLTree<T>::deleteRightBalance(AVLNode<T> *node)
{
	if (node->GetBF() == RH)
	{
		// set rightOfRight to right subtree
		AVLNode<T> *rightOfRight = node->GetRight();
		if (rightOfRight->GetBF() == LH)
		{
			AVLNode<T> *leftOfRight = rightOfRight->GetLeft();
			node->SetRight(rotateRight(rightOfRight));
			node = rotateLeft(node);
			// double rotation
		}
		else
		{
			node = rotateLeft(node);
		}
	}
	return node;
}

template<class T>
inline AVLNode<T>* AVLTree<T>::deleteLeftBalance(AVLNode<T> *node)
{
	if (node->GetBF() == LH)
	{
		AVLNode<T> *leftOfLeft = node->GetLeft();
		if (leftOfLeft->GetBF() == RH)
		{
			AVLNode<T> *rightOfLeft = leftOfLeft->GetRight();
			node->SetLeft(rotateLeft(leftOfLeft));
			node = rotateRight(node);
		}
		else
			node = rotateRight(node);
	}
	return node;
}

template<class T>
inline void AVLTree<T>::Purge()
{
	if (_root != nullptr)
		recursivePurge(_root, nullptr);
}

template<class T>
inline void AVLTree<T>::recursivePurge(AVLNode<T> *node, AVLNode<T> *parent)
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
inline int AVLTree<T>::Height()
{
	int _height = 0;
	if (_root != nullptr)
	{
		_height = 1 + max(height(_root->GetLeft()), height(_root->GetRight()));
	}

	return _height;
}

template<class T>
inline int AVLTree<T>::height(AVLNode<T> *root)
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
inline int AVLTree<T>::max(int left, int right)
{
	return (left > right ? left : right);
}