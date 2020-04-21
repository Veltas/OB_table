#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <OB_table/table.h>
#include <OB_table/hash.h>
#include <OB_table/util.h>
#include <OB_table/assert.h>

static bool comp(union param p, const void *s1, const void *s2)
{
	UNUSED(p);
	return !strcmp(s1, s2);
}

#define N_STRS 400000

int main(void)
{
	struct OB_table tab = {
		.hash = FNV_1a_hash,
		.comp = comp
	};
	void **l;
	char *strs, *str;
	size_t i, j;

	OB_table_init(&tab, N_STRS);

	srand(0);

	printf("Loading array / calculating strings\n");
	strs = calloc(N_STRS * 10, 1);
	for (j = 0; j < N_STRS; j++) {
		str = &strs[10 * j];
		for (i = 0; i < 9; i++) {
			str[i] = rand() % 32 + 'a';
		}
	}
	printf("Storing in table\n");
	for (j = 0; j < N_STRS; j++) {
		str = &strs[10 * j];
		ASSERT(OB_table_insert(&tab, str) == str);
	}

	printf("Traversing table\n");
	i = 0;
	for (l = OB_table_step(&tab, NULL); l; l = OB_table_step(&tab, l)) i++;

	printf("Table length: %zu vs %zu traversed\n", OB_table_len(&tab), i);
	ASSERT(OB_table_len(&tab) == i);
	ASSERT(N_STRS == i);

	printf("Table capacity: %zu\n", tab.cap);

	printf("Removing all strings\n");
	for (j = 0; j < N_STRS; j++) {
		str = &strs[10 * j];
		ASSERT(OB_table_remove(&tab, str));
	}

	printf("Done\n");

	ASSERT(tab.n == 0);

	OB_table_clear(&tab);

	free(strs);

	return 0;
}
