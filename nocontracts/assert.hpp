#pragma once
#include <cstdio>
#include <cstdlib>
#include <csignal>


///////////////////////////////////////////////////////////////////
// Possible bits used to compose the behavior:
#ifndef NOCONTRACTS_LOG_FAILURE
# define NOCONTRACTS_LOG_FAILURE( expr__, message__ ) \
    fprintf(stderr, "Assertion Failed (%s:%i): %s - (%s is wrong)\n", __FILE__, __LINE__, message__, #expr__ );
#endif

#ifndef NOCONTRACTS_ABORT
# define NOCONTRACTS_ABORT() \
    std::abort();
#endif

#ifndef NOCONTRACTS_DEBUGBREAK
# ifdef _WIN32
#   define NOCONTRACTS_DEBUGBREAK() __debugbreak();
# else
#   define NOCONTRACTS_DEBUGBREAK() std::raise(SIGTRAP);
# endif
#endif

///////////////////////////////////////////////////////////////////
// Default behavior:

#define NOCONTRACTS_DEFAULT_CHECKS_ENABLED 1

#define NOCONTRACTS_DEFAULT_ON_FAILURE( expr__, message__ ) \
  NOCONTRACTS_LOG_FAILURE( expr__, message__ ); \
  NOCONTRACTS_DEBUGBREAK(); \
  NOCONTRACTS_ABORT();

///////////////////////////////////////////////////////////////////
// Apply Configuration:

// If not override, use the default behavior.
#ifndef NOCONTRACTS_CHECKS_ENABLED
# define NOCONTRACTS_CHECKS_ENABLED NOCONTRACTS_DEFAULT_CHECKS_ENABLED
#endif

#if NOCONTRACTS_CHECKS_ENABLED == 1 // Behavior when contracts are enabled.

# ifndef NOCONTRACTS_ON_FAILURE
#   define NOCONTRACTS_ON_FAILURE( expr__, message__ ) \
      NOCONTRACTS_DEFAULT_ON_FAILURE( expr__, message__ )
# endif

# ifndef NC_ASSERT
#   define NC_ASSERT( expr__, message__ ) \
      if(!( expr__ )) \
      { NOCONTRACTS_ON_FAILURE( expr__, message__ ); }
# endif

# define NC_ASSERT_TRUE( expr__ ) NC_ASSERT( expr__, #expr__ )
# define NC_ASSERT_FALSE( expr__ ) NC_ASSERT( !(expr__), "!("#expr__")" )

# else // Do nothing otherwise.
# define NOCONTRACTS_ON_FAILURE( expr__ )
# define NC_ASSERT( expr__, message__ )
# define NC_ASSERT_TRUE( expr__ )
# define NC_ASSERT_FALSE( expr__ )
#endif

