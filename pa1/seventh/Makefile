all: seventh

test: seventh.c
	gcc -Wall -Werror -fsanitize=address seventh.c -o seventh.out
	
clean: 
	rm -rf seventh.out
