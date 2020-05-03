int FindMax(int *a,int n);
int DPLL(cnf p,int *assignment,int NOV,int STRATEGY,int *_times);
int DPLL_VSIDS(cnf p,int *assignment,int NOV,int *_times,int *frequency);
int checkAssignment(cnf p,int *assignment);
void output_file(char *filename,int r,int *assignment,int NOV,double w_time);
