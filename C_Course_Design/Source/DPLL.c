#include "DPLL.h"
 
 /*功能：找到整数数组中的最大值
   输入：数组名a、数组长度n
   输出：最大值的下标+1*/
int FindMax(int *a,int n){
	int cursor=0,i;
	for(i=1;i<n;i++)
		if(a[i]>a[cursor])
			cursor=i;
	return cursor+1;
}

/*功能：递归方式的DPLL算法求解SAT问题
  输入：CNF公式p，变元数NOV，变元选取策略STRATEGY
  输出：是否可满足、满足时的真值指派assignment、递归次数times*/
int DPLL(cnf p,int *assignment,int NOV,int STRATEGY,int *_times){
	int k;
	*_times=*_times+1;
	while(k=ExistUnitClause(p)){                          //满足所有的单子句
		if(k>0)assignment[k-1]=1;
		else assignment[-k-1]=0;
		clearLiteral(p,k);
		if(!p->next) return TRUE;
		else if(ExistNullClause(p)) return FALSE;
	}
	if(STRATEGY==1)k=MPstrategy(p,NOV);                   //用户选择MP变元选取策略
	else if(STRATEGY==2)k=JWstrategy(p,NOV);              //用户选择JW变元选取策略
	else k=p->next->C->next->ele;                         //用户选择不优化的策略
	cnf p_p=addUnitClause(p,k);
	if(DPLL(p_p,assignment,NOV,STRATEGY,_times)){
		destroyCNF(p_p);                                  //已经满足
		return TRUE;
	}
	else{
		cnf n_p=addUnitClause(p,-k);                      //待定的情况下进行下一次决策
		assignment[abs(k)-1]=-1; 
		if(DPLL(n_p,assignment,NOV,STRATEGY,_times)){
		    destroyCNF(n_p);
		    return TRUE;
	    }
	    else {
	    	assignment[abs(k)-1]=-1;
	    	destroyCNF(n_p);
	    	return FALSE;                                 //已经不满足，回退
		}
	}
}

int checkAssignment(cnf p,int *assignment){
	int r=TRUE;
	conjunct c=p->next;
	while(c){
		if(!checkClause(c->C,assignment)){
			r=FALSE;
			break;
		}
		c=c->next;
	}
	return r;
}

/*功能：将SAT问题的求解结果保存在一个.res文件中
  输入：.cnf文件名、是否可满足r、真值指派assignment、求解时间W_time
  输出：一个.res文件*/
void output_file(char *filename,int r,int *assignment,int NOV,double w_time){
	int len=strlen(filename);
	filename[len-3]='r';
	filename[len-2]='e';
	filename[len-1]='s';
	FILE *out=fopen(filename,"w");
	if(r){
		fprintf(out,"r 1\n");
		int i;
		fprintf(out,"v");
		for(i=0;i<NOV;i++)
			if(assignment[i])fprintf(out," %d",i+1);
			else if(!assignment[i])fprintf(out," %d",-(i+1));
			else fprintf(out," 0");
		fprintf(out,"\nt %.0lfms\n",w_time);
	}
	fclose(out);
}
