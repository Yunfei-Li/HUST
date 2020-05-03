#include "SudokuCNF.h"

/*功能：返回一个degree阶二进制数独棋盘第row行第column列对应的编号
  输入：二进制数独棋盘阶数degree、行数row和列数column
  输出：对应编号*/
int order(int degree,int row,int column){
	return (row-1)*degree+column;
}

/*功能：在一个CNF公式中增加一个单子句k
  输入：CNF公式p、文字k
  输出|增加后的CNF公式p*/
void addrestriction(cnf p,int k){
	conjunct tmp=p->next;
	p->next=malloc(sizeof(struct clause));
	p->next->next=tmp;
	p->next->C=malloc(sizeof(struct node));
	p->next->C->next=NULL;
	Literal L=p->next->C;
	L->next=malloc(sizeof(struct node));
	L=L->next;
	L->ele=k;
	L->next=NULL;
}

/*功能：在一个CNF公式中增加一个子句，子句以一个数组形式传入
  输入：CNF公式p、数组名a、数组长度n
  输出|增加后的CNF公式p*/
void addClause(cnf p,int *a,int n){
	conjunct tmp=p->next;
	p->next=malloc(sizeof(struct clause));
	p->next->next=tmp;
	p->next->C=malloc(sizeof(struct node));
	p->next->C->next=NULL;
	Literal L=p->next->C;
	int i;
	for(i=0;i<n;i++){
		L->next=malloc(sizeof(struct node));
		L=L->next;
		L->ele=a[i];
		L->next=NULL;
	}
}

/*功能：创建一个CNF公式，其中包含二进制数独游戏规则所对应的所有约束子句
  输入：二进制数独棋盘阶数degree
  输出：CNF公式p*/
cnf createSudokuCNF(int degree){
	cnf p=malloc(sizeof(struct clause));
	p->next=NULL;
	addClauses_rule1(p,degree);
	addClauses_rule2(p,degree);
	addClauses_rule3(p,degree);
	return p;
}

/*功能：在一个CNF公式增加二进制数独棋盘规则一所对应的所有约束子句
  输入：CNF公式p、二进制数独棋盘阶数degree
  输出：增加约束后的CNF公式p*/
void addClauses_rule1(cnf p,int degree){
	int row,column,i;
	int a[3];
	for(row=1;row<=degree;row++){
		for(column=1;column<=degree-2;column++){
			for(i=0;i<3;i++)
			    a[i]=order(degree,row,column+i);
			addClause(p,a,3);
			for(i=0;i<3;i++)
			    a[i]=-order(degree,row,column+i);
			addClause(p,a,3);
		}
	}
	for(column=1;column<=degree;column++){
		for(row=1;row<=degree-2;row++){
			for(i=0;i<3;i++)
			    a[i]=order(degree,row+i,column);
			addClause(p,a,3);
			for(i=0;i<3;i++)
			    a[i]=-order(degree,row+i,column);
			addClause(p,a,3);
		}
	}
}

/*功能：在一个CNF公式中增加二进制数独规则二所对应的所有约束子句
  输入：CNF公式p、二进制数独棋盘阶数degree
  输出：增加约束后的CNF公式p*/
void addClauses_rule2(cnf p,int degree){
	switch(degree){
		case 4:
		    addClauses_rule2_4(p);
		    break;
		case 6:
			addClauses_rule2_6(p);
			break;
		case 8:
			addClauses_rule2_8(p);
			break;
		case 10:
			addClauses_rule2_10(p);
			break;
		case 12:
			addClauses_rule2_12(p);
			break;
		case 14:
			addClauses_rule2_14(p);
			break;
	}
}

/*功能：在一个CNF公式中增加二进制数独规则三所对应的所有约束子句
  输入：CNF公式p、二进制数独棋盘阶数degree
  输出：增加约束后的CNF公式p*/
void addClauses_rule3(cnf p,int degree){
	switch(degree){
		case 4:
		    addClauses_rule3_4(p);
		    break;
		case 6:
		    addClauses_rule3_6(p);
			break;
		case 8:
		    addClauses_rule3_8(p);
		    break;
		case 10:
			addClauses_rule3_10(p);
			break;
		case 12:
			addClauses_rule3_12(p);
			break;
		case 14:
			addClauses_rule3_14(p);
			break;
	}
}

/*功能：在一个CNF公式中增加一个四阶二进制数独规则二所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule2_4(cnf p){
	int column[3],row[3];
	int _row,_column;
	int a[3];
	for(_row=1;_row<=4;_row++){
		for(column[0]=1;column[0]<=2;column[0]++){
			for(column[1]=column[0]+1;column[1]<=3;column[1]++){
				for(column[2]=column[1]+1;column[2]<=4;column[2]++){
					a[0]=order(4,_row,column[0]);
					a[1]=order(4,_row,column[1]);
					a[2]=order(4,_row,column[2]);
					addClause(p,a,3);
					a[0]=-order(4,_row,column[0]);
					a[1]=-order(4,_row,column[1]);
					a[2]=-order(4,_row,column[2]);
					addClause(p,a,3);
				}
			}
		}
	}
	for(_column=1;_column<=4;_column++){
		for(row[0]=1;row[0]<=2;row[0]++){
			for(row[1]=row[0]+1;row[1]<=3;row[1]++){
				for(row[2]=row[1]+1;row[2]<=4;row[2]++){
					a[0]=order(4,row[0],_column);
					a[1]=order(4,row[1],_column);
					a[2]=order(4,row[2],_column);
					addClause(p,a,3);
					a[0]=-order(4,row[0],_column);
					a[1]=-order(4,row[1],_column);
					a[2]=-order(4,row[2],_column);
					addClause(p,a,3);
				}
			}
		}
	}
}

/*功能：在一个CNF公式中增加一个六阶二进制数独规则二所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule2_6(cnf p){
	int column[4],row[4];
	int _row,_column;
	int a[4];
	for(_row=1;_row<=6;_row++){
		for(column[0]=1;column[0]<=3;column[0]++){
			for(column[1]=column[0]+1;column[1]<=4;column[1]++){
				for(column[2]=column[1]+1;column[2]<=5;column[2]++){
					for(column[3]=column[2]+1;column[3]<=6;column[3]++){
						a[0]=order(6,_row,column[0]);
						a[1]=order(6,_row,column[1]);
						a[2]=order(6,_row,column[2]);
						a[3]=order(6,_row,column[3]);
						addClause(p,a,4);
						a[0]=-order(6,_row,column[0]);
						a[1]=-order(6,_row,column[1]);
						a[2]=-order(6,_row,column[2]);
						a[3]=-order(6,_row,column[3]);
						addClause(p,a,4);
				    }
				}
			}
		}
	}
	for(_column=1;_column<=6;_column++){
		for(row[0]=1;row[0]<=3;row[0]++){
			for(row[1]=row[0]+1;row[1]<=4;row[1]++){
				for(row[2]=row[1]+1;row[2]<=5;row[2]++){
					for(row[3]=row[2]+1;row[3]<=6;row[3]++){
						a[0]=order(6,row[0],_column);
						a[1]=order(6,row[1],_column);
						a[2]=order(6,row[2],_column);
						a[3]=order(6,row[3],_column);
						addClause(p,a,4);
						a[0]=-order(6,row[0],_column);
						a[1]=-order(6,row[1],_column);
						a[2]=-order(6,row[2],_column);
						a[3]=-order(6,row[3],_column);
						addClause(p,a,4);
				    }
				}
			}
		}
	}
}

/*功能：在一个CNF公式中增加一个八阶二进制数独规则二所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule2_8(cnf p){
	int column[5],row[5];
	int _row,_column;
	int a[5];
	for(_row=1;_row<=8;_row++){
		for(column[0]=1;column[0]<=4;column[0]++){
			for(column[1]=column[0]+1;column[1]<=5;column[1]++){
				for(column[2]=column[1]+1;column[2]<=6;column[2]++){
					for(column[3]=column[2]+1;column[3]<=7;column[3]++){
						for(column[4]=column[3]+1;column[4]<=8;column[4]++){
							a[0]=order(8,_row,column[0]);
							a[1]=order(8,_row,column[1]);
							a[2]=order(8,_row,column[2]);
							a[3]=order(8,_row,column[3]);
							a[4]=order(8,_row,column[4]);
							addClause(p,a,5);
							a[0]=-order(8,_row,column[0]);
							a[1]=-order(8,_row,column[1]);
							a[2]=-order(8,_row,column[2]);
							a[3]=-order(8,_row,column[3]);
							a[4]=-order(8,_row,column[4]);
							addClause(p,a,5);
					    }
				    }
				}
			}
		}
	}
	for(_column=1;_column<=8;_column++){
		for(row[0]=1;row[0]<=4;row[0]++){
			for(row[1]=row[0]+1;row[1]<=5;row[1]++){
				for(row[2]=row[1]+1;row[2]<=6;row[2]++){
					for(row[3]=row[2]+1;row[3]<=7;row[3]++){
						for(row[4]=row[3]+1;row[4]<=8;row[4]++){
							a[0]=order(8,row[0],_column);
							a[1]=order(8,row[1],_column);
							a[2]=order(8,row[2],_column);
							a[3]=order(8,row[3],_column);
							a[4]=order(8,row[4],_column);
							addClause(p,a,5);
							a[0]=-order(8,row[0],_column);
							a[1]=-order(8,row[1],_column);
							a[2]=-order(8,row[2],_column);
							a[3]=-order(8,row[3],_column);
							a[4]=-order(8,row[4],_column);
							addClause(p,a,5);
					    }
				    }
				}
			}
		}
	}
}

/*功能：在一个CNF公式中增加一个十阶二进制数独规则二所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule2_10(cnf p){
	int column[6],row[6];
	int _row,_column;
	int a[6];
	for(_row=1;_row<=10;_row++){
		for(column[0]=1;column[0]<=5;column[0]++){
			for(column[1]=column[0]+1;column[1]<=6;column[1]++){
				for(column[2]=column[1]+1;column[2]<=7;column[2]++){
					for(column[3]=column[2]+1;column[3]<=8;column[3]++){
						for(column[4]=column[3]+1;column[4]<=9;column[4]++){
							for(column[5]=column[4]+1;column[5]<=10;column[5]++){
								a[0]=order(10,_row,column[0]);
								a[1]=order(10,_row,column[1]);
								a[2]=order(10,_row,column[2]);
								a[3]=order(10,_row,column[3]);
								a[4]=order(10,_row,column[4]);
								a[5]=order(10,_row,column[5]);
								addClause(p,a,6);
								a[0]=-order(10,_row,column[0]);
								a[1]=-order(10,_row,column[1]);
								a[2]=-order(10,_row,column[2]);
								a[3]=-order(10,_row,column[3]);
								a[4]=-order(10,_row,column[4]);
								a[5]=-order(10,_row,column[5]);
								addClause(p,a,6);
						    }
					    }
				    }
				}
			}
		}
	}
	for(_column=1;_column<=10;_column++){
		for(row[0]=1;row[0]<=5;row[0]++){
			for(row[1]=row[0]+1;row[1]<=6;row[1]++){
				for(row[2]=row[1]+1;row[2]<=7;row[2]++){
					for(row[3]=row[2]+1;row[3]<=8;row[3]++){
						for(row[4]=row[3]+1;row[4]<=9;row[4]++){
							for(row[5]=row[4]+1;row[5]<=10;row[5]++){
								a[0]=order(10,row[0],_column);
								a[1]=order(10,row[1],_column);
								a[2]=order(10,row[2],_column);
								a[3]=order(10,row[3],_column);
								a[4]=order(10,row[4],_column);
								a[5]=order(10,row[5],_column);
								addClause(p,a,6);
								a[0]=-order(10,row[0],_column);
								a[1]=-order(10,row[1],_column);
								a[2]=-order(10,row[2],_column);
								a[3]=-order(10,row[3],_column);
								a[4]=-order(10,row[4],_column);
								a[5]=-order(10,row[5],_column);
								addClause(p,a,6);
						    }
					    }
				    }
				}
			}
		}
	}
}

/*功能：在一个CNF公式中增加一个十二阶二进制数独规则二所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule2_12(cnf p){
	int column[7],row[7];
	int _row,_column;
	int a[7];
	for(_row=1;_row<=12;_row++){
		for(column[0]=1;column[0]<=6;column[0]++){
			for(column[1]=column[0]+1;column[1]<=7;column[1]++){
				for(column[2]=column[1]+1;column[2]<=8;column[2]++){
					for(column[3]=column[2]+1;column[3]<=9;column[3]++){
						for(column[4]=column[3]+1;column[4]<=10;column[4]++){
							for(column[5]=column[4]+1;column[5]<=11;column[5]++){
								for(column[6]=column[5]+1;column[6]<=12;column[6]++){
									a[0]=order(12,_row,column[0]);
									a[1]=order(12,_row,column[1]);
									a[2]=order(12,_row,column[2]);
									a[3]=order(12,_row,column[3]);
									a[4]=order(12,_row,column[4]);
									a[5]=order(12,_row,column[5]);
									a[6]=order(12,_row,column[6]);
									addClause(p,a,7);
									a[0]=-order(12,_row,column[0]);
									a[1]=-order(12,_row,column[1]);
									a[2]=-order(12,_row,column[2]);
									a[3]=-order(12,_row,column[3]);
									a[4]=-order(12,_row,column[4]);
									a[5]=-order(12,_row,column[5]);
									a[6]=-order(12,_row,column[6]);
									addClause(p,a,7);
								}
						    }
					    }
				    }
				}
			}
		}
	}
	for(_column=1;_column<=10;_column++){
		for(row[0]=1;row[0]<=6;row[0]++){
			for(row[1]=row[0]+1;row[1]<=7;row[1]++){
				for(row[2]=row[1]+1;row[2]<=8;row[2]++){
					for(row[3]=row[2]+1;row[3]<=9;row[3]++){
						for(row[4]=row[3]+1;row[4]<=10;row[4]++){
							for(row[5]=row[4]+1;row[5]<=11;row[5]++){
								for(row[6]=row[5]+1;row[6]<=12;row[6]++){
									a[0]=order(12,row[0],_column);
									a[1]=order(12,row[1],_column);
									a[2]=order(12,row[2],_column);
									a[3]=order(12,row[3],_column);
									a[4]=order(12,row[4],_column);
									a[5]=order(12,row[5],_column);
									a[6]=order(12,row[6],_column);
									addClause(p,a,7);
									a[0]=-order(12,row[0],_column);
									a[1]=-order(12,row[1],_column);
									a[2]=-order(12,row[2],_column);
									a[3]=-order(12,row[3],_column);
									a[4]=-order(12,row[4],_column);
									a[5]=-order(12,row[5],_column);
									a[6]=-order(12,row[6],_column);
									addClause(p,a,7);
								} 
						    }
					    }
				    }
				}
			}
		}
	}
}

/*功能：在一个CNF公式中增加一个十四阶二进制数独规则二所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule2_14(cnf p){
	int column[8],row[8];
	int _row,_column;
	int a[8];
	for(_row=1;_row<=14;_row++){
		for(column[0]=1;column[0]<=7;column[0]++){
			for(column[1]=column[0]+1;column[1]<=8;column[1]++){
				for(column[2]=column[1]+1;column[2]<=9;column[2]++){
					for(column[3]=column[2]+1;column[3]<=10;column[3]++){
						for(column[4]=column[3]+1;column[4]<=11;column[4]++){
							for(column[5]=column[4]+1;column[5]<=12;column[5]++){
								for(column[6]=column[5]+1;column[6]<=13;column[6]++){
									for(column[7]=column[6]+1;column[7]<=14;column[7]++){
										a[0]=order(14,_row,column[0]);
										a[1]=order(14,_row,column[1]);
										a[2]=order(14,_row,column[2]);
										a[3]=order(14,_row,column[3]);
										a[4]=order(14,_row,column[4]);
										a[5]=order(14,_row,column[5]);
										a[6]=order(14,_row,column[6]);
										a[7]=order(14,_row,column[7]);
										addClause(p,a,8);
										a[0]=-order(14,_row,column[0]);
										a[1]=-order(14,_row,column[1]);
										a[2]=-order(14,_row,column[2]);
										a[3]=-order(14,_row,column[3]);
										a[4]=-order(14,_row,column[4]);
										a[5]=-order(14,_row,column[5]);
										a[6]=-order(14,_row,column[6]);
										a[7]=-order(14,_row,column[7]);
										addClause(p,a,8);
									}
								}
						    }
					    }
				    }
				}
			}
		}
	}
	for(_column=1;_column<=14;_column++){
		for(row[0]=1;row[0]<=7;row[0]++){
			for(row[1]=row[0]+1;row[1]<=8;row[1]++){
				for(row[2]=row[1]+1;row[2]<=9;row[2]++){
					for(row[3]=row[2]+1;row[3]<=10;row[3]++){
						for(row[4]=row[3]+1;row[4]<=11;row[4]++){
							for(row[5]=row[4]+1;row[5]<=12;row[5]++){
								for(row[6]=row[5]+1;row[6]<=13;row[6]++){
									for(row[7]=row[6]+1;row[7]<=14;row[7]++){
										a[0]=order(14,row[0],_column);
										a[1]=order(14,row[1],_column);
										a[2]=order(14,row[2],_column);
										a[3]=order(14,row[3],_column);
										a[4]=order(14,row[4],_column);
										a[5]=order(14,row[5],_column);
										a[6]=order(14,row[6],_column);
										a[7]=order(14,row[7],_column);
										addClause(p,a,8);
										a[0]=-order(14,row[0],_column);
										a[1]=-order(14,row[1],_column);
										a[2]=-order(14,row[2],_column);
										a[3]=-order(14,row[3],_column);
										a[4]=-order(14,row[4],_column);
										a[5]=-order(14,row[5],_column);
										a[6]=-order(14,row[6],_column);
										a[7]=-order(14,row[7],_column);
										addClause(p,a,8);
									}
								}
						    }
					    }
				    }
				}
			}
		}
	}
}

/*功能：在一个CNF公式中增加一个四阶二进制数独规则三所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule3_4(cnf p){
	int flag[4],a[8];
	int row1,row2,column1,column2,i;
	for(row1=1;row1<=3;row1++){
		for(row2=row1+1;row2<=4;row2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(i=0;i<4;i++){
				                if(flag[i]){
									a[2*i]=order(4,row1,i+1);
									a[2*i+1]=order(4,row2,i+1);
								}
								else{
									a[2*i]=-order(4,row1,i+1);
									a[2*i+1]=-order(4,row2,i+1);
								}
							}
							addClause(p,a,8);
			            }
			        }
			    }
		    }
		}
	}
	for(column1=1;column1<=3;column1++){
		for(column2=column1+1;column2<=4;column2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(i=0;i<4;i++){
				                if(flag[i]){
									a[2*i]=order(4,i+1,column1);
									a[2*i+1]=order(4,i+1,column2);
								}
								else{
									a[2*i]=-order(4,i+1,column1);
									a[2*i+1]=-order(4,i+1,column2);
								}
							}
							addClause(p,a,8);
			            }
			        }
			    }
		    }
		}
	}
}

/*功能：在一个CNF公式中增加一个六阶二进制数独规则三所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule3_6(cnf p){
	int flag[6],a[12];
	int row1,row2,column1,column2,i;
	for(row1=1;row1<=5;row1++){
		for(row2=row1+1;row2<=6;row2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(i=0;i<6;i++){
				                        if(flag[i]){
											a[2*i]=order(6,row1,i+1);
											a[2*i+1]=order(6,row2,i+1);
										}
										else{
											a[2*i]=-order(6,row1,i+1);
											a[2*i+1]=-order(6,row2,i+1);
										}
									}
									addClause(p,a,12);
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
	for(column1=1;column1<=5;column1++){
		for(column2=column1+1;column2<=6;column2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(i=0;i<6;i++){
				                        if(flag[i]){
											a[2*i]=order(6,i+1,column1);
											a[2*i+1]=order(6,i+1,column2);
										}
										else{
											a[2*i]=-order(6,i+1,column1);
											a[2*i+1]=-order(6,i+1,column2);
										}
									}
									addClause(p,a,12);
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
}

/*功能：在一个CNF公式中增加一个八阶二进制数独规则三所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule3_8(cnf p){
	int flag[8],a[16];
	int row1,row2,column1,column2,i;
	for(row1=1;row1<=7;row1++){
		for(row2=row1+1;row2<=8;row2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(flag[6]=0;flag[6]<2;flag[6]++){
				                        for(flag[7]=0;flag[7]<2;flag[7]++){
				                            for(i=0;i<8;i++){
				                            	if(flag[i]){
												    a[2*i]=order(8,row1,i+1);
												    a[2*i+1]=order(8,row2,i+1);
												}
												else{
													a[2*i]=-order(8,row1,i+1);
												    a[2*i+1]=-order(8,row2,i+1);
												}
											}
											addClause(p,a,16);
			                            }
			                        }
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
	for(column1=1;column1<=7;column1++){
		for(column2=column1+1;column2<=8;column2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(flag[6]=0;flag[6]<2;flag[6]++){
				                        for(flag[7]=0;flag[7]<2;flag[7]++){
				                            for(i=0;i<8;i++){
				                            	if(flag[i]){
												    a[2*i]=order(8,i+1,column1);
												    a[2*i+1]=order(8,i+1,column2);
												}
												else{
													a[2*i]=-order(8,i+1,column1);
												    a[2*i+1]=-order(8,i+1,column2);
												}
											}
											addClause(p,a,16);
			                            }
			                        }
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
}

/*功能：在一个CNF公式中增加一个十阶二进制数独规则三所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule3_10(cnf p){
	int flag[10],a[20];
	int row1,row2,column1,column2,i;
	for(row1=1;row1<=9;row1++){
		for(row2=row1+1;row2<=10;row2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(flag[6]=0;flag[6]<2;flag[6]++){
				                        for(flag[7]=0;flag[7]<2;flag[7]++){
				                        	for(flag[8]=0;flag[8]<2;flag[8]++){
				                        		for(flag[9]=0;flag[9]<2;flag[9]++){
						                            for(i=0;i<10;i++){
						                            	if(flag[i]){
														    a[2*i]=order(10,row1,i+1);
														    a[2*i+1]=order(10,row2,i+1);
														}
														else{
															a[2*i]=-order(10,row1,i+1);
														    a[2*i+1]=-order(10,row2,i+1);
														}
													}
													addClause(p,a,20);
												}
											}
			                            }
			                        }
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
	for(column1=1;column1<=9;column1++){
		for(column2=column1+1;column2<=10;column2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(flag[6]=0;flag[6]<2;flag[6]++){
				                        for(flag[7]=0;flag[7]<2;flag[7]++){
				                        	for(flag[8]=0;flag[8]<2;flag[8]++){
				                        		for(flag[9]=0;flag[9]<2;flag[9]++){
						                            for(i=0;i<10;i++){
						                            	if(flag[i]){
														    a[2*i]=order(10,i+1,column1);
														    a[2*i+1]=order(10,i+1,column2);
														}
														else{
															a[2*i]=-order(10,i+1,column1);
														    a[2*i+1]=-order(10,i+1,column2);
														}
													}
													addClause(p,a,20);
												}
											}
			                            }
			                        }
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
}

/*功能：在一个CNF公式中增加一个十二阶二进制数独规则三所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule3_12(cnf p){
	int flag[12],a[24];
	int row1,row2,column1,column2,i;
	for(row1=1;row1<=11;row1++){
		for(row2=row1+1;row2<=12;row2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(flag[6]=0;flag[6]<2;flag[6]++){
				                        for(flag[7]=0;flag[7]<2;flag[7]++){
				                        	for(flag[8]=0;flag[8]<2;flag[8]++){
				                        		for(flag[9]=0;flag[9]<2;flag[9]++){
				                        			for(flag[10]=0;flag[10]<2;flag[10]++){
				                        				for(flag[11]=0;flag[11]<2;flag[11]++){
								                            for(i=0;i<12;i++){
								                            	if(flag[i]){
																    a[2*i]=order(12,row1,i+1);
																    a[2*i+1]=order(12,row2,i+1);
																}
																else{
																	a[2*i]=-order(12,row1,i+1);
																    a[2*i+1]=-order(12,row2,i+1);
																}
															}
															addClause(p,a,24);
														}
													}
												}
											}
			                            }
			                        }
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
	for(column1=1;column1<=11;column1++){
		for(column2=column1+1;column2<=12;column2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(flag[6]=0;flag[6]<2;flag[6]++){
				                        for(flag[7]=0;flag[7]<2;flag[7]++){
				                        	for(flag[8]=0;flag[8]<2;flag[8]++){
				                        		for(flag[9]=0;flag[9]<2;flag[9]++){
				                        			for(flag[10]=0;flag[10]<2;flag[10]++){
				                        				for(flag[11]=0;flag[11]<2;flag[11]++){
								                            for(i=0;i<12;i++){
								                            	if(flag[i]){
																    a[2*i]=order(12,i+1,column1);
																    a[2*i+1]=order(12,i+1,column2);
																}
																else{
																	a[2*i]=-order(12,i+1,column1);
																    a[2*i+1]=-order(12,i+1,column2);
																}
															}
															addClause(p,a,24);
														}
													}
												}
											}
			                            }
			                        }
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
}

/*功能：在一个CNF公式中增加一个十四阶二进制数独规则三所对应的所有约束子句
  输入：CNF公式p
  输出：增加约束后的CNF公式p*/
void addClauses_rule3_14(cnf p){
	int flag[14],a[28];
	int row1,row2,column1,column2,i;
	for(row1=1;row1<=13;row1++){
		for(row2=row1+1;row2<=14;row2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(flag[6]=0;flag[6]<2;flag[6]++){
				                        for(flag[7]=0;flag[7]<2;flag[7]++){
				                        	for(flag[8]=0;flag[8]<2;flag[8]++){
				                        		for(flag[9]=0;flag[9]<2;flag[9]++){
				                        			for(flag[10]=0;flag[10]<2;flag[10]++){
				                        				for(flag[11]=0;flag[11]<2;flag[11]++){
				                        					for(flag[12]=0;flag[12]<2;flag[12]++){
				                        						for(flag[13]=0;flag[13]<2;flag[13]++){
										                            for(i=0;i<12;i++){
										                            	if(flag[i]){
																		    a[2*i]=order(14,row1,i+1);
																		    a[2*i+1]=order(14,row2,i+1);
																		}
																		else{
																			a[2*i]=-order(14,row1,i+1);
																		    a[2*i+1]=-order(14,row2,i+1);
																		}
																	}
																	addClause(p,a,28);
																}
															}
														}
													}
												}
											}
			                            }
			                        }
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
	for(column1=1;column1<=13;column1++){
		for(column2=column1+1;column2<=14;column2++){
			for(flag[0]=0;flag[0]<2;flag[0]++){
				for(flag[1]=0;flag[1]<2;flag[1]++){
				    for(flag[2]=0;flag[2]<2;flag[2]++){
				        for(flag[3]=0;flag[3]<2;flag[3]++){
				            for(flag[4]=0;flag[4]<2;flag[4]++){
				                for(flag[5]=0;flag[5]<2;flag[5]++){
				                    for(flag[6]=0;flag[6]<2;flag[6]++){
				                        for(flag[7]=0;flag[7]<2;flag[7]++){
				                        	for(flag[8]=0;flag[8]<2;flag[8]++){
				                        		for(flag[9]=0;flag[9]<2;flag[9]++){
				                        			for(flag[10]=0;flag[10]<2;flag[10]++){
				                        				for(flag[11]=0;flag[11]<2;flag[11]++){
				                        					for(flag[12]=0;flag[12]<2;flag[12]++){
				                        						for(flag[13]=0;flag[13]<2;flag[13]++){
										                            for(i=0;i<12;i++){
										                            	if(flag[i]){
																		    a[2*i]=order(14,i+1,column1);
																		    a[2*i+1]=order(14,i+1,column2);
																		}
																		else{
																			a[2*i]=-order(14,i+1,column1);
																		    a[2*i+1]=-order(14,i+1,column2);
																		}
																	}
																	addClause(p,a,28);
																}
															}
														}
													}
												}
											}
			                            }
			                        }
			                    }
			                }
			            }
			        }
			    }
		    }
		}
	}
}