
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

#include <testngppst/testngppst.hpp>

#include <testngpp/desc/TestCaseInfoReader.h>
#include <testngpp/desc/FixtureInfoReader.h>
#include <testngpp/desc/ModuleFileInfoReader.h>
#include <testngpp/desc/SuiteInfoReader.h>
#include <testngpp/loaders/DLModuleLoader.h>

USING_TESTNGPP_NS

FIXTURE(SuiteInfoReader)
{
   TESTNGPPST_RCP checkpoint;
   ModuleLoader* loader;
   
   typedef const TESTNGPP_NS::SuiteInfoReader * const (*SuiteGetter)();

   SuiteGetter getSuite;

   SETUP()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
      loader = new DLModuleLoader();
      ASSERT_TRUE(0 != loader);

      ASSERT_THROWS_NOTHING(loader->load("libMySuite"));
      ASSERT_THROWS_NOTHING(getSuite = (SuiteGetter)loader->findSymbol("get_suite"));
      ASSERT_TRUE(getSuite != 0);
   }

   TEARDOWN()
   {
      loader->unload();
      delete loader;
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   TEST("$> get suite info")
   {
      const TESTNGPP_NS::SuiteInfoReader* const suite = getSuite();

      ASSERT_TRUE(0 != suite);

      ASSERT_EQ("MySuite", suite->getName());
      ASSERT_EQ(2, suite->numberOfModuleFiles());
   }
};
