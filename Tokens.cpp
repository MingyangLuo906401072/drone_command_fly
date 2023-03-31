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
	// TODO
}


// Returns whether the string token argument represents an integer constant.
// Integer constants are non-empty and contain only digits optionally preceded by a '+' or '-' sign.

bool isIntConstant(const string& token)
{
	// TODO
}


// Returns whether the string token argument represents a label definition.
// Labels are non-empty, begin with an alphabetic character, and are terminated with a ':' character.
// No other error checking is performed.

bool isLabelDefinition(const string& token)
{
	// TODO
}


// Returns whether the string token argument represents a drone command.
// Drone commands consist of at least 2 characters where the first character is '<'
// and the last character is '>'.
// No other error checking is performed.

bool isDroneCommand(const string& token)
{
	// TODO
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
