#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	
	char* argString;
	int i, argsNum, length;
	
	argsNum = argc-1;
	//printf("argsNum: %d\n", argsNum);
	
	for(i=1;i<=argsNum;i++){
		argString = argv[i];
		//printf("argString: %s\n", argString);
		length = strlen(argString)-1;
		//printf("length: %d\n", length);
		printf("%c", argString[length]);
	}
	printf("\n");


	return(0);
}
