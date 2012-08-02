/*
 *
 * Copyright (c) 2009
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <boost/regex.hpp>
#include <boost/test/test_tools.hpp>
#include "IwTest.h"

#undef BOOST_STATIC_ASSERT
#define BOOST_STATIC_ASSERT

#undef BOOST_TEST
#define BOOST_TEST(COND) IW_TEST_ASSERT_ACTION(COND, 1 == 1, (""))

#undef BOOST_CHECK
#define BOOST_CHECK(COND) BOOST_TEST(COND)

#undef BOOST_ERROR
#define BOOST_ERROR(MSG) IwTestError(MSG)

#undef BOOST_TEST_EQ
#define BOOST_TEST_EQ(VAL1, VAL2) IW_TEST_ASSERT_EQ(VAL1, VAL2)

#undef BOOST_TEST_NE
#define BOOST_TEST_NE(VAL1, VAL2) IW_TEST_ASSERT_NOTEQ(VAL1, VAL2)

#undef BOOST_CHECK_EQUAL
#define BOOST_CHECK_EQUAL(VAL1, VAL2) IW_TEST_ASSERT_COMPARATION_IMPL(VAL1, == , VAL2, 1==1)

#undef BOOST_CHECK_THROW
#define BOOST_CHECK_THROW(S, E)                                                  \
    try {                                                                        \
        S;                                                                       \
        BOOST_ERROR("Exception was expected but not thrown - " #S);              \
    }                                                                            \
    catch( E const& ex ) {                                                       \
        ::boost::unit_test::ut_detail::ignore_unused_variable_warning( ex );     \
    }

#undef BOOST_CHECK_CLOSE_FRACTION
#define BOOST_CHECK_CLOSE_FRACTION( L, R, T )             \
    BOOST_CHECK(::boost::test_tools::check_is_close(L, R, \
        ::boost::test_tools::fraction_tolerance(T)))


/*<boost.py:auto_insert>*/ namespace named_subexpressions_test_ns {/*<boost.py:auto_insert>*/


#ifdef BOOST_INTEL
#pragma warning(disable:1418 981 983 383)
#endif

template <class charT>
void test_named_subexpressions(charT)
{
   //
   // Really this is just a test that the overloaded access functions work correctly:
   //
   static const charT e[] = 
   {
      '(', '?', '\'', 'o', 'n', 'e', '\'', 'a', '+', ')', '(', '?', '<', 't', 'w', 'o', '>', 'b', '+', ')', '\0'
   };
   static const charT t[] = 
   {
      'm', 'm', 'a', 'a', 'a', 'b', 'b', 'n', 'n', '\0'
   };
   static const charT one[] = 
   {
      'o', 'n', 'e', '\0'
   };
   static const charT two[] = 
   {
      't', 'w', 'o', '\0'
   };
   static const std::basic_string<charT> s_one(one);
   static const std::basic_string<charT> s_two(two);
   static const charT result1[] = { 'a', 'a', 'a', '\0' };
   static const charT result2[] = { 'b', 'b', '\0' };
   static const std::basic_string<charT> s_result1(result1);
   static const std::basic_string<charT> s_result2(result2);

   static const char* c_one = "one";
   static const char* c_two = "two";
   static const std::string cs_one(c_one);
   static const std::string cs_two(c_two);

   boost::basic_regex<charT> expression(e);
   boost::match_results<const charT*> what;
   if(regex_search(t, what, expression))
   {
      BOOST_CHECK(what.length(1) == 3);
      BOOST_CHECK(what.length(one) == 3);
      BOOST_CHECK(what.length(s_one) == 3);
      BOOST_CHECK(what.length(c_one) == 3);
      BOOST_CHECK(what.length(cs_one) == 3);
      BOOST_CHECK(what.position(1) == 2);
      BOOST_CHECK(what.position(one) == 2);
      BOOST_CHECK(what.position(s_one) == 2);
      BOOST_CHECK(what.position(c_one) == 2);
      BOOST_CHECK(what.position(cs_one) == 2);
      BOOST_CHECK(what.str(1) == s_result1);
      BOOST_CHECK(what.str(one) == s_result1);
      BOOST_CHECK(what.str(s_one) == s_result1);
      BOOST_CHECK(what.str(c_one) == s_result1);
      BOOST_CHECK(what.str(cs_one) == s_result1);
      BOOST_CHECK(what[1] == s_result1);
      BOOST_CHECK(what[one] == s_result1);
      BOOST_CHECK(what[s_one] == s_result1);
      BOOST_CHECK(what[c_one] == s_result1);
      BOOST_CHECK(what[cs_one] == s_result1);

      BOOST_CHECK(what.length(2) == 2);
      BOOST_CHECK(what.length(two) == 2);
      BOOST_CHECK(what.length(s_two) == 2);
      BOOST_CHECK(what.length(c_two) == 2);
      BOOST_CHECK(what.length(cs_two) == 2);
      BOOST_CHECK(what.position(2) == 5);
      BOOST_CHECK(what.position(two) == 5);
      BOOST_CHECK(what.position(s_two) == 5);
      BOOST_CHECK(what.position(c_two) == 5);
      BOOST_CHECK(what.position(cs_two) == 5);
      BOOST_CHECK(what.str(2) == s_result2);
      BOOST_CHECK(what.str(two) == s_result2);
      BOOST_CHECK(what.str(s_two) == s_result2);
      BOOST_CHECK(what.str(c_two) == s_result2);
      BOOST_CHECK(what.str(cs_two) == s_result2);
      BOOST_CHECK(what[2] == s_result2);
      BOOST_CHECK(what[two] == s_result2);
      BOOST_CHECK(what[s_two] == s_result2);
      BOOST_CHECK(what[c_two] == s_result2);
      BOOST_CHECK(what[cs_two] == s_result2);
   }
   else
   {
      BOOST_ERROR("Expected match not found");
   }
}

int test_main( int , char* [] )
{
   test_named_subexpressions(char(0));
   test_named_subexpressions(wchar_t(0));
   return 0;
}

//#include <boost/test/included/test_exec_monitor.hpp>

/*<boost.py:auto_insert>*/}/*<boost.py:auto_insert>*/

IW_TEST(named_subexpressions_test)
{
    named_subexpressions_test_ns::test_main(0, NULL);
    return S3E_TRUE;
}