/*功能：利用非递归结构的DPLL算法求解SAT问题
  输入：一个CNF公式c
  输出：是否可满足、可满足时的一组真值指派assignment*/
int DPLL_nonRecursive(cnf_i c,int *assignment){
	int layer=1;
	int k;
	int *a=malloc(c->NOV*sizeof(int));              //数组a用于标记每一决策层选取的变元
	int *b=malloc(c->NOV*sizeof(int));              //数组b用于标记每一决策层是否翻转过
	int *s=malloc(c->NOV*sizeof(int));              //数组s用于标记单子句规则得到的决策
	for(k=0;k<c->NOV;k++){
		a[k]=0;
		b[k]=0;
		s[k]=0;
	}
	int flag=1;                                     //flag变量用于标记是回退还是进行下一层决策
	int check,check_;
	while(layer>0 && layer<=c->NOV){                //当回退到第0层的时候证明这个CNF公式不可满足
		if(!flag){                                  //flag=0代表这是一次回退
			retract(c,layer,a[layer-1]);            //撤销第layer决策层
			if(s[layer-1]){                         //如果这是单子句规则得到的决策，则不需要进行翻转，直接判定继续回退
				assignment[abs(a[layer-1])-1]=0;
			    s[layer-1]=0;
				a[layer-1]=0;
				b[layer-1]=0;
				layer--;	
			}
			else if(b[layer-1]){                    //如果这已经是这一决策层的第二次回退了，则不需要再翻转了，直接判定继续回退
				assignment[abs(a[layer-1])-1]=0;
				a[layer-1]=0;
				b[layer-1]=0;
				layer--;
			}
			else{                                   //以上两个条件均不满足，对这一决策层进行翻转
				a[layer-1]=-a[layer-1];
				assignment[abs(a[layer-1])-1]=a[layer-1];
				b[layer-1]=1;
				clearLiteral_2(c,layer,a[layer-1]);
				check=checkCNF(c);
				if(check==UNSATISFIED){             //翻转后仍不满足，则撤销翻转操作，并判定回退
					retract(c,layer,a[layer-1]);
					assignment[abs(a[layer-1])-1]=0;
					a[layer-1]=0;
					b[layer-1]=0;
					flag=0;
					layer--;
				}
				else if(check==SATISFIED)     
					return TRUE;
				else{                               //翻转后待定，进入下一决策层
					flag=1;
					layer++;
				}
			}
		}
		else{                                       //flag=1代表这是一次决策，不是回退
		    k=FindUnitClause_2(c);                  //判定c中是否存在单子句
		    if(k)
		        s[layer-1]=1;                       //若存在单子句，则拿单子句作为决策，同时做上标记
		    else
		    	k=RandomStrategy(c);                //若不存在标记，则选取第一个未满足子句的第一个变元作为决策
			assignment[abs(k)-1]=k;
		    a[layer-1]=k;
		    clearLiteral_2(c,layer,a[layer-1]);
		    check=checkCNF(c);
		    if(check==UNSATISFIED){                 //决策后不满足
		    	retract(c,layer,a[layer-1]);
		    	assignment[abs(k)-1]=-k;
		    	a[layer-1]=-k;                      //对这一层的决策进行翻转
		    	b[layer-1]=1;
		    	clearLiteral_2(c,layer,a[layer-1]);
		    	check_=checkCNF(c);
		    	if(check_==UNSATISFIED){            //翻转后仍不满足，撤销翻转，并判定回退
		    		retract(c,layer,a[layer-1]);
		    		assignment[abs(k)-1]=0;
		    		a[layer-1]=0;
		    		b[layer-1]=0;
		    		flag=0;
		    		layer--;
				}
				else if(check_==SATISFIED)
			        return TRUE;
			    else
			    	layer++;
			}
			else if(check==SATISFIED)
			    return TRUE;
			else
				layer++;
		}
	}
	return FALSE;
}
