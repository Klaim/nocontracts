

// No function defined here must be run, but the compilation must succeed.
// This is for testing that default generated code actually compiles.
// Do not add macros here, we must check the default config.


#include <nocontracts/assert.hxx>

void do_not_call()
{
    NC_ASSERT(false, "don't run this - must fail");
    NC_ASSERT(true, "don't run this - must fail");
}

