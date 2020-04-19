#ifndef VV_ASSERT_INCLUDED
#define VV_ASSERT_INCLUDED

#include "util.h"
#include <stdio.h>
#include <stdlib.h>

/* Like assert but regardless of NDEBUG */
#define ASSERT(exp) ((exp) ? (void)0 : \
	(fprintf(stderr, __FILE__ ":%d: ASSERT failed (%s)\n", __LINE__, #exp), abort()) \
)

/* Like ASSERT but exit rather than abort on failure */
#define E_ASSERT(exp) ((exp) ? (void)0 : \
	(fprintf(stderr, __FILE__ ":%d: E_ASSERT failed (%s)\n", __LINE__, #exp), exit(EXIT_FAILURE)) \
)

/* Output a compiler error if the constant expression is not true */
#define STATIC_ASSERT(exp) _Static_assert(exp, #exp)

#endif /* VV_ASSERT_INCLUDED */
