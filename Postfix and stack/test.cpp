#include "pch.h"
#include "Tpostfix.h"

TEST(TectingCorrectValue, 2plas3) {
	Tpostfix p("2+3");
	int r;
	r = p.calculate();
	EXPECT_EQ(5, r);
}
TEST(TectingCorrectValue, 2plas3mines4) {
	Tpostfix p("2+3-4");
	int r, rr;
	r = p.calculate();
	rr = 2 + 3 - 4;
	EXPECT_EQ(rr, r);
}
TEST(TectingCorrectValue, TestBrackets) {
	Tpostfix p("5-(2+2)");
	int r, rr;
	r = p.calculate();
	rr = 5 - (2 + 2);
	EXPECT_EQ(rr, r);
}
TEST(TectingCorrectValue, TestLongExpression) {
	Tpostfix p("5-(2+2)-3*5+4/2-1+6-8*1");
	int r, rr;
	r = p.calculate();
	rr = 5 - (2 + 2) - 3 * 5 + 4 / 2 - 1 + 6 - 8 * 1;
	EXPECT_EQ(rr, r);
}
TEST(TectingCorrectValue, TestManyBrackets) {
	Tpostfix p("5-(((2+2)*3-8/(3+1))-(2-5/(2-1)))");
	int r, rr;
	r = p.calculate();
	rr = 5 - (((2 + 2) * 3 - 8 / (3 + 1)) - (2 - 5 / (2 - 1)));
	EXPECT_EQ(rr, r);
}
TEST(TectingErrors, UncorrectSymbol) {
	Tpostfix p("2+r");
	int e;
	p.calculate();
	e = p.status();
	EXPECT_EQ(8, e);
}
TEST(TectingErrors, UncorrectBrackets) {
	Tpostfix p("2-(3-2(");
	int e;
	p.calculate();
	e = p.status();
	EXPECT_EQ(6, e);
}
TEST(TectingErrors, UncorrectLexOrder) {
	Tpostfix p("2-(3-+2)");
	int e;
	p.calculate();
	e = p.status();
	EXPECT_EQ(7, e);
}
TEST(TectingErrors, EmptyString) {
	Tpostfix p("");
	int e;
	p.calculate();
	e = p.status();
	EXPECT_EQ(8, e);
}