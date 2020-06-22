#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <vector>

using namespace std;

class word {
public:
	string content;
	int type;
	//1 - keyword
	//2 - identifier
	//3 - number
	//4 - operator
};

char operators[12][3] = { "+", "-", "*", "/", "%", "**", "=", "+=", "-=", "*=",
					"/=", "%=" };
char keywords[56][11] = { "abstract","and","array()","as","break","callable","case",
						"catch","class","clone","const","continue","declare","default","die",
						"do","echo","else","elseif","empty()","endfor",
						"endif","endswitch","endwhile","eval","exit()",
						"extends","final","for","foreach", "function", "global", "goto", "if", "implements",
						"include", "instanceof", "interface", "isset()", "list()",
						"namespace", "new", "or", "print", "private", "protected", "public", "require", "return", "static",
						"switch", "throw", "try", "use", "var", "while" };
char numbers[10][2] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static vector<word> sentences;
vector<vector<word>> lines;