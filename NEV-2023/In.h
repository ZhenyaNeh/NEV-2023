#pragma once

#define IN_MAX_LEN_TEXT 1024*1024
#define MAX_LEN_BUFFER 2048
#define IN_CODE_ENDL  '\n'
#define IN_CODE_SPACE ' '
#define IN_CODE_NULL  '\0'
#define IN_CODE_QUOTE '\"'
#include <fstream>

#define IN_CODE_TABLE	{\
		/*0*/  /*1*/  /*2*/  /*3*/   /*4*/  /*5*/  /*6*/  /*7*/    /*8*/  /*9*/  /*A*/  /*B*/	/*C*/  /*D*/  /*E*/  /*F*/ \
/*0*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::P, IN::N, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*1*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*2*/	IN::P, IN::S, IN::Q, IN::S,  IN::T, IN::S, IN::S, IN::F,   IN::S, IN::S, IN::S, IN::S,  IN::S, IN::S, IN::T, IN::S,\
/*3*/	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::S, IN::S, IN::S, IN::T,\
/*4*/	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,\
/*5*/	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::F,  IN::T, IN::F, IN::T, IN::T,\
/*6*/	IN::F, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,\
/*7*/	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::T, IN::T, IN::S, IN::T,\
																														   \
/*8*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*9*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*A*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*B*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*C*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*D*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*E*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
/*F*/	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F \
}

namespace In
{
	struct InWord
	{
		char word[MAX_LEN_BUFFER];
		int line;
		static int size;
	};

	struct IN
	{
		// S Ц ( ) # < > ! & * + - = , ;
		// P Ц пробел, табул€ци€
		// N (NEW) Ц нова€ строка
		// F (FALSE) Ц запрещЄнный
		// T (TRUE) Ц разрешЄнный
		// I (IGNORED) Ц игнорируемый
		// Q Ц "

		enum { T = 1024, F = 2048, I = 4096, S, Q, P, N };

		int code[256] = IN_CODE_TABLE;
		int size = 0;
		int lines = 1;
		int ignor = 0;
		unsigned char* text;
		InWord* words;
	};

	IN getin(wchar_t infile[], std::ostream* stream);

	void addWord(InWord* words, char* word, int line);
	InWord* getWordsTable(std::ostream* stream, unsigned char* text, int* code, int textSize);
	void printTable(InWord* table);
}
