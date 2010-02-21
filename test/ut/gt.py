#!/usr/bin/python

import sys
import os.path

template = '''

#include <iostream>

#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/ResourceCheckPoint.h>

#include <testngpp/%s.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

FIXTURE(%s)
{

   TESTNGPPST_RCP checkpoint;

   SETUP()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
   }

   TEARDOWN()
   {
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

};
'''

def checkFileExistance(filename):
   if os.path.exists(filename):
      print >> sys.stderr, "file", filename, "exists, please make sure you wanna overwrite it"
      sys.exit(1)

def generate(name, filename):
   FILE = open(filename, "w")
   content = template % (name, name)
   FILE.writelines(content)
   FILE.close()

def generateTestFixture(name):
   filename = name + "_UT.h"
   checkFileExistance(filename)
   generate(name, filename)

def usage(prog):
   print "Usage:", prog, "class_name_under_test"

if __name__ == "__main__":
   if len(sys.argv) < 2:
      usage(sys.argv[0])
      sys.exit()

   generateTestFixture(sys.argv[1])
