#include "JackTokens.hpp"
JackTokenFactory* JackTokenFactory::_instance = nullptr;
/*
string sanitize(string text)
{
	ostringstream sanitized{};
	istringstream input{ text };
	while (input.good() == true)
	{
		char next = '\0';
		input >> noskipws >> next;
		switch (next)
		{
		case '<':
			sanitized << "&lt;";
			break;

		case '>':
			sanitized << "&gt;";
			break;
		default:
			sanitized << next;
			break;
		}
	}
	return sanitized.str();
}
*/

string JackToken::toString()
{
	ostringstream result{};
	switch (token)
	{
	case TokenType::Identifier:
		result << "<identifier> " << identifier << " </identifier>";
		break;

	case TokenType::IntegerConstant:
		result << "<integerConstant> " << int_value << " </integerConstant>";
		break;

	case TokenType::Keyword:
		result << "<keyword> " << rawText << " </keyword>";
		break;

	case TokenType::StringConstant:
		result << "<stringConstant> " << string_value << " </stringConstant>";
		break;

	case TokenType::Symbol:
		switch (symbol)
		{
		case Symbol::LessThan:
			result << "<symbol> &lt; </symbol>";
			break;
		case Symbol::GreaterThan:
			result << "<symbol> &gt; </symbol>";
			break;
		case Symbol::Ampersand:
			result << "<symbol> &amp; </symbol>";
			break;
		default:
			result << "<symbol> " << (char)symbol << " </symbol>";
			break;
		}
		break;

	default:
		throw "unknown token type";
		break;
	}
	return result.str();
}

JackTokenizer::JackTokenizer(string file_name) : _file_to_process(file_name)
{
	_symbols['{'] = 1;
	_symbols['}'] = 1;
	_symbols['('] = 1;
	_symbols[')'] = 1;
	_symbols['['] = 1;
	_symbols[']'] = 1;
	_symbols['.'] = 1;
	_symbols[','] = 1;
	_symbols[';'] = 1;
	_symbols['+'] = 1;
	_symbols['-'] = 1;
	_symbols['*'] = 1;
	_symbols['/'] = 1;
	_symbols['&'] = 1;
	_symbols['|'] = 1;
	_symbols['<'] = 1;
	_symbols['>'] = 1;
	_symbols['='] = 1;
	_symbols['~'] = 1;

	_whitespace[' '] = 1;
	_whitespace['\t'] = 1;
	_whitespace['\n'] = 1;
}

string JackTokenizer::removeComments(const string& text)
{
	string result{ text };
	int index = result.find("//");
	result = result.substr(0, index);
	for (int i = 0; result.length() > 0 && i < result.length() - 1; i++)
	{
		//cout << result[i] << result[i + 1] << endl;
		if (result[i] == '/' && result[i + 1] == '*')
		{
			_in_comment_mode = true;
			result[i] = ' ';
			result[i + 1] = ' ';
		}
		else if (result[i] == '*' && result[i + 1] == '/')
		{
			_in_comment_mode = false;
			result[i] = ' ';
			result[i + 1] = ' ';
		}
		if (_in_comment_mode == true)
		{
			result[i] = ' ';
			if (i + 2 == result.length())
			{
				result[i + 1] = ' ';
			}
		}
	}
	return result;
}

vector<vector<string>> JackTokenizer::processFile()
{
	vector<vector<string>> result{};
	ifstream to_process{ _file_to_process };
	bool is_quote_mode = false;
	if (to_process.is_open() == true)
	{
		while (to_process.good() == true)
		{
			string line;
			getline(to_process, line);
			line = removeComments(line);

			istringstream input{ line };
			vector<string> current_line{};
			while (input.good() == true)
			{
				string next;
				getline(input, next);
				if (next.length() > 0)
				{
					//it's possible to have identifiers (and maybe keywords) mixed with symbols, e.g. class foo{
					//we need to separate these out into their own tokens
					istringstream text{ next };
					ostringstream current{};
					while (text.good() == true)
					{
						char ch;
						if (!(text.get(ch)))
						{
							continue;
						}
						if (_symbols.find(ch) == _symbols.end())
						{
							//ignore spaces excpet when inside a string
							if (_whitespace.find(ch) != _whitespace.end() && is_quote_mode == false)
							{
								string currentStr = current.str();
								if (currentStr.length() > 0 && currentStr != " ")
								{
									current_line.push_back(currentStr);
								}
								current = ostringstream{};
								continue;
							}

							//toggle between string and identifier
							if (ch == '"')
							{
								current << ch;
								if (is_quote_mode == true)
								{
									current_line.push_back(current.str());
									current = ostringstream{};
								}

								//toggle quote mode
								is_quote_mode = !is_quote_mode;
							}
							else
							{
								current << ch;
							}
						}
						else
						{
							string currentStr = current.str();
							if (currentStr.length() > 0 && currentStr != " ")
							{
								current_line.push_back(currentStr);
							}
							current = ostringstream{};
							current_line.push_back(string{ ch });
						}
					}
					string leftover = current.str();
					if (leftover.length() > 0 && leftover != " ")
					{
						current_line.push_back(leftover);
					}
				}
			}
			if (current_line.size() > 0)
			{
				result.push_back(current_line);
			}

		}
	}

	return result;
}

JackTokenFactory::JackTokenFactory()
{
	_keyword_map["class"] = Keyword::Class;
	_keyword_map["constructor"] = Keyword::Constructor;
	_keyword_map["function"] = Keyword::Function;
	_keyword_map["method"] = Keyword::Method;
	_keyword_map["field"] = Keyword::Field;
	_keyword_map["static"] = Keyword::Static;
	_keyword_map["var"] = Keyword::Var;
	_keyword_map["int"] = Keyword::Int;
	_keyword_map["char"] = Keyword::Char;
	_keyword_map["boolean"] = Keyword::Boolean;
	_keyword_map["void"] = Keyword::Void;
	_keyword_map["true"] = Keyword::True;
	_keyword_map["false"] = Keyword::False;
	_keyword_map["null"] = Keyword::Null;
	_keyword_map["this"] = Keyword::This;
	_keyword_map["let"] = Keyword::Let;
	_keyword_map["do"] = Keyword::Do;
	_keyword_map["if"] = Keyword::If;
	_keyword_map["else"] = Keyword::Else;
	_keyword_map["while"] = Keyword::While;
	_keyword_map["return"] = Keyword::Return;

	_symbols['{'] = 1;
	_symbols['}'] = 1;
	_symbols['('] = 1;
	_symbols[')'] = 1;
	_symbols['['] = 1;
	_symbols[']'] = 1;
	_symbols['.'] = 1;
	_symbols[','] = 1;
	_symbols[';'] = 1;
	_symbols['+'] = 1;
	_symbols['-'] = 1;
	_symbols['*'] = 1;
	_symbols['/'] = 1;
	_symbols['&'] = 1;
	_symbols['|'] = 1;
	_symbols['<'] = 1;
	_symbols['>'] = 1;
	_symbols['='] = 1;
	_symbols['~'] = 1;
}

JackToken* JackTokenFactory::tokenFromString(string text)
{
	JackToken* token = new JackToken{};
	token->keyword = Keyword::Unknown;
	token->token = TokenType::Unknown;

	//PROJECT 10 TODO: Use IF statements and Table 10.5 Lexical Elements to figure out what kind of token 
	//the supplied text variable represents.  
	token->rawText = text;

	if (_keyword_map.find(text) != _keyword_map.end())
	{
		//this token is a keyword
		token->keyword = _keyword_map[text];
		token->token = TokenType::Keyword;
	}
	else if (_symbols.find(text[0]) != _symbols.end() && text.length() == 1)
	{
		//token is a symbol
		token->symbol = (Symbol)text[0];
		token->token = TokenType::Symbol;
	}
	else if (text[0] == '"')
	{
		//token is a string constant
		token->string_value = text.substr(1, text.size() - 2);
		token->token = TokenType::StringConstant;
	}
	else if (text[0] < '0' || text[0] > '9')
	{
		//token is an identifier
		token->identifier = text;
		token->token = TokenType::Identifier;
	}
	else
	{
		//integer constant
		token->int_value = stoi(text);
		token->token = TokenType::IntegerConstant;
	}

	return token;
}