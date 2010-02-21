
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

