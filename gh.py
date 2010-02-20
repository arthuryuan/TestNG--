#!/usr/bin/python

import sys

copyright='''
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
'''

hdr_template = '''
#ifndef __TESTNGPP_%s_H__
#define __TESTNGPP_%s_H__

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct %sImpl;

//////////////////////////////////////
struct %s %s
{
   %s();
   ~%s();

private:
   %sImpl* This;
};

//////////////////////////////////////

TESTNGPP_NS_END

#endif 

'''

src_template = '''

#include <testngpp/%s.h>

TESTNGPP_NS_START

//////////////////////////////////////
struct %sImpl
{
   %sImpl();
   ~%sImpl();
};

//////////////////////////////////////
%sImpl::
%sImpl()
{
}

//////////////////////////////////////
%sImpl::
~%sImpl()
{
}

//////////////////////////////////////
%s::
%s()
   : This(new %sImpl())
{
}

//////////////////////////////////////
%s::
~%s()
{
   delete This;
}

//////////////////////////////////////

TESTNGPP_NS_END

'''

def seperate(name):
  if len(name) == 0:
    return []

  word = [name[0]]

  for i in range(1, len(name)):
    if not name[i].isupper():
       word += name[i]
    else:
       return [word] + seperate(name[i:])

  return [word]

def get_inheritance(parents):
   result = ""
   if len(parents) > 0:
      result = result + "\n      : public " + parents[0]

   for i in range(1, len(parents)):
      result = result + "\n      , public " + parents[i]

   return result

def get_header_content(names):
   name = names[0]
   parents = get_inheritance(names[1:])
   words = ["".join(word) for word in seperate(name)]
   macro = "_".join(words).upper()
   return hdr_template % (macro, macro, name, name, parents, name, name, name)

def generate_header(names):
   file_name = names[0] + ".h"
   file = open(file_name, mode="w")
   file.write(copyright)
   file.write(get_header_content(names))
   file.close()
   
def get_src_content(name):
   return src_template % (name, name, name, name, name, name, \
            name, name, name, name, name, name, name)

def generate_src(names):
   file_name = names[0] + ".cpp"
   file = open(file_name, mode="w")
   file.write(copyright)
   file.write(get_src_content(names[0]))
   file.close()

def generate(names):
   generate_header(names)
   generate_src(names)

if __name__ == '__main__':
   if len(sys.argv) < 2:
     sys.exit(0)

   generate(sys.argv[1:])
