#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

//pa5



//typedefs
typedef struct Variable{
	int value;
	char name[50];
	//int type; // 0 = static, 1 = in, 2 = out, 3 = temp
	int id; 
}Variable;

typedef struct Gate{
	int op;
	int length;
	int var[20];
	
} Gate;

//Function Defs
void readFile(char* fileName);
//long* greyCode(long caseNum); //generates greycode
int circuitSelect(char* op); //turns op string into int
void NOT(Gate gate);
void AND(Gate gate);
void OR(Gate gate);
void NAND(Gate gate);
void NOR(Gate gate);
void XOR(Gate gate);
void caseCheck(char* name);
int searchID(char* name);
int getValue(int id);
void setValue(int id, int value);
//void printArray(Variable* array, int length);


//Global Variables
int N, Nout; //number of inputs
int NumGates = 0; //number of gates
int NumTemp = 0; //number of temp variables
int IdCount = 0;
Variable* InputArray, *OutputArray;
Variable TempArray[50];
Gate CircuitArray[50];


void caseCheck(char* name){//if variable is unique temp, adds to array;
	int i;
	char ch = name[0];
	if(ch <= 'Z') return;
	if(NumTemp == 0){
		strcpy(TempArray[0].name, name);
		TempArray[0].id = IdCount;
		++IdCount;
	}
	else{
		for(i=0;i<NumTemp;i++){//check for duplicate
			if(strcmp(TempArray[i].name,name) == 0){ //dup
				return;
			}
		}
		strcpy(TempArray[i].name, name);
		TempArray[i].id = IdCount;
		++IdCount;
	}
	++NumTemp;
	
}
int circuitSelect(char* op){
	//printf("OP: %s ", op);
	++NumGates;
	if(strcmp(op, "NOT") == 0) return 1;
	if(strcmp(op, "AND") == 0) return 2;
	if(strcmp(op, "OR") == 0) return 3;
	if(strcmp(op, "NAND") == 0) return 4;
	if(strcmp(op, "NOR") == 0) return 5;
	if(strcmp(op, "XOR") == 0) return 6;
	if(strcmp(op, "DECODER") == 0) return 7;
	if(strcmp(op, "MULTIPLEXER") == 0) return 8;
	
	printf("circuitSelect ERROR\n");
	return 0;

}

void NOT(Gate gate){
	int IN1 = getValue(gate.var[0]);
	IN1 = ~IN1;
	setValue(gate.var[1], IN1);
	//printf("NOT\n");
}

void AND(Gate gate){
	int IN1 = getValue(gate.var[0]);
	int IN2 = getValue(gate.var[1]);
	int OUT1 = IN1 & IN2;
	setValue(gate.var[2], OUT1);
	//printf("AND\n");
}

void OR(Gate gate){
	int IN1 = getValue(gate.var[0]);
	int IN2 = getValue(gate.var[1]);
	int OUT1 = IN1 | IN2;
	//printf("%d OR %d = %d\n", IN1, IN2, OUT1);  
	setValue(gate.var[2], OUT1);
	//printf("OR\n");
}

void NAND(Gate gate){
	int IN1 = getValue(gate.var[0]);
	int IN2 = getValue(gate.var[1]);
	int OUT1 = IN1 & IN2;
	OUT1 = ~OUT1;
	setValue(gate.var[2], OUT1);
	//printf("NAND\n");
}

void NOR(Gate gate){
	int IN1 = getValue(gate.var[0]);
	int IN2 = getValue(gate.var[1]);
	int OUT1 = IN1 | IN2;
	OUT1 = ~OUT1;
	setValue(gate.var[2], OUT1);
	//printf("NOR\n");
}

void XOR(Gate gate){
	int IN1 = getValue(gate.var[0]);
	int IN2 = getValue(gate.var[1]);
	int OUT1 = IN1 ^ IN2;
	setValue(gate.var[2], OUT1);
	//printf("XOR\n");
}

int getValue(int id){ //takes the id of a variable and returns it's value
	int i;
	for(i=0;i<N;i++){//search inputs array
		if(InputArray[i].id == id) return InputArray[i].value; 
	}
	for(i=0;i<Nout;i++){//search inputs array
		if(OutputArray[i].id == id) return OutputArray[i].value; 
	}
	for(i=0;i<NumTemp;i++){//search inputs array
		if(TempArray[i].id == id) return TempArray[i].value; 
	}
	printf("get ID not found\n");
	return(-1);
}

void setValue(int id, int value){
	int i;
	for(i=0;i<N;i++){//search inputs array
		if(InputArray[i].id == id){
			printf("WRONGO\n");
			return;
		}	
	}
	for(i=0;i<Nout;i++){//search inputs array
		if(OutputArray[i].id == id){
			OutputArray[i].value = value;
			return;
		} 
	}
	for(i=0;i<NumTemp;i++){//search inputs array
		if(TempArray[i].id == id){
			TempArray[i].value = value;
			return; 
		}
	}
	printf("set ID not found\n");
	return;

}

void loadCircuit(int c, char* name, int length){
	int id;
	id = searchID(name);
	CircuitArray[c].var[length] = id;

}
int searchID(char* name){//returns id of variable with given name
	int i;
	for(i=0;i<N;i++){//search inputs array
		if(strcmp(InputArray[i].name,name)== 0) return InputArray[i].id; 
	}
	for(i=0;i<Nout;i++){//search inputs array
		if(strcmp(OutputArray[i].name,name)== 0) return OutputArray[i].id; 
	}
	for(i=0;i<NumTemp;i++){//search inputs array
		if(strcmp(TempArray[i].name,name)== 0) return TempArray[i].id; 
	}
	printf("ID not found");
	return(-1);
}

void readFile(char* fileName){
	char op[12] = "";
	char name[50] = "";
	char IN1[50] = "", OUT1[50] = "";
	int x;//varible to fix NOT case ;}
	int num, i, opCode, length = 0, c = 0; // j = 0, k;
	//int length = 3;
	FILE* fp = NULL;
	
	printf("Read file (%s)\n", fileName);
	fp = fopen(fileName, "r");
	
	
	//Scan in inputvars
	
	fscanf(fp, "%*s ");
	fscanf(fp, "%d ", &num); //scan in num of inputs
	N = num;
	 
	//printf("INPUTS: ");
	//printf("%d ", num);
	InputArray = (Variable*)malloc(num * sizeof(Variable));
	for(i=0;i<num;i++){
		
		fscanf(fp, "%s ", name);
		//printf("%s ", name);
		strcpy(InputArray[i].name , name);
		InputArray[i].id = IdCount;
		++IdCount;
	}
	fscanf(fp,"\n");
	
	//printf("\n");
	
	//Scan in outputvars
	fscanf(fp, "%*s ");
	fscanf(fp, "%d ", &num);
	//printf("OUTPUTS: %d ", num);
	Nout = num;
	OutputArray = (Variable*)malloc(num * sizeof(Variable));
	for(i=0;i<num;i++){
		
		fscanf(fp, "%s ", name);
		//printf("%s ", name);
		strcpy(OutputArray[i].name , name);
		OutputArray[i].id = IdCount;
		++IdCount;
	}
	fscanf(fp,"\n");
	//printf("\n");

	//Fill TempArray
	//Build Circuit
	
	
	//first run through
	while(!feof(fp)){
		fscanf(fp, "%s " , op);
		//printf("%s ", op);
		opCode = circuitSelect(op);
		CircuitArray[c].op = opCode;
		
		
		
		if(opCode < 7){ //not mult or dec
			if(opCode == 1) x = 1;
			else x = 2;
			for(i=0;i<x;i++){//Scan Inputs
			
				fscanf(fp, "%s ", IN1);
				//printf("%s ", IN1);
				caseCheck(IN1);
				loadCircuit(c, IN1, length);
				++length;
			}
			fscanf(fp, "%s ", OUT1);
			//printf("%s", OUT1);
			caseCheck(OUT1);
			loadCircuit(c, OUT1, length);
			++length;
		}		
		
		else if(opCode == 7){ //dec
			fscanf(fp, "%d ", &num);
			for(i=0;i<num;i++){ //scan in inputs
				fscanf(fp, "%s ", IN1);
				//printf("%s ", IN1);
				caseCheck(IN1);
				loadCircuit(c, IN1, length);
				++length;
			}
			num = pow(2, num); //num = 2^num (num outputs)
			for(i=0;i<num;i++){ //scan in outputs
				fscanf(fp, "%s ", OUT1);
				//printf("%s ", OUT1);
				caseCheck(OUT1);
				loadCircuit(c, OUT1, length);
				++length;
			}
		}
		
		else{ //mult
			fscanf(fp, "%d ", &num);//read num inputs
			//printf("%d ", num);
			for(i=0;i<num;i++){//read inputs
				fscanf(fp, "%s ", IN1);
				//printf("%s ", IN1);
				caseCheck(IN1);
				loadCircuit(c, IN1, length);
				++length;
			}
			num = (log(num)/log(2)); // num = log base 2 (n)
			for(i=0;i<num;i++){//scan selectors
				fscanf(fp, "%s ", IN1);
				//printf("%s ", IN1);
				caseCheck(IN1);
				loadCircuit(c, IN1, length);
				++length;
			}
			fscanf(fp, "%s ", OUT1);
			//printf("%s ", OUT1);
			caseCheck(OUT1);
			loadCircuit(c, OUT1, length);
			++length;
		}
		

		fscanf(fp, "\n");
		//printf("\n");
		CircuitArray[c].length = length;
		++c;
		length = 0;
	}
	//printf("OPERATIONS: %d	TEMPS: %d\n", NumGates, NumTemp);
		
}

void printArray(Variable* array, int length){
	int i;
	//printf("ARRAY: ");
	for(i=0;i<length;i++){
		printf("%d ", array[i].value);
	}
	printf("\n");
}

void printOut(){
	int i;
	//printf("ARRAY: ");
	for(i=0;i<N;i++){
		printf("%d ", InputArray[i].value);
	}
	for(i=0;i<Nout;i++){
		printf("%d ", OutputArray[i].value);
	}
	printf("\n");
}

void runCircuit(){
	int i;
	int opCode;
	//int length;
	//int* array;
	for(i=0;i<NumGates;i++){
		opCode = CircuitArray[i].op;
		//length = CircuitArray[i].length;
		//array = CircuitArray[i].var;
		
		switch(opCode){
			case 1: //NOT
				NOT(CircuitArray[i]);
				break;
			case 2: //AND
				AND(CircuitArray[i]);
				break;
			case 3: //OR
				OR(CircuitArray[i]);
				break;
			case 4: //NAND
				NAND(CircuitArray[i]);
				break;
			case 5: //NOR
				NOR(CircuitArray[i]);
				break;
			case 6: //XOR
				XOR(CircuitArray[i]);
				break;
			case 7: //DECODER
				printf("No Decoder Yet");
				break;	
			case 8: //MULTIPLEXOR
				printf("No Multiplexor Yet");
				break;
			default:
				printf("Invalid Operation");
		
		}
		
	}
	//printOut();
	
}

void greyCode(int x){//fills InputArray with N bits of greycode depending on test case number
	int i, j;
	//int mask = 0xfffffffe;
	int bit;
	int greyCode = (x ^ (x>>1));
	
	
	for(i=0,j=(N-1);i<N;i++,j--){
		bit = greyCode % 2;
		InputArray[j].value = bit;
		greyCode = greyCode >> 1;
		
	}
	
	//printf("%d ", greyCode);
}

int main(int argc, char** argv){
	int i;
	char* fileName = argv[1];
	readFile(fileName);
	int numCases = pow(2, N);
	//greyCode();
	//printArray(InputArray, N);
	//printArray(OutputArray, Nout);
	//printArray(TempArray, NumTemp);
	//printf("NumTemp: %d\n", NumTemp);
	/*
	printf("CIRCUIT ARRAY\n");
	for(i=0;i<NumGates;i++){
		printf("%d [", CircuitArray[i].op);
		for(j=0;j<CircuitArray[i].length;j++){
			printf("%d ", CircuitArray[i].var[j]);
		}
		printf("] \n");
	}
	//*/
	//printf("%d\n%d\n", numCases, N);
	for(i=0;i<numCases;i++){
		greyCode(i);
		//printArray(InputArray, N);
		runCircuit();
		printOut();
	}

	return 0;
}
