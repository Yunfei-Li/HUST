.386
STACK   SEGMENT USE16   STACK
        DB  200 DUP(0)
STACK   ENDS

DATA    SEGMENT USE16
BNAME   DB  'LI YONGKANG',0
NLENGTH EQU 11
BPASS   DB  'LOVECS',0
PLENGTH EQU 6
AUTH    DB  0
GOOD    DW  0
N       EQU 30
SNAME   DB  'ASMSHOP',0
GA1     DB  'EDITOR', 4 DUP(0), 10
		DW  35, 56, 70, 25, ?
GA2     DB  'BAG', 7 DUP(0), 9
		DW  12, 30, 25, 5, ?
GA3     DB  'PEN', 7 DUP(0), 8
		DW  50, 70, 65535, 0, ?
GAN     DB  N-3 DUP('TEMPVALUE', 0, 8, 15, 0, 20, 0, 30, 0, 2, 0, ?, ?)

GLENGTH EQU 21

CRLF    DB  0DH,0AH,'$'
FORMAT  DB  '                                      ',0AH
		DB  '----------Welcome to ASMSHOP----------',0AH,'$'
CSTM	DB  'Current User: Customer',0AH,'$'
BOSS    DB  'Current User: LI YONGKANG',0AH,'$'
BRSING  DB  'You are browsing ','$'
MENU    DB  '--------------------------------------',0AH
		DB  '|             MAIN MENU              |',0AH
		DB  '|                                    |',0AH
		DB  '|             1.log in               |',0AH
		DB  '|        2.search commodities        |',0AH
		DB  '|         3.place an order           |',0AH
		DB  '|      4.compute recommendation      |',0AH
		DB  '|          5.update rankings         |',0AH
		DB  '|         6.update information       |',0AH
		DB  '| 7.migrate to operation environment |',0AH
		DB  '| 8.display the offset address of CS |',0AH
		DB  '|          9.exit the system         |',0AH
		DB  '--------------------------------------',0AH,'$'
CHOICE  DB  0
        DB  'Please choose a function:','$'
LOGIN   DB  'You have not logged in yet.',0AH
        DB  'Please log in first.',0AH,'$'
NAMEH   DB  'Please input your name:$'
IN_NAME DB  25
        DB  ?
		DB  25 DUP(0)
PWDH    DB  'Please inpur your password:$'
IN_PWD  DB  40
        DB  ?
		DB  40 DUP(0)
SRCH    DB  'Please inpur your name of the commodity you are going to search:$'
IN_SRC  DB  20
        DB  ?
		DB  20 DUP(0)

SUCCESS DB  'You have logged in successfully!',0AH,'$'
RPT     DB  'You have already logged in. Do not repeate.',0AH,'$'
SORRY   DB  'Sorry, this function is waiting for implementation.',0AH,'$'
AGAIN   DB  'Invalid input, please make your choice again:','$'
WNH     DB  'Wrong Username, unable to log in.',0AH
		DB  'Please log in again.',0AH,'$'
WPH     DB  'Wrong Password, unable to log in.',0AH
		DB  'Please log in again.',0AH,'$'
NFOUND  DB  'Sorry, we do not have this.',0AH,'$'
FOUND   DB  ' is found.',0AH,'$'
BRSN    DB  'You have not chosen any product.',0AH
		DB  'Search a commodity before making an order.',0AH,'$'
ORMD    DB  'Your order is processed successfully.',0AH,'$'
CMPTED  DB  'All recommendation computation is done.',0AH,'$'
UPDATED DB  'All recommendation information is updated.',0AH,'$'
SOLD    DB  ' is sold out. We are sorry about this.',0AH,'$'

OUT_CS  DB  6   DUP(0)

M       EQU 60000
DATA    ENDS

CODE    SEGMENT USE16
        ASSUME  CS:CODE,DS:DATA,SS:STACK
START:  MOV AX, DATA
        MOV DS, AX
		
MAIN:    ;dos功能调用输出主菜单格式
		LEA DX, FORMAT
		MOV AH, 09H
		INT 21H
		;判断当前用户是顾客还是老板，以输出当前用户信息
		CMP AUTH, 0
		JNE  OBOSS
		;dos功能调用输出当前用户信息（顾客）
        LEA DX, CSTM
		MOV AH, 09H
		INT 21H
		JMP OGOOD
        ;dos功能调用输出当前用户信息（老板）
OBOSS:  LEA DX, BOSS
		MOV AH, 09H
		INT 21H
		;dos功能调用输出当前浏览商品信息
OGOOD:  LEA DX, BRSING
		MOV AH, 09H
		INT 21H
    	MOV SI, 0
		CMP GOOD, 0
		JE  MN
    	MOV BX, GOOD
GNAME:	MOV DL, [BX][SI]
        CMP DL, 0
		JE  MN
		MOV AH, 02H
		INT 21H
		INC SI
		JMP GNAME
		;dos功能调用输出功能选择菜单
MN:		MOV DL, 0AH
		MOV AH, 02H
		INT 21H
		LEA DX, MENU
		MOV AH, 09H
		INT 21H
		
	    ;dos功能调用提示用户选择功能
		LEA DX, CHOICE+1
		MOV AH, 09H
		INT 21H
		
CHOOSE:	;dos功能调用获得用户想选择的功能
		MOV AH, 01H
		INT 21H
		MOV CHOICE, AL
		LEA DX, CRLF
		MOV AH, 09H
		INT 21H
		;判断是否需要退出程序
		CMP CHOICE, '9'
		JE  EXIT
		
		;判断用户输入的有效性
		CMP CHOICE, '1'
		JB  INVALID
		CMP CHOICE, '9'
		JB VALID

INVALID:;用户输入的功能不合法，提示用户重新输入
		LEA DX, AGAIN
		MOV AH, 09H
		INT 21H
		JMP CHOOSE
		
VALID:	;根据用户选择功能进行跳转
		;判断用户是否选择了功能一
		CMP CHOICE, '1'
		JNE F2
		
F1:		;判断用户是否已经登陆过，若是，提示用户请勿重复登录
		CMP AUTH, 1
		JNE LOG
		LEA DX, RPT
		MOV AH, 09H
		INT 21H
		JMP MAIN
		;dos功能调用提示用户输入用户名
LOG:    LEA DX, NAMEH
		MOV AH, 09H
		INT 21H
		
		;dos功能调用获得用户姓名
		LEA DX, IN_NAME
		MOV AH, 0AH
		INT 21H
		LEA DX, CRLF
		MOV AH, 09H
		INT 21H
		MOV BL, IN_NAME+1
		MOV BH, 0
		MOV BYTE PTR IN_NAME+2[BX], '$'

        ;dos功能调用提示用户输入密码
		MOV DX, OFFSET PWDH
		MOV AH, 09H
		INT 21H
		
		;dos功能调用获得用户密码
		LEA DX, IN_PWD
		MOV AH, 0AH
		INT 21H
		LEA DX, CRLF
		MOV AH, 09H
		INT 21H
		MOV BL, IN_PWD+1
		MOV BH, 0
		MOV BYTE PTR IN_PWD+2[BX], '$'
		
		CMP IN_NAME+1, 0
		JNE CMPNAME
		MOV AUTH, 0
		JMP MAIN


CMPNAME:;验证用户输入的姓名是否正确
		;不正确则跳转到WRONGN
		;正确则跳转到CMPWD（继续比较密码）
        CMP IN_NAME+1, NLENGTH
		JNE WRONGN
		MOV CX, NLENGTH
CNL:    MOV SI, CX
		MOV AL, BNAME-1[SI]
		CMP AL, IN_NAME+1[SI]
		JNE WRONGN
		DEC CX
		JNZ CNL
		JMP CMPPWD
		
WRONGN: ;提示用户输入的姓名错误
		LEA DX, WNH
		MOV AH, 09H
		INT 21H
		JMP F1
		
CMPPWD:;验证用户输入的密码是否正确
		;不正确则跳转到WRONGP
		;正确则跳转到RIGHT（登录成功）
		CMP IN_PWD+1, PLENGTH
		JNE WRONGP
		MOV CX, PLENGTH
CPL:    MOV SI, CX
		MOV AL, BPASS-1[SI]
		CMP AL, IN_PWD+1[SI]
		JNE WRONGP
		DEC CX
		JNZ CPL
		JMP RIGHT

WRONGP: ;提示用户输入的密码错误
		LEA DX, WPH
		MOV AH, 09H
		INT 21H
		JMP F1
		
RIGHT:	;dos功能调用提示用户登录成功
		LEA DX, SUCCESS
		MOV AH, 09H
		INT 21H
		MOV AUTH, 1
		CMP CHOICE, '1'
		JE  MAIN
		
F2:     ;判断用户是否选择功能二
		CMP CHOICE, '2'
		JNE F3
		;dos功能调用提示用户输入商品名称
		MOV DX, OFFSET SRCH
		MOV AH, 09H
		INT 21H
		
		;dos功能调用获得商品名称
		LEA DX, IN_SRC
		MOV AH, 0AH
		INT 21H
		LEA DX, CRLF
		MOV AH, 09H
		INT 21H
		MOV BL, IN_SRC+1
		MOV BH, 0
		MOV BYTE PTR IN_SRC+2[BX], '$'
		
		;依次检查每一个商品的名称
		;是否能和用户输入的名称匹配
		MOV CX, N
    	MOV BX, OFFSET GA1
GOODS:	MOV DI, 0
CMPG:	MOV AL, [BX][DI]
		CMP AL, 0
		;检查到商品名称的末尾
		;去检查输入缓冲区此处是否是'$'
		JE  MARGIN
		CMP AL, IN_SRC+2[DI]
		JNE NMATCH
		INC DI
		JMP CMPG
NMATCH:	ADD BX, GLENGTH
		LOOP GOODS

MARGIN: CMP BYTE PTR IN_SRC+2[DI], '$'
		;两个字符串同时结束且完全匹配
		JE  ISFOUND
		
		;dos功能调用提示用户未找到商品
		LEA DX, NFOUND
		MOV AH, 09H
		INT 21H
		JMP MAIN
		
		;dos功能调用提示用户找到商品
		;并更改数据段中GOOD的值
ISFOUND:MOV GOOD, BX
		LEA DX, IN_SRC+2
		MOV AH, 09H
		INT 21H
		LEA DX, FOUND
		MOV AH, 09H
		INT 21H
		JMP MAIN
		
F3:     ;判断用户是否选择了功能三
		CMP CHOICE, '3'
		JNE F4
		
		MOV BP, M
		MOV AX, 0
		CALL TIMER
		
LOPA:	;判断当前是否有正在浏览的商品
		CMP GOOD, 0
		JNE CTN
		LEA DX, BRSN
		MOV AH, 09H
		INT 21H
		JMP TIME
		
CTN:	;判断当前商品是否有剩余
		MOV BX, GOOD
		MOV AX, 17[BX]
		CMP 15[BX], AX
		JA  ORDER
		;提示用户商品已售空
		MOV BX, GOOD
		MOV SI, 0
CNAME:	MOV DL, [BX][SI]
        CMP DL, 0
		JE  SOLDH
		MOV AH, 02H
		INT 21H
		INC SI
		JMP CNAME
SOLDH:	LEA DX, SOLD
		MOV AH, 09H
		INT 21H
		JMP TIME
		
ORDER:  INC WORD PTR 17[BX]
		MOV CX, N
		MOV EDI, 0
		MOV EBX, OFFSET GA1
		MOV SI, $+5   ;将“输出订单处理成功的提示信息”的指令地址保存在SI中
		JMP ALLG      ;跳转到功能四中去计算商品推荐度
		
		;输出订单处理成功的提示信息
		;LEA DX, ORMD
		;MOV AH, 09H
		;INT 21H
		;dos功能调用提示用户推荐度信息已经更新
		;LEA DX, UPDATED
		;MOV AH, 09H
		;INT 21H
		
		DEC BP
		JNZ LOPA
		
TIME:	MOV AX, 1
		CALL TIMER

		JMP MAIN     ;返回到主菜单

F4:     ;判断用户是否选择了功能四
		CMP CHOICE, '4'
		JNE F5
		MOV CX, N                ;CX中存放商品总数
		MOV EDI, 0
    	MOV BX, OFFSET GA1       ;BX指向第一个商品
ALLG:   MOV EAX, 0
		MOV AX, WORD PTR 11[BX]  ;商品的进价->AX
		MOV EDX, 1280
		MUL EDX                   ;EDX*EAX->EDX:EAX
		MOV DI, WORD PTR 13[BX]      ;DX：AX / 售价 的商->AX
		DIV EDI
		DIV BYTE PTR 10[BX]
		MOV AH, 0
		PUSH EAX;
		MOV EAX, 0
		MOV AX, WORD PTR 17[BX]  ;商品的已售数量->AX
		MOV EDX, 64
		MUL EDX               ;EDX*EAX->EDX:EAX
		MOV DI, WORD PTR 15[BX]
		DIV EDI               ;DX：AX / 进货数量 的商->AX
		MOV EDI, EAX
		POP EAX               ;两次计算的商相加既是推荐度
		ADD EAX, EDI
		MOV 19[BX], AX           ;将计算结果保存在内存中的对应单元
		ADD BX, GLENGTH          ;使BX指向下一商品
		DEC CX
		JNZ ALLG
		CMP CHOICE,'3'           ;判断这次推荐度计算是否是由功能三引起的
		JE  MEDIA                ;跳转到JMP SI的中转
		;dos功能调用提示用户推荐度信息计算完成
    	LEA DX, CMPTED
		MOV AH, 09H
		INT 21H
		JMP MAIN	

MEDIA:  JMP SI		

F5:     ;判断用户是否选择了功能五
		CMP CHOICE, '5'
		JNE F6
		;dos功能调用提示用户此功能暂未开放
		LEA DX, SORRY
		MOV AH, 09H
		INT 21H	
		JMP MAIN

F6:     ;判断用户是否选择了功能六
		CMP CHOICE, '6'
		JNE F7
		;dos功能调用提示用户此功能暂未开放
		LEA DX, SORRY
		MOV AH, 09H
		INT 21H
		JMP MAIN

F7:     ;判断用户是否选择了功能七
		CMP CHOICE, '7'
		JNE F8
		;dos功能调用提示用户此功能暂未开放
		LEA DX, SORRY
		MOV AH, 09H
		INT 21H
		JMP MAIN

F8:     ;判断用户是否选择了功能八
		CMP CHOICE, '8'
        JNE EXIT
		;调用RADIX子程序计算输出的字符串
        MOV BX, 10H     ;转化的进制数（16）->BX
		MOV AX, CS      ;代码段首址->AX
		LEA SI, OUT_CS  ;输出缓冲区首址->SI
		CALL RADIX
		MOV BYTE PTR [SI], 'H' ;在输出缓冲区末尾增加16进制后缀
		INC SI
		MOV BYTE PTR [SI], '$' ;在输出缓冲区末尾添加'$'
		;dos功能调用输出代码段首址
		LEA DX, OUT_CS
		MOV AH, 09H
		INT 21H
		JMP MAIN
		
EXIT:   ;4CH号系统功能调用退出程序
		MOV AH, 4CH
        INT 21H

RADIX   PROC
        PUSH CX  ;现场保护
		PUSH DX
		
		MOV CX, 0    ;记录压入堆栈中的字节数
LOP1:	MOV DX, 0
		DIV BX       ;DX:AX / BX的余数->DX
		PUSH DX
		INC CX
		CMP AX, 0    ;判断DX:AX / BX的商是否为0
		JNE LOP1
		;将刚刚压入堆栈中的数依次弹出并转化为对应字符
LOP2:   POP AX
		CMP AL, 0AH
		JB NUM
		ADD AL, 07H
NUM:    ADD AL, 30H
        MOV [SI], AL
		INC SI
		LOOP LOP2
		
		POP DX     ;恢复现场
		POP CX
		RET
RADIX   ENDP

	
;时间计数器(ms),在屏幕上显示程序的执行时间(ms)。精度1%s，最大量程<1分钟。
;使用方法:
;	   MOV  AX, 0	;表示开始计时
;	   CALL TIMER
;	   ... ...	;需要计时的程序
;	   MOV  AX, 1	
;	   CALL TIMER	;终止计时并显示计时结果(ms)
;输出: 改变了AX和状态寄存器
TIMER	PROC
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT   21H	     ;CH=hour(0-23),CL=minute(0-59),DH=second(0-59),DL=centisecond(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000    ;后续毫秒数小，说明秒部分跨0了，
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'Time elapsed in ms is '
_TMSG	DB    12 DUP(0)
TIMER   ENDP
	
CODE    ENDS
        END START