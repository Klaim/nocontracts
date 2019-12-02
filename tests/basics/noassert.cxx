#undef NOCONTRACTS_CHECKS_ENABLED
#define NOCONTRACTS_CHECKS_ENABLED 0 // Disable assertion checks

#include <nocontracts/assert.hxx>
#include "driver.hxx"

#if NOCONTRACTS_CHECKS_ENABLED == 1
#  error WTF
#endif


void noassert()
{
  // This should produce no code as contracts checks
  // are disabled. If not disabled, this file should produce
  // calls to abort() by default.
  check_assertions();
  printf(" -> None of the disabled assertions were checked- As expected.\n");
}

