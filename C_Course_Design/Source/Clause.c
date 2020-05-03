#include "Clause.h"

#ifndef NULL
#define NULL 0
#endif/*NULL*/

#ifndef TRUE
#define TRUE 1
#endif/*TRUE*/

#ifndef FALSE
#define FALSE 0
#endif/*FALSE*/

struct node{
	int ele;
	Literal next;
};

/*功能：从一个CNF文件中读取一行，并以链表的方式创建一个子句
  输入：文件指针in
  输出：链表头C*/
Clause createClause(FILE *in){
	int tmp,i=0;
	Clause C=malloc(sizeof(struct node));
	Literal L=C;
	C->next=NULL;
	do{
		fscanf(in,"%d",&tmp);
		if(tmp!=0){
			L->next=malloc(sizeof(struct node));
			L=L->next;
			L->ele=tmp;
			L->next=NULL;
		}
	}while(tmp!=0);
	return C;
}

/*功能：销毁一个以链表形式保存的子句
  输入：一个子句C
  输出：无输出*/
void destroyClause(Clause C){
	Literal L=C->next,tmp;
	while(L){
		tmp=L->next;
		free(L);
		L=tmp;
	}
	free(C);
}

/*功能：检查子句C中是否存在变元k
  输入：一个子句C、一个变元k
  输出：是否存在*/
int ExistLiteral(Clause C,int k){
	int r=FALSE;
	Literal L=C->next;
	int i=1;
	while(L){
		if(L->ele==k){
			r=TRUE;
			break;
		}
		L=L->next;
	}
    return r;
}

/*功能：从一个子句中移除变元k
  输入：一个子句C、一个变元k
  输出：移除掉变元k的子句C*/
void removeLiteral(Clause C,int k){
	Literal L=C;
	while(L&&L->next){
		if(L->next->ele==k){
			Literal tmp=L->next;
			L->next=L->next->next;
			free(tmp);
		}
		L=L->next;
	}
}

/*功能：复制一遍子句C并保存在一个新的子句中
  输入：子句C
  输出：复制C后的子句_C*/
Clause copyClause(Clause C){
	Clause _C=malloc(sizeof(struct node));
	_C->next=NULL;
	Literal _L=_C,L=C->next;
	while(L){
		_L->next=malloc(sizeof(struct node));
		_L=_L->next;
		_L->next=NULL;
		_L->ele=L->ele;
		L=L->next;
	}
	return _C;
}

/*功能：判断子句C是否是单子句
  输入：一个子句C
  输出：是否为单子句*/
int isUnitClause(Clause C){
	if(C->next) return C->next->next==NULL;
	else return FALSE;
}

/*功能：检查子句在某个真值指派下是否已被满足
  输入：子句C、真值指派assignment
  输出：是否已被满足*/
int checkClause(Clause C,int *assignment){
	int r=FALSE;
	Literal L=C->next;
	int k;
	while(L){
		k=L->ele;
		if(k>0&&assignment[k-1]==1){
			r=TRUE;
			break;
		}
		else if(k<0 && assignment[-k-1]==0){
			r=TRUE;
			break;
		}
		L=L->next;
	}
	return r;
}

/*功能：输出一个以链表形式保存的子句
  输入：子句C
  输出：无输出*/
void printClause(Clause C){
	Literal L=C->next;
	while(L){
		printf("%4d ",L->ele);
		L=L->next;
	}
}
