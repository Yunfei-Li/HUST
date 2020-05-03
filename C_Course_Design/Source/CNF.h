struct clause;

typedef struct clause *cnf;
typedef struct clause *conjunct;

cnf createCNF(FILE *in,int *_NOV);
cnf addUnitClause(cnf p,int k);
void removeClause(cnf p,conjunct c);
int ExistNullClause(cnf p);
int ExistUnitClause(cnf p);
void clearLiteral(cnf p,int k);
void printCNF(cnf p);
void destroyCNF(cnf p);
