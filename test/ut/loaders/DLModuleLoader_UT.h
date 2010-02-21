
#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/ResourceCheckPoint.h>

#include <testngpp/loaders/DLModuleLoader.h>
#include <testngpp/desc/SuiteInfoReader.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

FIXTURE(DLModuleLoader)
{

   TESTNGPPST_RCP checkpoint;

   ModuleLoader* loader;

   SETUP()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
      loader = new DLModuleLoader();
   }

   TEARDOWN()
   {
      delete loader;
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   // @test(id=load)
   TEST($-> load modules without suffix ".so")
   {
      ASSERT_THROWS_NOTHING(loader->load("libMySuite"));
   }

   TEST($-> load modules with suffix ".so")
   {
      ASSERT_THROWS_NOTHING(loader->load("libMySuite.so"));
   }

   TEST(non-existent module => throw TESTNGPP_NS::Error)
   {
      ASSERT_THROWS(loader->load("libNonExist"), TESTNGPP_NS::Error);
   }

   // @test(id=unload, depends=load)
   TEST($-> unload module)
   {
      ASSERT_THROWS_NOTHING(loader->unload());
   }

   TEST("$-> unload module, even if it hasn't been loaded")
   {
      ASSERT_THROWS_NOTHING(loader->unload());
   }

   // @test(depends=load)
   TEST($-> find exported symbol)
   {
      void * ptr;
      ASSERT_THROWS_NOTHING(ptr = loader->findSymbol("get_suite"));
      ASSERT_NE((void*)0, ptr);

      typedef const TESTNGPP_NS::SuiteInfoReader * const (*SuiteGetter)();
      SuiteGetter get_suite = (SuiteGetter)ptr;
      const TESTNGPP_NS::SuiteInfoReader* const suite = get_suite();
     
      ASSERT_TRUE(0 != suite);

      ASSERT_EQ("MySuite", suite->getName());
    
   }

   // @test(depends=load)
   TEST(non-existent symbol => throw TESTNGPP_NS::Error )
   {
      ASSERT_THROWS(loader->findSymbol("whatever"), TESTNGPP_NS::Error);
   }

   TEST(non-loaded module, find symbol => throw TESTNGPP_NS::Error)
   {
      ASSERT_THROWS(loader->findSymbol("get_suite"), TESTNGPP_NS::Error);
   }

   // @test(depends=unload)
   TEST("load->unload->findSymbol => throw TESTNGPP_NS::Error")
   {
      ASSERT_THROWS(loader->findSymbol("get_suite"), TESTNGPP_NS::Error);
   }
};
