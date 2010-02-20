
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

#ifndef __TESTNGPP_FIXTURE_INFO_H__
#define __TESTNGPP_FIXTURE_INFO_H__

#include <testngpp/testngpp.h>
#include <testngpp/desc/FixtureInfoReader.h>

TESTNGPP_NS_START

struct FixtureInfoImpl;

//////////////////////////////////////
struct FixtureInfo 
      : public FixtureInfoReader
{
   const TestCaseInfoReader* const
   getTestCase(unsigned int index)
   {
      if(index >= numberOfTestCases())
      { return 0; }

      return getTestCases()[index];
   }

private:

   virtual const TestCaseInfoReader* const * const
   getTestCases() const = 0;

};

//////////////////////////////////////

TESTNGPP_NS_END

#endif 

