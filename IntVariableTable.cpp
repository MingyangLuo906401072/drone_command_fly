#include "IntVariableTable.h"
#include "Tokens.h"

#include <assert.h>
#include <iostream>
#include <iomanip>

using std::string;


// The IntVariableTable constructor dynamically allocates the fixed size array of integer variables.

IntVariableTable::IntVariableTable()
{
	int_variable_table = new IntVariableEntry[MAX_INT_VARIABLES];
}


// The IntVariableTable destructor deallocates the integer variable array.

IntVariableTable::~IntVariableTable()
{
	delete[] int_variable_table;
}


// Returns the number of variables added to the integer variable table.

int IntVariableTable::numVariables() const
{
	return num_int_variables;
}


// Returns the index of the string token argument in the integer variable table,
// or -1 if the variable name is not found in the integer variable table.

int IntVariableTable::lookupVariable(const string& token) const
{
	// TODO
}


// Adds integer variable name and initial value string tokens to the integer variable
// table, and returns the index of the table entry used to store the variable.
// If the variable name is already present in the integer variable table, a message is
// generated and the table entry index is returned.
// If there is no available entry in the integer variable table, a message is generated
// and -1 is returned.

int IntVariableTable::defineVariable(const string& token1, const string& token2)
{
	// TODO
}


// Returns the name string present in the integer variable table entry specified
// by the index argument.
// An assertion is triggered if the index argument is out of bounds.

string IntVariableTable::getName(int index) const
{
	assert(validIndex(index));

	return int_variable_table[index].name;
}


// Returns the numeric value present in the integer variable table entry specified
// by the index argument.
// An assertion is triggered if the index argument is out of bounds.

int IntVariableTable::getValue(int index) const
{
	assert(validIndex(index));

	return int_variable_table[index].value;
}


// Sets the numeric value in the integer variable table entry specified by the index argument.
// An assertion is triggered if the index argument is out of bounds.

void IntVariableTable::setValue(int index, int value)
{
	assert(validIndex(index));

	int_variable_table[index].value = value;
}


// Returns whether the argument is a valid integer variable table index.

bool IntVariableTable::validIndex(int index) const
{
	return ((index >= 0) && (index < num_int_variables));
}


// Displays the contents of the integer variable table on the console.

void IntVariableTable::display() const
{
	if (num_int_variables == 0) {
		std::cout << '\n' << "The integer variable table is empty\n";
	}
	else {
		std::cout << '\n' << "Integer variable table: [index | variable name | initial value]\n\n";
		for (int i = 0; i < num_int_variables; i++) {
			std::cout << std::right << std::setw(8)  << i << "    "
				 << std::left  << std::setw(24) << addQuotes(int_variable_table[i].name)
				 << std::right << std::setw(8)  << int_variable_table[i].value << '\n';
		}
	}
}
