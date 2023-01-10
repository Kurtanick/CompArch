#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv){
	
	char* argString = argv[1];
	char* newString = NULL;
	char string[50];
	char letter;
	int maxSize, length;
	//char character;
	int i, num;
	
	//allocate space for new string
	maxSize = sizeof(argString);
	length = strlen(argString);
	
	newString = (char*) malloc(maxSize*sizeof(char));
	
	for(i=0;i<length;i++){
		num = 1;
		//string = NULL;
		letter = argString[i];
		//printf("letter: %c\n" , letter);
		while(letter == argString[i+1] && letter != '\0'){
			if(!isalpha(letter)){
				printf("error\n");
				exit(0);
			}
			num++;
			i++;
		}
		sprintf(string, "%c%d", letter, num);
		//printf("%s\n", string);
		strcat(newString, string);
	}
	
	//print string
	if(strlen(argString) <= strlen(newString))
		printf("%s\n", argString);
	else printf("%s\n", newString);
	
	return(0);
}
