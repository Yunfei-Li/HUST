.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD
RADIX    proto
RECOM    proto 
F2T10    proto
SORT     proto

include      menuID.INC

include      windows.inc
include      user32.inc
include      kernel32.inc
include      gdi32.inc
include      shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib

item	     struct
	     itemname   db  10 dup(0)
	     discount   db  0
	     purchas    dw  0
	     price      dw  0
	     stock      dw  0
	     sold       dw  0
		 recommend  dw  0
item      ends

.data
ClassName    db       'TryWinClass',0
AppName      db       'ASM SHOP',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       'I am ASM1801 Li Yongkang.',0
RecomMsg     db       'All Recommendation Information is updated!',0
hInstance    dd       0
CommandLine  dd       0
buf	     item  <'Pencil',8,1,5,100,65,0>
         item  <'Pen',8,6,10,80,40,0>
		 item  <'Ruler',7,2,10,50,29,0>
	     item  <'Book',9,50,60,65,30,0>
		 item  <'Bag',6,80,120,20,10,0>
num          db       5
maxarg       db       -1
order        db       4,3,2,1,0
sorted       db       0,0,0,0,0
cmpted       db       0
done         db       0
recommend    dw       0
msg_name     db       'itemname',0
msg_discount db       'discount',0
msg_purchas  db       'purchased cost',0
msg_price    db       'price',0
msg_stock    db       'stock',0
msg_sold     db       'sold',0
msg_recom    db       'recommendation',0
menuItem     db       0  ;��ǰ�˵�״̬, 1=����list, 0=Clear
OUT_BUF      db       10 DUP(0)
.code
Start:	 
		 invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain  proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
         invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage,addr msg,NULL,0,0
             cmp    EAX,0
             je     ExitLoop
             INVOKE TranslateMessage,addr msg
             INVOKE DispatchMessage,addr msg
	     jmp    MsgLoop 
ExitLoop:    mov    eax,msg.wParam
	     ret
WinMain      endp

WndProc  proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	     LOCAL  hdc:HDC
	     LOCAL  ps:PAINTSTRUCT
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL
     .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
             ;;your code
	    .ENDIF
     .ELSEIF uMsg == WM_COMMAND
	    .IF     wParam == IDM_FILE_EXIT
		    invoke SendMessage,hWnd,WM_CLOSE,0,0
		.ELSEIF wParam == IDM_ACTN_RECOM
		    invoke RECOM
			invoke MessageBox,hWnd,addr RecomMsg,addr AppName,0
	    .ELSEIF wParam == IDM_ACTN_LIST
		    mov menuItem, 1
		    invoke InvalidateRect,hWnd,0,1  ;���������ͻ���
		    invoke UpdateWindow, hWnd
	    .ELSEIF wParam == IDM_ACTN_CLEAR
		    mov menuItem, 0
		    invoke InvalidateRect,hWnd,0,1  ;���������ͻ���
		    invoke UpdateWindow, hWnd
	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	    .ENDIF
     .ELSEIF uMsg == WM_PAINT
             invoke BeginPaint,hWnd, addr ps
             mov hdc,eax
	     .IF menuItem == 1
		 invoke Display,hdc
	     .ENDIF
	     invoke EndPaint,hWnd,addr ps
     .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
     .ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp

Display      proc   hdc:HDC
             XX     equ  10
             YY     equ  10
	         XX_GAP equ  160
	         YY_GAP equ  30
             invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_name,8
             invoke TextOut,hdc,XX+1*XX_GAP,YY+0*YY_GAP,offset msg_discount,8
             invoke TextOut,hdc,XX+2*XX_GAP,YY+0*YY_GAP,offset msg_purchas,14
             invoke TextOut,hdc,XX+3*XX_GAP,YY+0*YY_GAP,offset msg_price,5
             invoke TextOut,hdc,XX+4*XX_GAP,YY+0*YY_GAP,offset msg_stock,5
             invoke TextOut,hdc,XX+5*XX_GAP,YY+0*YY_GAP,offset msg_sold,4
			 invoke TextOut,hdc,XX+6*XX_GAP,YY+0*YY_GAP,offset msg_recom,14
             
			 cmp cmpted, 1
			 jne output
			 cmp done, 1
			 je output
			 invoke SORT

output:	     mov   ebx, XX
			 mov   edi,3*YY
			 mov   dx,16
			 mov   num,5
	LOOP1:
             movzx   bx, num
			 dec     bx
			 movzx   esi, byte ptr order[bx]
			 imul    esi, 21
			 add     esi, offset buf
			 mov     ebx, XX
			 invoke  TextOut,hdc,ebx,edi,esi,10
			 movsx   ax, byte ptr[esi+10]
			 invoke  F2T10
			 add     ebx,XX_GAP
             invoke  TextOut,hdc,ebx,edi,offset OUT_BUF,eax
			 mov     ax,[esi+11]
			 invoke  F2T10
			 add     ebx,XX_GAP
             invoke  TextOut,hdc,ebx,edi,offset OUT_BUF,eax
			 mov     ax,[esi+13]
			 invoke  F2T10
			 add     ebx,XX_GAP
             invoke  TextOut,hdc,ebx,edi,offset OUT_BUF,eax
			 mov     ax,[esi+15]
			 invoke  F2T10
			 add     ebx,XX_GAP
             invoke  TextOut,hdc,ebx,edi,offset OUT_BUF,eax
			 mov     ax,[esi+17]
			 invoke  F2T10
			 add     ebx,XX_GAP
             invoke  TextOut,hdc,ebx,edi,offset OUT_BUF,eax
			 mov     ax,[esi+19]
			 invoke  F2T10
			 add     ebx,XX_GAP
			 invoke  TextOut,hdc,ebx,edi,offset OUT_BUF,eax
			 add     esi,21
			 add     edi,YY_GAP
			 dec     num
			 jnz     LOOP1
             ret
Display      endp

RECOM   PROC USES EAX EBX ECX EDX DI
		MOV EBX, OFFSET buf       ;EBX指向第一个商品
		MOV ECX, 0
		MOV EAX, 0
ALLG:   
        MOV AX, WORD PTR 11[EBX]  ;商品的进价->AX
		IMUL EAX, 1280
		MOV EDX, 0
		MOV CX, WORD PTR 13[EBX]
		DIV ECX                   ;EDX：EAX / 售价 的商->EAX
		DIV BYTE PTR 10[EBX]
		MOVZX EAX, AL
		MOV EDI, EAX
		MOV AX, WORD PTR 17[EBX]  ;商品的已售数量->AX
		SHL EAX, 6
		MOV EDX, 0
		MOV CX, WORD PTR 15[EBX]
		DIV ECX                   ;EDX：EAX / 进货数量 的商->EAX
		ADD EAX, EDI              ;两次计算的商相加即是推荐度
		MOV 19[EBX], AX           ;将计算结果保存在内存中的对应单元
		ADD EBX, 21               ;使BX指向下一商品
		CMP EBX, OFFSET buf + 21 * 5
		JNE ALLG
		MOV cmpted, 1
		RET
RECOM   ENDP

F2T10   PROC USES EBX ESI
        LEA   ESI,OUT_BUF
        CMP   DX,32
        JE    TRAN
        MOVSX EAX,AX
TRAN:   OR    EAX,EAX
        JNS   PLUS
        NEG   EAX
        MOV   BYTE PTR [ESI],'-'
        INC   ESI
PLUS:   MOV   EBX,10
        invoke RADIX
        SUB   ESI,OFFSET OUT_BUF
        MOV   EAX,ESI
        RET
F2T10   ENDP

RADIX   PROC
        PUSH ECX
        PUSH EDX
        XOR ECX, ECX
LOP1:   XOR EDX, EDX
        DIV EBX
        PUSH DX     
        INC ECX      
        OR EAX, EAX
        JNZ LOP1
LOP2:   POP AX
        CMP AL, 10
        JB L1 
        ADD AL, 7
L1:     ADD AL, 30H
        MOV [ESI], AL
        INC ESI
        LOOP LOP2
        POP EDX
        POP ECX
        RET
RADIX   ENDP

SORT    PROC USES EAX EBX ECX EDX
        mov num, 5
pick:   mov ecx, 5
		mov recommend, 0
		mov maxarg, -1
next:	cmp ecx, 0
        je getmax
        cmp byte ptr [ecx+offset sorted-1], 0
		je comp
        dec ecx
		jmp next
comp:   mov ebx, ecx
        imul ebx, 21
        mov dx, word ptr [ebx+offset buf-2]
        cmp recommend, dx
        jbe update
		dec ecx
		jmp next
update: mov recommend, dx
        dec ecx
		mov maxarg, cl
		jmp next
getmax: mov ebx, 0
        mov bl, num
        mov al, maxarg
        mov byte ptr [ebx+offset order-1], al
		mov bl, al
		mov byte ptr [ebx+offset sorted], 1
		dec num
		jnz pick
		mov done, 1
		ret
SORT    ENDP
END  Start