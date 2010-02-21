
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

