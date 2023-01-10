#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//PA4

//Function Defs:

void readFile(char* filename);//reads the traceFile and begins the other proccesses
void buildCache(); //uses the global variables to build the cash
unsigned long int getIndex(unsigned long int address);
unsigned long int getTag(unsigned long int address);
void read(unsigned long int address);
void write(unsigned long int address);
int cache(unsigned long int address); //search and Cache address
void prefetch(unsigned long int address);


typedef struct block{
	unsigned long int address;
	int valid; //0 by default
	unsigned long int timeStamp;
	//add LRU functionality
} block;


//Global Variables
int CacheSize;
int Assoc; //Blocks per Set
int Policy = 1; //1 if FIFO, 0 if LRU
int BlockSize;
int Sets; //Number of sets
int Prefetch = 0; //prefetch off/on
int Found = 0; //Is 1 if prefectch address is already in Cache
int Reads = 0, Writes = 0, Hits = 0, Misses = 0, Time = 0;
//masks
unsigned long int IndexMask;
unsigned long int NumIndex, NumOffset; //number of tag and offset bits
block **Cache;


unsigned long int getIndex(unsigned long int address){
	//get the index bits of a given address
	unsigned long int index;
	index = (address >> NumOffset)&IndexMask;
	index = index % Sets;
	//printf("Index = (%lu >> %lu) & %lu = %lu\n", address, NumOffset, IndexMask, index);
	return index;	
	
}

unsigned long int getTag(unsigned long int address){
	//get the tag bits of a given address
	unsigned long int tag = address;
	tag = tag >> (NumOffset + NumIndex);
	//printf("Address: %lu	Tag: %lu\n", address, tag);
	return tag;

}

void buildCache(){
	//build Cache
	int i, j;
	Cache = (block**)malloc(Sets * sizeof(block*));//allocate space in Cache for sets
	for(i=0; i<Sets;i++){//allocate space for blocks in sets
		Cache[i] = (block*) malloc(Assoc * sizeof(block));
	}
	//printf("Creating an %d by %d matrix...\n", Sets, Assoc);
	//set all valid bits = to 0
	for(i=0;i<Sets;i++){
		for(j=0;j<Assoc;j++){
			Cache[i][j].valid = 0;
		}
	}
}

void readFile(char* filename){
	//readFile
	char operation;
	unsigned int address;
	FILE* fp = fopen(filename, "r");
	
	while(!feof(fp)){
		fscanf(fp, "0x%*x: ");
		fscanf(fp, "%c ", &operation);
		fscanf(fp, "0x%x\n", &address);
		if(operation == '#') break;
		
		if(operation == 'R'){
			read(address);
		
		}
		else{
			write(address);
			
		}
		++Time;
		
		
		//printf("%c %x\n", operation, address);
	}
	
}

void read(unsigned long int address){
	//printf("Read");
	if (cache(address) == 1){//hit
	
		++Hits;
		//printf("1");
	}
	else{//miss
	
		++Misses;
		++Reads;
		//printf("2");
		if(Prefetch == 1) prefetch(address);
	}

}

void write(unsigned long int address){
	//printf("Write");
	if (cache(address) == 1){
		
		++Hits;
		++Writes;
		//printf("3");
	}
	else{
		
		++Misses;
		++Reads;
		++Writes;
		if(Prefetch == 1) prefetch(address);
		//printf("4");
	}

}

int cache(unsigned long int address){
	
	int hit = 0;
	
	
	int i;
	int j;
	unsigned long int index, tag;
	index = getIndex(address);
	//printf("Search index%lu\n", index);
	tag = getTag(address);
	block currBlock;

	block tempBlock;
	tempBlock.valid = 1;
	tempBlock.address = address;
	tempBlock.timeStamp = Time;
	
	//cashing agorithm
	for(i=0; i<Assoc; i++){//search for matches
		currBlock = Cache[index][i]; //already in cash (hit)
		if(currBlock.valid == 1 && getTag(currBlock.address) == tag){
			Found = 1;
			return hit = 1;
		}
	}
	
	//Write into Cache...
	for(i=0; i<Assoc; i++){ //search for 0 valid bits
		currBlock = Cache[index][i];
		if(currBlock.valid != 1){
			Cache[index][i] = tempBlock;
			return hit; //Block inserted into Cache
		}
	}
	
	j = 0;
	for(i=0; i<Assoc; i++){ //search for earliest timestamp
		currBlock = Cache[index][i];
		
		if (currBlock.timeStamp < Cache[index][j].timeStamp){
			j = i;
		}
	
	}
	Cache[index][j] = tempBlock; //insert into block w/ lowest timestamp 
	
	
	return hit;
}

void prefetch(unsigned long int address){
	Found = 0;
	unsigned long int preAddress = address + BlockSize;
	cache(preAddress);
	if(Found == 0) ++Reads;

}

int main(int argc, char** argv){
	
	//const char* delim = ":";
	char* assocString;
	char* policyString;
	char* traceFile;
	//int tagBits, indexBits, offsetBits;
	
	//Command Line Inputs
	CacheSize = atoi(argv[1]);
	assocString = argv[2];
	policyString = argv[3];
	BlockSize = atoi(argv[4]);
	traceFile = argv[5];
	
	//Parse Command Line Inputs
	
	if(policyString[0] != 'f')	
		Policy = 0;	//policy is LRU
		
	//Parse Associativity
	
	if(assocString[0] == 'a'){ //If Associative
		if(strlen(assocString) < 7){ //If full Associative
			//1 set for all blocks
			Sets = 1;
			Assoc = CacheSize/BlockSize;
			//printf("ASSOC: Assoc = %d.\n", Assoc);
			
		}
		else{ //if set Associative
			assocString = strtok(assocString, ":"); //n blocks per set
			assocString = strtok(NULL, ":");
			Assoc = atoi(assocString);
			Sets = CacheSize/(BlockSize*Assoc);
			//printf("SETS = %d/(%d*%d) = %d", CacheSize, BlockSize, Assoc, Sets);
		}
	}
	else{ //if Direct
		Assoc = 1; //1 block per set
		Sets = CacheSize/BlockSize;
		//printf("DIRECT	Sets = %d.\n", Sets);
	}
	
	//Compute Number of Bits for Idexes
	NumOffset = log(BlockSize)/log(2);
	NumIndex = (log(Sets)/log(2));
	//printf("NumOffset: %lu	NumIndex: %lu\n", NumOffset, NumIndex);
	//Compute Index Mask
	IndexMask = pow(2, NumIndex) - 1;
	//printf("IndexMask = %lu\n", IndexMask);

	
	buildCache();
	
	readFile(traceFile);
	
	printf("no-prefetch\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",Reads, Writes, Hits, Misses);

	
	buildCache();
	
	++Prefetch; Reads = 0; Writes = 0; Hits = 0; Misses = 0;
	readFile(traceFile);
	

	
	printf("with-prefetch\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",Reads, Writes, Hits, Misses);
	
	return 0;
}
