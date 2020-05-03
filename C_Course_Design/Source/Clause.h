struct node;

typedef struct node *Clause;
typedef struct node *Literal;

Clause createClause(FILE *in);
void destroyClause(Clause C);
int ExistLiteral(Clause C,int k);
void removeLiteral(Clause C,int k);
Clause copyClause(Clause C);
int isUnitClause(Clause C);
int checkClause(Clause C,int *assignment);
void printClause(Clause C);
