#include "CNF_ImprovedDataStructure.h"

#ifndef NULL
#define NULL 0
#endif/*NULL*/

/*功能：从一个文件中读取一个CNF公式
  输入：一个文件指针in
  输出：cnf公式c*/
cnf_i parseCNF(FILE *in){
	char tmp[20];
	do{
		fscanf(in,"%s",tmp);
	}while(tmp[0]!='p' || tmp[1]!=0);
	cnf_i c=malloc(sizeof(CNF_I));
	fscanf(in,"%s %d %d",tmp,&c->NOV,&c->NOC);
	c->p=malloc(c->NOV*sizeof(info_var));
	c->ad=malloc(c->NOC*sizeof(clause_i));
	c->orinal=malloc(sizeof(formula));
	c->orinal->next=NULL;
	int i,L;
	for(i=0;i<c->NOV;i++){
		c->p[i].fp=0;
		c->p[i].fn=0;
		c->p[i].in=malloc(sizeof(index));
		c->p[i].in->next=NULL;
	}
	clause_i cl=c->orinal;
	for(i=0;i<c->NOC;i++){
		cl->next=malloc(sizeof(formula));
		c->ad[i]=cl->next;
		cl->next->s=UNCERTAIN;
		cl->next->n=0;
		cl->next->next=NULL;
		cl->next->hc=malloc(sizeof(node_i));
		literal lit=cl->next->hc;
		lit->next=NULL;
		while(1){
			fscanf(in,"%d",&L);
			if(!L)break;
			cl->next->n++;
			lit->next=malloc(sizeof(node_i));
			lit->next->L.v=L;
			lit->next->L.s=UNCERTAIN;
			lit->next->next=NULL;
			lit=lit->next;
			index_number tmp=c->p[abs(L)-1].in->next;
			c->p[abs(L)-1].in->next=malloc(sizeof(index));
			c->p[abs(L)-1].in->next->k=i;
			c->p[abs(L)-1].in->next->next=tmp;
			if(L>0){
				c->p[abs(L)-1].in->next->pmc=1;
				c->p[abs(L)-1].fp++;
			}
			else{
				c->p[abs(L)-1].in->next->pmc=-1;
				c->p[abs(L)-1].fn++;
			}
		}
		cl=cl->next;
	}
	return c;
}

/*功能：在屏幕上输出一个一个CNF公式c
  输入：CNF公式c
  输出：无输出*/
void outputCNF(cnf_i c){
	int i;
	clause_i cl=c->orinal->next;
	while(cl){
		printf("    c");
		literal lit=cl->hc->next;
		while(lit){
			printf(" %5d",lit->L.v);
			lit=lit->next;
		}
		printf("%5d\n",0);
		cl=cl->next;
	}
}

/*功能：将cnf公式c中文字k以及包含文字k的子句的状态s改为已满足，同时将文字-k的状态改为不满足
  输入：CNF公式c、决策层layer、文字k
  输出：修改后的CNF公式p*/
void clearLiteral_2(cnf_i c,int layer,int k){
	int L=abs(k);
	index_number idx=c->p[L-1].in->next;
	literal lit;
	int isNull;
	while(idx){
		if(c->ad[idx->k]->s>=0){
			lit=c->ad[idx->k]->hc->next;
			isNull=1;
			while(lit){
				if(lit->L.s>=SATISFIED){
					isNull=0;
				}
				else if(lit->L.s==UNCERTAIN && abs(lit->L.v)==L){
					c->ad[idx->k]->n--;
					if(lit->L.v==k){
						lit->L.s=SATISFIED*layer;
						c->ad[idx->k]->s=SATISFIED;
						isNull=0;
					}
					else
					    lit->L.s=REMOVED*layer;
				}
				else if(lit->L.s==UNCERTAIN){
					isNull=0;
				}
				lit=lit->next;
			}
			if(isNull)
			    c->ad[idx->k]->s=UNSATISFIED;
		}
		idx=idx->next;
	}
}

/*功能：撤销决策层layer对CNF公式p中文字以及子句状态作出的修改
  输入：CNF公式c、决策层layer、文字k
  输出：撤销修改后的CNF公式p*/
void retract(cnf_i c,int layer,int k){
	int L=abs(k);
	index_number idx=c->p[L-1].in->next;
	literal lit;
	int isSatisfied;
	while(idx){
		lit=c->ad[idx->k]->hc->next;
		isSatisfied=0;
		while(lit){
			if(lit->L.s==SATISFIED*layer){
				lit->L.s=UNCERTAIN;
				c->ad[idx->k]->n++;
			}
			else if(lit->L.s==UNSATISFIED*layer){
				lit->L.s=UNCERTAIN;
				c->ad[idx->k]->n++;
			}
			else if(lit->L.s>=SATISFIED)
				isSatisfied=1;
			lit=lit->next;
		}
		if(isSatisfied)
		    c->ad[idx->k]->s=SATISFIED;
		else
		    c->ad[idx->k]->s=UNCERTAIN;
		idx=idx->next;
	}
}

/*功能：判断CNF公式c中是否存在单子句
  输入：CNF公式c
  输出：是否存在单子句，若存在则返回这个单子句中的文字*/
int FindUnitClause_2(cnf_i c){
	int number=0,r;
	clause_i cl=c->orinal->next;
	literal lit;
	while(cl){
		number=0;
		if(cl->s==UNCERTAIN){
			lit=cl->hc->next;
			while(lit){
				if(lit->L.s==UNCERTAIN){
					r=lit->L.v;
					number++;
				}
				if(number>1){
					r=0;
					break;
				}
				lit=lit->next;
			}
		}
		if(number==1)
		    break;
		cl=cl->next;
	}
	return r;
}

/*功能：返回第一个尚未满足的子句中的第一个尚未满足的文字k
  输入：CNF公式c
  输出：文字k*/
int RandomStrategy(cnf_i c){
	clause_i cl=c->orinal->next;
	while(cl){
		if(cl->s==UNCERTAIN){
			literal lit=cl->hc->next;
			while(lit){
				if(lit->L.s==UNCERTAIN)
				    return lit->L.v;
				lit=lit->next;
			}
		}
		cl=cl->next;
	}
}

/*功能：判断检查CNF公式c是否已经完全满足
  输入：CNF公式c
  输出：是否已完全满足*/
int checkCNF(cnf_i c){
	int r=SATISFIED;
	clause_i cl=c->orinal->next;
	while(cl){
		if(cl->s==UNSATISFIED)
		    return UNSATISFIED;
		else if(cl->s==UNCERTAIN)
		    r=UNCERTAIN;
		cl=cl->next;
	}
	return r;
}

/*功能：检查CNF公式c在真值指派assignment下是否满足
  输入：CNF公式c、真值指派assignment*/
int checkAssignment_2(cnf_i c,int *assignment){
	clause_i cl=c->orinal->next;
	literal lit;
	int r=0,k;
	while(cl){
		lit=cl->hc->next;
		r=0;
		while(lit){
			k=lit->L.v;
			if(assignment[abs(k)-1]==k){
				r=1;
				break;
			}
			lit=lit->next;
		}
		if(!r)
		    return FALSE;
		cl=cl->next;
	}
	return TRUE;
}