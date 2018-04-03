#pragma once

#include <list>
#include <iterator>
#include "Edge.h"

template<class V, class E>
class Edge;

using std::list;
using std::iterator;

template<class V, class E>
class Vertex
{
private:
	/*MEMBERS*/
	V _data;
	int _inDegree;
	int _outDegree;
	bool _processed;
	list<Edge<V, E>> _edges;
	/*METHODS*/
	void _copyVertex(const Vertex<V, E> &copy) noexcept;
	const list<Edge<V, E>>& _getEdgeList() const noexcept;
public:
	Vertex() noexcept;
	Vertex(const Vertex<V, E> &copy);
	Vertex(const V &data) noexcept;
	~Vertex();

	const V& GetData() const noexcept;
	const int GetInDegree() const noexcept;
	const int GetOutDegree() const noexcept;
	const bool GetProcessed() const noexcept;
	typename list<Edge<V, E>>::iterator GetEdges() noexcept;
	typename list<Edge<V, E>>::iterator GetEdgesEnd() noexcept;
	void SetData(const V &data) noexcept;
	void SetInDegree(int degree) noexcept;
	void SetOutDegree(int degree) noexcept;
	void SetProcessed(bool processed) noexcept;
	void InsertEdge(Edge<V, E> edge);
	void DeleteEdge(const Edge<V, E> &edge);
	Vertex<V, E>& operator=(const Vertex<V, E> &rhs);
};

/*PRIVATE METHODS*/

template<class V, class E>
inline void Vertex<V, E>::_copyVertex(const Vertex<V, E> &copy) noexcept
{
	if (&copy != this)
	{
		_inDegree = copy.GetInDegree();
		_outDegree = copy.GetOutDegree();
		_processed = copy.GetProcessed();
		_data = copy.GetData();
		_edges = copy._getEdgeList();
	}
}

template<class V, class E>
inline const list<Edge<V, E>>& Vertex<V, E>::_getEdgeList() const noexcept
{
	return _edges;
}

/*PUBLIC METHODS*/

template<class V, class E>
inline Vertex<V, E>::Vertex() noexcept
	: _inDegree(0), _outDegree(0), _processed(false), _data() {}

template<class V, class E>
inline Vertex<V, E>::Vertex(const Vertex<V, E> &copy)
{
	if (&copy != this)
		_copyVertex(copy);
	else
		throw Exception("Vertex cannot copy itself.");
}

template<class V, class E>
inline Vertex<V, E>::Vertex(const V &data) noexcept
	: _inDegree(0), _outDegree(0), _processed(false), _data(data) {}

template<class V, class E>
inline Vertex<V, E>::~Vertex() {}

template<class V, class E>
inline const V& Vertex<V, E>::GetData() const noexcept { return _data; }

template<class V, class E>
inline typename list<Edge<V, E>>::iterator Vertex<V, E>::GetEdges() noexcept
{ 
	typename list<Edge<V, E>>::iterator frontOfList;
	frontOfList = _edges.begin();
	return frontOfList;
}

template<class V, class E>
inline typename list<Edge<V, E>>::iterator Vertex<V, E>::GetEdgesEnd() noexcept
{
	typename list<Edge<V, E>>::iterator endOfList;
	endOfList = _edges.end();
	return endOfList;
}

template<class V, class E>
inline const int Vertex<V, E>::GetInDegree() const noexcept { return _inDegree; }

template<class V, class E>
inline const int Vertex<V, E>::GetOutDegree() const noexcept { return _outDegree; }

template<class V, class E>
inline const bool Vertex<V, E>::GetProcessed() const noexcept { return _processed; }

template<class V, class E>
inline void Vertex<V, E>::SetData(const V &data) noexcept { _data = data; }

template<class V, class E>
inline void Vertex<V, E>::SetInDegree(int degree) noexcept { _inDegree = degree; }

template<class V, class E>
inline void Vertex<V, E>::SetOutDegree(int degree) noexcept { _outDegree = degree; }

template<class V, class E>
inline void Vertex<V, E>::SetProcessed(bool processed) noexcept { _processed = processed; }

template<class V, class E>
inline void Vertex<V, E>::InsertEdge(Edge<V, E> edge)
{
	bool present = false;

	if (!_edges.empty())
	{
		typename list<Edge<V, E>>::iterator edgeIter;
		edgeIter = _edges.begin();
		for (size_t i = 0; i < _edges.size() && !present; i++, edgeIter++)
			if ((*edgeIter) == edge)
				present = true;
	}
	if (!present || _edges.empty())
	{
		_edges.emplace_back(edge);
		_outDegree++;
	}
	else
		throw Exception("Edge already present.");
}

template<class V, class E>
inline void Vertex<V, E>::DeleteEdge(const Edge<V, E> &edge) 
{ 
	bool found = false;
	typename list<Edge<V, E>>::iterator iter;
	iter = _edges.begin();
	while (iter != _edges.end() && !found)
		if (iter->GetData() == edge.GetData())
			found = true;
	if (found)
	{
		_edges.erase(iter);
		_outDegree--;
	}
	else
		throw Exception("Unable to remove: Edge not found.");
}

template<class V, class E>
inline Vertex<V, E>& Vertex<V, E>::operator=(const Vertex<V, E> &rhs)
{
	_copyVertex(rhs);
	return *this;
}