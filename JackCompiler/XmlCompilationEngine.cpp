#include "XmlCompilationEngine.hpp"

void XmlCompilationEngine::compileClass()
{
	output << "<class>" << endl;
	output << _tokens[_tokenCounter]->toString() << endl;
	_tokenCounter++; //this has to be done after every read of the tokens

	output << _tokens[_tokenCounter]->toString() << endl;
	_tokenCounter++; //this has to be done after every read of the tokens

	output << _tokens[_tokenCounter]->toString() << endl;
	_tokenCounter++; //this has to be done after every read of the tokens

	while (_tokens[_tokenCounter]->keyword == Keyword::Static || _tokens[_tokenCounter]->keyword == Keyword::Field)
	{
		//todo Zero or More
		//We have to figure out how to call multiple times for each variable
		compileClassVarDec();
	}

	while (_tokens[_tokenCounter]->keyword == Keyword::Constructor
		|| _tokens[_tokenCounter]->keyword == Keyword::Function
		|| _tokens[_tokenCounter]->keyword == Keyword::Method
		)
	{
		//todo Zero or More
		//We have to figure out how to call multiple times for each variable
		compileSubroutine();
	}


	output << "</class>" << endl;
}
void XmlCompilationEngine::compileClassVarDec()
{
	output << "<classVarDec>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //Var
	_tokenCounter++; //this has to be done after every read of the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //Type
	_tokenCounter++; //this has to be done after every read of the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //Name
	_tokenCounter++; //this has to be done after every read of the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //Semi Colon
	_tokenCounter++; //this has to be done after every read of the tokens

	output << "</classVarDec>" << endl;
}
void XmlCompilationEngine::compileSubroutine()
{
	output << "<subroutineDec>" << endl;
	//Specific code for method //todo make this conditional and add the other types
	// 
	//go until the parameter list starts
	while (_tokens[_tokenCounter]->symbol != Symbol::LeftParentheses)
	{
		output << _tokens[_tokenCounter]->toString() << endl; 
		_tokenCounter++; //this has to be done after every read of the tokens
	}
	

	//parameter list
	compileParameterList();

	output << _tokens[_tokenCounter]->toString() << endl; //for the {
	_tokenCounter++; //this has to be done after every read of the tokens
	
	while (_tokens[_tokenCounter]->keyword == Keyword::Var
		|| _tokens[_tokenCounter]->keyword == Keyword::Let
		)
	{
		if (_tokens[_tokenCounter]->keyword == Keyword::Var) //not super efficient, but readable
		{
			compileVarDec();
		}
	}


	output << "</subroutineDec>" << endl;
}

void XmlCompilationEngine::compileSubroutineCall()
{
}

void XmlCompilationEngine::compileParameterList()
{
	output << _tokens[_tokenCounter]->toString() << endl; //for the (
	_tokenCounter++; //this has to be done after every read of the tokens

	output << "<parameterList>" << endl;

	while (_tokens[_tokenCounter]->symbol != Symbol::RightParentheses)
	{
		output << _tokens[_tokenCounter]->toString() << endl;
		_tokenCounter++; //this has to be done after every read of the tokens
	}

	output << _tokens[_tokenCounter]->toString() << endl; //for the )
	_tokenCounter++; //this has to be done after every read of the tokens

	output << "</parameterList>" << endl;
}
void XmlCompilationEngine::compileVarDec()
{
	output << "<varDec>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //Var
	_tokenCounter++; //this has to be done after every read of the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //Type
	_tokenCounter++; //this has to be done after every read of the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //Name
	_tokenCounter++; //this has to be done after every read of the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //Semi Colon
	_tokenCounter++; //this has to be done after every read of the tokens

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