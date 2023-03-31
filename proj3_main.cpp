#include "IntVariableTable.h"
#include "LabelTable.h"
#include "DroneCommandTable.h"
#include "InstructionTable.h"
#include "FlightPlanParse.h"

#include <iostream>
#include <fstream>

using std::string;


// Provides an example of using the FlightPlanParse class supporting FPL parsing.
// The program prompts for the name of a FPL file, parses the file, and displays
// the parse tables generated.


int main()
{
	std::cout << "Enter the FPL file name without the .txt suffix: ";

	string file_name;
	std::cin >> file_name;
	file_name += ".txt";

	std::ifstream fpl_file(file_name);

	if (fpl_file.is_open()) {
		IntVariableTable  int_variables;
		LabelTable        labels;
		DroneCommandTable drone_commands;
		InstructionTable  instructions;
		FlightPlanParse   fpl_parse(int_variables, labels, drone_commands, instructions);
		string            line;
		while (std::getline(fpl_file, line)) {
			line += ' ';
			fpl_parse.parseLine(line);
		}
		int_variables.display();
		labels.display();
		drone_commands.display();
		if (fpl_parse.parseSuccess()) {
			fpl_parse.displayInstructions();
		}
	}
	else {
		std::cout << "File " << file_name << " not found\n";
	}

	return 0;
}
