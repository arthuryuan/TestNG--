/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

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

#ifndef __TESTNGPPST_ASSERTER_H
#define __TESTNGPPST_ASSERTER_H

#include <sstream>
#include <string.h>

#include <testngppst/testngppst.h>
#include <testngppst/utils/Formatter.h>


#if defined(__GNUC__)
#define TESTNGPPST_TYPEOF(expr) typeof(expr)
#else
#include <boost/typeof/typeof.hpp>
#define TESTNGPPST_TYPEOF(expr) BOOST_TYPEOF(expr)
#endif

TESTNGPPST_NS_START

//////////////////////////////////////////////////////////////////
#define __TESTNGPPST_REPORT_FAILURE(what) \
      reportFailure(__FILE__, __LINE__, what)

//////////////////////////////////////////////////////////////////
#define ASSERT_TRUE(expr) do { \
   if(!(expr)) {\
      __TESTNGPPST_REPORT_FAILURE("expected (" #expr ") being TRUE, but it's actually FALSE"); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_FALSE(expr) do { \
   if(expr) {\
      __TESTNGPPST_REPORT_FAILURE("expected (" #expr ") being FALSE, but it's actually TRUE"); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __TESTNGPPST_MAKE_STR(expr) " " #expr " "

//////////////////////////////////////////////////////////////////
#define __TESTNGPPST_ASSERT_EQUALITY(expected, expected_equality, wrong_equality, value) do {\
   TESTNGPPST_TYPEOF(value) __testngppst_expected = (expected); \
   TESTNGPPST_TYPEOF(value) __testngppst_value = (value); \
   if(__testngppst_expected wrong_equality __testngppst_value) { \
      std::stringstream ss; \
      ss << "expected (" #expected __TESTNGPPST_MAKE_STR(expected_equality) #value "), found (" \
         << TESTNGPPST_NS::toTypeAndValueString(__testngppst_expected) \
         << __TESTNGPPST_MAKE_STR(wrong_equality) \
         << TESTNGPPST_NS::toTypeAndValueString(__testngppst_value) \
         << ")"; \
      __TESTNGPPST_REPORT_FAILURE(ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_EQ(expected, value) \
   __TESTNGPPST_ASSERT_EQUALITY(expected, ==, !=, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_NE(expected, value) \
   __TESTNGPPST_ASSERT_EQUALITY(expected, !=, ==, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROWS(expr, except) do { \
   bool testngppst_caught_exception = false; \
   try { \
      expr; \
   }catch(except&){ \
      testngppst_caught_exception = true; \
   } catch(...) {\
	  __TESTNGPPST_REPORT_FAILURE( \
         "expected " #expr " will throw an exception of type " #except ", but actually raised a different kind of exception."); \
   } \
   if(!testngppst_caught_exception) { \
      __TESTNGPPST_REPORT_FAILURE( \
         "expected " #expr " will throw an exception of type " #except ", but actually not."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROWS_ANYTHING(expr) do { \
   bool __testngppst_caught_exception = false; \
   try { \
      expr; \
   }catch(...){ \
      __testngppst_caught_exception = true; \
   } \
   if(!__testngppst_caught_exception) { \
      __TESTNGPPST_REPORT_FAILURE ( \
         "expected " #expr " will throw an exception of any type, but actually not."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROWS_NOTHING(expr) do { \
   try { \
      expr; \
   }catch(...){ \
      __TESTNGPPST_REPORT_FAILURE ( \
          "expected " #expr " will not throw any exceptions, but it actually did."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROWS_EQUALS(expr, except, expected, value) do { \
   try { \
      expr; \
      __TESTNGPPST_REPORT_FAILURE ( \
          "expected " #expr " will throw an exception of type " #except ", but actually not."); \
   }catch(except){ \
      ASSERT_EQ(expected, value); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_SAME_DATA(addr1, addr2, size) do { \
   void* p1 = reinterpret_cast<void*>(addr1); \
   void* p2 = reinterpret_cast<void*>(addr2); \
   if(::memcmp((void*)p1, (void*)p2, size)) \
   { \
      std::stringstream ss; \
      ss << "expected (" #addr1 ", " #addr2 ") have same data, found (" \
         << TESTNGPPST_NS::toBufferString(p1, size) \
         << ", " \
         << TESTNGPPST_NS::toBufferString(p2, size) \
         << ")"; \
      __TESTNGPPST_REPORT_FAILURE(ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __TESTNGPPST_ABS(value) ((value) > 0?(value):-(value))
//////////////////////////////////////////////////////////////////
#define ASSERT_DELTA(x, y, d) do { \
   TESTNGPPST_TYPEOF(x) value1 = x; \
   TESTNGPPST_TYPEOF(y) value2 = y; \
   TESTNGPPST_TYPEOF(d) delta  = __TESTNGPPST_ABS(d); \
   TESTNGPPST_TYPEOF(d) actual_delta = __TESTNGPPST_ABS(value1 - value2); \
   if(actual_delta > delta) \
   { \
      std::stringstream ss; \
      ss << "expected the delta of (" #x ", " #y ") <= (" \
         << TESTNGPPST_NS::toTypeAndValueString(delta) \
         << "), actual delta: (" \
         << TESTNGPPST_NS::toTypeAndValueString(actual_delta) \
         << ")"; \
      __TESTNGPPST_REPORT_FAILURE(ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define FAIL(msg) do { \
    __TESTNGPPST_REPORT_FAILURE(msg); \
}while(0)

//////////////////////////////////////////////////////////////////
#define WARN(msg) do { \
    reportWarning(__FILE__, __LINE__, msg); \
}while(0)

//////////////////////////////////////////////////////////////////
#define INFO(msg) do { \
    reportInfo(__FILE__, __LINE__, msg); \
}while(0)

//////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

