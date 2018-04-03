#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::ostream;

class Exception
{
private:
	char m_msg[256];

public:
	Exception();
	Exception(const char *msg);
	Exception(const Exception &copy);
	~Exception();

	Exception& operator=(const Exception &rhs);
	friend ostream& operator<<(ostream &stream, const Exception &except);
	void initialize();
	const char* getMessage();
	const char* getMessage() const;
	void setMessage(const char *msg);
	int getSize();
	int getSize() const;
	void print();
	void print() const;
};

inline Exception::Exception()
{
	initialize();
}

inline void Exception::initialize()
{
	for (int i = 0; i < 256; i++)
	{
		m_msg[i] = '\0';
	}
}

inline Exception::Exception(const char *msg)
{
	strcpy_s(m_msg, msg);
}

inline Exception::Exception(const Exception &copy)
{
	strcpy_s(m_msg, copy.getMessage());
}

inline Exception::~Exception() {}

inline Exception& Exception::operator=(const Exception &rhs)
{
	if (this != &rhs)
	{
		strcpy_s(m_msg, rhs.getMessage());
	}

	return *this;
}

inline void Exception::print()
{
	int i = 0;
	for (int i = 0; i < getSize(); i++)
	{
		cout << m_msg[i];
	}
	cout << endl;
}

inline void Exception::print() const
{
	int i = 0;
	for (int i = 0; i < getSize(); i++)
	{
		cout << m_msg[i];
	}
	cout << endl;
}

inline const char * Exception::getMessage()
{
	return m_msg;
}

inline const char * Exception::getMessage() const
{
	return m_msg;
}

inline void Exception::setMessage(const char *msg)
{
	strcpy_s(m_msg, msg);
}

inline int Exception::getSize()
{
	return static_cast<int>(strlen(m_msg));
}

inline int Exception::getSize() const
{
	return static_cast<int>(strlen(m_msg));
}

inline ostream& operator<<(ostream &stream, const Exception &except)
{
	stream << except.getMessage() << endl;
	return stream;
}
#endif
