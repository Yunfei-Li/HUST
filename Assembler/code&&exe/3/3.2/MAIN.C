#include<stdio.h>
#include<string.h>

char AUTH = 0;
#ifdef __cplusplus
extern "C" {
#endif
//extern char AUTH;
extern char IN_SRC;
void RECOM(void);
void printInfo(void);
void CHANGE(void);
void SEARCH(void);
void ORDER(void);
#ifdef __cplusplus
}
#endif

void printMenu(void);
int login_check(char*, char*);
int login(void);
void printString(char *str);
void printChar(char ch);
void printShort(short sh);
void nextline(void);
int  getInt(void);

int printv(int v)
{
	printf("avg = %d\n", v);
	return v;
}

int main(void)
{
	int choice;
	printf("%d", AUTH);
	do{
		printMenu();
		printf("Please Make Your Choice:");
		scanf_s("%d",&choice);
		getchar();
		char *in_gn=&IN_SRC;
		int i;
		switch(choice){
			case 1: 
			    while(login()!=1)
					printf("Wrong Username or Password!\n");
				AUTH = 1;
				printf("You have logged in successfully!\n");
				break;
			case 2:
				printf("Please input product name:");
			    for (i = 0; i < 10; i++) {
					in_gn[i] = getchar();
					if (in_gn[i] == '\n') {
						in_gn[i] = 0;
						break;
					}
	            }
				SEARCH();
				printInfo();
			    break;
			case 3:
				ORDER();
			    break;
			case 4:
				RECOM();
				break;
			case 5:
			    printf("Pending for Implementation!\n");
			    break;
			case 6:
				if (AUTH == 1)
					CHANGE();
				else {
					printf("You have not logged in yet. Please log in first!\n");
					while (login() != 1) 
						printf("Wrong Username or Password!\n");
					AUTH = 1;
					printf("You have logged in successfully!\n");
					CHANGE();
				}
			    break;
			case 7:
			    printf("Pending for Implementation!\n");
			    break;
			case 8:
			    printf("Pending for Implementation!\n");
			    break;
			case 9:
				break;
			default:
			    printf("Invalid input! Please make your choice again!\n");
		}
	} while (choice != 9);
	return 0;
}

void printMenu(void){
	printf("--------------------------------------\n");
	printf("|             MAIN MENU              |\n");
	printf("|                                    |\n");
	printf("|             1.log in               |\n");
    printf("|        2.search commodities        |\n");
	printf("|         3.place an order           |\n");
	printf("|      4.compute recommendation      |\n");
	printf("|          5.update rankings         |\n");
	printf("|         6.update information       |\n");
	printf("| 7.migrate to operation environment |\n");
	printf("| 8.display the offset address of CS |\n");
	printf("|          9.exit the system         |\n");
	printf("--------------------------------------\n");
}

int login(void){
	char in_name[20], in_pwd[16];
	printf("Please input your username:");
	int i;
	for (i = 0; i < 20; i++){
		in_name[i] = getchar();
	    if (in_name[i] == '\n') {
		    in_name[i] = 0;
			break;
	    }
	}
	printf("Please input your password:");
	for (i = 0; i < 16; i++) {
		in_pwd[i] = getchar();
		if (in_pwd[i] == '\n') {
			in_pwd[i] = 0;
			break;
		}
	}
	return login_check(in_name, in_pwd);
}

int login_check(char *in_name, char *in_pwd){
    char username[20], password[16];
	strcpy_s(username, 20, "LI YONGKANG");
	strcpy_s(password, 16, "LOVECS");
	int i,flag=1;
	for(i=0;i<20&&flag==1;i++){
        if(in_name[i]==username[i] && in_name[i]==0)
		    break;
		else if (in_name[i] != username[i]) 
			flag = 0;
	}
	for(i=0;i<16&&flag==1;i++){
        if(in_pwd[i]==password[i] && in_pwd[i]==0)
		    break;
		else if(in_pwd[i]!=password[i])
		    flag=0;
	}
	return flag;
}

void printString(char* str) {
	printf("%s", str);
}

void printChar(char ch){
	printf("%d",ch);
}

void printShort(short sh){
	printf("%d", sh);
}

void nextline(void){
	printf("\n");
}

int getInt(void){
	int sh;
    scanf_s("%d",&sh);
	return sh;
}