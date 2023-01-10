#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){

	FILE* fp = NULL;
	char* filename;
	int size, i, temp;
	int* array;
	
	if(argc < 2){
		printf("error\n");
		exit(0);
	}
	
	filename = argv[1];
	fp = fopen(filename, "r");
	
	fscanf(fp, "%d\n" , &size); //scan in the size of array
	
	array = (int*)malloc(size * sizeof(int));
	
	//populate array
	for(i=0; i<size; i++){
		fscanf(fp, "%d\t", &array[i]);
	}
	
	//sort array
	i=0;
	while(i<size-1){
		if(array[i] > array[i+1]){
			temp = array[i];
			array[i] = array[i+1];
			array[i+1] = temp;
			i=0;
		}
		else ++i;
	}
	
	
	//print out array
	for(i=0; i<size; i++){
		printf("%d\t", array[i]);
	}
	printf("\n");
	free(array);
	
	return 0;
	
}
