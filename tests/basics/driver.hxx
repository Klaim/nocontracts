#pragma once
#include <nocontracts/assert.hxx>

extern int abort_count;
void myabort();
void noassert();

#if NOCONTRACTS_CHECKS_ENABLED == 1
# define myassert(expr__) if(!(expr__)) throw "Assertion failed";
#else
# define myassert(expr__)
#endif

#define check_assertions() \
{ \
  NC_ASSERT(1 == 1, "basic assumptions with message"); \
  myassert(abort_count == 0); \
 \
  NC_ASSERT_TRUE(1 == 1); \
  myassert(abort_count == 0); \
 \
  NC_ASSERT_FALSE(1 != 1); \
  myassert(abort_count == 0); \
 \
  NC_ASSERT_TRUE(1 == 2); \
  myassert(abort_count == 1); \
 \
  NC_ASSERT_FALSE(2 == 2); \
  myassert(abort_count == 2); \
 \
  NC_ASSERT(1 != 1, "basic assumptions with message"); \
  myassert(abort_count == 3); \
}

