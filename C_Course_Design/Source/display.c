#include "display.h"

/*功能：得到一个min-max之间的整数，�对所有无效输入提示用户重新输入
  输入：最大值max、最小值min
  输出：一个min-max之间的整数*/
int getInt(int max,int min){
	char ch[50];
	int r;
	if(max>=10){
		scanf("%s",ch);
	    while( (strlen(ch)!=1|| !(ch[0]>=min+'0'&&ch[0]<='9')) && (strlen(ch)!=2||(ch[0]!='1'|| !(ch[1]>='0'&&ch[1]<=max-10+'0')))){
		    printf("INVALID INPUT!\nPlease try again:");
		    scanf("%s",ch);
	    }
	    if(strlen(ch)==1) r=ch[0]-'0';
	    else r=ch[1]-'0'+10;
	}
	else{
		scanf("%s",ch);
	    while( (strlen(ch)!=1|| !(ch[0]>=min+'0'&&ch[0]<=max+'0'))){
		    printf("INVALID INPUT!\nPlease try again:");
		    scanf("%s",ch);
	    }
	    r=ch[0]-'0';
	}
	return r;
}

/*功能：从一个文件中读取一个min-max之间的整数
  输入：一个文件指针in、最大值max、最小值min
  输出：一个min-max之间的整数*/
int getIntFromFile(FILE *in,int max,int min){
	char ch[50];
	int r;
	if(max>=10){
		fscanf(in,"%s",ch);
	    while( (strlen(ch)!=1|| !(ch[0]>=min+'0'&&ch[0]<='9')) && (strlen(ch)!=2||(ch[0]!='1'|| !(ch[1]>='0'&&ch[1]<=max-10+'0')))){
		    fscanf(in,"%s",ch);
	    }
	    if(strlen(ch)==1) r=ch[0]-'0';
	    else r=ch[1]-'0'+10;
	}
	else{
		fscanf(in,"%s",ch);
	    while( (strlen(ch)!=1|| !(ch[0]>=min+'0'&&ch[0]<=max+'0'))){
		    fscanf(in,"%s",ch);
	    }
	    r=ch[0]-'0';
	}
	return r;
}

/*功能：在屏幕上输出一个二进制数独棋盘
  输入：棋盘assignment、阶数degree
  输出：无输出*/
void displaySudoku(int *assignment,int degree){
	int i,j;
	printf("   | ");
	for(j=0;j<degree;j++)
	    printf("%2d  ",j+1);
	printf("\n");
	printf("---|");
	for(i=0;i<degree;i++)
	    printf("----");
	printf("\n");
	for(i=0;i<degree;i++){
		printf("%2d | ",i+1);
		for(j=0;j<degree;j++){
			if(assignment[order(degree,i+1,j+1)-1]==-1)printf("    ");
			else printf("%2d  ",assignment[order(degree,i+1,j+1)-1]);
		}
		printf("\n");
		if(i!=degree-1)printf("   |\n");
	}
}

/*功能：求解二进制数独板块的交互
  输入：无输入
  输出：无输出*/
void SolveSudoku(void){
	int degree;
	cnf p;
	printInputMethod();
	if(getInt(2,1)==1){
		printf("\nPlease input the size of your binary puzzle(4 or 6 or 8 or 10 or 12 or 14):");
		char ch[10];
		scanf("%s",ch);
		while( (strlen(ch)!=1||(ch[0]!='4'&&ch[0]!='6'&&ch[0]!='8')) && (strlen(ch)!=2||(ch[0]!='1'||(ch[1]!='0'&&ch[1]!='2'&&ch[1]!='4'))) ){
			printf("INVALID INPUT!\nPlease input your choice again:");
			scanf("%s",ch);
		}
		if(strlen(ch)==1) degree=ch[0]-'0';
		else degree=ch[1]-'0'+10;
		if(degree==14)
		    printf("\nPreparing! Please wait for a little while!\n");
		p=createSudokuCNF(degree);
		int row,column,value;
		printf("\n\nPLEASE INPUT YOUR PUZZLE!\n");
		printf("Please Input your puzzle as the following instructions says.\nPlease start your input!\n");
		printf("\nInput the row number (0 means the end of your input):");
		while(row=getInt(degree,0)){
			printf("\nInput the column number :");
			column=getInt(degree,1);
			printf("\nInput the value :");
			value=getInt(1,0);
			if(value) addrestriction(p,order(degree,row,column));
			else addrestriction(p,-order(degree,row,column));
			printf("\nInput the row number (0 means the end of your input):");
		}
	}
	else{
		char filename[50];
		FILE *in=NULL;
		printf("Please input your filename:\n");
		do{
			scanf("%s",filename);
			while(access(filename,0)==-1){
			    printf("\nSorry, %s does NOT exist!\nPlease input your filename once again:\n",filename);
			    scanf("%s",filename);
			}
		    in=fopen(filename,"r");
		    if(!in){
		    	printf("Sorry, %s CANNOT be opened!\nPlease reassure %s is a CNF file!\n",filename,filename);
		    	printf("Pease input your filename once again after confirmation:\n");
			}
		}while(!in);
		in=fopen(filename,"r");
		char ch[10];
		fscanf(in,"%s",ch);
		while( (strlen(ch)!=1||(ch[0]!='4'&&ch[0]!='6'&&ch[0]!='8')) && (strlen(ch)!=2||(ch[0]!='1'||(ch[1]!='0'&&ch[1]!='2'&&ch[1]!='4'))) ){
			fscanf(in,"%s",ch);
		}
		if(strlen(ch)==1) degree=ch[0]-'0';
		else degree=ch[1]-'0'+10;
		if(degree==14)
		    printf("\nPreparing...\nPlease wait for a little while...\n");
		p=createSudokuCNF(degree);
		int row,column,value;
		while(row=getIntFromFile(in,degree,0)){
			column=getIntFromFile(in,degree,1);
			value=getIntFromFile(in,1,0);
			if(value) addrestriction(p,order(degree,row,column));
			else addrestriction(p,-order(degree,row,column));
		}
	}
	int *assignment=malloc(degree*degree*sizeof(int));
	int i;
	for(i=0;i<degree*degree;i++)
	    assignment[i]=-1;
	int times=0;
	if(degree==12)
	    printf("\nIt may take a little while(a few seconds) to solve a Sudoku with a degree of 12.\nThank you for your patience...\n");
	else if(degree==14)
	    printf("\nIt may take a little while(a minute or so, sometimes 2 minutes) to solve a Sudoku with a degree of 14.\nThank you for your patience...\n");
	int r;
	double start=clock();
	r=DPLL(p,assignment,degree*degree,3,&times);
	double end=clock();
	if(r){
		printf("\n\nCongratulations!\nYour puzzle is solved!\nThe answer is as follows!\n");
		displaySudoku(assignment,degree);
	}
	else printf("\nSorry, there is no such an answer that satisfies your puzzle!\n");
	printf("Solving time: %lfms\n",(end-start)/CLOCKS_PER_SEC*1000);
	free(assignment);
}

/*功能：二进制数独游戏的交互
  输入：无输入
  输出：无输出*/
void PlayBinaryPuzzle(void){
	printf("Please input the order of the puzzle you wanna try(4 or 6 or 8 or 10 or 12):");
	int degree,mode;
	char ch[10];
	scanf("%s",ch);
	while( (strlen(ch)!=1||(ch[0]!='4'&&ch[0]!='6'&&ch[0]!='8'))&&(strlen(ch)!=2||(ch[0]!='1'||ch[1]!='0'&&ch[1]!='2'))){
		printf("INVALID INPUT!\nPlease input your choice again:");
		scanf("%s",ch);
	}
	if(strlen(ch)==1) degree=ch[0]-'0';
	else degree=ch[1]-'0'+10;
	if(degree<=10){
	    mode=2;
	    if(degree==10)printf("\nGenerating a puzzle...\nIt may take a few seconds.\nThank you for your patience!\n");
	}
	else{
		mode=1;
		printf("\nGenerating a puzzle...\nIt may take 1-2 minutes.\nThank you for your patience!\n");
    }
	int *assignment=malloc(degree*degree*sizeof(int));
	int *puzzle=malloc(degree*degree*sizeof(int));
	double start=clock();
	cnf p=PuzzleWithOnlySolution(degree,mode,assignment,puzzle);
	double end=clock();
	int *users=malloc(degree*degree*sizeof(int));
	int i,blanks=0,filled=0,flag,r,c,v,confirmation=0;
	for(i=0;i<degree*degree;i++)
	    if((users[i]=puzzle[i])==-1) blanks++;
	printf("\nGenerating time: %lfms",(end-start)/CLOCKS_PER_SEC*1000);
	while(!confirmation){
		printf("\n\n");
		displaySudoku(users,degree);
		printPuzzleOperation();
	    flag=getInt(4,1);
		switch(flag){
			case 1:
				printf("\nPlease fill in the blank as the following instructions says.");
				printf("\nInput the row number :");
				r=getInt(degree,1);
				printf("\nInput the column number :");
				c=getInt(degree,1);
				printf("\nInput the value :");
				v=getInt(1,0);
				if(puzzle[order(degree,r,c)-1]==-1){
					if(users[order(degree,r,c)-1]==-1) filled++;
					users[order(degree,r,c)-1]=v;
				}
				else printf("\nSorry, the number you chose is given by the puzzle.\nYou CANNOT change it!\n");
				break;
			case 2:
				printf("\nPlease fill in the blank as the following instructions says.");
				printf("\nInput the row number :");
				r=getInt(degree,1);
				printf("\nInput the column number :");
				c=getInt(degree,1);
				if(puzzle[order(degree,r,c-1)]==-1){
					if(users[order(degree,r,c)-1]==-1)printf("This blank has NOT been filled yet!\n");
					else{
						users[order(degree,r,c)-1]=-1;
						filled--;
					}
				}
				else printf("\nSorry, the number you chose is given by the puzzle.\nYou CANNOT clear it!\n");
				break;
			case 3:
				printf("\nIt is a pity for you to quit.\nWish you more patience next time!\n");
				break;
			case 4:
				for(i=0;i<degree*degree;i++)
	                users[i]=puzzle[i];
	            filled=0;
	            break;
		}
		if(filled==blanks){
			displaySudoku(users,degree);
			printf("|---------------------|\n");
			printf("| Confirm to Submit?  |\n");
			printf("|        1.yes        |\n");
			printf("|        0.no         |\n");
			printf("|---------------------|\n");
			confirmation=getInt(1,0);
		}
		else if(flag==3)
			break;
	}
	printf("Your answer is as follows.\n");
	displaySudoku(users,degree);
	if(checkAssignment(p,users))printf("CONGRATULATIONS! \nYour answer is exactly what it should be!\n");
	else if(flag==3){
		printf("The CORRECT answer is as follows.\n");
		displaySudoku(assignment,degree);
	}
	else{
		printf("Sorry, maybe there is something wrong with your answer!\nThe CORRECT answer is as follows.\n");
		displaySudoku(assignment,degree);
	}
}

/*功能：在屏幕上输出一个系统主菜单
  输入：无输入
  输出：无输出*/
void printMainMenu(void){
	printf("|-------------------------------------------|\n");
	printf("|      Welcome to My SAT/Sudoku System      |\n");
	printf("|***********Menu For this system************|\n");
	printf("| 1.SAT        2.Sudoku       0.EXIT SYSTEM |\n"); 
	printf("|-------------------------------------------|\n");
	printf("\nPlease choose the function you wanna try:");
}

/*功能：在屏幕上输出一个二进制数独板块的菜单
  输入：无输入
  输出：无输出*/
void printBinaryPuzzleMenu(void){
	printf("********************************************\n");
	printf("*     Welcome to My Binary Puzzle Game     *\n");
	printf("*--- ------------FUNCTIONS-----------------*\n");
	printf("*1.Play Binary Puzzle(with ONLY 1 solution)*\n");
	printf("*      2.Solve the Puzzle You Provide      *\n");
	printf("*         0.EXIT BINARY PUZZLE GAME        *\n");
	printf("********************************************\n");
	printf("\n\nPlease Make Your Choice:");
}

/*功能：在屏幕上输出一个输入二进制数独棋盘方式的选择菜单
  输入：无输入
  输出：无输出*/
void printInputMethod(void){
	printf("|--------------------------------------------|\n");
	printf("|    How do you want to INPUT your puzzle?   |\n"); 
	printf("|                                            |\n");
	printf("|              1.input MANUALLY              |\n");
	printf("|             2.READ from a FILE             |\n");
	printf("|--------------------------------------------|\n");
	printf("\nPlease choose a mode:");
}

/*功能：输出二进制数独游戏操作菜单
  输入：无输入
  输出：无输出*/
void printPuzzleOperation(void){
	printf("\nHINT: ONLY SOLUTION GUARANTEED\n\n");
	printf("|---------------------------|\n");
	printf("|    Available Operation    |\n"); 
	printf("|                           |\n");
	printf("|  1.change/fill in a blank |\n");
	printf("|      2.clear a blank      |\n");
	printf("|3.quit & display the answer|\n");
	printf("|    4.clear all blanks     |\n");
	printf("|---------------------------|\n");
	printf("(Any other number would be considered to be 4)\n\nchoose a operation:");
}

/*功能：二进制数独板块交互
  输入：无输入
  输出：无输出*/
void Puzzle(void){
	printf("\n\n");
	printBinaryPuzzleMenu();
	char c[10];
	while(scanf("%s",c)){
		while(strlen(c)!=1||(c[0]!='0'&&c[0]!='1'&&c[0]!='2')){
			printf("INVALID INPUT!\nPlease input your choice once again:");
			scanf("%s",c);
		}
		if(c[0]=='1')PlayBinaryPuzzle();
		else if(c[0]=='2')SolveSudoku();
		else break;
		printf("\n\n"); 
		printBinaryPuzzleMenu();
	}
}

/*功能：输出变元选择策略菜单
  输入：无输入
  输出：无输出*/
void printSATStrategyMenu(void){
	printf("\n");
	printf("**************************\n");
	printf("*-Strategy for DPLL BCP--*\n");
	printf("*          1.MP          *\n");
	printf("*          2.JW          *\n");
	printf("**************************\n");
	printf("\nPlease choose a strategy.\nYour choice:");
}

/*功能：变元选择策略优化的SAT交互（包括不优化的策略）
  输入：无输入
  输出：无输出*/
void SAT_Recursive(int k){
	printf("\n\n");
	int STRATEGY;
	if(!k){
		printSATStrategyMenu();
		STRATEGY=getInt(2,1);
	}
	else STRATEGY=3;
	char filename[50];
	FILE *in=NULL;
	printf("Please input your filename:\n");
	do{
		scanf("%s",filename);
		while(access(filename,0)==-1){
		    printf("\nSorry, %s does NOT exist!\nPlease input your filename once again:\n",filename);
		    scanf("%s",filename);
		}
	    in=fopen(filename,"r");
	    if(!in){
	    	printf("Sorry, %s CANNOT be opened!\nPlease reassure %s is a CNF file!\n",filename,filename);
	    	printf("Pease input your filename once again after confirmation:\n");
		}
	}while(!in);
	int NOV;
	cnf p=createCNF(in,&NOV);
	fclose(in);
	printf("\nYou want to see the Conjunctive Normal Formula?\n");
	printf("0.no  1.yes\nYour choice:");
	int *assignment=malloc(NOV*sizeof(int));
	char c[10];
	scanf("%s",c);
	while(strlen(c)!=1||(c[0]!='0'&&c[0]!='1')){
		printf("INVALID INPUT!\nPlease input your choice again:");
		scanf("%s",c);
	}
	if(c[0]=='1')printCNF(p);
	int i;
	for(i=0;i<NOV;i++)
	    assignment[i]=-1;
	int times=0;
	double start=clock();
	int r=DPLL(p,assignment,NOV,STRATEGY,&times);
	double end=clock();
	if(r){
		printf("\nThis Conjunctive Normal Formula is SATISFIABLE��\n");
		printf("The Truth Assignments are as followed\n");
	    for(i=0;i<NOV;i++)
			if(assignment[i])printf("%d ",i+1);
			else if(!assignment[i])printf("%d ",-(i+1));
			else printf("0 ");
		if(checkAssignment(p,assignment))printf("\nIt has been checked that the truth assignments above CAN satisfy the CNF!\n");
		else printf("\n\nIt has been checked that the truth assignments above CANNOT satisfy the CNF!\n");
    }
	else printf("\nThis Conjunctive Normal Formula is UNSATISFIABLE\n");
	printf("\nDPLL Core Module Running Time: %lfms\n",(end-start)/CLOCKS_PER_SEC*1000);
	printf("DPLL was called for %d times!\n",times);
	output_file(filename,r,assignment,NOV,(end-start)/CLOCKS_PER_SEC*1000);
	printf("\nThe Running Result is also saved in a file whose path is %s\n",filename);
}

/*功能：数据结构和算法结构优化的SAT交互
  输入：无输入
  输出：无输出*/
void SAT_nonRecursive(void){
	printf("\n\n");
	char filename[50];
	FILE *in=NULL;
	printf("Please input your filename:\n");
	do{
		scanf("%s",filename);
		while(access(filename,0)==-1){
		    printf("\nSorry, %s does NOT exist!\nPlease input your filename once again:\n",filename);
		    scanf("%s",filename);
		}
	    in=fopen(filename,"r");
	    if(!in){
	    	printf("Sorry, %s CANNOT be opened!\nPlease reassure %s is a CNF file!\n",filename,filename);
	    	printf("Pease input your filename once again after confirmation:\n");
		}
	}while(!in);
	in=fopen(filename,"r");
	if(!in)printf("Sorry, %s CANNOT be opened!\nDon\'t worry, let\'s try again!\n\n",filename);
	cnf_i p=parseCNF(in);
	fclose(in);
	printf("\nYou want to see the Conjunctive Normal Formula?\n");
	printf("0.no  1.yes\nYour choice:");
	int *assignment=malloc(p->NOV*sizeof(int));
	char c[10];
	scanf("%s",c);
	while(strlen(c)!=1||(c[0]!='0'&&c[0]!='1')){
		printf("INVALID INPUT!\nPlease input your choice again:");
		scanf("%s",c);
	}
	if(c[0]=='1')outputCNF(p);
	int i;
	for(i=0;i<p->NOV ;i++)
	    assignment[i]=0;
	double start=clock();
	int r=DPLL_nonRecursive(p,assignment);
	double end=clock();
	if(r){
		printf("\nThis Conjunctive Normal Formula is SATISFIABLE��\n");
		printf("The Truth Assignments are as followed\n");
	    for(i=0;i<p->NOV;i++)
	        printf("%d ",assignment[i]);
		if(checkAssignment_2(p,assignment))printf("\nIt has been checked that the truth assignments above CAN satisfy the CNF!\n");
		else printf("\n\nIt has been checked that the truth assignments above CANNOT satisfy the CNF!\n");
    }
	else printf("\nThis Conjunctive Normal Formula is UNSATISFIABLE\n");
	printf("\nDPLL Core Module Running Time: %lfms\n",(end-start)/CLOCKS_PER_SEC*1000);
	output_file(filename,r,assignment,p->NOV,(end-start)/CLOCKS_PER_SEC*1000);
	printf("\nThe Running Result is also saved in a file whose path is %s\n",filename);
}

/*功能：SAT板块的交互
  输入：无输入
  输出：无输出*/
void SAT(void){
	printf("\n");
	printf("########################################################\n");
	printf("#              Welcome to My SAT Solver                #\n");
	printf("#-------------Choose an Improvement Aspect-------------#\n");
	printf("#      1.Variable Selection Strategy Improvement       #\n");
	printf("#  2.Data Structure && Algorithm Structure Improvement #\n");
	printf("#                  3.No Improvement                    #\n");
	printf("#               0.Exit SAT Solver Module               #\n");
	printf("########################################################\n");
	printf("\nPlease Make Your choice:");
	int s=getInt(3,0);
	if(s==1)
	    SAT_Recursive(0);
	else if(s==2)
	    SAT_nonRecursive();
	else if(s==3)
	    SAT_Recursive(1);
}

