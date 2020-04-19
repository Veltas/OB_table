#ifndef VV_UTIL_INCLUDED
#define VV_UTIL_INCLUDED

#include <stddef.h>

#define STRING_MAC(exp) #exp
#define STRING_MAC2(exp) STRING_MAC(exp)

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define UNUSED(name) ((void)(name))

union param {
	void   *p;
	int    i;
	size_t n;
};

#endif /* VV_UTIL_INCLUDED */
