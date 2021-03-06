#include "pch.h"

#include "../c_rational/CRational.h"
#include "../c_rational/math_util.h"
#include <iostream>
#include <sstream>
#include <utility>

using namespace std;

SCENARIO("rational number can be constructed by inputing 0, 1 or 2 parameters")
{
	WHEN("to input 0 parameters")
	{
		CRational n1;

		THEN("it creates rational number with zero numerator")
		{
			REQUIRE(n1.GetNumerator() == 0);
			REQUIRE(n1.GetDenominator() == 1);
			REQUIRE(n1.ToDouble() == 0);
		}
	}

	WHEN("to input 1 parameter")
	{
		CRational n1(10);

		THEN("it creates rational number with numerator equal to parameter and denominator equal to 1")
		{
			REQUIRE(n1.GetNumerator() == 10);
			REQUIRE(n1.GetDenominator() == 1);
			REQUIRE(n1.ToDouble() == 10);
		}
	}

	GIVEN("2 parameters for input")
	{
		WHEN("to input 2 whole numbers as parameters")
		{
			CRational n1(10, 5);

			THEN("it creates rational number with numerator equal to the first parameter and denominator equal to the second parameter")
			{
				REQUIRE(n1.GetNumerator() == 2);
				REQUIRE(n1.GetDenominator() == 1);
				REQUIRE(n1.ToDouble() == 2);
			}
		}

		WHEN("to input 1 whole number and 0 as parameters")
		{
			THEN("it throw exception because denaminator can't equal to zero")
			{
				try
				{
					CRational n1(10, 0);
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					cout << e.what() << '\n';
					REQUIRE(true);
				}
			}
		}
	}
}

SCENARIO("check convertion to double")
{
	WHEN("convert number to double")
	{
		CRational n(3, 5);
		THEN("get float number")
		{
			REQUIRE(n.ToDouble() == 0.6);
		}
	}
}

SCENARIO("check unary + and -")
{
	CRational n(10, 5);

	WHEN("apply - to n")
	{
		n = -n;

		THEN("it changes numerator sign")
		{
			REQUIRE(n.GetNumerator() == -2);
			REQUIRE(n.GetDenominator() == 1);
		}
	}

	WHEN("apply + to n")
	{
		n = +n;

		THEN("it doesn't changes numerator sign")
		{
			REQUIRE(n.GetNumerator() == 2);
			REQUIRE(n.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary +")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("add n2 to n1")
	{
		n1 = n1 + n2;

		THEN("it increase n1 on n2")
		{
			REQUIRE(n1.GetNumerator() == 17);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("add const number to n1")
	{
		n1 = n1 + 5;

		THEN("it increases n1 on const number")
		{
			REQUIRE(n1.GetNumerator() == 7);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}

	WHEN("add n1 to const number")
	{
		n1 = 5 + n1;

		THEN("it return sum of n1 and const number")
		{
			REQUIRE(n1.GetNumerator() == 7);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check +=")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("add n2 to n1")
	{
		n1 += n2;

		THEN("it increase n1 on n2")
		{
			REQUIRE(n1.GetNumerator() == 17);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("add 5 to n1")
	{
		n1 += 5;

		THEN("it increases n1 on const number")
		{
			REQUIRE(n1.GetNumerator() == 7);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary -")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("substruct n2 from n1")
	{
		n1 = n1 - n2;

		THEN("it descrease n1 on n2")
		{
			REQUIRE(n1.GetNumerator() == 11);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("substruct const number from n1")
	{
		n1 = n1 - 5;

		THEN("it decrease n1 on const number")
		{
			REQUIRE(n1.GetNumerator() == -3);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}

	WHEN("substruct n1 from const number")
	{
		n1 = 5 - n1;

		THEN("it return substraction of const number and n1")
		{
			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check -=")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("substruct n2 from n1")
	{
		n1 -= n2;

		THEN("it descrease n1 on n2")
		{
			REQUIRE(n1.GetNumerator() == 11);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("substruct const number from n1")
	{
		n1 -= 5;

		THEN("it decrease n1 on const number")
		{
			REQUIRE(n1.GetNumerator() == -3);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary *")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("multiply n1 and n2")
	{
		n1 = n1 * n2;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 6);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("multiply const number and n1")
	{
		n1 = 5 * n1;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 10);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}

	WHEN("multiply n1 and const number")
	{
		n1 = n1 * 5;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 10);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary *=")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("multiply n1 and n2")
	{
		n1 *= n2;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 6);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("multiply n1 and const number")
	{
		n1 *= 5;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 10);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary /")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("devide n1 by n2")
	{
		n1 = n1 / n2;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 14);
			REQUIRE(n1.GetDenominator() == 3);
		}
	}

	WHEN("devide const number by n1")
	{
		n1 = 5 / n1;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 5);
			REQUIRE(n1.GetDenominator() == 2);
		}
	}

	WHEN("devide n1 by const number")
	{
		n1 = n1 / 5;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 2);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check /=")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("devide n1 by n2")
	{
		n1 /= n2;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 14);
			REQUIRE(n1.GetDenominator() == 3);
		}
	}

	WHEN("devide n1 by const number")
	{
		n1 /= 5;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 2);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}

	WHEN("devide n1 by zero")
	{
		THEN("it throws an exception")
		{
			try
			{
				n1 /= 0;
				REQUIRE(false);
			}
			catch (const exception& e)
			{
				cout << e.what() << '\n';
				REQUIRE(true);
				REQUIRE(n1.GetNumerator() == 2);
				REQUIRE(n1.GetDenominator() == 1);
			}
		}
	}
}

SCENARIO("check boolean ==")
{
	WHEN("check equality of 1/2 and 1/2")
	{
		CRational n1(1, 2);
		CRational n2(1, 2);

		THEN("it returns true")
		{
			REQUIRE(n1 == n2);

			REQUIRE(n1.GetNumerator() == 1);
			REQUIRE(n1.GetDenominator() == 2);
			REQUIRE(n2.GetNumerator() == 1);
			REQUIRE(n2.GetDenominator() == 2);
		}
	}

	WHEN("check equality of not equal numbers")
	{
		CRational n1(1, 2);
		CRational n2(2, 3);

		THEN("it returns false")
		{
			REQUIRE_FALSE(n1 == n2);

			REQUIRE(n1.GetNumerator() == 1);
			REQUIRE(n1.GetDenominator() == 2);
			REQUIRE(n2.GetNumerator() == 2);
			REQUIRE(n2.GetDenominator() == 3);
		}
	}

	WHEN("check equality of equal numbers")
	{
		CRational n(4, 1);

		THEN("it returns true")
		{
			REQUIRE(n == 4);

			REQUIRE(n.GetNumerator() == 4);
			REQUIRE(n.GetDenominator() == 1);
		}
	}
}

SCENARIO("check boolean !=")
{
	WHEN("check inequality of inequal numbers")
	{
		CRational n1(1, 2);
		CRational n2(1, 2);

		THEN("it returns false")
		{
			REQUIRE_FALSE(n1 != n2);

			REQUIRE(n1.GetNumerator() == 1);
			REQUIRE(n1.GetDenominator() == 2);
			REQUIRE(n2.GetNumerator() == 1);
			REQUIRE(n2.GetDenominator() == 2);
		}
	}

	WHEN("check inequality of inequal numbers")
	{
		CRational n1(1, 2);
		CRational n2(2, 3);

		THEN("it returns true")
		{
			REQUIRE(n1 != n2);

			REQUIRE(n1.GetNumerator() == 1);
			REQUIRE(n1.GetDenominator() == 2);
			REQUIRE(n2.GetNumerator() == 2);
			REQUIRE(n2.GetDenominator() == 3);
		}
	}

	WHEN("check inequality of equal numbers")
	{
		CRational n(4, 1);

		THEN("it returns false")
		{
			REQUIRE_FALSE(n != 4);

			REQUIRE(n.GetNumerator() == 4);
			REQUIRE(n.GetDenominator() == 1);
		}
	}
}

SCENARIO("check <")
{
	WHEN("check `<` of greatest and lowest number")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);
			CRational n2(2, 4);

			REQUIRE_FALSE(n1 < n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 1);
			REQUIRE(n2.GetDenominator() == 2);
		}
	}

	WHEN("check `<` of lowest and greates number")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);

			REQUIRE(n1 < 4);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check `>`")
{
	WHEN("check `>` of greatest and lowest number")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);
			CRational n2(2, 4);

			REQUIRE(n1 > n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 1);
			REQUIRE(n2.GetDenominator() == 2);
		}
	}

	WHEN("check `>` of lowerst and greate number")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);

			REQUIRE_FALSE(n1 > 4);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check >=")
{
	WHEN("check `>=` of grestest and lowest number")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);
			CRational n2(2, 4);

			REQUIRE(n1 >= n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 1);
			REQUIRE(n2.GetDenominator() == 2);
		}
	}

	WHEN("check `>=` of equal numbers")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);
			CRational n2(6, 10);

			REQUIRE(n1 >= n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 3);
			REQUIRE(n2.GetDenominator() == 5);
		}
	}

	WHEN("check `>=` of lowerst and greates number")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);

			REQUIRE_FALSE(n1 >= 4);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check `<=`")
{
	WHEN("check `<=` of greates and lowerst number")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);
			CRational n2(2, 4);

			REQUIRE_FALSE(n1 <= n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 1);
			REQUIRE(n2.GetDenominator() == 2);
		}
	}

	WHEN("check `<=` of equal numbers")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);
			CRational n2(6, 10);

			REQUIRE(n1 <= n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 3);
			REQUIRE(n2.GetDenominator() == 5);
		}
	}

	WHEN("check `<=` of greates and lowest number")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);

			REQUIRE_FALSE(4 <= n1);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check >>")
{
	WHEN("try to get from rational number from correct input")
	{
		istringstream input("3/5");
		CRational n;

		THEN("get rational number")
		{
			input >> n;
			REQUIRE(n.GetNumerator() == 3);
			REQUIRE(n.GetDenominator() == 5);
		}
	}

	WHEN("try to get from rational number from incorrect input")
	{
		istringstream input("3 5");
		CRational n;

		THEN("get exception")
		{
			try
			{
				input >> n;
				REQUIRE(false);
			}
			catch (const std::exception& e)
			{
				cout << e.what() << '\n';
				REQUIRE(true);
			}
		}
	}
}

SCENARIO("check <<")
{
	WHEN("apply `<<` for rational number")
	{
		ostringstream output;
		CRational n(3, 5);

		THEN("get rational 3/5 in output")
		{
			output << n;
			REQUIRE(output.str() == "3/5");

			REQUIRE(n.GetNumerator() == 3);
			REQUIRE(n.GetDenominator() == 5);
		}
	}

	WHEN("apply << for const int number")
	{
		ostringstream output;
		CRational n(3);

		THEN("get rational 3/1 in output")
		{
			output << n;
			REQUIRE(output.str() == "3/1");

			REQUIRE(n.GetNumerator() == 3);
			REQUIRE(n.GetDenominator() == 1);
		}
	}
}

SCENARIO("check convertion to Compound fraction")
{
	WHEN("convert rational number with intPart")
	{
		CRational n(9, 5);
		THEN("get intPart and normal rational number")
		{
			REQUIRE(n.ToCompoundFraction() == make_pair<int, CRational>(1, CRational(4, 5)));
		}
	}

	WHEN("convert rational number without intPart")
	{
		CRational n(4, 5);
		THEN("get 0 as intPart and normal rational number")
		{
			REQUIRE(n.ToCompoundFraction() == make_pair<int, CRational>(0, CRational(4, 5)));
		}
	}

	WHEN("convert negative retional number with intPart")
	{
		CRational n(-9, 5);
		THEN("get intPart and negative normal rational number")
		{
			REQUIRE(n.ToCompoundFraction() == make_pair<int, CRational>(-1, CRational(-4, 5)));
		}
	}

	WHEN("convert zero")
	{
		CRational n(0);
		THEN("get zero and 0/1")
		{
			REQUIRE(n.ToCompoundFraction() == make_pair<int, CRational>(0, CRational(0, 1)));
		}
	}
}

SCENARIO("check getting of LCM")
{
	WHEN("try to get LCM of natural number and zero")
	{
		THEN("it returns zero")
		{
			REQUIRE(LCM(0, 5) == 0);
		}
	}
}
