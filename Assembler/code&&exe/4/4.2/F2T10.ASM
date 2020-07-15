;��ģ����ɹ��ܣ����з��Ŷ�������ת����ʮ����ASCII�������
    PUBLIC  F2T10
.386
;�ӳ���F2T10
;���ܣ����з��Ŷ�������ת����ʮ����ASCII�������16λ�Σ���
;��ڲ�����
    ;AX/EAX ��Ŵ�ת���Ķ���������
    ;DX ���16λ��32λ��־��(DX)=32��ʾ��ת������EAX�С�����ʱ�ᱻ�޸ģ���ΪҪ�������
;���ڲ������ޡ�

;�ӳ���RADIX
;���ܣ���EAX�е�32λ�޷��Ŷ�������ת��ΪP��������16λ�Σ���
;��ڲ�����
    ;EAX ��Ŵ�ת���Ķ���������
    ;EBX ���Ҫת�����ƵĻ�����
    ;SI ���ת�����P����ASCII�����ִ����ֽڻ�������ַ��
;���ڲ�����
    ;����P����ASCII�����ִ�����λ��ǰ����λ�ں��˳��������SIΪָ����ֽڻ������С�
    ;SI ָ���ֽڻ����������һ��ASCII�����һ���ֽڴ���
DATA SEGMENT USE16 PARA PUBLIC 'DATA'
BUF     DB  12 DUP(5)
DATA ENDS
CODE SEGMENT USE16 PARA PUBLIC 'CODE'
    ASSUME  CS:CODE, DS:DATA
F2T10   PROC    FAR     ;NEAR������أ�
        PUSH EBX
        PUSH SI
        LEA SI, BUF
        CMP DX, 32
        JE B
        MOVSX EAX, AX
B:      OR EAX, EAX
        JNS PLUS
        NEG EAX
        MOV BYTE PTR [SI], '-'
        INC SI
PLUS:   MOV EBX, 10
        CALL RADIX
        MOV BYTE PTR [SI], '$'
        LEA DX, BUF
        MOV AH, 9
        INT 21H
        POP SI
        POP EBX
        RET
F2T10   ENDP

RADIX   PROC
        PUSH CX
        PUSH EDX
        XOR CX, CX
LOP1:   XOR EDX, EDX
        DIV EBX
        PUSH DX     ;������ջ
        INC CX      ;��¼��������
        OR EAX, EAX
        JNZ LOP1
LOP2:   POP AX
        CMP AL, 10
        JB L1 
        ADD AL, 7
L1:     ADD AL, 30H
        MOV [SI], AL
        INC SI
        LOOP LOP2
        POP EDX
        POP CX
        RET
RADIX   ENDP
CODE    ENDS
        END 