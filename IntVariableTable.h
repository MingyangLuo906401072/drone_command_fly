#ifndef INT_VARIABLE_TABLE_H
#define INT_VARIABLE_TABLE_H


#include <string>


// An integer variable table entry has two fields: the variable name string (token) and its
// current integer value that can change during FPL execution.

struct IntVariableEntry {
	std::string name;
	int         value{ -1 };
};


// All integer variables are stored in a table in the order they were parsed.

class IntVariableTable
{
public:		// member functions intended to be used by clients of the class

	IntVariableTable();			// constructor
	~IntVariableTable();		// destructor

	int         numVariables() const;
	int         lookupVariable(const std::string& token) const;
	int         defineVariable(const std::string& token1, const std::string& token2);
	std::string getName(int index) const;
	int         getValue(int index) const;
	void        setValue(int index, int value);
	bool        validIndex(int index) const;
	void        display() const;

private:	// data members should always have private scope

	IntVariableEntry* int_variable_table{ nullptr };	// dynamically allocated array of integer variables
	const int         MAX_INT_VARIABLES{ 5000 };		// maximum number of variables allowed
	int               num_int_variables{ 0 };			// current number of variables defined
};


#endif // INT_VARIABLE_TABLE_H
