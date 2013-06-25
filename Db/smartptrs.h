/***************************************************************************
 smartptrs.h  -  Header file that contains the definition and inline
                 implementation of smart pointers. This is not entirely
                 my code ... most of it was lifted from the MSDN. Search
                 for "refcount smart pointers" and view the "Templates and
                 Smart Pointers" article there.
                 What did I do? I added the RefCount::lessthan function and
                 the Ptr::operator < operator. I also allow the assignment
                 of const T* by casting it to non-const. This was required
                 so that the smart pointers could be stored in std::vectors,
                 lists, maps, etc. Finally, I added a few more comparison
                 operators.

 begin     : April 2004
 copyright : (C) 2004 by Phil Cairns
 email     : philcairns@hotmail.com

 This code may be used in compiled form in any way you desire (including
 commercial use). The code may be redistributed unmodified by any means
 providing it is not sold for profit without the authors written consent,
 and providing that this notice and the authors name and all copyright
 notices remains intact.

 This software is provided "as is" without express or implied warranty. Use
 it at your own risk!
 ***************************************************************************/

#if !defined(__smartptrs_h)
#define __smartptrs_h


	/*!
	Base class of smart pointer classes.
	*/
	class RefCount
	{
	private:
		int _crefs;

	public:
		RefCount() : _crefs(0) {}
		virtual ~RefCount() {}
		virtual void upcount() { ++_crefs; }
		virtual void downcount(void)
		{
			if (--_crefs == 0)
			{
				delete this;
			}
		}
		virtual bool lessthan(const RefCount* other)
		{
			return this < other;
		}
	};

	/*!
	Smart pointer template.
	*/
	template <class T> class Ptr
	{
	private:
		T* _p;

	public:
		Ptr(const Ptr<T>& ptr) : _p(ptr._p) { if (_p) _p->upcount(); }
		Ptr() : _p(0) {}
		Ptr(T* p) : _p(p) { if (_p) _p->upcount(); }
		~Ptr(void) { if (_p) _p->downcount(); }
		operator T*(void) const { return _p; }
		T& operator*(void) const { return *_p; }
		T* operator->(void) const { return _p; }
		Ptr& operator=(const Ptr<T> &p) { return operator=((T*)(Ptr<T>)p); }
		Ptr& operator=(T* p)
		{
			if (_p) _p->downcount();
			_p = p;
			if (_p) _p->upcount();
			return *this;
		}
		Ptr& operator=(const T* p)
		{
			return operator=((T*)p);
		}
		bool operator ==(const Ptr<T> &p) const { return _p == p._p; }
		bool operator ==(const T* p) const { return _p == p; }
		bool operator !=(const Ptr<T> &p) const { return _p != p._p; }
		bool operator !=(const T* p) const { return _p != p; }
		bool operator < (const Ptr<T> &p) const { return _p->lessthan(p._p); }
	};

	typedef Ptr<RefCount> RefCountPtr;

#endif

