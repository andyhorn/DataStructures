#pragma once

#include "BinarySearchNode.h"

enum BAL { LH = -1, EH, RH };

template<class T>
class AVLNode
{
private:
	T _data;
	size_t _bf;
	AVLNode<T>* _left;
	AVLNode<T>* _right;
public:
	AVLNode();
	AVLNode(const T &data, AVLNode<T> *left = nullptr, AVLNode<T> *right = nullptr);
	AVLNode(const AVLNode<T> &copy);
	~AVLNode();

	int GetBF() const;
	void SetBF(int);
	void SetRight(AVLNode<T> *left);
	void SetLeft(AVLNode<T> *right);
	AVLNode<T>* GetLeft() const;
	AVLNode<T>* GetRight() const;
	T& GetDataRef();
	T GetDataCopy() const;
	void SetData(const T &data);

	AVLNode<T>& operator=(const AVLNode<T> &rhs);
};

template<class T>
inline AVLNode<T>::AVLNode()
	: _bf(EH), _left(nullptr), _right(nullptr) {}

template<class T>
inline AVLNode<T>::AVLNode(const T &data, AVLNode<T> *left, AVLNode<T> *right)
	: _data(data), _bf(EH), _left(left), _right(right) {}

template<class T>
inline AVLNode<T>::AVLNode(const AVLNode<T> &copy)
	: _data(copy.GetDataCopy()), _left(copy.GetLeft()), _right(copy.GetRight()), _bf(copy.GetBF()) {}

template<class T>
inline AVLNode<T>::~AVLNode() {}

template<class T>
inline int AVLNode<T>::GetBF() const { return (int)_bf; }

template<class T>
inline void AVLNode<T>::SetBF(int bf) { _bf = bf; }

template<class T>
inline void AVLNode<T>::SetRight(AVLNode<T> *right) { _right = right; }

template<class T>
inline void AVLNode<T>::SetLeft(AVLNode<T> *left) { _left = left; }

template<class T>
inline AVLNode<T>* AVLNode<T>::GetLeft() const { return _left; }

template<class T>
inline AVLNode<T>* AVLNode<T>::GetRight() const { return _right; }

template<class T>
inline T& AVLNode<T>::GetDataRef() { return _data; }

template<class T>
inline T AVLNode<T>::GetDataCopy() const { return _data; }

template<class T>
inline void AVLNode<T>::SetData(const T &data) { _data = data; }

template<class T>
inline AVLNode<T>& AVLNode<T>::operator=(const AVLNode<T> &rhs)
{
	if (&rhs != this)
	{
		_right = rhs.GetRight();
		_left = rhs.GetLeft();
		_data = rhs.GetDataCopy();
		_bf = rhs.GetBF();
	}
}