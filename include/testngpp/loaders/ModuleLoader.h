
#ifndef __TESTNGPP_MODULE_LOADER_H__
#define __TESTNGPP_MODULE_LOADER_H__

#include <string>

#include <testngpp/testngpp.h>
#include <testngpp/internal/Error.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

////////////////////////////////////////////
struct ModuleLoader
{
	virtual void load
      ( const std::string& modulePath ) 
         TESTNGPP_THROW(TESTNGPP_NS::Error) = 0;

	virtual void load
      ( const StringList& searchingPaths
      , const std::string& modulePath )
         TESTNGPP_THROW(TESTNGPP_NS::Error) = 0;

   virtual void
   unload() = 0;

   virtual void* findSymbol
      ( const std::string& symbol ) 
         TESTNGPP_THROW(TESTNGPP_NS::Error) = 0;

   virtual ~ModuleLoader() {}
};

////////////////////////////////////////////

TESTNGPP_NS_END

#endif

