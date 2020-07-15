        EXTERN DISPLAY:FAR, CHANGE:FAR, INSTALL:FAR, RECOVER:FAR, F10TBCD:FAR, F2T10:FAR
        PUBLIC BNAME, BPASS
.386
STACK   SEGMENT USE16   STACK
        DB  200 DUP(0)
STACK   ENDS

DATA    SEGMENT USE16 PARA PUBLIC 'DATA'
A1      DW  LOGINT
A2      DW  SEARCH
A3      DW  ORDER
A4      DW  RECOM_W
A5      DW  RANK
A6      DW  CHINT
A7      DW  INST
A8      DW  PRINTCS
A9      DW  EXIT
NEWINT1 DW  LOGGING
NEWINT3 DW  CH_P
AUTH    DB  0
GOOD    DW  0
N       EQU 30
SNAME   DB  'ASMSHOP',0
GA1     DB  'BOOK', 6 DUP(0), 10
		DW  35 XOR 0DBCH, 56, 70, 25, ?
GA2     DB  'BAG', 7 DUP(0), 9
		DW  12 XOR 0DBCH, 30, 25, 5, ?
GA3     DB  'PEN', 7 DUP(0), 8
		DW  50 XOR 0DBCH, 70, 80, 0, ?
GAN     DB  N-3 DUP('TEMPVALUE', 0, 8, 15, 0 XOR 0DH, 20 XOR 0BCH, 0, 30, 0, 2, 0, ?, ?)

GLENGTH EQU 21

CRLF    DB  0DH,0AH,'$'
FORMAT  DB  '                                      ',0AH
		DB  '----------Welcome to ASMSHOP----------',0AH,'$'
CSTM	DB  'Current User: Customer',0AH,'$'
BOSS    DB  'Current User: OWNER',0AH,'$'
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
PWDH    DB  'Please input your password:$'
IN_PWD  DB  40
        DB  ?
		DB  40 DUP(0)
SRCH    DB  'Please input your name of the commodity you are going to search:$'
IN_SRC  DB  20
        DB  ?
		DB  20 DUP(0)

SUCCESS DB  'You have logged in successfully!',0AH,'$'
RPT     DB  'You have already logged in. Do not repeate.',0AH,'$'
SORRY   DB  'Sorry, this function is waiting for implementation.',0AH,'$'
AGAIN   DB  'Invalid input, please make your choice again:','$'
WNPH     DB  'Wrong Username or Password, unable to log in.',0AH
		DB  'Please log in again.',0AH,'$'
NFOUND  DB  'Sorry, we do not have this.',0AH,'$'
FOUND   DB  ' is found.',0AH,'Information about the product is as follows.',0AH,'$'
BRSN    DB  'You have not chosen any product.',0AH
		DB  'Search a commodity first.',0AH,'$'
ORMD    DB  'Your order is processed successfully.',0AH,'$'
CMPTED  DB  'All recommendation computation is done.',0AH,'$'
UPDATED DB  'All recommendation information is updated.',0AH,'$'
SOLD    DB  ' is sold out. We are sorry about this.',0AH,'$'
BNAME   DB  'L' XOR 'H'
        DB  'i' XOR 'I'
		DB  ' ' XOR 'T'
		DB  'Y' XOR 'Y'
		DB  'o' XOR 'O'
		DB  'N' XOR 'U'
		DB  'g' XOR 'H'
		DB  'K' XOR 'I'
		DB  'a' XOR 'T'
		DB  'N' XOR 'Y'
		DB  'g' XOR 'O'
		DB   0  XOR 'U'

THINT   DB  'Please set the time to switch the stack segment.',0AH,'$'
MINUTE  DB  'Minute :$'
SECOND  DB  'Second :$'
RHINT   DB  'You have to provide the information about seconds',0AH,'$'
ILLEGAL DB  'Illegal input!',0AH,'Please input again.',0AH,'$'

IN_TIME DB  4
        DB  ?
		DB  4   DUP(0)
		
MIN     DW  ?
SEC     DW  ?
BPASS   DB  'L' + 'H', 'i' + 'I', ' ' + 'T', 'Y' + 'Y', 'o' + 'O', 'N' + 'U', 0

OUT_CS  DB  6   DUP(0)

INTED   DB  0
DOK1    DW  OK1
DOGOOD  DW  OGOOD
Dexitrec DW exitrec
dchangeint DW  changeint
dgoon   DW  goon2
DATA    ENDS

CODE    SEGMENT USE16 'CODE'
        ASSUME  CS:CODE,DS:DATA,SS:STACK
		
OLDINT1 DW  ?, ?
OLDINT3 DW  ?, ?

START:  ;MOV AX, DATA
        ;MOV DS, AX
		push data
		
WRITE   MACRO   BUF
        LEA DX, BUF
		MOV AH, 09H
		INT 21H
		ENDM
		
find:		xor  ax,ax                  ;接管调试用中断，中断矢量表反跟踪
            mov  es,ax
			pop  ax
			mov  bx, 4
			mov  ds, ax
			cmp  -2[esp], data          ;检查堆栈反跟踪
			jne  disturb
			jmp  dchangeint
disturb:	db   'Here we go! I just do not want you to do that'
			
changeint:  mov  ax,es:[bx]            ;保存原1号和3号中断矢量
            mov  OLDINT1,ax
            mov  ax,es:2[bx]
            mov  OLDINT1+2,ax
            mov  ax,es:8[bx]
            mov  OLDINT3,ax
            mov  ax,es:10[bx]
            mov  OLDINT3+2,ax
			
            mov  ax, cs           ;设置新的中断矢量
			shl  eax, 16
			
			mov  ax, NEWINT1
            mov  es:[bx],eax

			mov  ax, NEWINT3
            mov  es:8[bx],eax
		
MAIN:   WRITE FORMAT      ;dos功能调用输出主菜单格式
		CMP AUTH, 0       ;判断当前用户是顾客还是老板，以输出当前用户信息
		JNE  OBOSS
        WRITE CSTM        ;dos功能调用输出当前用户信息（顾客）
		JMP DOGOOD 
OBOSS:  WRITE BOSS        ;dos功能调用输出当前用户信息（老板）
OGOOD:  WRITE BRSING      ;dos功能调用输出当前浏览商品信息
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
		
MN:		MOV DL, 0AH      ;输出一个换行
		MOV AH, 02H
		INT 21H
		WRITE MENU       ;dos功能调用输出功能选择菜单
		    push ax
			mov  ax, dx
			pop  dx
			mov  ax, dx
    		jmp  dgoon
			db  'I am here to disturb you incase that you hack this program'
goon2:	MOV DX, OFFSET CHOICE + 1   ;dos功能调用提示用户选择功能
		    mov  ax, -2[esp]
		INT 21H
		
CHOOSE:	MOV AH, 01H
		INT 21H
		MOV CHOICE, AL   ;dos功能调用获得用户想选择的功能
		WRITE CRLF       ;输出一个回车换行
		    mov  bx, 04h
		
		;判断用户输入的有效性
		CMP CHOICE, '1'
		JB  INVALID
		CMP CHOICE, '9'
		JBE VALID

INVALID:WRITE AGAIN      ;用户输入的功能不合法，提示用户重新输入
		JMP CHOOSE
		
VALID:	    mov  ax, NEWINT1
            cmp  es:[bx], ax
            je   OK2
			mov  choice, '9'
OK2:    MOV BX, 0
        MOV BL, CHOICE
		SUB BX, 30H
		MOV SI, BX
		ADD SI, SI
		MOV BX, 0
		MOV AX, -2[BX][SI]
		CALL AX
FOLLOWING:		
        JMP MAIN

EXIT    PROC
        CMP INTED,1
        JNE OFF
		CALL RECOVER
		    xor  ax, ax                  ;还原被修改的中断矢量表
			mov  ds, ax
			mov  ax, cs:OLDINT1
			mov  ds:[0004h], ax
			mov  ax, cs:OLDINT1+2
			mov  ds:[0006h], ax
			mov  ax, cs:OLDINT3
			mov  ds:[000ch], ax
			mov  ax, cs:OLDINT3+2
			mov  ds:[000eh], ax
OFF:	MOV AH, 4CH      ;4CH号系统功能调用退出程序
        INT 21H
EXIT    ENDP
		
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

LOGINT  PROC
        INT 01H
        RET
LOGINT  ENDP

CHINT   PROC
        INT 03H
        RET
CHINT   ENDP

goon3:      jmp cx	

LOGGING PROC
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		PUSH DI
		PUSH SI
		
F1:		    mov bp, 04H
        CMP AUTH, 04H  ;判断用户是否已经登陆过
		JNE LOG
		WRITE RPT    ;若已登陆，提示用户请勿重复登录
		JMP MAIN
		
LOG:    WRITE NAMEH  ;dos功能调用提示用户输入用户名
		LEA DX, IN_NAME
		MOV AH, 0AH  ;dos功能调用获得用户姓名
		INT 21H
		    mov si, NEWINT1
		WRITE CRLF   ;输出一个回车换行
		MOV BL, IN_NAME+1
		MOV BH, 0
		MOV BYTE PTR IN_NAME+2[BX], 0
		
		    mov cx, starti
			cmp es:[bp], si
			je  goon3
			db  'Indirect jump to anti track! Important! Do not ignore!'
        
starti: WRITE PWDH    ;dos功能调用提示用户输入密码
		LEA DX, IN_PWD
		MOV AH, 0AH   ;dos功能调用获得用户密码
		INT 21H
		WRITE CRLF    ;输出一个回车换行
		MOV BL, IN_PWD+1
		MOV BH, 0
		MOV BYTE PTR IN_PWD+2[BX], 0
		
		CMP IN_NAME+1, 0
		JNE CMPNAME
		MOV AUTH, 0
		JMP EXITLOG


CMPNAME:;验证用户输入的姓名是否正确
		;不正确则跳转到WRONGN
		;正确则跳转到CMPWD（继续比较密码）
		CMP IN_PWD+1, 0
		JE  WRONGP
		
		MOV BL, IN_PWD+1
		MOV SI, 0
CNL:    MOV AX, SI
	    DIV BL
		MOVSX DI, AH
		    mov  cx, indi1
			jmp  goon3
			db   'sdfklsdkfldskfjdsjfldjfkssoirewnjfdiufdsfsdhewr'
indi1:  MOV AL, IN_NAME+2[SI]
		    mov  cx, indi2
			jmp  goon3
			db   'erwlkjnkj343nm,djfsi98324k45nxzn,mziu984234,mjk432'
indi2:  XOR AL, IN_PWD+2[DI]
            mov  cx, indi3
			jmp  goon3
			db   'trjnfdsmiubbmiewyvcnbqk39874ndnmjfifd37'
indi3:	CMP AL, BNAME[SI]
		JNE WRONGN
		MOVSX DI, BL
		XOR AL, IN_PWD+1[DI]
		CMP AL, 0
		JE  CMPPWD
		INC SI
		JMP CNL
		
WRONGN: WRITE WNPH    ;提示用户输入的姓名错误
		JMP F1
		
CMPPWD:;验证用户输入的密码是否正确
		;不正确则跳转到WRONGP
		;正确则跳转到RIGHT（登录成功）
		MOV SI, 0
CPL:    CMP BPASS[SI], 0
		JE  RIGHT
        MOV AL, IN_NAME+2[SI]
        ADD AL, IN_PWD+2[SI]
		CMP AL, BPASS[SI]
		JNE WRONGP
		INC SI
		JMP CPL

WRONGP: WRITE WNPH    ;提示用户输入的密码错误
		JMP F1
		
RIGHT:	    PUSH WORD PTR BNAME
        WRITE SUCCESS;dos功能调用提示用户登录成功
            POP AX
		MOV AUTH, AL 
		
EXITLOG:POP SI
		POP DI
		POP DX
		POP CX
		POP BX
		POP AX
		IRET
LOGGING ENDP

SEARCH  PROC
        PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		PUSH DI
        
		WRITE SRCH   ;dos功能调用提示用户输入商品名称
		
		LEA DX, IN_SRC
		MOV AH, 0AH  ;dos功能调用获得商品名称
		INT 21H
		WRITE CRLF ;输出一个回车换行
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
		
		WRITE NFOUND  ;dos功能调用提示用户未找到商品
		JMP RCV1

MARGIN: CMP BYTE PTR IN_SRC+2[DI], '$'
		JE  ISFOUND   ;两个字符串同时结束且完全匹配
		
		;dos功能调用提示用户找到商品
		;并更改数据段中GOOD的值
ISFOUND:WRITE IN_SRC+2;输出用户输入的商品名称
		MOV GOOD, BX
		WRITE FOUND   ;提示用户商品已找到
		
		CALL DISPLAY
		
RCV1:	POP DI
		POP DX
		POP CX
		POP BX
		POP AX
		RET
SEARCH  ENDP

RECOM   PROC
        PUSH EAX
		PUSH EBX
		PUSH ECX
		PUSH EDX
		PUSH DI
		
		MOV EBX, OFFSET GA1       ;BX指向第一个商品
		MOV ECX, 0
		MOV EAX, 0
ALLG:   
		
        PUSH WORD PTR 11[EBX]  ;商品的进价（密文）->AX
		    cli                       ;计时反跟踪开始 
            mov  ah,2ch 
            int  21h
            push dx                   ;保存获取的秒和百分秒
		MOV CH, BNAME
        MOV CL, BPASS
		IMUL CX, 3
		PUSH CX
		    mov  ah,2ch                 ;获取第二次秒与百分秒
            int  21h
            sti
            cmp  dx, 2[esp]                 ;计时是否相同
			je   OK1
			pop  ax
			pop  dx
			pop  ax
            jmp  Dexitrec                ;如果计时相同，通过本次计时反跟踪，将jmp指令改为call指令混淆视线
			db   'How are you? I am fine!'

OK1:        pop  ax
            pop  dx                          ;准备检查一次堆栈，进行反跟踪，顺便解密进货价
            xor  ax, cx                      ;扰乱视线
			mov  dx, -4[esp]                 ;堆栈检查
            xor  [esp], dx
			pop  ax
        IMUL EAX, 1280
		MOV EDX, 0
		MOV CX, WORD PTR 13[EBX]
		DIV ECX                   ;EDX：EAX / 售价 的商->EAX
		DIV BYTE PTR 10[EBX]
		MOV AH, 0
		MOV DI, AX;
		MOV AX, WORD PTR 17[EBX]  ;商品的已售数量->AX
		SHL EAX, 6
		MOV EDX, 0
		MOV CX, WORD PTR 15[EBX] 
		DIV ECX                   ;DX：AX / 进货数量 的商->AX
		ADD AX, DI                ;两次计算的商相加即是推荐度
		MOV 19[EBX], AX           ;将计算结果保存在内存中的对应单元
		ADD EBX, GLENGTH          ;使BX指向下一商品
		CMP EBX, OFFSET GA1 + GLENGTH * N
		JNE ALLG

exitrec:POP DI
		POP EDX
		POP ECX
		POP EBX
		POP EAX
		RET
RECOM   ENDP

RECOM_W PROC
        PUSH AX
		PUSH DX
		
		CALL RECOM
		WRITE CMPTED
		
		POP DX
		POP AX
		RET
RECOM_W ENDP

RANK    PROC
        PUSH AX
		PUSH DX
		
		WRITE SORRY
		
		POP DX
		POP AX
		RET
RANK    ENDP

indi4:  CALL EXIT
        db  'I am going to exit now because you changed the AUTH!'

CH_P    PROC
        PUSH AX
		PUSH BX
		PUSH DX
		
		MOV AL, IN_NAME+2
		XOR AL, AUTH
		MOV BL, IN_PWD+2
		XOR BL, AUTH
		ADD BL, AL
        CMP BL, 94H      ;判断用户是否已经登陆过
		JE UPDATE
		CMP AUTH, 0
		JNE  indi4
		WRITE LOGIN      ;若用户还未登陆则提示用户先进行登陆
		INT 01H          ;引导用户进行登陆
		
UPDATE: CMP GOOD, 0
		JNE CHG
		WRITE BRSN      ;提示用户当前未浏览商品
		JMP E2
		
CHG:    MOV BX, GOOD
        CALL CHANGE
        CALL RECOM
		
E2:		POP DX
        POP BX
		POP AX
		IRET
CH_P    ENDP

INST    PROC
        PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		PUSH SI
        
		CMP INTED, 1
		JE  E
		
		WRITE THINT
MHINT:	WRITE MINUTE
		LEA DX, IN_TIME
		MOV AH, 0AH
		INT 21H
		WRITE CRLF
		CMP IN_TIME+1, 0
		JNE  NEXT
		MOV BX, -1
		JMP SHINT
NEXT:	MOV SI, OFFSET IN_TIME+2
		MOV CX, 0
		MOV CL, IN_TIME+1
		CALL F10TBCD
		CMP SI, -1
		JNE CONT
		WRITE ILLEGAL
		JMP MHINT
		
CONT:	MOV BX, AX
SHINT:	WRITE SECOND
		LEA DX, IN_TIME
		MOV AH, 0AH
		INT 21H
		WRITE CRLF
		CMP IN_TIME+1, 0
		JNE GOON
		WRITE RHINT
		JMP SHINT
GOON:	MOV SI, OFFSET IN_TIME+2
		MOV CX, 0
		MOV CL, IN_TIME+1
		CALL F10TBCD
		CMP SI, -1
		JNE IST
		WRITE ILLEGAL
		JMP SHINT

IST:	CALL INSTALL
		MOV INTED, 1
		
E:		POP SI
		POP DX
		POP CX
		POP BX
		POP AX
		RET
INST    ENDP

ORDER   PROC
        PUSH AX
		PUSH BX
		PUSH DX
		PUSH SI
		PUSH DI
		
		CMP GOOD, 0         ;判断当前是否有正在浏览的商品
		JNE CTN
		WRITE BRSN
		JMP RCV2
CTN:	MOV BX, GOOD
		MOV AX, 17[BX]
		CMP 15[BX], AX      ;判断当前商品是否有剩余
		JA  BUY
		MOV SI, 0
CNAME:	MOV DL, [BX][SI]    ;输出商品名称
        CMP DL, 0
		JE  SOLDH
		MOV AH, 02H
		INT 21H
		INC SI
		JMP CNAME
SOLDH:	WRITE SOLD          ;提示用户商品已售空
		JMP RCV2
BUY:    INC WORD PTR 17[BX]
		CALL RECOM
		WRITE ORMD          ;输出订单处理成功的提示信息
		WRITE UPDATED
RCV2:	AND DX, DX

        POP DI
		POP SI
		POP DX
		POP BX
		POP AX
		RET
ORDER   ENDP

PRINTCS PROC
        PUSH AX
        PUSH BX
		PUSH DX
		PUSH SI
		
        MOV BX, 10H      ;转化的进制数（16）->BX
		MOV AX, CS        ;代码段首址->AX
		LEA SI, OUT_CS   ;输出缓冲区首址->SI
		CALL RADIX       ;调用RADIX子程序计算输出的字符串
		MOV BYTE PTR [SI], 'H' ;在输出缓冲区末尾增加16进制后缀
		INC SI
		MOV BYTE PTR [SI], '$' ;在输出缓冲区末尾添加'$'
		WRITE OUT_CS     ;dos功能调用输出代码段首址
		
		POP SI
		POP DX
		POP BX
		POP AX
		RET
PRINTCS ENDP

CODE    ENDS
        END START