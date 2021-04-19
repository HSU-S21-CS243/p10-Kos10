#include "XmlCompilationEngine.hpp"

void XmlCompilationEngine::compileClass()
{
	output << "<class>" << endl;



	output << "</class>" << endl;
}
void XmlCompilationEngine::compileClassVarDec()
{
	output << "<classVarDec>" << endl;

	output << "</classVarDec>" << endl;
}
void XmlCompilationEngine::compileSubroutine()
{
	output << "<subroutineDec>" << endl;

	output << "</subroutineDec>" << endl;
}

void XmlCompilationEngine::compileSubroutineCall()
{
}

void XmlCompilationEngine::compileParameterList()
{
	output << "<parameterList>" << endl;

	output << "</parameterList>" << endl;
}
void XmlCompilationEngine::compileVarDec()
{
	output << "<varDec>" << endl;

	output << "</varDec>" << endl;
}
void XmlCompilationEngine::compileStatement()
{
	
}

void XmlCompilationEngine::compileDo()
{
	output << "<doStatement>" << endl;

	output << "</doStatement>" << endl;
}
void XmlCompilationEngine::compileLet()
{
	output << "<letStatement>" << endl;

	output << "</letStatement>" << endl;
}
void XmlCompilationEngine::compileWhile()
{
	output << "<whileStatement>" << endl;

	output << "</whileStatement>" << endl;
}
void XmlCompilationEngine::compileReturn()
{
	output << "<returnStatement>" << endl;

	output << "</returnStatement>" << endl;
}
void XmlCompilationEngine::compileIf()
{
	output << "<ifStatement>" << endl;

	output << "</ifStatement>" << endl;
}
void XmlCompilationEngine::compileExpression()
{
	output << "<expression>" << endl;

	output << "</expression>" << endl;
}

/*
integerConstant | stringConstant | keywordConstant | unaryOp term | varName | varName ' [ ' expression ' ] ' 
| subroutineCall | ' ( ' expression ' ) '
*/
void XmlCompilationEngine::compileTerm()
{
}

void XmlCompilationEngine::compileExpressionList()
{
	output << "<expressionList>" << endl;
	output << "</expressionList>" << endl;
}