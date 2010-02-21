
/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2010>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <string>
#include <dlfcn.h>

#include <testngpp/internal/Error.h>

#include <testngpp/loaders/DLModuleLoader.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct DLModuleLoaderImpl
{
    DLModuleLoaderImpl();
    ~DLModuleLoaderImpl();

    void load( const StringList& searchingPaths \
             , const std::string& modulePath);

    void loadInSearchingPaths
             ( const StringList& searchingPaths \
             , const std::string& modulePath);

    void unload();

    void* findSymbol(const std::string& symbol);

    void* handle;

};

////////////////////////////////////////////////////////
DLModuleLoaderImpl::
DLModuleLoaderImpl()
    : handle(0)
{
}
////////////////////////////////////////////////////////
DLModuleLoaderImpl::~DLModuleLoaderImpl()
{
   unload();
}

/////////////////////////////////////////////////////////////////
namespace
{
   std::string getFullPath( const std::string& path
                           , const std::string& modulePath)
   {
      std::string fullPath(path);

      if(fullPath.at(fullPath.length()-1) != '/')
      {
         fullPath += "/";
      }

      fullPath += modulePath;

      return fullPath;
   }

   void* DlOpen(const char* path)
   {
      return ::dlopen(path, RTLD_LAZY | RTLD_LOCAL);
   }

   const std::string suffix(".so");

   bool hasSuffix(const std::string& modulePath)
   {
      return ( modulePath.size() > suffix.size() ) &&
             ( modulePath.find(suffix) == \
                (modulePath.size() - suffix.size()));
   }

   void* openModule(const std::string& modulePath)
   {
      void* p = DlOpen(modulePath.c_str());
      if(p == 0 && !hasSuffix(modulePath))
      {
         std::string module = modulePath + ".so";
         return DlOpen(module.c_str());
      }

      return p;
   }
}

/////////////////////////////////////////////////////////////////
void
DLModuleLoaderImpl::
loadInSearchingPaths
   ( const StringList& searchingPaths
   , const std::string& modulePath)
{
   StringList::const_iterator i = \
       searchingPaths.begin();
   for(; i != searchingPaths.end(); i++)
   {
      handle = openModule(getFullPath(*i, modulePath));
      if(handle != 0)
      {
         return;
      }
   }

   throw Error(::dlerror());
}

////////////////////////////////////////////////////////
void
DLModuleLoaderImpl::
load( const StringList& searchingPaths
    , const std::string& modulePath)
{
   if(handle != 0)
   {
      unload();
   }

   handle = openModule(modulePath);
   if(handle == 0)
   {
      loadInSearchingPaths(searchingPaths, modulePath);
   }
}

////////////////////////////////////////////////////////
void
DLModuleLoaderImpl::
unload()
{
   if(handle != 0)
   {
      ::dlclose(handle);
      handle = 0;
   }
}

////////////////////////////////////////////////////////
void*
DLModuleLoaderImpl::
findSymbol(const std::string& symbol)
{
    if(handle == 0)
    {
        throw Error("module has not been loaded yet");
    }

    void* ptr = (void*) ::dlsym(handle, symbol.c_str());
    if(ptr == 0)
    {
        throw Error(::dlerror());
    }

    return ptr;
}

////////////////////////////////////////////////////////
DLModuleLoader::
DLModuleLoader()
   : This(new DLModuleLoaderImpl())
{
}

////////////////////////////////////////////////////////
DLModuleLoader::
~DLModuleLoader()
{
    delete This;
}

////////////////////////////////////////////////////////
void
DLModuleLoader::
load( const StringList& searchingPaths
    , const std::string& modulePath)
{
    This->load(searchingPaths, modulePath);
}

////////////////////////////////////////////////////////
void
DLModuleLoader::
load(const std::string& modulePath)
{
    StringList searchingPaths;
    This->load(searchingPaths, modulePath);
}

////////////////////////////////////////////////////////
void
DLModuleLoader::unload()
{
    This->unload();
}

////////////////////////////////////////////////////////
void*
DLModuleLoader::findSymbol(const std::string& symbol)
{
   return This->findSymbol(symbol);
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END

