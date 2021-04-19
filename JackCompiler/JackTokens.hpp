#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

enum class TokenType { Unknown = -1, Keyword, Symbol, Identifier, IntegerConstant, StringConstant };
enum class Keyword { Unknown = -1, Class, Method, Function, Constructor, Int, Boolean, Char, Void, Var, Static, Field, Let, Do, If, Else, While, Return, True, False, Null, This };
enum class Symbol {
	Unknown = -1,
	LeftCurlyBrace = (int)'{',
	RightCurlyBrace = (int)'}',
	LeftParentheses = (int)'(',
	RightParentheses = (int)')',
	LeftHardBracket = (int)'[',
	RightHardBracket = (int)']',
	Period = (int)'.',
	Comma = (int)',',
	SemiColon = (int)';',
	Plus = (int)'+',
	Minus = (int)'-',
	Asterisk = (int)'*',
	ForwardSlash = (int)'/',
	Ampersand = (int)'&',
	Pipe = (int)'|',
	LessThan = (int)'<',
	GreaterThan = (int)'>',
	Equal = (int)'=',
	Tilde = (int)'~',
};

class JackToken
{
public:
	TokenType token;
	Keyword keyword;
	string rawText;
	Symbol symbol;
	string identifier;
	int int_value;
	string string_value;
	string toString();

	bool isClassDeclaration();
	bool isClassVariableDeclaration();
	bool isSubroutineDeclaration();
	bool isVariableDeclaration();
	bool isLetStatement();
	bool isIfStatement();
	bool isWhileStatement();
	bool isDoStatement();
	bool isReturnStatement();
	bool isStatement();
};

class JackTokenizer
{
private:
	string _file_to_process;
	unordered_map<char, int> _symbols;
	unordered_map<char, int> _whitespace;
	bool _in_comment_mode = false;

public:
	JackTokenizer(string file_name);

	JackTokenizer()
	{

	}

	void load(string file_name)
	{
		_file_to_process = file_name;
	}


	string removeComments(const string& text);

	vector<vector<string>> processFile();
};

class JackTokenFactory
{
private:
	unordered_map<string, Keyword> _keyword_map;
	unordered_map<char, int> _symbols;
	static JackTokenFactory* _instance;

	JackTokenFactory();

public:

	static JackTokenFactory* getInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new JackTokenFactory{};
		}
		return _instance;
	}

	Keyword keywordFromString(string keyword)
	{
		return _keyword_map[keyword];
	}

	Symbol symbolFromChar(char symbol)
	{
		return (Symbol)symbol;
	}

	JackToken* tokenFromString(string text);
};