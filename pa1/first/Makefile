all: first

test: first.c
	gcc -g -Wall -Werror -fsanitize=address first.c -o first.out
	
clean: 
	rm -rf first.out
