;本模块完成功能：编写新8号时钟中断程序以及安装和还原的子程序
;本模块编写者：ACM1801班李永康
		PUBLIC INSTALL, RECOVER
.386
;子程序INSTALL
;功能：安装新8号时钟中断，并设定切换堆栈段的时刻
;入口参数：‘分’存放在BL中，‘秒’存放在AL中
;出口参数：无

;子程序RECOVER
;功能：还原原有的8号时钟中断
;入口参数：无
;出口参数：无
DATA    SEGMENT USE16
STACKBAK DB  200 DUP(0)
HINT    DB  0AH,'NOTE: THE STACK HAS BEEN SWITCHED JUST NOW!',0AH,'$'
DATA    ENDS
CODE    SEGMENT USE16 PUBLIC PARA 'INT'
        ASSUME CS:CODE, DS:DATA
SLENGTH EQU 200
TMP_SS  DW  ?
OLD_INT DW  ?, ?
DIRECT  DB  0
SEC     DB  ?
MIN     DB  ?
COUNT   DB  18

NEW08H: PUSHF
        CALL DWORD PTR CS:OLD_INT
		
    	DEC CS:COUNT
		JZ  DO
		IRET
		
DO:		MOV CS:COUNT, 18
        PUSH AX
        PUSH SI
		PUSH BP
		PUSH DS
		
		MOV AX, DATA
		MOV DS, AX
		CMP CS:MIN, 0FFH
		JE CSEC
		MOV AL, 2     ;2是“分钟”信息的偏移地址
        OUT 70H, AL   ;设定将要访问的单元是偏移值为2的“分钟”信息（完成切换）
        JMP $+2       ;延时，保证端口操作的可靠性（因端口电路的响应速度较慢）
        IN  AL,71H    ;读取“分钟”信息
		CMP AL, CS:MIN
		JNE EXIT
CSEC:	MOV AL, 0     ;0是“秒”信息的偏移地址
        OUT 70H, AL   ;设定将要访问的单元是偏移值为0的“秒”信息（完成切换）
        JMP $+2       ;延时，保证端口操作的可靠性（因端口电路的响应速度较慢）
        IN  AL, 71H   ;读取“秒”信息
		CMP AL, CS:SEC
		JNE EXIT
CHANGE:	CMP CS:DIRECT, 1
		JE  RETURN

		MOV SI, SP
LOAD1:  MOV AL, SS:[SI]
        MOV DS:[SI], AL
		INC SI
		CMP SI, SLENGTH
		JNE  LOAD1
ELOAD1: MOV CS:TMP_SS, SS
		MOV BP, DS
		MOV SS, BP
		MOV CS:DIRECT, 1
		LEA DX, HINT
		MOV AH, 09H
		INT 21H
		JMP EXIT
		
RETURN: MOV SI, SP
        MOV AX, CS:TMP_SS
		MOV DS, AX
LOAD2:  MOV AL, SS:[SI]
        MOV DS:[SI], AL
		INC SI
		CMP SI, SLENGTH
		JNE LOAD2
ELOAD2: MOV SS, CS:TMP_SS
		MOV CS:DIRECT, 0
		MOV AX, DATA
		MOV DS, AX
		LEA DX, HINT
		MOV AH, 09H
		INT 21H
		
EXIT:   POP DS
        POP BP
		POP SI
        POP AX
        IRET

INSTALL PROC FAR
		PUSH DS
		
		MOV CS:MIN, BL
		MOV CS:SEC, AL
		
		XOR AX, AX
		MOV DS, AX
		MOV AX, DS:[08H*4]
		MOV BX, DS:[08H*4+2]
		MOV CS:OLD_INT, AX
		MOV CS:OLD_INT+2, BX
		
		CLI
		MOV WORD PTR DS:[08H*4], OFFSET NEW08H
		MOV DS:[08H*4+2], CS
		STI
		
		POP DS
ENDI:	RET
INSTALL ENDP

RECOVER PROC FAR
        PUSH AX
		PUSH DS
		
		XOR AX, AX
		MOV DS, AX
		
		CLI
		MOV AX, OLD_INT
		MOV DS:[08H*4], AX
		MOV AX, OLD_INT+2
		MOV DS:[08H*4+2], AX
		STI
		
		POP DS
		POP AX
		RET
RECOVER ENDP

CODE    ENDS
		END