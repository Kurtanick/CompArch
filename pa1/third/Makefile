all: third

test: third.c
	gcc -Wall -Werror -fsanitize=address third.c -o third.out
	
clean: 
	rm -rf third.out
