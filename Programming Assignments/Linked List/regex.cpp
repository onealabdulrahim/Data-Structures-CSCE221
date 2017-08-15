#include <iostream>
#include <string>
#include <regex>
using namespace std;

void part_1() {
	regex pattern{R"(\d\d)"};
	string to_search = "I would like the number 98 to be found and printed, thanks.";
	smatch matches;
	regex_search(to_search, matches, pattern);
	
	for (auto match : matches){
		cout << match << endl;
	}
}

/*

3.
	a.) Any sequence of two digits is stored in matches. Any matched regex pattern
		from the string to_search is stored in matches.
	b.) \d is regex for one digit

*/

void part_2() {
	regex pattern{R"(<head>(.*?)<\/head>)"};
	string to_search = "<html><head>Wow such header<title>This is a title</title>So top</head>Much body</html>";
	smatch matches;
	regex_search(to_search, matches, pattern);
	
	cout << matches[0] << endl;
	cout << matches[1] << endl;
}

/*

4.
	a.) "\s\S" is regex for a sequence consisting of whitespace first, then
		anything that is not whitespace.
	b.) In matches[0], the first matched regex pattern is stored.
	c.) In matches[1], the second matched regex pattern is stored. This one
		does not interpret "<title>" or other literals
	d.)

*/


int main() {
	//part_1();
	part_2();
}

