#ifndef VV_OB_TABLE_INCLUDED
#define VV_OB_TABLE_INCLUDED

#include <OB_table/util.h>

#include <stddef.h>
#include <stdbool.h>

struct OB_table {
	size_t (*hash)(union param, const void *);
	bool (*comp)(union param, const void *, const void *);
	void **table;
	union param p;
	size_t n, cap;
};

/* Pass t with hash_fn and comp_fn set, zero other members */
struct OB_table *
OB_table_init(struct OB_table *t, size_t n_hint);

/* Find element */
void **
OB_table_find(struct OB_table *t, void *el);

/* Store the given element if not already exists, return locator of new element
 * or existing element if already exists */
void **
OB_table_insert_loc(struct OB_table *t, void *el);

/* Remove the given element (returns removed ptr - or NULL if none found) */
void *
OB_table_remove_loc(struct OB_table *t, void **loc);

/* Step through all locators (loc = previous locator or NULL to get first
 * locator) */
void **
OB_table_step(struct OB_table *t, void **loc);

/* Deallocates table */
struct OB_table *
OB_table_clear(struct OB_table *t);

/* Get number of stored entries in table */
size_t
OB_table_len(const struct OB_table *t);


/* Store the given element if not already exists, return element or NULL if
 * fail */
void *
OB_table_insert(struct OB_table *t, void *el);

/* Remove an element (returns removed ptr - or NULL if none found) */
void *
OB_table_remove(struct OB_table *t, void *el);

#endif /* VV_OB_TABLE_INCLUDED */
