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
void XmlCompilationEngine::compileClassVarDec() //todo FIX
{
	//this is broken and BAD...I think????
	output << "<classVarDec>" << endl;

	while (_tokens[_tokenCounter]->symbol != Symbol::SemiColon)
	{
		if (_tokens[_tokenCounter]->symbol == Symbol::LeftParentheses) //I don't think this is needed??
		{
			compileParameterList();
		}
		else
		{
			output << _tokens[_tokenCounter]->toString() << endl;
			_tokenCounter++; //this has to be done after every write from the tokens
		}
	}
	output << _tokens[_tokenCounter]->toString() << endl; //for the ';'
	_tokenCounter++; //this has to be done after every write from the tokens

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
	
	output << _tokens[_tokenCounter]->toString() << endl;
	_tokenCounter++; //this has to be done after every read of the tokens

	//parameter list
	compileParameterList();

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

	output << "</subroutineDec>" << endl;
}

void XmlCompilationEngine::compileSubroutineCall()
{
	//I don't think this will work. I'm at a loss. I've missed some critical piece of information and I don't
	//know how to ask for help in a way that will actually aid me.
	while (_tokens[_tokenCounter]->symbol != Symbol::SemiColon) //go until the end of the statment
	{
		if (_tokens[_tokenCounter]->symbol != Symbol::LeftParentheses)
		{
			compileExpressionList();
		}
		else
		{
			output << _tokens[_tokenCounter]->toString() << endl;
			_tokenCounter++; //this has to be done after every write from the tokens
		}
	}
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

	output << _tokens[_tokenCounter]->toString() << endl; //for the )
	_tokenCounter++; //this has to be done after every read of the tokens

	output << "</parameterList>" << endl;
}
void XmlCompilationEngine::compileVarDec()
{
	output << "<varDec>" << endl;

	while (_tokens[_tokenCounter]->symbol != Symbol::SemiColon)
	{
		if (_tokens[_tokenCounter]->symbol == Symbol::LeftParentheses) //I don't think this is needed??
		{
			compileParameterList();
		}
		else
		{
			output << _tokens[_tokenCounter]->toString() << endl;
			_tokenCounter++; //this has to be done after every write from the tokens
		}
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
	while (_tokens[_tokenCounter]->symbol != Symbol::Equal) //go until the end of the statment
	{
		output << _tokens[_tokenCounter]->toString() << endl;
		_tokenCounter++; //this has to be done after every write from the tokens
	}
	//go until the equal
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
	
	compileExpressionList();

	output << _tokens[_tokenCounter]->toString() << endl; //for the '{'
	_tokenCounter++; //this has to be done after every write from the tokens

	while (_tokens[_tokenCounter]->isStatement())
	{
		compileStatement();
	}

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

	compileExpressionList();
	output << _tokens[_tokenCounter]->toString() << endl; //for the '{'
	_tokenCounter++; //this has to be done after every write from the tokens

	while (_tokens[_tokenCounter]->isStatement())
	{
		compileStatement();
	}
	output << _tokens[_tokenCounter]->toString() << endl; //for the '}'
	if (_tokens[_tokenCounter]->keyword == Keyword::Else)
	{
		output << _tokens[_tokenCounter]->toString() << endl; //for the 'if'
		_tokenCounter++; //this has to be done after every write from the tokens

		output << _tokens[_tokenCounter]->toString() << endl; //for the '{'
		_tokenCounter++; //this has to be done after every write from the tokens

		compileStatement(); //for the else

		output << _tokens[_tokenCounter]->toString() << endl; //for the '}'
		_tokenCounter++; //this has to be done after every write from the tokens
	}
	_tokenCounter++; //this has to be done after every write from the tokens

	output << "</ifStatement>" << endl;
}
void XmlCompilationEngine::compileExpression()
{
	output << "<expression>" << endl;
	while (_tokens[_tokenCounter]->symbol != Symbol::SemiColon &&
		_tokens[_tokenCounter]->symbol != Symbol::RightParentheses &&
		_tokens[_tokenCounter]->symbol != Symbol::RightHardBracket &&
		_tokens[_tokenCounter]->symbol != Symbol::RightCurlyBrace && 
		_tokens[_tokenCounter]->symbol != Symbol::Comma
		)
	{
		if (_tokens[_tokenCounter]->symbol == Symbol::Equal ||
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
			output << _tokens[_tokenCounter]->toString() << endl; //output that operator
			_tokenCounter++; //this has to be done after every write from the tokens
		}
		else
		{
			compileTerm();
		}
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
	//all of this is wrong
	//output << _tokens[_tokenCounter]->toString() << endl;
	//_tokenCounter++; //this has to be done after every write from the tokens
	//if (_tokens[_tokenCounter]->symbol == Symbol::LeftHardBracket)
	//{
	//	output << _tokens[_tokenCounter]->toString() << endl; //for the '['
	//	_tokenCounter++; //this has to be done after every write from the tokens

	//	compileExpression();

	//	output << _tokens[_tokenCounter]->toString() << endl; //for the ']'
	//	_tokenCounter++; //this has to be done after every write from the tokens
	//}
	//all of this is wrong
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