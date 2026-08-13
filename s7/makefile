CC ?= clang
CFLAGS = -std=gnu17

clex: 1-clex.c
	$(CC) $(CFLAGS) 1-clex.c -Wall -Wextra -fsanitize=address -g -o clex


.PHONY: all clex

