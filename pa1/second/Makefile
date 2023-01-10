all: second

test: second.c
	gcc -Wall -Werror -fsanitize=address second.c -o second.out
	
clean: 
	rm -rf second.out
