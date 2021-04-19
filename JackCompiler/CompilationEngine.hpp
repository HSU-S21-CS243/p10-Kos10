#pragma once
#include "JackTokens.hpp"
#include <vector>
#include <sstream>
#include <string>
using namespace std;
class CompilationEngine
{
protected:
	vector<JackToken*> _tokens;
	int _tokenCounter = 0; 
	ostringstream output;

public:
	CompilationEngine(vector<JackToken*> tokens)
		: _tokens(tokens)
	{}

	void clearOutput()
	{
		output = ostringstream{};
	}

	string toString()
	{
		return output.str();
	}

	void compile()
	{
		compileClass();
	}

	virtual void compileClass() = 0;
	virtual void compileClassVarDec() = 0;

	//for implementing subroutineDec on page 208
	virtual void compileSubroutine() = 0;

	//for implementing subroutineCall on page 209
	virtual void compileSubroutineCall() = 0;
	virtual void compileParameterList() = 0;
	virtual void compileVarDec() = 0;
	virtual void compileStatement() = 0;
	virtual void compileDo() = 0;
	virtual void compileLet() = 0;
	virtual void compileWhile() = 0;
	virtual void compileReturn() = 0;
	virtual void compileIf() = 0;
	virtual void compileExpression() = 0;
	virtual void compileTerm() = 0;
	virtual void compileExpressionList() = 0;

};