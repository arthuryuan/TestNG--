
#ifndef __TESTNGPP_DL_MODULE_LOADER_H__
#define __TESTNGPP_DL_MODULE_LOADER_H__

#include <testngpp/testngpp.h>

#include <testngpp/loaders/ModuleLoader.h>

TESTNGPP_NS_START

struct DLModuleLoaderImpl;

/////////////////////////////////////////////
struct DLModuleLoader
   : public ModuleLoader
{
   DLModuleLoader();
   ~DLModuleLoader(); 

   void load
      ( const std::string& modulePath )
         TESTNGPP_THROW(TESTNGPP_NS::Error);

	void load
      ( const StringList& searchingPaths \
      , const std::string& modulePath)
         TESTNGPP_THROW(TESTNGPP_NS::Error);

   void unload();

   void* findSymbol
      ( const std::string& symbol )
         TESTNGPP_THROW(TESTNGPP_NS::Error);

private:

   DLModuleLoaderImpl* This;
};

/////////////////////////////////////////////

TESTNGPP_NS_END

#endif

