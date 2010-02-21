
#include <testngpp/desc/TestCaseInfoReader.h>
#include <testngpp/desc/FixtureInfoReader.h>
#include <testngpp/desc/ModuleFileInfoReader.h>
#include <testngpp/desc/SuiteInfoReader.h>

static struct TESTCASE_TestFoo_case0
      : public TESTNGPP_NS::TestCaseInfoReader
{
   const std::string getName() const
   { return "case0"; }

   const std::string getFixtureName() const
   { return "TestFoo"; }

   const std::string getSuiteName() const
   { return "MySuite"; }

   const std::string getModuleFileName() const
   { return "/Users/darwin/testngpp/test/ut/TestFoo.so"; }

   const std::string getFullPath() const
   { return "/Users/darwin/testngpp/test/ut/TestFoo.h"; }

   const std::string getFileName() const
   { return "TestFoo.h"; }

   const unsigned int getLineNumber() const
   { return 30; }

   const TESTNGPP_NS::TestCaseInfoReader* getDependant() const
   { return 0; }

   const unsigned int numberOfTags() const
   { return 2; }

   // @tags="fast", "it"
   const char* const * const getTags() const
   {
      static const char* const tags[] = {"fast","it"};
      return tags;
   }

   // @timeout=10s
   const unsigned int timeout() const
   {  return 10000; }

} testcase_TestFoo_case0;

static struct TESTCASE_TestFoo_case1
      : public TESTNGPP_NS::TestCaseInfoReader
{
   const std::string getName() const
   { return "case1"; }

   const std::string getFixtureName() const
   { return "TestFoo"; }

   const std::string getSuiteName() const
   { return "MySuite"; }

   const std::string getModuleFileName() const
   { return "/Users/darwin/testngpp/test/ut/TestFoo.so"; }

   const std::string getFullPath() const
   { return "/Users/darwin/testngpp/test/ut/TestFoo.h"; }

   const std::string getFileName() const
   { return "TestFoo.h"; }

   const unsigned int getLineNumber() const
   { return 42; }

   const TESTNGPP_NS::TestCaseInfoReader* getDependant() const
   { return &testcase_TestFoo_case0; }

   const unsigned int numberOfTags() const
   { return 3; }

   // @tags="fast", "it", "mock"
   const char* const * const getTags() const
   {
      static const char* const tags[] = {"fast","it","mock"};
      return tags;
   }

   // @timeout=60s
   const unsigned int timeout() const
   {  return 60000; }

} testcase_TestFoo_case1;


//////////////////////////////////////////////////////////////
static const TESTNGPP_NS::TestCaseInfoReader * const 
g_TESTCASEARRAY_TestFoo[] =
{
  &testcase_TestFoo_case0,
  &testcase_TestFoo_case1,
  0
};

static struct FIXTURE_TestFoo
   : public TESTNGPP_NS::FixtureInfoReader
{
   const std::string getName() const
   { return "TestFoo"; }

   const std::string getSuiteName() const
   { return "MySuite"; }

   const std::string getModuleFileName() const
   { return "/Users/darwin/testngpp/test/ut/TestFoo.so"; }

   const std::string getFullPath() const
   { return "/Users/darwin/testngpp/test/ut/TestFoo.h"; }

   const std::string getFileName() const
   { return "TestFoo.h"; }

   const unsigned int getLine() const
   { return 15; }

   const unsigned int numberOfTestCases() const
   { return sizeof(g_TESTCASEARRAY_TestFoo)/sizeof(g_TESTCASEARRAY_TestFoo[0])-1; }

   const TESTNGPP_NS::TestCaseInfoReader* const * const
   getTestCases() const
   { return g_TESTCASEARRAY_TestFoo; }

} fixture_TestFoo;

static const TESTNGPP_NS::FixtureInfoReader* const g_TestFoo_fixtures[] =
{
   &fixture_TestFoo,
   0
};

static struct MODULEFILE_TestFoo 
   : public TESTNGPP_NS::ModuleFileInfoReader
{
   const std::string
   getSuiteName() const
   { return "MySuite"; }

   const std::string
   getName() const
   { return "/Users/darwin/testngpp/test/ut/TestFoo.so"; }

   const unsigned int
   numberOfFixtures() const
   { return sizeof(g_TestFoo_fixtures)/sizeof(g_TestFoo_fixtures[0])-1; }

   const TESTNGPP_NS::FixtureInfoReader* const * const
   getFixtures() const
   {
      return g_TestFoo_fixtures; 
   }

} module_TestFoo;

/////////////////////////////////////////////////////
static struct TESTCASE_TestBar_case0
      : public TESTNGPP_NS::TestCaseInfoReader
{
   const std::string getName() const
   { return "case0"; }

   const std::string getFixtureName() const
   { return "TestBar"; }

   const std::string getSuiteName() const
   { return "MySuite"; }

   const std::string getModuleFileName() const
   { return "/Users/darwin/testngpp/test/ut/TestBar.so"; }

   const std::string getFullPath() const
   { return "/Users/darwin/testngpp/test/ut/TestBar.h"; }

   const std::string getFileName() const
   { return "TestBar.h"; }

   const unsigned int getLineNumber() const
   { return 25; }

   const TESTNGPP_NS::TestCaseInfoReader* getDependant() const
   { return 0; }

   const unsigned int numberOfTags() const
   { return 2; }

   // @tags="fast", "it"
   const char* const * const getTags() const
   {
      static const char* const tags[] = {"fast","it"};
      return tags;
   }

   // @timeout=10s
   const unsigned int timeout() const
   {  return 10000; }

} testcase_TestBar_case0;

//////////////////////////////////////////////////////////////
static const TESTNGPP_NS::TestCaseInfoReader * const 
g_TESTCASEARRAY_TestBar[] =
{
  &testcase_TestBar_case0,
  0
};

static struct FIXTURE_TestBar
   : public TESTNGPP_NS::FixtureInfoReader
{
   const std::string getName() const
   { return "TestBar"; }

   const std::string getSuiteName() const
   { return "MySuite"; }

   const std::string getModuleFileName() const
   { return "/Users/darwin/testngpp/test/ut/TestBar.so"; }

   const std::string getFullPath() const
   { return "/Users/darwin/testngpp/test/ut/TestBar.h"; }

   const std::string getFileName() const
   { return "TestBar.h"; }

   const unsigned int getLine() const
   { return 9; }

   const unsigned int numberOfTestCases() const
   { return sizeof(g_TESTCASEARRAY_TestBar)/sizeof(g_TESTCASEARRAY_TestBar[0])-1; }

   const TESTNGPP_NS::TestCaseInfoReader* const * const
   getTestCases() const
   { return g_TESTCASEARRAY_TestBar; }

} fixture_TestBar;

static const TESTNGPP_NS::FixtureInfoReader* const g_TestBar_fixtures[] =
{
   &fixture_TestBar,
   0
};

static struct MODULEFILE_TestBar 
   : public TESTNGPP_NS::ModuleFileInfoReader
{
   const std::string
   getSuiteName() const
   { return "MySuite"; }

   const std::string
   getName() const
   { return "/Users/darwin/testngpp/test/ut/TestBar.so"; }

   const unsigned int
   numberOfFixtures() const
   { return sizeof(g_TestBar_fixtures)/sizeof(g_TestBar_fixtures[0])-1; }

   const TESTNGPP_NS::FixtureInfoReader* const * const
   getFixtures() const
   { return g_TestBar_fixtures; }

} module_TestBar;

/////////////////////////////////////////////////////////////////
static const TESTNGPP_NS::ModuleFileInfoReader* const g_MODULEFILE_MySuite[] =
{
  &module_TestFoo,
  &module_TestBar,
  0
};

//////////////////////////////////////
struct SUITE_MySuite 
   : public TESTNGPP_NS::SuiteInfoReader
{
   const std::string
   getName() const
   { return "MySuite"; }

   const unsigned int
   numberOfModuleFiles() const
   { return sizeof(g_MODULEFILE_MySuite)/sizeof(g_MODULEFILE_MySuite[0])-1; }
  
   virtual
   const TESTNGPP_NS::ModuleFileInfoReader* const * const
   getModuleFiles() const
   { return g_MODULEFILE_MySuite; }

}suite_MySuite;

///////////////////////////////////////////////
extern "C" DLL_EXPORT 
const TESTNGPP_NS::SuiteInfoReader * const
get_suite()
{
   return &suite_MySuite;
}
