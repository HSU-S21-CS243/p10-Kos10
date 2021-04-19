#pragma once
#include "JackTokens.hpp"

bool JackToken::isClassDeclaration()
{
	return keyword == Keyword::Class;
}
bool JackToken::isClassVariableDeclaration()
{
	return keyword == Keyword::Static || keyword == Keyword::Field;
}
bool JackToken::isSubroutineDeclaration()
{
	return keyword == Keyword::Constructor || keyword == Keyword::Function || keyword == Keyword::Method;
}
bool JackToken::isVariableDeclaration()
{
	return keyword == Keyword::Var;
}
bool JackToken::isLetStatement()
{
	return keyword == Keyword::Let;
}
bool JackToken::isIfStatement()
{
	return keyword == Keyword::If;
}
bool JackToken::isWhileStatement()
{
	return keyword == Keyword::While;
}
bool JackToken::isDoStatement()
{
	return keyword == Keyword::Do;
}
bool JackToken::isReturnStatement()
{
	return keyword == Keyword::Return;
}
bool JackToken::isStatement()
{
	return isLetStatement() || isIfStatement() || isWhileStatement() || isDoStatement() || isReturnStatement();
}