// Overrides the abort mechanism to just call our counting function.
#define NOCONTRACTS_ABORT() myabort();
#define NOCONTRACTS_DEBUGBREAK() printf("--debugbreak--\n");

#include <nocontracts/version.hpp>
#include "driver.hpp"

int abort_count = 0;

void myabort()
{
  abort_count++;
}

int main ()
{
  printf("===== IGNORE ASSERTIONS LOGS - BEGIN ====\n");
  check_assertions();
  printf("===== IGNORE ASSERTIONS LOGS - END ====\n");

  abort_count = 0;
  noassert();

  printf(" -> All checks for assertions passed.\n");
}
