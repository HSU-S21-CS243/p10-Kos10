#pragma once
#include "CompilationEngine.hpp"
class XmlCompilationEngine : public CompilationEngine
{
private:
public:
	XmlCompilationEngine(vector<JackToken*> tokens) : CompilationEngine(tokens)
	{}

	virtual void compileClass();
	virtual void compileClassVarDec();
	virtual void compileSubroutine();
	virtual void compileSubroutineCall();
	virtual void compileParameterList();
	virtual void compileVarDec();
	virtual void compileStatement();
	virtual void compileDo();
	virtual void compileLet();
	virtual void compileWhile();
	virtual void compileReturn();
	virtual void compileIf();
	virtual void compileExpression();
	virtual void compileTerm();
	virtual void compileExpressionList();
};