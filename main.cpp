//# include "CommandLine.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
# include "EmptyCell.h"
# include "Double.h"
# include "Int.h"
# include "String.h"
# include "Formula.h"
#include <string>
TEST_CASE("Test EmptyCell") {
    EmptyCell* emptyCell = new EmptyCell();
    CHECK((emptyCell->get_value()).value() == 0);
    CHECK((emptyCell->get_size()) == 0);
}

TEST_CASE("Test DoubleNumber") {
    DoubleNumber* DoubleNumberNumber = new DoubleNumber("123.45");
    CHECK((DoubleNumberNumber->get_value()).value() == 123.45);
    CHECK((DoubleNumberNumber->get_size()) == 6);

    DoubleNumber* DoubleNumberNumber1 = new DoubleNumber("-123.45");
    CHECK((DoubleNumberNumber1->get_value()).value() == -123.45);
    CHECK((DoubleNumberNumber1->get_size()) == 7);

    DoubleNumber* DoubleNumberNumber2 = new DoubleNumber("123.4500");
    CHECK((DoubleNumberNumber2->get_value()).value() == 123.45);
    CHECK((DoubleNumberNumber2->get_size()) == 6);

    DoubleNumber* DoubleNumberNumber3 = new DoubleNumber("0.0045");
    CHECK(((double)DoubleNumberNumber3->get_value().value() - (double)0.0045) < 0.00001);
    CHECK((DoubleNumberNumber3->get_size()) == 6);

    DoubleNumber* DoubleNumberNumber4 = new DoubleNumber("0.0");
    CHECK((DoubleNumberNumber4->get_value()).value() == 0.0);
    CHECK((DoubleNumberNumber4->get_size()) == 3);
}

TEST_CASE("Test Integer") {
    Integer* integer = new Integer("5");
    CHECK(integer->get_value().value() == 5);
    CHECK(integer->get_size() == 1);

    Integer* integer1 = new Integer("-1");
    CHECK(integer1->get_value().value() == -1);
    CHECK(integer1->get_size() == 2);

    Integer* integer2 = new Integer("-12345678");
    CHECK(integer2->get_value().value() == -12345678);
    CHECK(integer2->get_size() == 9);
}

TEST_CASE("Test String") {
    String* stringCell = new String("\"Hello World!\"");
    CHECK(stringCell->get_value().value() == 0);
    CHECK(stringCell->get_size() == 12);

    String* stringCell1 = new String("\"\\\\Hello\\\\\""); // The string is "\\Hello\\"
    CHECK(stringCell1->get_value().value() == 0);
    CHECK(stringCell1->get_size() == 7);

    String* stringCell2 = new String("\"\\\"Hello\\\"\""); // The string is "\"Hello\""
    CHECK(stringCell2->get_value().value() == 0);
    CHECK(stringCell2->get_size() == 7);

    String* stringCell3 = new String("\"153\"");
    CHECK(stringCell3->get_value().value() == 153);
    CHECK(stringCell3->get_size() == 3);

    String* stringCell4 = new String("\"-1.53\"");
    CHECK(stringCell4->get_value().value() == -1.53);
    CHECK(stringCell4->get_size() == 5);

    String* stringCell5 = new String("\"-1.53x\"");
    CHECK(stringCell5->get_value().value() == 0);
    CHECK(stringCell5->get_size() == 6);
}

TEST_CASE("Test Formula without references to other cells") {
    Formula* formula = new Formula("=1");
    CHECK(formula->get_value().value() == 1);
    CHECK(formula->get_size() == 1);

    Formula* formula1 = new Formula("=  1");
    CHECK(formula1->get_value().value() == 1);
    CHECK(formula1->get_size() == 1);

    Formula* formula2 = new Formula("=  -1.25 ");
    CHECK(formula2->get_value().value() == -1.25);
    CHECK(formula2->get_size() == 5);

    Formula* formula3 = new Formula("=1 + 13.2 - 5");
    CHECK(formula3->get_value().value() == 9.2);
    CHECK(formula3->get_size() == 3);

    Formula* formula4 = new Formula("=  2 * 7 - 4 + 2  ^4");
    CHECK(formula4->get_value().value() == 26);
    CHECK(formula4->get_size() == 2);

    Formula* formula5 = new Formula("=1 + 13.2 - 5 + 49/0");
    CHECK(formula5->get_value() == std::nullopt);
    CHECK(formula5->get_size() == 5);
}

/*
int main()
{
    CommandLine* line = new CommandLine;
    line -> run();
}
*/


