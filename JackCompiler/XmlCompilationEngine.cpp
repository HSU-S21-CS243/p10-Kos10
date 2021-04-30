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

	output << _tokens[_tokenCounter]->toString() << endl; //for the }
	_tokenCounter++; //this has to be done after every Write from the tokens

	output << "</class>" << endl;
}
void XmlCompilationEngine::compileClassVarDec() //todo FIX
{
	//this is broken and BAD...I think????
	output << "<classVarDec>" << endl;

	while (_tokens[_tokenCounter]->symbol != Symbol::SemiColon)
	{
		output << _tokens[_tokenCounter]->toString() << endl;
		_tokenCounter++; //this has to be done after every write from the tokens
	}
	output << _tokens[_tokenCounter]->toString() << endl; //for the ';'
	_tokenCounter++; //this has to be done after every write from the tokens

	output << "</classVarDec>" << endl;
}
void XmlCompilationEngine::compileSubroutine()
{
	output << "<subroutineDec>" << endl; 
	//go until the parameter list starts
	output << _tokens[_tokenCounter]->toString() << endl; //kind of subroutine 
	_tokenCounter++; //this has to be done after every write from the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //return type
	_tokenCounter++; //this has to be done after every write from the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //name
	_tokenCounter++; //this has to be done after every write from the tokens

	//parameter list
	compileParameterList();

	output << "<subroutineBody>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //for the {
	_tokenCounter++; //this has to be done after every read of the tokens
	
	//Var Decs
	while (_tokens[_tokenCounter]->keyword == Keyword::Var)
	{
		compileVarDec();
	}
	
	//statments 
	output << "<statements>" << endl;
	while(_tokens[_tokenCounter]->isStatement())
	{
		compileStatement();
	}
	output << "</statements>" << endl;
	output << _tokens[_tokenCounter]->toString() << endl; //for the }
	_tokenCounter++; //this has to be done after every read of the tokens
	output << "</subroutineBody>" << endl;
	output << "</subroutineDec>" << endl;
}

void XmlCompilationEngine::compileSubroutineCall()
{
	//I don't think this will work. I'm at a loss. I've missed some critical piece of information and I don't
	//know how to ask for help in a way that will actually aid me.
	
	output << _tokens[_tokenCounter]->toString() << endl;
	_tokenCounter++; //this has to be done after every write from the tokens

	if (_tokens[_tokenCounter]->symbol == Symbol::Period)
	{
		output << _tokens[_tokenCounter]->toString() << endl;
		_tokenCounter++; //this has to be done after every write from the tokens

		output << _tokens[_tokenCounter]->toString() << endl;
		_tokenCounter++; //this has to be done after every write from the tokens

	}

	compileExpressionList();

	//output << _tokens[_tokenCounter]->toString() << endl; //for the ';'
	//_tokenCounter++; //this has to be done after every write from the tokens
}

void XmlCompilationEngine::compileParameterList()
{
	output << _tokens[_tokenCounter]->toString() << endl; //for the (
	_tokenCounter++; //this has to be done after every read of the tokens

	output << "<parameterList>" << endl;

	while (_tokens[_tokenCounter]->symbol != Symbol::RightParentheses)
	{
		//parameter lists aren't made of expressions
		output << _tokens[_tokenCounter]->toString() << endl;
		_tokenCounter++; //this has to be done after every read of the tokens
	}

	output << "</parameterList>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //for the )
	_tokenCounter++; //this has to be done after every read of the tokens
}
void XmlCompilationEngine::compileVarDec()
{
	output << "<varDec>" << endl;

	while (_tokens[_tokenCounter]->symbol != Symbol::SemiColon)
	{
		output << _tokens[_tokenCounter]->toString() << endl;
		_tokenCounter++; //this has to be done after every write from the tokens
	}
	output << _tokens[_tokenCounter]->toString() << endl; //for the ';'
	_tokenCounter++; //this has to be done after every write from the tokens

	output << "</varDec>" << endl;
}
void XmlCompilationEngine::compileStatement()
{
	switch (_tokens[_tokenCounter]->keyword)
	{
	case Keyword::While:
		compileWhile();
		break;
	case Keyword::If:
		compileIf();
		break;
	case Keyword::Let:
		compileLet();
		break;
	case Keyword::Do:
		compileDo();
		break;
	case Keyword::Return:
		compileReturn();
		break;
	default:
		break;
	}
}

void XmlCompilationEngine::compileDo()
{
	output << "<doStatement>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //for the do
	_tokenCounter++; //this has to be done after every write from the tokens

	//while (_tokens[_tokenCounter]->symbol != Symbol::SemiColon) //go until the end of the statment
	//{
	//	if (_tokens[_tokenCounter]->symbol != Symbol::LeftParentheses)
	//	{
	//		compileParameterList();
	//	}
	//	else
	//	{
	//		output << _tokens[_tokenCounter]->toString() << endl;
	//		_tokenCounter++; //this has to be done after every write from the tokens
	//	}
	//}
	//output << _tokens[_tokenCounter]->toString() << endl; //for the ';'
	//_tokenCounter++; //this has to be done after every write from the tokens


	compileSubroutineCall();

	output << _tokens[_tokenCounter]->toString() << endl; //for the ;
	_tokenCounter++; //this has to be done after every write from the tokens
	output << "</doStatement>" << endl;
}
void XmlCompilationEngine::compileLet()
{
	output << "<letStatement>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //for the 'let'
	_tokenCounter++; //this has to be done after every write from the tokens
	
	output << _tokens[_tokenCounter]->toString() << endl; //for the variable name
	_tokenCounter++; //this has to be done after every write from the tokens

	if (_tokens[_tokenCounter]->symbol == Symbol::LeftHardBracket)
	{
		output << _tokens[_tokenCounter]->toString() << endl; //for the [
		_tokenCounter++; //this has to be done after every write from the tokens
		compileExpression();
		output << _tokens[_tokenCounter]->toString() << endl; //for the ]
		_tokenCounter++; //this has to be done after every write from the tokens

	}

	output << _tokens[_tokenCounter]->toString() << endl; //for the '='
	_tokenCounter++; //this has to be done after every write from the tokens

	compileExpression();

	output << _tokens[_tokenCounter]->toString() << endl; //for the ';'
	_tokenCounter++; //this has to be done after every write from the tokens
	output << "</letStatement>" << endl;
}
void XmlCompilationEngine::compileWhile()
{
	output << "<whileStatement>" << endl;
	//this should be identical code for 'if'
	output << _tokens[_tokenCounter]->toString() << endl; //for the 'while'
	_tokenCounter++; //this has to be done after every write from the tokens
	
	output << _tokens[_tokenCounter]->toString() << endl; //for the '('
	_tokenCounter++; //this has to be done after every write from the tokens

	compileExpression();

	output << _tokens[_tokenCounter]->toString() << endl; //for the ')'
	_tokenCounter++; //this has to be done after every write from the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //for the '{'
	_tokenCounter++; //this has to be done after every write from the tokens

	output << "<statements>" << endl;

	while (_tokens[_tokenCounter]->isStatement())
	{
		compileStatement();
	}

	output << "</statements>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //for the '}'
	_tokenCounter++; //this has to be done after every write from the tokens

	output << "</whileStatement>" << endl;
}
void XmlCompilationEngine::compileReturn()
{
	output << "<returnStatement>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //for the keyword 'return'
	_tokenCounter++; //this has to be done after every write from the tokens

	if (_tokens[_tokenCounter]->symbol != Symbol::SemiColon)
	{
		compileExpression();
	}

	output << _tokens[_tokenCounter]->toString() << endl; //for the ';'
	_tokenCounter++; //this has to be done after every write from the tokens
	output << "</returnStatement>" << endl;
}
void XmlCompilationEngine::compileIf()
{
	output << "<ifStatement>" << endl;
	//code copied from 'while'
	output << _tokens[_tokenCounter]->toString() << endl; //for the 'if'
	_tokenCounter++; //this has to be done after every write from the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //for the '('
	_tokenCounter++; //this has to be done after every write from the tokens

	compileExpression();

	output << _tokens[_tokenCounter]->toString() << endl; //for the ')'
	_tokenCounter++; //this has to be done after every write from the tokens

	output << _tokens[_tokenCounter]->toString() << endl; //for the '{'
	_tokenCounter++; //this has to be done after every write from the tokens

	output << "<statements>" << endl;

	while (_tokens[_tokenCounter]->isStatement())
	{
		compileStatement();
	}

	output << "</statements>" << endl;

	output << _tokens[_tokenCounter]->toString() << endl; //for the '}'
	_tokenCounter++; //this has to be done after every write from the tokens

	if (_tokens[_tokenCounter]->keyword == Keyword::Else)
	{
		output << _tokens[_tokenCounter]->toString() << endl; //for the 'else'
		_tokenCounter++; //this has to be done after every write from the tokens

		output << _tokens[_tokenCounter]->toString() << endl; //for the '{'
		_tokenCounter++; //this has to be done after every write from the tokens

		output << "<statements>" << endl;

		while (_tokens[_tokenCounter]->isStatement())
		{
			compileStatement(); //important while
		}

		output << "</statements>" << endl;

		output << _tokens[_tokenCounter]->toString() << endl; //for the '}'
		_tokenCounter++; //this has to be done after every write from the tokens
	}
	_tokenCounter++; //this has to be done after every write from the tokens

	output << "</ifStatement>" << endl;
}
void XmlCompilationEngine::compileExpression()
{
	output << "<expression>" << endl;
	compileTerm();
	while (_tokens[_tokenCounter]->symbol == Symbol::Equal ||
		_tokens[_tokenCounter]->symbol == Symbol::Pipe ||
		_tokens[_tokenCounter]->symbol == Symbol::Plus ||
		_tokens[_tokenCounter]->symbol == Symbol::Minus ||
		_tokens[_tokenCounter]->symbol == Symbol::Asterisk ||
		_tokens[_tokenCounter]->symbol == Symbol::ForwardSlash ||
		_tokens[_tokenCounter]->symbol == Symbol::Ampersand ||
		_tokens[_tokenCounter]->symbol == Symbol::LessThan ||
		_tokens[_tokenCounter]->symbol == Symbol::GreaterThan
		)
	{
		output << _tokens[_tokenCounter]->toString() << endl; // for the operator
		_tokenCounter++; //this has to be done after every write from the tokens
		
		compileTerm();
	}
	output << "</expression>" << endl;
}

/*
integerConstant | stringConstant | keywordConstant | unaryOp term | varName | varName ' [ ' expression ' ] ' 
| subroutineCall | ' ( ' expression ' ) '
*/
void XmlCompilationEngine::compileTerm()
{
	output << "<term>" << endl;
	if (_tokens[_tokenCounter]->symbol == Symbol::LeftParentheses)
	{
		output << _tokens[_tokenCounter]->toString() << endl; // for the (
		_tokenCounter++; //this has to be done after every write from the tokens

		compileExpression();

		output << _tokens[_tokenCounter]->toString() << endl; // for the )
		_tokenCounter++; //this has to be done after every write from the tokens

	}
	else if (_tokens[_tokenCounter]->symbol == Symbol::Minus || //this is a Unary Op
		_tokens[_tokenCounter]->symbol == Symbol::Tilde
		)
	{
		output << _tokens[_tokenCounter]->toString() << endl; //for the Unary Op
		_tokenCounter++; //this has to be done after every write from the tokens

		compileTerm();

	} else if (_tokens[_tokenCounter + 1]->symbol == Symbol::Period || _tokens[_tokenCounter + 1]->symbol == Symbol::LeftParentheses)
	{

		compileSubroutineCall();

	}
	else if (_tokens[_tokenCounter + 1]->symbol == Symbol::LeftHardBracket)
	{

		output << _tokens[_tokenCounter]->toString() << endl; //for the var name
		_tokenCounter++; //this has to be done after every write from the tokens

		output << _tokens[_tokenCounter]->toString() << endl; //for the [
		_tokenCounter++; //this has to be done after every write from the tokens

		compileExpression();

		output << _tokens[_tokenCounter]->toString() << endl; //for the ]
		_tokenCounter++; //this has to be done after every write from the tokens
	}
	else
	{
		output << _tokens[_tokenCounter]->toString() << endl; //just spit it out
		_tokenCounter++; //this has to be done after every write from the tokens
	}
	

	output << "</term>" << endl;
}

void XmlCompilationEngine::compileExpressionList()
{
	output << _tokens[_tokenCounter]->toString() << endl; //for the (
	_tokenCounter++; //this has to be done after every read of the tokens
	output << "<expressionList>" << endl;
	while (_tokens[_tokenCounter]->symbol != Symbol::RightParentheses)
	{
		compileExpression();
		if (_tokens[_tokenCounter]->symbol == Symbol::Comma)
		{
			output << _tokens[_tokenCounter]->toString() << endl; //for the ','
			_tokenCounter++; //this has to be done after every read of the tokens
		}
	} 

	output << "</expressionList>" << endl;
	output << _tokens[_tokenCounter]->toString() << endl; //for the )
	_tokenCounter++; //this has to be done after every read of the tokens
}