#pragma once

#include <unordered_map>
#include <map>
#include <vector>

#include "base/Base.h"

#include "type/Type.h"
#include "runnable/Runnable.h"
#include "Exception.h"

namespace gse {

CLASS( GSE, base::Base )
	GSE();
	virtual ~GSE();

	void AddModule( const std::string& path, runnable::Runnable* module );

	void Run();

	void SetGlobal( const std::string& identifier, Value variable );
	const Value& GetGlobal( const std::string& identifier );

private:

	std::unordered_map< std::string, runnable::Runnable* > m_modules = {};
	std::vector< std::string > m_modules_order = {};
	std::map< std::string, Value > m_globals = {};

};

}
