#pragma once
#include <cstdio>
#include <csignal>


///////////////////////////////////////////////////////////////////
// Possible bits used to compose the behavior:

// if not specified by the user but available, use std::print
#if not defined(NOCONTRACTS_USE_STD_PRINT) and not defined(NOCONTRACTS_USE_STD_FORMAT)
# if __cplusplus >= 202002L
#  include <version>
#  ifdef __cpp_lib_print
#   define NOCONTRACTS_USE_STD_PRINT 1
#  endif
# endif
#else
// The option is defined, but is it supported? If not we fail.
#  if defined(NOCONTRACTS_USE_STD_PRINT) and not defined(__cpp_lib_print)
#    error "std::print usage is requested but not available"
#  endif
#endif

// if not specified by the user but available and std::print is not already forced, use std::format
#if not defined(NOCONTRACTS_USE_STD_FORMAT) and not defined(NOCONTRACTS_USE_STD_PRINT)
# if __cplusplus >= 202002L
#  include <version>
#  ifdef __cpp_lib_format
#   define NOCONTRACTS_USE_STD_FORMAT 1
#  endif
# endif
// The option is defined, but is it supported? If not we fail.
#  if defined(NOCONTRACTS_USE_STD_FORMAT) and not defined(__cpp_lib_format)
#    error "std::format usage is requested but not available"
#  endif
#endif

// user specified to use neither std::format nor std::print, but C's formatting
#if defined(NOCONTRACTS_USE_CFORMAT) && NOCONTRACTS_USE_CFORMAT == 1
# ifdef NOCONTRACTS_USE_STD_FORMAT
#   undef NOCONTRACTS_USE_STD_FORMAT
# endif
# ifdef NOCONTRACTS_USE_STD_PRINT
#   undef NOCONTRACTS_USE_STD_PRINT
# endif
#endif

#ifndef NOCONTRACTS_LOG_FAILURE
# if defined(NOCONTRACTS_USE_STD_PRINT) && NOCONTRACTS_USE_STD_PRINT == 1
#   include <print>
#   include <cstdio>
#   define NOCONTRACTS_LOG_FAILURE( expr__, message__ ) \
      ::std::print(stderr, "Assertion Failed ({}:{}): {} - ({} is wrong)\n", __FILE__, __LINE__, message__, #expr__ )
# elif defined(NOCONTRACTS_USE_STD_FORMAT) && NOCONTRACTS_USE_STD_FORMAT == 1
#   include <format>
#   include <cstdio>
#   define NOCONTRACTS_LOG_FAILURE( expr__, message__ ) \
      fprintf(stderr, ::std::format("Assertion Failed ({}:{}): {} - ({} is wrong)\n", __FILE__, __LINE__, message__, #expr__ ).c_str())
# else
#   include <cstdlib>
#   include <cstdio>
#   define NOCONTRACTS_LOG_FAILURE( expr__, message__ ) \
      ::fprintf(stderr, "Assertion Failed (%s:%i): %s - (%s is wrong)\n", __FILE__, __LINE__, message__, #expr__ )
# endif
#endif

#ifndef NOCONTRACTS_ABORT
# define NOCONTRACTS_ABORT() \
    std::abort()
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

