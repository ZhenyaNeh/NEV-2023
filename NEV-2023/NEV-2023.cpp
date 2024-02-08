//11352
//Тип: int(4 byte), string
//Операции: +,-,*,/,%
//Представление данных: целые (десятичное и шестнадцатеричное); строковые,символьные (поизвольно)
//Назначение: копирование строк; вычисление длины строки
//Описание: оператор цикла
#include "stdafx.h"
#include "Message.h"

#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	Log::LOG log;

	try
	{
		Parm::PARM parm = Parm::getParm(argc, argv);                            
		log = Log::getStream(parm.log);											
		Log::writeLog(log);														
		Log::writeParm(log, parm);												
		In::IN in = In::getin(parm.in, log.stream);								
		//std::cout << in.text << std::endl;
		Log::writeIn(log.stream, in);											
		in.words = In::getWordsTable(log.stream, in.text, in.code, in.size);
		if (in.words == NULL) 
		{
			Log::writeLine(&std::cout, STOP, "");
			return 0;
		}
		//In::printTable(in.words);

		Lexer::LEX tables;											//лексический анализ			
		bool lex_ok = Lexer::analyze(tables, in, log, parm);					
		LT::writeLexTable(log.stream, tables.lextable);							
		IT::writeIdTable(log.stream, tables.idtable);							
		LT::writeLexemsOnLines(log.stream, tables.lextable);					
		if (!lex_ok)
		{
			Log::writeLine(log.stream, LEXERROR, "");
			Log::writeLine(&std::cout, LEXERROR, STOP, "");						
			return 0;
		}
		else
			Log::writeLine(&std::cout, LEXGOOD, "");							
		
		MFST_TRACE_START(log.stream);								//синтаксический анализ
		MFST::Mfst mfst(tables, GRB::getGreibach());							
		bool synt_ok = mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);													
		if (!synt_ok)
		{
			Log::writeLine(log.stream, SYNTERROR, "");
			Log::writeLine(&std::cout, SYNTERROR, STOP, "");					
			return 0;
		}
		else
			Log::writeLine(&std::cout, SYNTGOOD, "");

		bool sem_ok = Semantic::semanticsCheck(tables, log);		//семантический анализ			
		if (!sem_ok)
		{
			Log::writeLine(log.stream, SEMERROR, "");
			Log::writeLine(&std::cout, SEMERROR, STOP, "");						
			return 0;
		}
		else
			Log::writeLine(&std::cout, SEMGOOD, "");							


		bool polish_ok = Polish::PolishNotation(tables, log);		//польская нотация		
		if (!polish_ok)
		{
			Log::writeLine(log.stream, POLISHERROR, "");
			Log::writeLine(&std::cout, POLISHERROR, STOP, "");					
			return 0;
		}
		else 
			Log::writeLine(&std::cout, POLISHGOOD, "");						


		Log::writeLine(log.stream, MESSAGE, "");								
		LT::writeLexTable(log.stream, tables.lextable);							
		IT::writeIdTable(log.stream, tables.idtable);							
		LT::writeLexemsOnLines(log.stream, tables.lextable);					
		//Log::writeLine(&std::cout, MESSAGE, "");								
		//IT::writeIdTable(&std::cout, tables.idtable);							
		//LT::writeLexTable(&std::cout, tables.lextable);							
		//LT::writeLexemsOnLines(&std::cout, tables.lextable);					


		Gener::CodeGeneration(tables, parm, log);								
		Log::writeLine(log.stream, ALLGOOD, "");								
		Log::writeLine(&std::cout, ALLGOOD, "");								
		Log::Close(log);													    
	}
	catch (Error::ERROR e)
	{
		Log::writeError(log.stream, e);											
	}
}
