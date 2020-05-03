#include "MP.h"

/*功能：判断一个子句是否全部都是正文字
  输入：一个子句C
  输出：是否只含有正文字*/
int allPositive(Clause C){
	int r=0;
	Literal L=C->next;
	while(L){
		if(L->ele>0)r++;
		else{
			r=0;
			break;
		}
		L=L->next;
	}
	return r;
}

/*功能：返回一个CNF公式中全部都是正文字的子句中最短的那一个子句的最后一个文字
  输入：CNF公式p
  输出：MP策略下选取的文字r*/
int MPstrategy(cnf p,int NOV){
	int r=p->next->C->next->ele;
	int minlen=NOV;
	conjunct c=p->next;
	while(c){
		int len=allPositive(c->C);
		if(len && len<=minlen){
			minlen=len;
			r=c->C->next->ele;
		}
		c=c->next;
	}
	return r;
}