#include <OB_table/hash.h>

#include <limits.h>
#include <stdint.h>

#ifndef SIZE_MAX
#warning "SIZE_MAX not defined, assuming ULONG_MAX"
#define SIZE_MAX ULONG_MAX
#endif

#if SIZE_MAX >= 0xFFFFFFFFFFFFFFFF
#define FNV_1a_offset_basis 14695981039346656037u
#define FNV_1a_prime        0x100000001b3
#else
#define FNV_1a_offset_basis 2166136261u
#define FNV_1a_prime        0x1000193
#endif

#if SIZE_MAX >= 0xFFFFFFFF
typedef size_t FNV_1a_calc_t;
#else
typedef uint_least32_t FNV_1a_calc_t;
#endif

size_t FNV_1a_hash(union param p, const void *s)
{
	FNV_1a_calc_t result = FNV_1a_offset_basis;
	const char *str = s;
	size_t i;

	UNUSED(p);

	for (i = 0; str[i]; i++) {
		result ^= str[i];
		result *= FNV_1a_prime;
	}
#if SIZE_MAX < 0xFFFFFFFF
	result = (result >> 16) ^ (result & 0xFFFF);
#endif

	return result;
}
