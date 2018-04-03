#pragma once

template<class K, class V>
class HashNode
{
private:
	K key_;
	V value_;
	HashNode() = delete;
public:
	HashNode(const K key, const V value);
	HashNode(const HashNode<K, V> &copy);
	~HashNode();
	K GetKey() const noexcept;
	V& GetValue() noexcept;
	V GetValueCopy() const noexcept;
	void SetKey(const K key) noexcept;
	void SetValue(const V value) noexcept;
};

template<class K, class V>
inline HashNode<K, V>::HashNode(const K key, const V value)
{
	key_ = key;
	value_ = value;
}

template<class K, class V>
inline HashNode<K, V>::HashNode(const HashNode<K, V>& copy)
	: key_(copy.GetKey()), value_(copy.GetValue()) {}

template<class K, class V>
inline HashNode<K, V>::~HashNode() {}

template<class K, class V>
inline K HashNode<K, V>::GetKey() const noexcept { return key_; }

template<class K, class V>
inline V& HashNode<K, V>::GetValue() noexcept { return value_; }

template<class K, class V>
inline V HashNode<K, V>::GetValueCopy() const noexcept { return value_; }

template<class K, class V>
inline void HashNode<K, V>::SetKey(K key) noexcept { key_ = key; }

template<class K, class V>
inline void HashNode<K, V>::SetValue(V value) noexcept { value_ = value; }