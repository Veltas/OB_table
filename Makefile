.PHONY: all
all:

.PHONY: tests
tests:
	cd tests && $(MAKE) tests

.PHONY: clean
clean:
	cd tests && $(MAKE) clean
