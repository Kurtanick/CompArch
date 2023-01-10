all: eighth

test: eighth.c
	gcc -g -Wall -Werror -fsanitize=address eighth.c -o eighth.out
	
clean: 
	rm -rf eighth.out
