CC ?= clang
CFLAGS = -std=gnu17

clex: 1-clex.c
	$(CC) $(CFLAGS) 1-clex.c -Wall -Wextra -fsanitize=address -g -o clex

eclosure: 2-eclosure.c
	$(CC) $(CFLAGS) 2-eclosure.c -Wall -Wextra -fsanitize=address -g -o eclosure

op: 3-op-precedence.c
	$(CC) $(CFLAGS) 3-op-precedence.c -Wall -Wextra -fsanitize=address -g -o op

recdec: 4-recdec.c
	$(CC) $(CFLAGS) 4-recdec.c -Wall -Wextra -fsanitize=address -g -o recdec

srparser: 5-sr-parser.c
	$(CC) $(CFLAGS) 5-sr-parser.c -Wall -Wextra -fsanitize=address -g -o srparser

constprop: 6-const-prop.c
	$(CC) $(CFLAGS) 6-const-prop.c -Wall -Wextra -fsanitize=address -g -o constprop

immediate: 7-immediate-code-generation.c
	$(CC) $(CFLAGS) 7-immediate-code-generation.c -Wall -Wextra -fsanitize=address -g -o immediate

threeaddr: 8-threeaddress.c
	$(CC) $(CFLAGS) 8-threeaddress.c -Wall -Wextra -fsanitize=address -g -o threeaddr

lexvowels: 9-vowels-and-consonants.l
	nix run nixpkgs#flex 9-vowels-and-consonants.l
	$(CC) lex.yy.c -o lexvowels
	rm lex.yy.c

lexc: 10-lexc.l
	nix run nixpkgs#flex 10-lexc.l
	$(CC) lex.yy.c -o lexc
	rm lex.yy.c

.PHONY: all

