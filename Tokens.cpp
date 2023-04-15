#include "Tokens.h"
#include "Opcodes.h"
#include <cctype>

using std::string;


// Returns whether the string token argument represents an identifier such as a variable name.
// Identifier names are non-empty, begin with an alphabetic character, are not terminated with a ':' character,
// and are not an opcode.
// No other error checking is performed.

bool isIdentifier(const string& token)
{
	return (!isOpcode(token) && token.length() != 0 && isalpha(token[0]) && token[token.length() - 1] != ':');
}


// Returns whether the string token argument represents an integer constant.
// Integer constants are non-empty and contain only digits optionally preceded by a '+' or '-' sign.

bool isIntConstant(const string& token)
{
	int digit = 0;
	if (!(token[0] == '+' || token[0] == '-' || isdigit(token[0])))
	{
		digit = 1;
	}
	for (int i{ 1 }; i < token.length(); i++)
	{
		if (!isdigit(token[i]))
		{
			digit = 1;
		}
	}
	if (digit == 0 && token.length() != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// Returns whether the string token argument represents a label definition.
// Labels are non-empty, begin with an alphabetic character, and are terminated with a ':' character.
// No other error checking is performed.

bool isLabelDefinition(const string& token)
{
	return (token.length() != 0 && isalpha(token[0]) && token[token.length() - 1] == ':');
}


// Returns whether the string token argument represents a drone command.
// Drone commands consist of at least 2 characters where the first character is '<'
// and the last character is '>'.
// No other error checking is performed.

bool isDroneCommand(const string& token)
{
	return (token.length() >= 2 && token[0] == '<' && token[token.length() - 1] == '>');
}


// Returns whether the string token argument represents an opcode.

bool isOpcode(const string& token)
{
	return (stringToOpcode(token) != Opcodes::UNDEFINED);
}


// Return the string argument surrounded with double quotes.

string addQuotes(const string& token)
{
	return ('"' + token + '"');
}
