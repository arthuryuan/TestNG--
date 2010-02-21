

#include <iostream>

#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/ResourceCheckPoint.h>

#include <testngpp/desc/TestCaseInfoReader.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS


FIXTURE(TestCaseInfoReader)
{

   struct MyTestCaseInfo
      : public TESTNGPP_NS::TestCaseInfoReader
   {
      const std::string getName() const
      { return "my test case"; }

      const std::string getFixtureName() const
      { return "my fixture"; }

      const std::string getSuiteName() const
      { return "sample"; }

      const std::string getModuleFileName() const
      { return "libMyFixture.so"; }

      const std::string getFullPath() const
      { return "/Users/darwin/testngpp/samples/MyFixture.h"; }

      const std::string getFileName() const
      { return "MyFixture.h"; }

      const unsigned int getLineNumber() const
      { return 57; }

      const TestCaseInfoReader* getDependant() const
      { return 0; }

      const unsigned int numberOfTags() const
      { return 3; }

      const char* const * const getTags() const
      {
         static const char* const tags[] = {"ft","slow","empty"};
         return tags;
      }
      
      const unsigned int timeout() const
      {
         return 1200;
      }
   };

   TESTNGPPST_RCP checkpoint;

   SETUP()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
      INFO("SETUP");
   }

   TEARDOWN()
   {
      INFO("TEARDOWN");
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   TEST(Interface is defined correctly)
   {
      TestCaseInfoReader* testcase = new MyTestCaseInfo();

      std::string name = testcase->getName();
      ASSERT_EQ("my test case", name);
      unsigned int line = testcase->getLineNumber();
      ASSERT_EQ(57, line);

      INFO("Dependant has to be a const pointer");
      const TestCaseInfoReader* dependant = testcase->getDependant();
      ASSERT_TRUE(0 == dependant);

      ASSERT_EQ(3, testcase->numberOfTags());

      const char* const * tags = testcase->getTags();
      ASSERT_EQ(std::string("ft"), tags[0]);
      ASSERT_EQ(std::string("slow"), tags[1]);
      ASSERT_EQ(std::string("empty"), tags[2]);

      delete testcase;
   }
};
