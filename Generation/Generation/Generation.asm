.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "../Debug/GenLib.lib
ExitProcess PROTO:DWORD 
.stack 4096


 outnum PROTO : DWORD

 outstr PROTO : DWORD

 strcopy PROTO : DWORD, : DWORD

 lenght PROTO : DWORD, : DWORD

 atoii  PROTO : DWORD,  : DWORD

.const
	message db 'Division by zerro error', 0
		newline byte 13, 10, 0
		LTRL1 byte 'Minimal number is:   ', 0
		LTRL2 byte 'Standart function:   ', 0
		LTRL3 byte 'Lenght NEV-2023:     ', 0
		LTRL4 byte 'String copy:         ', 0
		LTRL5 byte 'String in number:    ', 0
		LTRL6 sdword 2
		LTRL7 byte '; ', 0
		LTRL8 sdword 2147483647
		LTRL9 sdword 3
		LTRL10 byte ' module 3:         ', 0
		LTRL11 byte 'NEV-2023', 0
		LTRL12 byte 'Course Project Test', 0
		LTRL13 byte '70', 0
		LTRL14 sdword 21
		LTRL15 sdword 13
		LTRL16 sdword 45
		LTRL17 sdword 20
		LTRL18 byte 'Cycle:               ', 0
		LTRL19 sdword 125
		LTRL20 byte 'Number before cycle: ', 0
		LTRL21 sdword 1
		LTRL22 byte 'Number after cycle:  ', 0
.data
		temp sdword ?
		buffer byte 256 dup(0)
		minres sdword 0
		standfk sdword 0
		standfstr dword ?
		standfnum sdword 0
		dividedf sdword 0
		mainx sdword 0
		mainy sdword 0
		mainstrx dword ?
		mainstry dword ?
		mainstrz dword ?
		mainminone sdword 0
		mainmintwo sdword 0
		mainresmin sdword 0
		mainab sdword 0
.code

;------------- min --------------
min PROC,
	minx : sdword, miny : sdword  
; -------- save registers -------
push ebx
push edx
; -------------------------------
mov edx, minx
cmp edx, miny

jl right1
jg wrong1
right1:
push minx

pop ebx
mov minres, ebx

jmp next1
wrong1:
push miny

pop ebx
mov minres, ebx

next1:

push offset LTRL1
call outstr


push minres
call outnum

push offset newline
call outstr

push offset newline
call outstr

; ------ restore registers ------
pop edx
pop ebx
; -------------------------------
mov eax, minres
ret
min ENDP
;---------------


;------------- standf --------------
standf PROC,
	standfa : dword, standfb : dword, standfc : dword  
; -------- save registers -------
push ebx
push edx
; -------------------------------

push offset LTRL2
call outstr

push offset newline
call outstr


push standfa
push offset buffer
call lenght
push eax

pop ebx
mov standfk, ebx


push offset LTRL3
call outstr


push standfk
call outnum

push offset newline
call outstr


push standfb
push offset buffer
call strcopy
mov standfstr, eax

push offset LTRL4
call outstr


push standfstr
call outstr

push offset newline
call outstr


push standfc
push offset buffer
call atoii
push eax

pop ebx
mov standfnum, ebx


push offset LTRL5
call outstr


push standfnum
call outnum

push offset newline
call outstr

push offset newline
call outstr

; ------ restore registers ------
pop edx
pop ebx
; -------------------------------
ret
standf ENDP
;---------------


;------------- divided --------------
divided PROC,
	dividedres : sdword  
; -------- save registers -------
push ebx
push edx
; -------------------------------
push LTRL6

pop ebx
mov dividedf, ebx

push dividedres
push dividedf
pop ebx
cmp ebx, 0
je division_by_zerro_error
pop eax
cdq
idiv ebx
push eax

pop ebx
mov dividedres, ebx


push dividedres
call outnum


push offset LTRL7
call outstr

; ------ restore registers ------
pop edx
pop ebx
; -------------------------------
mov eax, dividedres
ret
divided ENDP
;---------------


;------------- MAIN --------------
main PROC
push LTRL8

pop ebx
mov mainx, ebx


push mainx
call outnum

push LTRL9

pop ebx
mov mainy, ebx

push mainx
push mainy
pop ebx 
mov edx, 0 
pop eax 
idiv ebx 
push edx 
mov eax, edx

pop ebx
mov mainx, ebx


push offset LTRL10
call outstr


push mainx
call outnum

push offset newline
call outstr

push offset newline
call outstr

mov mainstrx, offset LTRL11
mov mainstry, offset LTRL12
mov mainstrz, offset LTRL13

push mainstrz
push mainstry
push mainstrx
call standf

push LTRL14

pop ebx
mov mainminone, ebx

push LTRL15

pop ebx
mov mainmintwo, ebx


push mainmintwo
push mainminone
call min
push eax
push LTRL16
pop ebx
pop eax
sub eax, ebx
push eax
push LTRL17
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov mainresmin, ebx


push mainresmin
call outnum

push offset newline
call outstr


push offset LTRL18
call outstr

push offset newline
call outstr

push LTRL19

pop ebx
mov mainab, ebx


push offset LTRL20
call outstr


push mainab
call outnum

push offset newline
call outstr

mov edx, mainab
cmp edx, LTRL21

jg cycle2
jmp cyclenext2
cycle2:

push mainab
call divided
push eax

pop ebx
mov mainab, ebx

mov edx, mainab
cmp edx, LTRL21

jg cycle2
cyclenext2:
push offset newline
call outstr


push offset LTRL22
call outstr


push mainab
call outnum

push offset newline
call outstr

push 0
call ExitProcess
main ENDP

;-----If division by zero occurs -----
jmp end_of_code
division_by_zerro_error:
push offset message
call outstr
push offset newline
call outstr
push 0
call ExitProcess
end_of_code:

end main
