#pragma once

#include "LT.h"
#include "IT.h"
#include "Lexer.h"


#define SEPSTREMP  "\n;---------------\n"
#define SEPSTR(x)  "\n;------------- " + string(x) + " --------------\n"


#define BEGIN ".586\n"\
".model flat, stdcall\n"\
"includelib libucrt.lib\n"\
"includelib kernel32.lib\n"\
"includelib \"../Debug/GenLib.lib\n"\
"ExitProcess PROTO:DWORD \n"\
".stack 4096\n"

#define END "push 0\ncall ExitProcess\nmain ENDP"\
"\n\n;-----If division by zero occurs -----\n"\
"jmp end_of_code\n"\
"division_by_zerro_error:\n"\
"push offset message\n"\
"call outstr\n"\
"push offset newline\n"\
"call outstr\n"\
"push 0\ncall ExitProcess\n"\
"end_of_code:\n"\
"\nend main"

#define EXTERN "\n outnum PROTO : DWORD\n"\
"\n outstr PROTO : DWORD\n"\
"\n strcopy PROTO : DWORD, : DWORD\n"\
"\n lenght PROTO : DWORD, : DWORD\n"\
"\n atoii  PROTO : DWORD,  : DWORD\n"


#define ITENTRY(x)  tables.idtable.table[tables.lextable.table[x].idxTI]
#define LEXEMA(x)   tables.lextable.table[x].lexema


#define CONST ".const\n\t\message db 'Division by zerro error', 0\n\t\tnewline byte 13, 10, 0"
#define DATA ".data\n\t\ttemp sdword ?\n\t\tbuffer byte 256 dup(0)"
#define CODE ".code"

namespace Gener
{
	void CodeGeneration(Lexer::LEX& tables, Parm::PARM& parm, Log::LOG& log);
};