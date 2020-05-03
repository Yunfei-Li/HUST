#include "CNF.h"

struct clause{
	Clause C;
	conjunct next;
};

/*功能：从一个cnf文件中读取一个CNF公式
  输入：一个文件指针in
  输出：CNF公式p，变元数NOV*/
cnf createCNF(FILE *in,int *_NOV){
	char tmp[20];
	do{
		fscanf(in,"%s",tmp);
	}while(tmp[0]!='p' || tmp[1]!=0);
	int NOC;  //Number of Conjucts
	fscanf(in,"%s %d %d",tmp,_NOV,&NOC);
	int i;
	cnf p=malloc(sizeof(struct clause));
	p->next=NULL;
	conjunct c=p;
	for(i=0;i<NOC;i++){
		c->next=malloc(sizeof(struct clause));
		c=c->next;
		c->C=createClause(in);
		c->next=NULL;
	}
	return p;
}

/*功能：复制一个CNF公式到一个新的CNF公式中并在新的公式中增加一个单子句k
  输入：需要复制的CNF公式p、需要增加的单子句k
  输出：复制并增加单子句后的CNF公式_p*/
cnf addUnitClause(cnf p,int k){
	cnf _p=malloc(sizeof(struct clause));
	_p->next=malloc(sizeof(struct clause));
	conjunct c=p->next,_c=_p->next;
	_c->C=malloc(sizeof(struct node));
	_c->C->next=malloc(sizeof(struct node));
	_c->C->next->ele=k;
	_c->C->next->next=NULL;
	while(c){
	    _c->next=malloc(sizeof(struct clause));
	    _c=_c->next;
	    _c->C=copyClause(c->C);
	    _c->next=NULL;
	    c=c->next;
	}
	return _p;
}

/*功能：从CNF公式中移除掉一个已经满足的子句
  输入：一个CNF公式p，需要移除的子句的上一个子句c
  输出：移除后的CNF公式p*/
void removeClause(cnf p,conjunct c){
	conjunct tmp=c->next;
	c->next=c->next->next;
	destroyClause(tmp->C);
	free(tmp);
}

/*功能：检查CNF公式中是否存在空子句
  输入：CNF公式p
  输出：是否存在空子句*/
int ExistNullClause(cnf p){
	int r=FALSE;
	conjunct c=p->next;
	while(c){
		if(!c->C->next){
			r=TRUE;
			break;
		}
		c=c->next;
	}
	return r;
}

/*功能：检查CNF公式中是否存在单子句
  输入：CNF公式p
  输出：是否存在单子句，若存在，返回这个单子句中的变元*/
int ExistUnitClause(cnf p){
	int r=0;
	conjunct c=p->next;
	while(c){
		if(isUnitClause(c->C)){
			r=c->C->next->ele;
			break;
		}
		c=c->next;
	}
	return r;
}

/*功能：从一个CNF公式中去掉所有含变元k的子句，并去掉所有变元-k
  输入：一个CNF公式p、变元k
  输出：清理后的CNF公式p*/
void clearLiteral(cnf p,int k){
	conjunct c=p;
	int i=1;
	while(c&&c->next){
		if(ExistLiteral(c->next->C,k)){
			removeClause(p,c);
		}
		else {
			removeLiteral(c->next->C,-k);
			c=c->next;
		}
	}
	
}

/*功能：在屏幕上显示一个CNF公式
  输入：CNF公式p
  输出：无输出*/
void printCNF(cnf p){
	conjunct c=p->next;
	int i=0;
	while(c){
		printClause(c->C);
		printf("   0\n");
		c=c->next;
		i++;
	}
}

/*功能：销毁掉一个CNF公式
  输入：CNF公式p
  输出：无输出*/
void destroyCNF(cnf p){
	conjunct c=p->next;
	while(c){
		destroyClause(c->C);
		conjunct tmp=c->next;
		free(c);
		c=tmp;
	}
	free(p);
}
