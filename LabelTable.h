#ifndef LABEL_TABLE_H
#define LABEL_TABLE_H


#include <string>


// A label table entry has two fields: the label string (without the ':') and the fixed index
// of the instruction line that the label precedes. 

struct LabelEntry {
	std::string name;
	int         value{ -1 };
};


// All labels are stored in a table in the order they were parsed.

class LabelTable
{
public:		// member functions intended to be used by clients of the class

	LabelTable();		//constructor
	~LabelTable();		// destructor

	int         numLabels() const;
	int         labelIsDefined(const std::string& token, int value);
	int         labelIsOperand(const std::string& token);
	std::string getName(int index) const;
	int         getValue(int index) const;
	bool        validIndex(int index) const;
	std::string instructionIndexToLabels(int index) const;
	void        display() const;

private:	// member functions not intended to be used by clients of the class

	int    lookupLabel(const std::string& token) const;
	int    addLabel(const std::string& token, int value);

private:	// data members should always have private scope

	LabelEntry* label_table{ nullptr };	// dynamically allocated array of labels excluding
	const int   MAX_LABELS{ 5000 };		// maximum number of labels allowed
	int         num_labels{ 0 };		// current number of labels defined
};


#endif // LABEL_TABLE_H
