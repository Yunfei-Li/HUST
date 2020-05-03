#include "JW.h"

/*功能：返回一个浮点数的绝对值
  输入：一个浮点数a
  输出：a的绝对值*/
float float_abs(float a){
	if(a>0)return a;
	else return -a;
}

/*功能：判断一个子句中是否存在变元k或者其否定
  输入：一个子句C、变元k
  输出：若出现k，返回这个子句的长度，若出现其否定，返回长度的相反数，否则返回0
*/
int JW_length(Clause C,int k){
	Literal L=C->next;
	int length=0,flag=0;
	while(L){
		if(L->ele==k)flag=1;
		else if(L->ele==-k)flag=-1;
		length++;
		L=L->next;
	}
	return flag*length;
}

/*功能：返回一个浮点数数组的最大值
  输入：浮点数数组名a，数组长度n
  输出：最大值r*/
int FindJWMax(float *a,int n){
	int i,r=1;
	float max=float_abs(a[0]);
	for(i=1;i<n;i++){
		if(float_abs(a[i])>max){
			if(a[i]>0) r=i+1;
			else r=-i-1;
			max=float_abs(a[i]);
		}
	}
	return r;
}

/*功能：返回CNF公式p中变元v的JW函数值
  输入：CNF公式p、变元v
  输出：JW函数值*/
float JWvalue(cnf p,int v){
	conjunct c=p->next;
	float negative=.0,positive=.0;
	int len;
	while(c){
		len=JW_length(c->C,v);
		if(len>0) positive+=(float)pow(2,-len);
		else if(len<0) negative-=(float)pow(2,len);
		c=c->next;
	}
	if(positive+negative>0) return positive;
	else return negative;
}

/*功能：返回CNF公式p中JW函数值最大的那个变元v
  输入：CNF公式p、变元数NOV
  输出：JW函数值最大的那个变元v*/
int JWstrategy(cnf p,int NOV){
	int i=0;
	float JW[NOV];
	for(i=0;i<NOV;i++)
	    JW[i]=JWvalue(p,i+1);
	return FindJWMax(JW,NOV);
}
