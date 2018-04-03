#pragma once
#include "Vertex.h"

template<class V, class E>
class Vertex;

template<class V, class E>
class Edge
{
private:
	Vertex<V,E> * _destination = nullptr;
	int _weight = 0;
	E _data;
public:
	Edge() noexcept;
	Edge(const Edge<V,E> &copy) noexcept;
	Edge(E &data, Vertex<V,E> *dest = nullptr, int weight = 0) noexcept;
	~Edge();

	E GetData() const noexcept;
	int GetWeight() const noexcept;
	Vertex<V, E>* GetDestination() const noexcept;
	void SetData(const E &data) noexcept;
	void SetWeight(int weight) noexcept;
	void SetDestination(Vertex<V,E> *dest) noexcept;
	bool operator==(Edge<V, E> &rhs) noexcept;
	Edge<V, E>& operator=(const Edge<V, E> &rhs);
};

template<class V, class E>
inline Edge<V,E>::Edge() noexcept
	: _destination(nullptr), _weight(0) {}

template<class V, class E>
inline Edge<V,E>::Edge(const Edge<V,E> &copy) noexcept
	: _destination(copy.GetDestination()), _weight(copy.GetWeight()), _data(copy.GetData()) {}

template<class V, class E>
inline Edge<V,E>::Edge(E &data, Vertex<V,E> *dest, int weight) noexcept
	: _destination(dest), _weight(weight), _data(data) {}

template<class V, class E>
inline Edge<V,E>::~Edge() {}

template<class V, class E>
inline E Edge<V,E>::GetData() const noexcept { return _data; }

template<class V, class E>
inline int Edge<V,E>::GetWeight() const noexcept { return _weight; }

template<class V, class E>
inline Vertex<V,E>* Edge<V,E>::GetDestination() const noexcept { return _destination; }

template<class V, class E>
inline void Edge<V,E>::SetData(const E &data) noexcept { _data = data; }

template<class V, class E>
inline void Edge<V,E>::SetWeight(int weight) noexcept { _weight = weight; }

template<class V, class E>
inline void Edge<V,E>::SetDestination(Vertex<V,E> *dest) noexcept { _destination = dest; }

template<class V, class E>
inline bool Edge<V, E>::operator==(Edge<V, E> &rhs) noexcept
{
	return (&rhs == this
		|| (rhs.GetData() == _data
			&& rhs.GetWeight() == _weight
			&& rhs.GetDestination() == _destination));
}

template<class V, class E>
inline Edge<V, E>& Edge<V, E>::operator=(const Edge<V, E> &rhs)
{
	_destination = rhs.GetDestination();
	_weight = rhs.GetWeight();
	_data = rhs.GetData();
	return *this;
}
