#ifndef STATES

#define TRUE         1
#define FALSE        0
#define SATISFIED    1
#define UNSATISFIED -1
#define REMOVED     -1
#define UNCERTAIN    0

#define STATES 1
#endif/*STATES*/


typedef struct Variable{
	int v;                //variable v
	int s;                //This variable is to signal wheather it is satisfied or not
}var;

typedef struct node_i{
	var L;                //Literal
	struct node_i *next;
}node_i;

typedef node_i *head_c;      //head pointer of a clause
typedef node_i *literal;




typedef struct index{
	int k;                 //pointer
	int pmc;               //plus or minus characteristic
	struct index *next;
}index;

typedef index *index_list;
typedef index *index_number;

typedef struct info_var{
	index_list in;
	int fp;                //frequency of positive literals
	int fn;                //frequency of negative literals
}info_var;
