all: fourth

test: fourth.c
	gcc -Wall -Werror -fsanitize=address fourth.c -o fourth.out
	
clean: 
	rm -rf fourth.out
