#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <string>
#include <atomic>

using namespace std;

namespace base {

class Base {
public:
	Base();
	virtual ~Base();
	virtual const string GetNamespace() const;
	const string GetName() const;
	const string& GetLocalName() const;
	virtual const string GetClassName() const = 0;
protected:
	const size_t m_object_id = 0;
	string m_class_name = "";
	string m_name = "";
	void Log( const string &text ) const;
};

#define NAMED_CLASS( _name, _parent, _namespace ) \
class _name : public _parent { \
public: \
	virtual const string GetNamespace() const { \
		return _parent::GetNamespace() + # _namespace + "::" ; \
	} \
	const string GetClassName() const { \
		return #_name; \
	}

#define CHILD_CLASS( _name, _parent) \
NAMED_CLASS( _name, _parent, _name )

#define MINOR_CLASS( _name, _parent) \
NAMED_CLASS( _name ## _parent, _parent, _name )

#define MAJOR_CLASS( _name, _parent ) \
class _name ## Error : public base::Error { \
public:\
	_name ## Error(const string &reason) : base::Error::Error( reason ) {} \
	virtual const string GetNamespace() const { \
		return base::Error::GetNamespace() + # _name + "::" ; \
	} \
	const string GetClassName() const { \
		return #_name; \
	} \
}; \
NAMED_CLASS( _name, _parent, _name )

} /* namespace base */

#include "base/Error.h"
