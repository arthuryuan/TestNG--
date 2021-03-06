
#include <testngppst/internal/Error.h>

#include <testngppst/runner/loaders/ModuleTestSuiteLoader.h>
#include <testngppst/runner/loaders/ModuleLoader.h>
#include <testngppst/runner/loaders/ModuleLoaderFactory.h>

#include <testngppst/runner/TestSuiteDescEntryNameGetter.h>

TESTNGPPST_NS_START

struct ModuleTestSuiteLoaderImpl
    : public TestSuiteDescEntryNameGetter
{
   ModuleTestSuiteLoaderImpl(ModuleLoader* moduleLoader)
      : loader(moduleLoader)
   {}
   
   ~ModuleTestSuiteLoaderImpl();

   TestSuiteDesc*
   load( const StringList& searchingPaths \
       , const std::string& path \
       , TestSuiteDescEntryNameGetter* nameGetter);

   void unload();

   std::string getDescEntryName() const
   { return "___testngppst_test_suite_desc_getter"; }

   ModuleLoader* loader; // Y
};

///////////////////////////////////////////////////////////////
void
ModuleTestSuiteLoaderImpl::unload()
{
   if(loader != 0)
   {
      delete loader;
      loader = 0;
   }
}
///////////////////////////////////////////////////////////////
ModuleTestSuiteLoaderImpl::~ModuleTestSuiteLoaderImpl()
{
   unload();
}

///////////////////////////////////////////////////////////////
TestSuiteDesc*
ModuleTestSuiteLoaderImpl::
load( const StringList& searchingPaths
    , const std::string& path
    , TestSuiteDescEntryNameGetter* nameGetter)
{
   if(loader == 0)
   {
      throw Error("Internal Error");
   }

   if(nameGetter == 0)
   {
      nameGetter = this;
   }

   loader->load(searchingPaths, path);
 
   typedef TestSuiteDesc* (*TestSuiteDescGetter)();

   TestSuiteDescGetter getter = (TestSuiteDescGetter) \
       loader->findSymbol(nameGetter->getDescEntryName());

   TestSuiteDesc* desc = getter();
   if(desc == 0)
   {
      throw Error("Invalid test suite shared object");
   }

   return desc;
}

///////////////////////////////////////////////////////////////
ModuleTestSuiteLoader::ModuleTestSuiteLoader(ModuleLoader* loader)
   : This(new ModuleTestSuiteLoaderImpl(loader))
{
}

///////////////////////////////////////////////////////////////
ModuleTestSuiteLoader::~ModuleTestSuiteLoader()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TestSuiteDesc*
ModuleTestSuiteLoader::
load( const StringList& searchingPaths
    , const std::string& path
    , TestSuiteDescEntryNameGetter* nameGetter)
{
   return This->load(searchingPaths, path, nameGetter);
}

/////////////////////////////////////////////////////////////////
void ModuleTestSuiteLoader::unload()
{
   This->unload();
}

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END

