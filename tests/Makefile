CC=cc
CFLAGS=-std=c11 -Wall -W -pedantic -O3
LD=$(CC)

TESTS = OB_table_test
FTESTS = assert_test e_assert_test

.PHONY: tests
tests: $(TESTS) $(FTESTS)
	for test in $(TESTS); do \
		./$$test || exit 1; \
		valgrind --leak-check=full --error-exitcode=1 ./$$test || exit 1; \
	done
	for test in $(FTESTS); do \
		! ./$$test || exit 1; \
	done
	@echo "=== All tests PASSED ==="

OB_table_test: ../OB_table.c ../hash.c OB_table_test.c
	$(LD) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(TESTS) $(FTESTS) *.core *.gmon
