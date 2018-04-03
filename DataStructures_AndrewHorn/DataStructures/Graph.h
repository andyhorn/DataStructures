#pragma once
#include <list>
#include <stack>
#include <queue>
#include <iterator>
#include <functional>
#include "Vertex.h"
#include "Edge.h"
#include "Exception.h"

using std::list;
using std::iterator;
using std::stack;
using std::queue;

// std::function<void(V value)> visit_ = nullptr;

template<class V, class E>
class Graph
{
private:
	/*MEMBERS*/
	list<Vertex<V, E>> _vertices;
	int _count;
	/*METHODS*/
	typename list<Vertex<V, E>>::iterator _getVertex(const V &data);
	void _removeEdges(typename list<Vertex<V, E>>::iterator &vertexIter, Vertex<V, E> *vPtr) noexcept;
	void _depthFirst(std::function<void(Vertex<V, E> &vertex)> visit, stack<Vertex<V, E>> &vStack) noexcept;
	void _breadthFirst(std::function<void(Vertex<V, E> &vertex)> visit, queue<Vertex<V, E>> &vQueue) noexcept;
	void _resetProcessed() noexcept;
protected:
	const list<Vertex<V, E>>& _getVertices() const noexcept;
public:
	Graph() noexcept;
	Graph(const Graph<V, E> &copy);
	~Graph();

	void InsertVertex(const V &data);
	void InsertEdge(V from, V to, E edge, int weight = 0);
	void DeleteVertex(const V &data);
	void DeleteEdge(V from, V to, E edge);
	void DepthFirst(std::function<void(Vertex<V, E> &vertex)> visit) noexcept;
	void BreadthFirst(std::function<void(Vertex<V, E> &vertex)> visit) noexcept;
	bool isEmpty() const noexcept;
	const int GetCount() const noexcept;
};

/*PRIVATE METHODS*/
template<class V, class E>
inline typename list<Vertex<V, E>>::iterator Graph<V, E>::_getVertex(const V &data)
{
	// Searches through list of Vertices to find a Vertex with the given data.
	bool found = false;
	typename list<Vertex<V, E>>::iterator vertexIter;
	vertexIter = _vertices.begin();
	while (vertexIter != _vertices.end() && !found)
	{
		if (vertexIter->GetData() == data)
		{
			found = true;
			continue;
		}
		vertexIter++;
	}

	if (found)
		return vertexIter;
	else
		throw Exception("Vertex not found.");
}

template<class V, class E>
inline void Graph<V, E>::_removeEdges(typename list<Vertex<V, E>>::iterator &vertexIter, Vertex<V, E> *vPtr) noexcept
{
	// This method is called by DeleteEdges to remove all edges of a selected Vertex that lead to the Vertex being deleted.
	typename list<Edge<V, E>>::iterator edgeIter;
	list<typename list<Edge<V, E>>::iterator> edges;

	edgeIter = vertexIter->GetEdges();
	// For all edges of this Vertex, if it points to vRemove, add to list to be deleted.
	for (size_t i = 0; i < vertexIter->GetOutDegree(); i++, edgeIter++)
	{
		if (edgeIter->GetDestination() == vPtr)
			edges.push_back(edgeIter);
	}

	if (!edges.empty())
	{
		while (!edges.empty())
		{
			// Delete all selected edges.
			vertexIter->DeleteEdge(*edges.front());
			edges.pop_front();
		}
	}
}

template<class V, class E>
inline void Graph<V, E>::_depthFirst(std::function<void(Vertex<V, E> &vertex)> visit, stack<Vertex<V, E>> &vStack) noexcept
{
	// Recursively visits all vertices in a depth-first algorithm.
	if (!vStack.empty())
	{
		typename list<Edge<V, E>>::iterator edgeIter;
		Vertex<V, E> _top = vStack.top();
		vStack.pop();
		visit(_top);

		edgeIter = _top.GetEdges();
		for (size_t j = 0; j < _top.GetOutDegree(); j++, edgeIter++)
		{
			if (!edgeIter->GetDestination()->GetProcessed())
			{
				vStack.push(*edgeIter->GetDestination());
				edgeIter->GetDestination()->SetProcessed(true);
			}
		}
		_depthFirst(visit, vStack);
	}
}

template<class V, class E>
inline void Graph<V, E>::_breadthFirst(std::function<void(Vertex<V, E> &vertex)> visit, queue<Vertex<V, E>> &vQueue) noexcept
{
	// Recursively visits all vertices in a breadth-first algorithm.
	if (!vQueue.empty())
	{
		typename list<Edge<V, E>>::iterator edgeIterRev;
		Vertex<V, E> _top = vQueue.front();
		vQueue.pop();
		visit(_top);

		edgeIterRev = _top.GetEdgesEnd();
		edgeIterRev--;
		for (size_t j = 0; j < _top.GetOutDegree(); j++)
		{
			if (!edgeIterRev->GetDestination()->GetProcessed())
			{
				vQueue.push(*edgeIterRev->GetDestination());
				edgeIterRev->GetDestination()->SetProcessed(true);
			}
			if (!(j == _top.GetOutDegree() - 1))
				edgeIterRev--;
		}
		_breadthFirst(visit, vQueue);
	}
}

template<class V, class E>
inline void Graph<V, E>::_resetProcessed() noexcept
{
	// Resets all _processed flags to false.
	typename list<Vertex<V, E>>::iterator vertexIter;
	vertexIter = _vertices.begin();
	while (vertexIter != _vertices.end())
	{
		vertexIter->SetProcessed(false);
		vertexIter++;
	}
}

/*PROTECTED METHODS*/

template<class V, class E>
inline const list<Vertex<V, E>>& Graph<V, E>::_getVertices() const noexcept
{
	return _vertices;
}

/*PUBLIC METHODS*/

template<class V, class E>
inline Graph<V, E>::Graph() noexcept
	: _count(0) {}

template<class V, class E>
inline Graph<V, E>::Graph(const Graph<V, E> &copy) 
{
	if (&copy != this)
	{
		if (!_vertices.empty())
			_vertices.clear();
		_vertices = copy._getVertices();
		_count = copy.GetCount();
	}
	else
		throw Exception("Graph cannot copy itself.");
}

template<class V, class E>
inline Graph<V, E>::~Graph() {}

template<class V, class E>
inline void Graph<V, E>::InsertVertex(const V &data)
{
	// check if vertex already exists
	bool present = false;
	for (Vertex<V, E> vertex : _vertices)
		if (vertex.GetData() == data)
			present = true;

	// if not, create a new vertex
	if (!present)
	{
		_vertices.emplace_back(Vertex<V, E>(data));
		_count++;
	}
	else
		throw Exception("Vertex already exists.");
}

template<class V, class E>
inline void Graph<V, E>::InsertEdge(V from, V to, E edge, int weight)
{
	typename list<Vertex<V, E>>::iterator vertexIter;
	bool found = false;
	Vertex<V, E> *fromPtr = nullptr, *toPtr = nullptr;
	vertexIter = _vertices.begin();

	for (size_t i = 0; i < GetCount() && !found; i++, vertexIter++)
	{
		// Find 'From" and 'To' Vertices.
		if (vertexIter->GetData() == from)
			fromPtr = &*vertexIter;
		if (vertexIter->GetData() == to)
			toPtr = &*vertexIter;
		if (fromPtr != nullptr && toPtr != nullptr) // If both are found, no need to continue searching.
			found = true;
	}

	if (found)
	{
		// Undirected graph means edges connect both ways.
		Edge<V, E> temp(edge, toPtr, weight);
		fromPtr->InsertEdge(temp);
		fromPtr->SetInDegree(fromPtr->GetInDegree() + 1);
		
		temp.SetDestination(fromPtr);
		toPtr->InsertEdge(temp);
		toPtr->SetInDegree(toPtr->GetInDegree() + 1);
	}
	else
		throw Exception("Unable to insert edge, vertices not found.");
}

template<class V, class E>
inline void Graph<V, E>::DeleteVertex(const V &data)
{
	try
	{
		typename list<Vertex<V, E>>::iterator vRemove = _getVertex(data);
		typename list<Vertex<V, E>>::iterator vertexIter;
		
		vertexIter = _vertices.begin();
		while (vertexIter != _vertices.end()) // For each Vertex in the graph:
		{
			if (&*vertexIter != &*vRemove) // Don't care about vRemove.
				_removeEdges(vertexIter, &*vRemove); // Remove edges from current Vertex that lead to vRemove.
			vertexIter++;
		}
		_vertices.erase(vRemove);
		_count--;
	}
	catch (Exception &e)
	{
		cout << e << endl;
		throw e;
	}
}

template<class V, class E>
inline void Graph<V, E>::DeleteEdge(V from, V to, E edge)
{
	try
	{
		bool present = false;
		// Find 'From' and 'To' Vertices.
		typename list<Vertex<V, E>>::iterator _from = _getVertex(from), _to = _getVertex(to);
		typename list<Edge<V, E>>::iterator edgeIter;
		edgeIter = _from->GetEdges();

		// Check is desired edge is present.
		for (size_t i = 0; i < _from->GetOutDegree() && !present; i++)
			if (edgeIter->GetData() == edge && edgeIter->GetDestination() == &*_to)
				present = true;

		if (present)
		{
			// If edge is present, delete it.
			_from->DeleteEdge(*edgeIter);
			_to->SetInDegree(_to->GetInDegree() - 1);
		}
	}
	catch (Exception &e)
	{
		// If edge not present, throw error.
		cout << e << endl;
		throw e;
	}
}

template<class V, class E>
inline void Graph<V, E>::DepthFirst(std::function<void(Vertex<V, E> &vertex)> visit) noexcept
{
	// Calls _depthFirst which recursively visits all vertices.
	if (!_vertices.empty())
	{
		stack<Vertex<V, E>> vStack;
		vStack.push(_vertices.front());
		_vertices.front().SetProcessed(true);
		_depthFirst(visit, vStack);
	}
	_resetProcessed();
}

template<class V, class E>
inline void Graph<V, E>::BreadthFirst(std::function<void(Vertex<V, E> &vertex)> visit) noexcept
{
	// Calls _breadthFirst which recursively visits all vertices.
	if (!_vertices.empty())
	{
		queue<Vertex<V, E>> vStack;
		vStack.push(_vertices.front());
		_vertices.front().SetProcessed(true);
		_breadthFirst(visit, vStack);
	}
	_resetProcessed();
}

template<class V, class E>
inline bool Graph<V, E>::isEmpty() const noexcept { return _count == 0; }

template<class V, class E>
inline const int Graph<V, E>::GetCount() const noexcept { return _count; }