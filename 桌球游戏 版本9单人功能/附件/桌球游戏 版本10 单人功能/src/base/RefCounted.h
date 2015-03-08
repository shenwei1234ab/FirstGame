#pragma once

class RefCounted {
public:

	RefCounted() : m_refCount(1) {}
	RefCounted(const RefCounted &) : m_refCount(1) {}
	virtual ~RefCounted() {}

	int GetRef()const 
	{
		return m_refCount;
	}
	void addRef() const { ++m_refCount; }
	bool release() const 
	{
		if (!--m_refCount) 
		{
			delete this;
			return true;
		}
		return false;
	}
private:
	mutable int m_refCount;
};


template <class T>
class RefCountedPtr
{
public:
	RefCountedPtr() : m_ptr(0) {}
	explicit RefCountedPtr(T *ptr) : m_ptr(ptr) {}

	RefCountedPtr(const RefCountedPtr &other) : m_ptr(other.m_ptr) 
	{
		if (m_ptr) 
		{
			m_ptr->addRef();
		}
	}

	~RefCountedPtr() {
		if (m_ptr) {
			m_ptr->release();
			m_ptr = 0;
		}
	}

	T * operator ->() const {
		return m_ptr;
	}

	T & operator *() const {
		return *m_ptr;
	}


	RefCountedPtr & operator =(T *rhs)
	{
		if (m_ptr) 
		{
			m_ptr->release();
		}
		if ((m_ptr = rhs)) {
			m_ptr->addRef();
		}
		return *this;
	}

	RefCountedPtr & operator =(const RefCountedPtr &rhs) {
		if (m_ptr) {
			m_ptr->release();
		}
		if ((m_ptr = rhs.m_ptr)) {
			m_ptr->addRef();
		}
		return *this;
	}

	T * get() const {
		return m_ptr;
	}

	void reset(T *ptr = 0) {
		if (m_ptr) {
			m_ptr->release();
		}
		if ((m_ptr = rhs)) {
			m_ptr->addRef();
		}
	}

	operator bool() const {
		return m_ptr != 0;
	}

private:
	T *m_ptr;
};