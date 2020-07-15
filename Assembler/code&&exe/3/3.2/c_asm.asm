.386
.model flat, c

public RECOM
;public AUTH
public GOOD
public IN_SRC
public SEARCH
public ORDER
public printInfo
public CHANGE

extern AUTH:byte

.data
N       EQU 30
;AUTH    DB  0
GOOD    DD  0
GA1     DB  'BOOK', 7 DUP(0), 10
		DW  35, 56, 70, 25, ?
GA2     DB  'BAG', 8 DUP(0), 9
		DW  12, 30, 25, 5, ?
GA3     DB  'PEN', 8 DUP(0), 8
		DW  50, 70, 80, 0, ?
GAN     DB  N-3 DUP('TEMPVALUE', 0, 0, 8, 15, 0, 20, 0, 30, 0, 2, 0, ?, ?)
GLENGTH EQU 22
IN_SRC  DB  10 DUP(0)
MYNAME  DB  '     Name     : ',0
DIS     DB  '   Discount   : ',0
COST    DB  'Purchased Cost: ',0
PRICE   DB  '     Price    : ',0
STOCK   DB  '     Stock    : ',0
SOLD    DB  '     Sold     : ',0
RE      DB  'Recommendation: ',0
TO      DB  ' -> ',0
NFOUND  DB  'Sorry, we do not have this! But the information about the last found item is as follows.',0
FOUND   DB  'Product Found! The information is as follows.',0
BRSN    DB  'You have not chosen any product.',0AH
		DB  'Search a commodity first.',0
ORMD    DB  'Your order is processed successfully.',0
CMPTED  DB  'All recommendation computation is done.',0
UPDATED DB  'All recommendation information is updated.',0
SOLDO   DB  ' is sold out. We are sorry about this.',0

.code
;C函数printv的原型
printv PROTO C, v:DWORD
printMenu PROTO C
printString PROTO C, string:DWORD
printChar PROTO C, cha:DWORD
printShort PROTO C, sh:DWORD
nextline PROTO C
getInt PROTO C


SEARCH  PROC
        PUSH EAX
		PUSH EBX
		PUSH ECX
		PUSH EDX
		PUSH EDI
        
		invoke nextline
		
		;依次检查每一个商品的名称
		;是否能和用户输入的名称匹配
		MOV ECX, N
    	MOV EBX, OFFSET GA1
GOODS:	MOV EDI, 0
CMPG:	MOV AL, [EBX][EDI]
		CMP AL, 0
		;检查到商品名称的末尾
		;去检查输入缓冲区此处是否是'$'
		JE  MARGIN
        
		CMP AL, IN_SRC[EDI]
		JNE NMATCH
		INC EDI
		JMP CMPG
NMATCH:	ADD EBX, GLENGTH
		LOOP GOODS
        invoke printString, offset NFOUND
        invoke nextline
		JMP RCV1

MARGIN: CMP BYTE PTR IN_SRC[EDI], 0
		JE  ISFOUND   ;两个字符串同时结束且完全匹配
		
		;dos功能调用提示用户找到商品
		;并更改数据段中GOOD的值
ISFOUND:mov GOOD, ebx
        invoke printString, offset FOUND
        invoke nextline
		
RCV1:	POP EDI
		POP EDX
		POP ECX
		POP EBX
		POP EAX
		RET
SEARCH  ENDP

ORDER   PROC
        push eax
        push ebx

		CMP GOOD, 0         ;判断当前是否有正在浏览的商品
		JNE CTN
		invoke printString, offset BRSN
        invoke nextline
		JMP RCV2
CTN:	MOV EBX, GOOD
		MOV AX, 18[EBX]
		CMP 16[EBX], AX      ;判断当前商品是否有剩余
		JA  BUY
        invoke printString, EBX
        invoke printString, offset SOLDO          ;提示用户商品已售空
        invoke nextline
		JMP RCV2
BUY:    INC WORD PTR 18[EBX]
		call RECOM
		invoke printString, offset ORMD          ;输出订单处理成功的提示信息
        invoke nextline
		invoke printString, offset UPDATED
        invoke nextline
RCV2:	pop ebx
        pop eax
ORDER   ENDP

RECOM   PROC
        PUSH EAX
		PUSH EBX
		PUSH ECX
		PUSH EDX
		PUSH EDI
		
		MOV EBX, OFFSET GA1       ;BX指向第一个商品
		MOV ECX, 0
		MOV EAX, 0
ALLG:   
        MOV AX, WORD PTR 12[EBX]  ;商品的进价->AX
		IMUL EAX, 1280
		MOV EDX, 0
		MOV CX, WORD PTR 14[EBX]
		DIV ECX                   ;EDX：EAX / 售价 的商->EAX
		DIV BYTE PTR 11[EBX]
		MOV AH, 0
		MOV DI, AX
		MOV AX, WORD PTR 18[EBX]  ;商品的已售数量->AX
		SHL EAX, 6
		MOV EDX, 0
		MOV CX, WORD PTR 16[EBX] 
		DIV ECX                   ;DX：AX / 进货数量 的商->AX
		ADD AX, DI                ;两次计算的商相加即是推荐度
		MOV 20[EBX], AX           ;将计算结果保存在内存中的对应单元
		ADD EBX, GLENGTH          ;使BX指向下一商品
		CMP EBX, OFFSET GA1 + GLENGTH * N
		JNE ALLG

        ;invoke printInfo, offset GA1

        POP EDI
		POP EDX
		POP ECX
		POP EBX
		POP EAX
		RET
RECOM   ENDP

printInfo   PROC
            push ebx

            cmp GOOD, 0
            je rcv
            mov ebx, GOOD
            invoke printString, offset MYNAME
            invoke printString, GOOD
            invoke nextline
            invoke printString, offset DIS
            invoke printChar, 11[ebx]
            invoke nextline
            cmp AUTH, 1
            JNE skip
            invoke printString, offset COST
            invoke printShort, 12[ebx]
            invoke nextline
skip:       invoke printString, offset PRICE
            invoke printShort, 14[ebx]
            invoke nextline
            invoke printString, offset STOCK
            invoke printShort, 16[ebx]
            invoke nextline
            invoke printString, offset SOLD
            invoke printShort, 18[ebx]
            invoke nextline
            invoke printString, offset RE
            invoke printShort, 20[ebx]
            invoke nextline

rcv:        pop ebx
            RET
printInfo   ENDP

CHANGE  PROC
        PUSH EAX
        PUSH EBX
		PUSH ECX
		PUSH EDX
		PUSH ESI

        cmp GOOD, 0
        jne updt
        invoke printString, offset BRSN
        invoke nextline
        jmp RECOVER
updt:   mov EBX, GOOD
		
        invoke printString, offset MYNAME
        invoke printString, EBX
        invoke nextline
        invoke printString, offset DIS
        invoke printChar, 11[EBX]
        invoke printString, offset TO
        invoke getInt
        mov 11[EBX], al
        invoke printString, offset COST
        invoke printShort, 12[EBX]
        invoke printString, offset TO
        invoke getInt
        mov 12[EBX], ax
        invoke printString, offset PRICE
        invoke printShort, 14[EBX]
        invoke printString, offset TO
        invoke getInt
        mov 14[EBX], ax
        invoke printString, offset STOCK
        invoke printShort, 16[EBX]
        invoke printString, offset TO
        invoke getInt
        mov 16[EBX], ax
        invoke printString, offset SOLD
        invoke printShort, 18[EBX]
        invoke printString, offset TO
        invoke getInt
        mov 18[EBX], ax
        call RECOM
		
RECOVER:invoke nextline
		POP ESI
		POP EDX
		POP ECX
        POP EBX
		POP EAX
		RET
CHANGE  ENDP
        end