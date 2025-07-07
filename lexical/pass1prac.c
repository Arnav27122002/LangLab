#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void addToSymtab(char label[], int ctr);
void printSymtab();
int isValidOpcode(char opcode[]);

char line[100];

struct Symtab {
	char label[50];
	int ctr;
};
struct Symtab Symtabs[50];

struct Instruction {
	char label[50];
	char opcode[50];
	char operand[50];
	int address;
};

char opcodes[10][10] = {
		"START", "LDA", "ADD", "SUB", "STA", "JMP", "END"
};

int nlines=0;
int symcount=0;
int startAddr, locCtr, operSize;

void main() {
	char label[50], opcode[50], operand[50];
	struct Instruction Instructions[100];
	int parts;
	FILE* fp = fopen("inp.txt","r");
	while(fgets(line, 100, fp)) {
		parts=sscanf(line, "%s %s %s", label, opcode, operand);
		
		if (parts == 2){
			strcpy(operand, opcode);
			strcpy(opcode, label);
			strcpy(label, "");
		}
		else if (parts == 1){
			strcpy(opcode, label);
			strcpy(operand, "");
			strcpy(label, "");
		}
		if (strcmp(opcode, "START") == 0) {
			startAddr = (int)strtol(operand, NULL, 16);
			locCtr = startAddr;
		}
		
		strcpy(Instructions[nlines].label, label);
		strcpy(Instructions[nlines].opcode, opcode);
		strcpy(Instructions[nlines].operand, operand);
		nlines++;
	}
	
	printf("Start Address: %x\n\n", startAddr);
	
	for (int i=0;i<nlines;i++){
		if (i>0 && Instructions[i].label[0] != '\0'){
			addToSymtab(Instructions[i].label, locCtr);
		}
		if (i==0){
			printf("%x\t%s\t%s\t%s\n",locCtr, Instructions[i].label, Instructions[i].opcode, Instructions[i].operand);
			continue;
		}
		if (isValidOpcode(Instructions[i].opcode)==1){
			printf("%x\t%s\t%s\t%s\n", locCtr, Instructions[i].label, Instructions[i].opcode, Instructions[i].operand);
			locCtr += 3;
			continue;
		}
		else if(strcmp(Instructions[i].opcode, "WORD")==0){
			printf("%x\t%s\t%s\t%s\n", locCtr, Instructions[i].label, Instructions[i].opcode, Instructions[i].operand);
			locCtr += 3;
			continue;
		}
		else if(strcmp(Instructions[i].opcode, "BYTE")==0){
			printf("%x\t%s\t%s\t%s\n", locCtr, Instructions[i].label, Instructions[i].opcode, Instructions[i].operand);
			if(Instructions[i].operand[0]=='C'){
				operSize = strlen(Instructions[i].operand) - 3;
			}
			else if(Instructions[i].operand[0]=='X'){
			operSize = (strlen(Instructions[i].operand) - 3)/2;
			}
			locCtr += operSize;
			continue;
		}
		else if(strcmp(Instructions[i].opcode, "RESW")==0){
			printf("%x\t%s\t%s\t%s\n", locCtr, Instructions[i].label, Instructions[i].opcode, Instructions[i].operand);
			operSize = atoi(Instructions[i].operand);
			locCtr += 3*operSize;
			continue;
		}
		else if(strcmp(Instructions[i].opcode, "RESB")==0){
			printf("%x\t%s\t%s\t%s\n", locCtr, Instructions[i].label, Instructions[i].opcode, Instructions[i].operand);
			operSize = atoi(Instructions[i].operand);
			locCtr += operSize;
		}
		else {
			printf("%x\t%s\t%s\t%s\n", locCtr, Instructions[i].label, Instructions[i].opcode, Instructions[i].operand);
		}
	}
	printSymtab();
	printf("\nProgram Length: %d", locCtr-startAddr-3);
}

int isValidOpcode(char label[]){
	for (int i=0;i<7;i++){
		if(strcmp(label, opcodes[i])==0){
			return 1;
		}
	}
	return 0;
}

void addToSymtab(char label[], int ctr){
	for (int i=0;i<symcount;i++) {
		if (strcmp(Symtabs[i].label, label)==0) {
			printf("Error: label already exists");
		}
	}
	strcpy(Symtabs[symcount].label, label);
	Symtabs[symcount].ctr = ctr;
	symcount++;
}

void printSymtab(){
	printf("\nSymtab\n");
	for (int i=0;i<symcount;i++) {
		printf("%s\t%x\n", Symtabs[i].label, Symtabs[i].ctr);
	}
}