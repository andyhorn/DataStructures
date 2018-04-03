#pragma once


template<class T>
class BinarySearchNode
{
private:
	T _data;
	BinarySearchNode<T> * _left;
	BinarySearchNode<T> * _right;
public:
	BinarySearchNode();
	BinarySearchNode(const T &data, BinarySearchNode<T> *left = nullptr, BinarySearchNode<T> *right = nullptr);
	BinarySearchNode(const BinarySearchNode<T> &copy);
	~BinarySearchNode();

	void SetData(const T &data);
	T GetDataCopy() const;
	T& GetDataRef();

	void SetLeft(BinarySearchNode<T> * const left);
	void SetRight(BinarySearchNode<T> * const right);

	BinarySearchNode<T>* GetLeft() const;
	BinarySearchNode<T>* GetRight() const;

	BinarySearchNode<T>& operator=(const BinarySearchNode<T> &rhs);
	bool operator==(const BinarySearchNode<T> &rhs);
};

template<class T>
inline BinarySearchNode<T>::BinarySearchNode()
	: _left(nullptr), _right(nullptr) {}

template<class T>
inline BinarySearchNode<T>::BinarySearchNode(const T &data, BinarySearchNode<T> *left, BinarySearchNode<T> *right)
	: _data(data), _left(left), _right(right) {}

template<class T>
inline BinarySearchNode<T>::BinarySearchNode(const BinarySearchNode<T> &copy)
	: _data(copy.GetData()), _left(copy.GetLeft()), _right(copy.GetRight()) {}

template<class T>
inline BinarySearchNode<T>::~BinarySearchNode() { _left = nullptr; _right = nullptr; }

template<class T>
inline void BinarySearchNode<T>::SetData(const T &data) { _data = data; }

template<class T>
inline T BinarySearchNode<T>::GetDataCopy() const { return _data; }

template<class T>
inline T& BinarySearchNode<T>::GetDataRef() { return _data; }

template<class T>
inline void BinarySearchNode<T>::SetLeft(BinarySearchNode<T> * const left) { _left = left; }

template<class T>
inline void BinarySearchNode<T>::SetRight(BinarySearchNode<T> * const right) { _right = right; }

template<class T>
inline BinarySearchNode<T>* BinarySearchNode<T>::GetLeft() const { return _left; }

template<class T>
inline BinarySearchNode<T>* BinarySearchNode<T>::GetRight() const { return _right; }

template<class T>
inline BinarySearchNode<T>& BinarySearchNode<T>::operator=(const BinarySearchNode<T> &rhs)
{
	_data = rhs.GetData();
	_left = rhs.GetLeft();
	_right = rhs.GetRight();
}

template<class T>
inline bool BinarySearchNode<T>::operator==(const BinarySearchNode<T> &rhs)
{
	return (_data == copy.GetData() && _left == copy.GetLeft() && _right == copy.GetRight());
}
