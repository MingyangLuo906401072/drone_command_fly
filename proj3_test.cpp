#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "DroneCommandTable.h"
#include "FlightPlanParse.h"
#include "InstructionTable.h"
#include "IntVariableTable.h"
#include "LabelTable.h"
#include "Opcodes.h"
#include "Tokens.h"

TEST_CASE("isIdentifier", "[asst10][Token]") {
    // Make sure an empty string is not an identifier
    REQUIRE_FALSE(isIdentifier(""));

    const std::vector<std::string> OPCODES = {
        "int",
        "add",
        "sub",
        "mul",
        "div",
        "set",
        "cmp",
        "beq",
        "bne",
        "bra",
        "cmd",
        "nop",
        "end"
    };

    // Make sure that opcodes are not identifiers
    for (const auto& opcode : OPCODES) {
        REQUIRE_FALSE(isIdentifier(opcode));
    }

    // Check some valid combinations
    std::vector<std::string> VALID = {
        "a", "b", "c", "ident", "myvar",
        "my_var", "my-var", "mYvAr", "this_var", "that_var"
    };

    for (const auto& identifier : VALID) {
        REQUIRE(isIdentifier(identifier));
    }

    const std::vector<std::string> INVALID = {
        "a:", "1b", "/c", "-ident", "_myvar",
        "_var", "my-var:", "@mYvAr", ":this_var", "that_var:"
    };

    for (const auto& identifier : INVALID) {
        REQUIRE_FALSE(isIdentifier(identifier));
    }
}

TEST_CASE("isIntConstant", "[asst10][Token]") {
    // Make sure an empty string is not an identifier
    REQUIRE_FALSE(isIntConstant(""));

    // Check some valid combinations
    const std::vector<std::string> VALID = {
        "1", "2", "5873", "12354", "4812",
        "-87654", "+845", "+1123", "-123", "+1"
    };

    for (const auto& constant : VALID) {
        REQUIRE(isIntConstant(constant));
    }

    // And some invalid combinations
    const std::vector<std::string> INVALID = {
        "A", "B", "C", "D", "E",
        "F", "0.0", "0-9", "12-3", "1+"
    };

    for (const auto& constant : INVALID) {
        REQUIRE_FALSE(isIntConstant(constant));
    }
}

TEST_CASE("isLabelDefinition", "[asst10][Token]") {
    REQUIRE_FALSE(isLabelDefinition(""));

    // Check some valid combinations
    const std::vector<std::string> VALID = {
        "start:", "right:", "left:", "loop_check:", "done:",
        "inc:", "dec:", "hi_there:", "wassup:", "hows_your_day:"
    };

    for (const auto& label : VALID) {
        REQUIRE(isLabelDefinition(label));
    }

    // And some invalid combinations
    const std::vector<std::string> INVALID = {
        "start", "1right:", "2left", "loop_check", "done",
        "inc:2", "dec:3", "56:", "123", "hows_your_day:?"
    };

    for (const auto& label : INVALID) {
        REQUIRE_FALSE(isDroneCommand(label));
    }
}

TEST_CASE("isDroneCommand", "[asst10][Token]") {
    // Make sure an empty string is not an identifier
    REQUIRE_FALSE(isDroneCommand(""));

    // Check some valid combinations
    const std::vector<std::string> VALID = {
        "<land>", "<move %x %y %z>", "<arm>", "<takeoff>", "<initialize>",
        "<disarm>", "<a>", "<1>", "<z>", "<9>"
    };

    for (const auto& command : VALID) {
        REQUIRE(isDroneCommand(command));
    }

    // And some invalid combinations
    const std::vector<std::string> INVALID = {
        "land>", "move %x %y %z>", "arm>", "takeoff>", "initialize>",
        "<disarm", "<a", "1", "z", "9>"
    };

    for (const auto& command : INVALID) {
        REQUIRE_FALSE(isDroneCommand(command));
    }
}

TEST_CASE("IntVariableTable - general test", "[asst11][IntVariableTable]") {
    IntVariableTable table;

    INFO("Trying to look up a variable in an empty table");
    REQUIRE(table.lookupVariable("some_unknown_var") == -1);

    std::vector<std::pair<std::string, std::string>> test_values = {
        { "my_var_a", "0" },
        { "my_var_b", "+1" },
        { "my_var_c", "-2" },
        { "my_var_d", "14" },
        { "my_var_e", "63" },
        { "my_var_f", "12" },
        { "my_var_g", "6548" },
        { "my_var_h", "-255" },
        { "my_var_i", "12321" },
        { "my_var_j", "+123" },
    };

    INFO("Inserting elements into IntVariableTable with defineVariable");
    for (std::size_t i = 0; i < test_values.size(); i++) {
        const auto& variable = test_values[i];
        auto index = table.defineVariable(variable.first, variable.second);
        REQUIRE(table.numVariables() == index + 1);
        REQUIRE(index == i);
    }

    INFO("Looking up elements in IntVariableTable with defineVariable");
    for (int i = static_cast<int>(table.numVariables()) - 1; i >= 0; i--) {
        REQUIRE(table.lookupVariable(test_values[i].first) == i);
    }

    INFO("Trying to look up a non-existent variable in a table");
    REQUIRE(table.lookupVariable("some_unknown_var") == -1);

    auto original_size = table.numVariables();

    INFO("Inserting already-existing elements into IntVariableTable with defineVariable");
    for (std::size_t i = 0; i < test_values.size(); i++) {
        const auto& variable = test_values[i];
        auto index = table.defineVariable(variable.first, variable.second);
        REQUIRE(table.numVariables() == original_size);
        REQUIRE(index == i);
    }
}

TEST_CASE("Adding a lot of elements", "[asst11][IntVariableTable]") {
    IntVariableTable table;

    std::string var_name = "a";
    for (std::size_t i = 0; i < 5000; i++) {
        auto index = table.defineVariable(var_name, "0");
        REQUIRE(index == i);

        {
            auto index = var_name.size() - 1;
            if (var_name[index] != 'z') {
                var_name[index]++;
            } else {
                var_name += "a";
            }
        }
    }

    INFO("Checking that adding the 5001st element fails");
    REQUIRE(table.defineVariable("a1123", "0") == -1);

}
