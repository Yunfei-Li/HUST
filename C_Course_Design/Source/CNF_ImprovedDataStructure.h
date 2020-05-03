#ifndef STATES

#define TRUE         1
#define FALSE        0
#define SATISFIED    1
#define UNSATISFIED -1
#define REMOVED     -1
#define UNCERTAIN    0

#define STATES 1
#endif/*STATES*/

typedef struct formula{
	head_c hc;
	int s;                 //To signal whether this clause_i is removed or not
	int n;                 //To denote how many varables are included in this clause_i
	struct formula *next;
}formula;

typedef formula *head_f;
typedef formula *clause_i;


typedef struct CNF_I{
	int NOV;               //Number of Variables
	int NOC;               //Number of Conjuncts
	head_f orinal;         //original clauses
	clause_i *ad;            //address of each clause_i
	info_var *p;
}CNF_I;

typedef CNF_I *cnf_i;



cnf_i parseCNF(FILE *in);
void outputCNF(cnf_i c);
void clearLiteral_2(cnf_i c,int layer,int k);
void retract(cnf_i c,int layer,int k);
void clearLiteral_2_(cnf_i c,int layer,int k);
void retract_(cnf_i c,int layer,int k);
int FindUnitClause_2(cnf_i c);
int RandomStrategy(cnf_i c);
int checkCNF(cnf_i c);
int checkAssignment_2(cnf_i c,int *assignment);
