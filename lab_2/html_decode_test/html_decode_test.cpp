#include "stdafx.h"
#include "../../lab_2/html_decode/html_processor.h"

std::string testString = "<h1>Hello world</h1> U can concat via & and escape symbolsvia \"";
std::string encodedTestString = "&lt;h1&gt;Hello world&lt;/h1&gt; U can concat via &amp; and escape symbolsvia &quot;";
TEST_CASE("Html decoding test")
{
	CHECK(HtmlDecode("") == "");
	CHECK(HtmlDecode("&quot;") == "\"");
	CHECK(HtmlDecode(encodedTestString) == testString);
}
