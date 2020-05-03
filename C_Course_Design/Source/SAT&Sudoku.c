#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <math.h>
#include "Clause.c"
#include "CNF.c"
#include "DPLL.c"
#include "MP.c"
#include "JW.c"
#include "Clause_ImprovedDataStructure.h"
#include "CNF_ImprovedDataStructure.c"
#include "DPLL_ImprovedDataStructure_nonRecursive.c"
#include "SudokuCNF.c"
#include "BinaryPuzzle.c"
#include "display.c"

int main(int argc,char *argv[]){
	printMainMenu();
	char f[10];
	scanf("%s",f);
	while(strlen(f)!=1||f[0]!='0'){
		while(strlen(f)!=1||(f[0]!='1'&&f[0]!='2')){
			printf("INVALID INPUT!\nPlease input your choice once again:");
			scanf("%s",f);
		}
		if(f[0]=='1')SAT();
		else if (f[0]=='2') Puzzle();
		printf("\n\n");
		printMainMenu();
	    scanf("%s",&f);
	}
	printf("\nThank YOU for using this system!\nWelcome to use this system again!\n");
}
