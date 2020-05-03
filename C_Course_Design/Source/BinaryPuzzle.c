#include "BinaryPuzzle.h"

/*功能：拉斯维加斯算法随机生成一个数独终盘
  输入：二进制数独棋盘的阶数degree
  输出：数独终盘assignment*/
cnf RandomFilled(int degree,int *assignment){
	srand((unsigned)time(NULL));
	cnf p=createSudokuCNF(degree);
	int i,o,v,times;
	cnf t[degree+4];
	do{
		times=0;
		for(i=0;i<degree+4;i++){
			o=rand()%(degree*degree-1)+1;                           //在一个空白的棋盘中随机填充degree+4个数字
			v=rand()%2;
			if(!v) o=-o;
			if(i==0)t[i]=addUnitClause(p,o);
			else t[i]=addUnitClause(t[i-1],o);
		}
		for(i=0;i<degree*degree;i++)
		    assignment[i]=-1;
		if(DPLL(t[degree+3],assignment,degree*degree,3,&times)){   //判断随机填充过一些数字的棋盘是否有解
			for(i=0;i<degree*degree;i++)
			    if(assignment[i]==-1) assignment[i]=rand()%2;      //有解则将满足的这一组真值指派放入assignment数组中，对于指派中待定的随机填
			for(i=0;i<degree+4;i++)
			    destroyCNF(t[i]);
			break;
		}
		else{                                                       //若无解则销毁这一次所用到的所有CNF公式，并进入下一次循环
			for(i=0;i<degree+4;i++)
			    destroyCNF(t[i]);
		}
	}while(1);
	return p;
}

/*功能：挖洞的第一步，剔除掉‘101’和‘010’中间的数字以及‘1001’和‘0110’两边的数字
        同时顺序生成其他未挖掉的空的编号并补充到CNF公式p中，如果mode=2，则不进行第二步
  输入：二进制数独棋盘阶数degree、模式mode、约束CNF公式p、数独终盘assignment
  输出：补充后的CNF公式p*/
int complement(int degree,int mode,cnf p,int *assignment){
	int a[degree][degree],i,j,chosen[degree*degree],o;
	for(i=0;i<degree;i++)
	    for(j=0;j<degree;j++)
	        a[i][j]=assignment[i*degree+j];                //把真值指派变换成二维数组，方便后续操作
	for(i=0;i<degree;i++)
		for(j=0;j<degree-1;j++)
			if(a[i][j]!=-1 && a[i][j]==a[i][j+1]){
				if(j-1>=0) a[i][j-1]=-1;                   //剔除掉每一列中‘1001’和‘0110’两边的数字
				if(j+2<degree) a[i][j+2]=-1;
			}
	for(i=0;i<degree-1;i++)
		for(j=0;j<degree;j++)
			if(a[i][j]!=-1 && a[i][j]==a[i+1][j]){
				if(i-1>=0) a[i-1][j]=-1;                   //剔除掉每一行中‘1001’和‘0110’两边的数字
				if(i+2<degree) a[i+2][j]=-1;
			}
	for(i=0;i<degree-2;i++)
		for(j=0;j<degree;j++)
			if(a[i][j]!=-1 && a[i][j]==a[i+2][j])          //剔除掉每一行中‘101’和‘010’中间的数字
			    a[i+1][j]=-1;
	for(i=0;i<degree;i++)
		for(j=0;j<degree-2;j++)
			if(a[i][j]!=-1 && a[i][j]==a[i][j+2])          //剔除掉每一列中‘101’和‘010’中间的数字
			    a[i][j+1]=-1;
	for(i=0;i<degree;i++)
	    for(j=0;j<degree;j++){
	    	if(a[i][j]==0 || a[i][j]==1)                   //将以上未剔除的数字的编号按顺序排列并以单子句的形式加入CNF公式中
	    		chosen[i*degree+j]=0;
			else chosen[i*degree+j]=1;
	    	assignment[i*degree+j]=a[i][j];
		}
	int n_tochoose=0;
	if(mode==2){                                           //对于12阶的二进制数独，不进行以下操作（挖洞的第二步），用mode变量来指示
		for(o=0;o<degree*degree;o++){
			if(!chosen[o]){
				n_tochoose++;
				if(!assignment[o])
				    addrestriction(p,-o-1);
				else
				    addrestriction(p,o+1);
			}
		}
	}
	return n_tochoose;
}

/*功能：判断第一步挖洞后剩余的数字是否可以挖去，若可则挖去
  输入：二进制数独棋盘的阶数degree、经过挖洞第一步后的棋盘puzzle、剩余数字数n
  输出：挖洞彻底结束后的棋盘puzzle*/
void digHole(int degree,cnf p,int *puzzle,int n){
	conjunct c=p;
	int i,occupation_times,tmp;
	int *occupation_assign=malloc(degree*degree*sizeof(int));
	for(i=0;i<1;i++){
		tmp=c->next->C->next->ele;
		removeClause(p,c);
		cnf p_=addUnitClause(p,-tmp);                                             //将一个空翻转
		if(DPLL(p_,occupation_assign,degree*degree,3,&occupation_times)==0){      //判断翻转后是否有解
			puzzle[abs(tmp)-1]=-1;                                                //若无解则证明挖去后仍可以保证唯一解
		}
		else
			addrestriction(p,tmp);                                                //若有解则证明不可挖去
		destroyCNF(p_);
	}
}


/*功能：生成一个具有唯一解的二进制数独棋盘
  输入：二进制数独棋盘的阶数degree、挖洞模式mode
  输出：数独终盘assignment、数独棋盘puzzle*/
cnf PuzzleWithOnlySolution(int degree,int mode,int *assignment,int *puzzle){
	cnf p=RandomFilled(degree,assignment);                                         //先得到一个数独终盘
	int i;
	for(i=0;i<degree*degree;i++)
	    puzzle[i]=assignment[i];
	int n=complement(degree,mode,p,puzzle);                                        //进行第一步挖洞并为第二步作准备
	digHole(degree,p,puzzle,n);                                                    //进行第二部挖洞
	return p;
}
