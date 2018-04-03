#ifndef PAIR_H
#define PAIR_H

#include <ostream>
#include <string>

template <class K, class V>
class Pair
{
private:
	K * m_key;
	V * m_value;
public:
	Pair();
	Pair(K key, V value);
	Pair(const Pair & copy);
	~Pair();
	Pair<K, V> & operator=(const Pair<K, V> & rhs);
	bool operator==(const Pair & rhs);
	bool operator==(const Pair & rhs) const;
	K & GetKey();
	K & GetKey() const;
	V & GetValue();
	V & GetValue() const;
	void SetKey(const K & newKey);
	void SetValue(const V & newValue);

	template <class K, class V>
	friend std::ostream & operator<<(std::ostream & stream, const Pair<K, V> & pair);

};

template<class K, class V>
inline Pair<K, V>::Pair()
{
	m_key = new K;
	m_value = new V;
}

template<class K, class V>
inline Pair<K, V>::Pair(K key, V value)
{
	m_key = new K(key);
	m_value = new V(value);
}

template<class K, class V>
inline Pair<K, V>::Pair(const Pair<K, V> & copy)
{
	m_key = new K(copy.GetKey());
	m_value = new V(copy.GetValue());
}

template<class K, class V>
inline Pair<K, V>::~Pair()
{
	delete m_key;
	delete m_value;
}

template<class K, class V>
inline Pair<K, V> & Pair<K, V>::operator=(const Pair & rhs)
{
	delete m_key;
	delete m_value;

	m_key = new K(rhs.GetKey());
	m_value = new V(rhs.GetValue());

	return *this;
}

template<class K, class V>
inline bool Pair<K, V>::operator==(const Pair & rhs)
{
	return *m_key == rhs.GetKey() && *m_value == rhs.GetValue();
}

template<class K, class V>
inline bool Pair<K, V>::operator==(const Pair & rhs) const
{
	return *m_key == rhs.GetKey() && *m_value == rhs.GetValue();
}

template<class K, class V>
inline K & Pair<K, V>::GetKey()
{
	return *m_key;
}

template<class K, class V>
inline K & Pair<K, V>::GetKey() const
{
	return *m_key;
}

template<class K, class V>
inline V & Pair<K, V>::GetValue()
{
	return *m_value;
}

template<class K, class V>
inline V & Pair<K, V>::GetValue() const
{
	return *m_value;
}

template<class K, class V>
inline void Pair<K, V>::SetKey(const K & newKey)
{
	*m_key = newKey;
}

template<class K, class V>
inline void Pair<K, V>::SetValue(const V & newValue)
{
	*m_value = newValue;
}

template<class K, class V>
std::ostream & operator<<(std::ostream & stream, const Pair<K, V>& pair)
{
	stream << "Key: " << pair.GetKey() << " Value: " << pair.GetValue() << std::endl;
	return stream;
}

#endif