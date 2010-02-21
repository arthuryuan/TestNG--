

#include <iostream>

#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/ResourceCheckPoint.h>

#include <testngpp/desc/TestCaseInfoReader.h>
#include <testngpp/desc/FixtureInfoReader.h>
#include <testngpp/desc/ModuleFileInfoReader.h>
#include <testngpp/desc/SuiteInfoReader.h>
#include <testngpp/loaders/DLModuleLoader.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

FIXTURE(TestCaseInfoReader)
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
