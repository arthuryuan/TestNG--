#!/usr/bin/python

import sys
import os.path

template = '''

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

#include <mockcpp/mockcpp.hpp>

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
