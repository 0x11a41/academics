CC ?= clang
CFLAGS = -std=gnu17

clex: 1-clex.c
	$(CC) $(CFLAGS) 1-clex.c -Wall -Wextra -fsanitize=address -g -o clex

eclosure: 2-eclosure.c
	$(CC) $(CFLAGS) 2-eclosure.c -Wall -Wextra -fsanitize=address -g -o eclosure

op: 3-op-precedence.c
	$(CC) $(CFLAGS) 3-op-precedence.c -Wall -Wextra -fsanitize=address -g -o op

.PHONY: all clex

