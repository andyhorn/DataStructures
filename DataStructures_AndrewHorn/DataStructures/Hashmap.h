#pragma once
#include <vector>
#include <list>
#include <functional>
#include "HashNode.h"

using std::vector;
using std::list;

template<class K, class V>
class HashMap
{
private:
	vector<list<HashNode<K, V>*>> hashmap_;
	std::function<void(V value)> visit_ = nullptr;
	std::function<int(K key)> hash_ = nullptr;
	size_t table_size_;
	void copyMap(const HashMap<K, V> &copy) noexcept;
	void copyVector(vector<list<HashNode<K, V>*>> &dest, const vector<list<HashNode<K, V>*>> &source) noexcept;
	void purgeTable(vector<list<HashNode<K, V>*>> &table) noexcept;
	void reHash();
protected:
	const vector<list<HashNode<K, V>*>>& getHashMap() const noexcept;
	std::function<void(V value)> getVisitFunc() const noexcept;
	std::function<int(K key)> getHashFunc() const noexcept;
public:
	HashMap() = delete;
	HashMap(size_t table_size, std::function<int(K key)> hash = nullptr);
	HashMap(const HashMap<K, V> &copy);
	HashMap<K, V>& operator=(const HashMap<K, V> &rhs);
	~HashMap();

	size_t getTableSize() const noexcept;
	void SetTableSize(int table_size);
	void Insert(K key, V value);
	void SetHashFunc(std::function<int(K key)> hash) noexcept; // remember to rehash the table
	V& operator[](K key) const;
	void Delete(K key);
	void Traverse(std::function<void(V value)> visit) const noexcept;
};

template<class K, class V>
inline void HashMap<K, V>::copyMap(const HashMap<K, V> &copy) noexcept
{
	purgeTable(hashmap_);
	hash_ = copy.getHashFunc();
	visit_ = copy.getVisitFunc();
	table_size_ = copy.getTableSize();
	hashmap_.resize(table_size_);
	copyVector(hashmap_, copy.getHashMap());
}

template<class K, class V>
inline void HashMap<K, V>::copyVector(vector<list<HashNode<K, V>*>> &dest, const vector<list<HashNode<K, V>*>> &source) noexcept
{
	// Performs a deep copy from the source hash table to destination table
	for (list<HashNode<K, V>*> list : source)
		for (HashNode<K, V>* node : list)
			dest[hash_(node->GetKey())].emplace_back(new HashNode<K, V>(node->GetKey(), node->GetValue()));
}

template<class K, class V>
inline void HashMap<K, V>::purgeTable(vector<list<HashNode<K, V>*>> &table) noexcept
{
	if (table.size() > 0) // if size == 0, nothing to delete
	{
		for (list<HashNode<K, V>*> list : table) // for each list in the table
			for (HashNode<K, V>* node : list) // for each node in the list, delete the pointed-to Value
				delete node;
		table.clear(); // clear table of pointers
	}
}

template<class K, class V>
inline void HashMap<K, V>::reHash()
{
	vector<list<HashNode<K, V>*>>* temp = new vector<list<HashNode<K, V>*>>(table_size_);
	copyVector(*temp, hashmap_); // copyVector will place nodes using current hash function
	purgeTable(hashmap_); // purge the old table
	hashmap_.resize(table_size_); // resize
	copyVector(hashmap_, *temp); // copy new table to hashmap_
	purgeTable(*temp); // purge temp table
	delete temp;
}

template<class K, class V>
inline const vector<list<HashNode<K, V>*>>& HashMap<K, V>::getHashMap() const noexcept { return hashmap_; }

template<class K, class V>
inline std::function<void(V value)> HashMap<K, V>::getVisitFunc() const noexcept { return visit_; }

template<class K, class V>
inline std::function<int(K key)> HashMap<K, V>::getHashFunc() const noexcept { return hash_; }

template<class K, class V>
inline HashMap<K, V>::HashMap(size_t table_size, std::function<int(K key)> hash)
	: table_size_(table_size), hash_(hash), visit_(nullptr) { hashmap_.resize(table_size_); }

template<class K, class V>
inline HashMap<K, V>::HashMap(const HashMap<K, V> &copy) { copyMap(copy); }

template<class K, class V>
inline HashMap<K, V>& HashMap<K, V>::operator=(const HashMap<K, V> &rhs) { copyMap(rhs); return *this; }

template<class K, class V>
inline HashMap<K, V>::~HashMap() { purgeTable(hashmap_); }

template<class K, class V>
inline size_t HashMap<K, V>::getTableSize() const noexcept { return table_size_; }

template<class K, class V>
inline void HashMap<K, V>::SetTableSize(int table_size)
{
	if (table_size > 0)
	{
		table_size_ = table_size;
		reHash();
	}
	else if (table_size == 0)
	{
		table_size_ = 0;
		purgeTable(hashmap_);
	}
	else
		throw Exception("Table size cannot be negative.");
}

template<class K, class V>
inline void HashMap<K, V>::Insert(K key, V value)
{
	if (hash_ != nullptr)
	{
		if (hashmap_[hash_(key)].size() == 0) // if nothing present, add
		{
			HashNode<K, V>* newNode = new HashNode<K, V>(key, value);
			hashmap_[hash_(key)].emplace_back(newNode);
		}
		else // if collision, check if unique key.
		{
			bool present = false;
			for (HashNode<K, V>* node : hashmap_[hash_(key)])
				if (node->GetKey() == key)
					present = true;
			if (!present)
			{
				HashNode<K, V>* newNode = new HashNode<K, V>(key, value);
				hashmap_[hash_(key)].emplace_back(newNode);
			}
			else
				throw Exception("Key already present. Keys must be unique.");
		}
	}	
	else
		throw Exception("Cannot operate without a hash function");
}

template<class K, class V>
inline void HashMap<K, V>::SetHashFunc(std::function<int(K key)> hash) noexcept 
{ 
	hash_ = hash; 
	if (hashmap_.size() > 0)
		reHash();
}

template<class K, class V>
inline V& HashMap<K, V>::operator[](K key) const 
{
	if (hash_ != nullptr)
	{
		if (hashmap_[hash_(key)].size() > 1)
		{
			for (HashNode<K, V>* node : hashmap_[hash_(key)])
				if (node->GetKey() == key)
					return node->GetValue();
			throw Exception("Value not found with given key.");
		}
		else 
			return hashmap_[hash_(key)].front()->GetValue();
	}
	else
		throw Exception("Cannot operate without a hash function.");
}

template<class K, class V>
inline void HashMap<K, V>::Delete(K key)
{
	if (hash_ != nullptr)
	{
		if (hashmap_[hash_(key)].size() > 0)
		{
			for (auto node : hashmap_[hash_(key)])
				if (node->GetKey() == key)
				{
					hashmap_[hash_(key)].remove(node);
					delete node;
					break;
				}
		}
		else
			throw Exception("No data at entered key.");
	}
	else
		throw Exception("Cannot operate without a hash function.");
}

template<class K, class V>
inline void HashMap<K, V>::Traverse(std::function<void(V value)> visit) const noexcept
{
	if (hashmap_.size() > 0)
	{
		for (list<HashNode<K, V>*> list : hashmap_)
			for (HashNode<K, V>* node : list)
				visit(node->GetValue());
	}
}
