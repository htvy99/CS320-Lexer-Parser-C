#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <vector>
#include <regex>

using namespace std;

class word {
public:
	string content;
	int type;
	//0 - invalid or { or }
	//1 - keyword
	//2 - identifier
	//3 - integer
	//4 - float
	//5 - operator
	//6 - lpar (
	//7 - rpar )
	//8 - string
};

int operatorSize = 18;
int keywordSize = 58;
char operators[18][3] = { "+", "-", "*", "/", "%", "^", "**", "=", "+=", "-=", "*=",
					"/=", "%=", "<", ">", "==", ">=", "<=" };
char keywords[58][11] = { "abstract","and","array()","as","break","callable","case",
						"catch","class","clone","const","continue","declare","default","die",
						"do","echo","else","elseif","empty()","endfor",
						"endif","endswitch","endwhile","eval","exit()",
						"extends","final","for","foreach", "function", "global", "goto", "if", "implements",
						"include", "instanceof", "interface", "isset()", "list()",
						"namespace", "new", "or", "print", "private", "protected", "public", "require", "return", "static",
						"switch", "throw", "try", "use", "var", "while", "TRUE", "FALSE"};
regex integer("[0-9]+");
regex floatRegex("([-]?[0-9]*\\.[0-9]*)");
regex identifier("(\\$[a-zA-Z_][a-zA-Z0-9_]*)");

static vector<word> sentences;
vector<vector<word>> lines;

word checkType(word& newWord) {
	//Check keyword
	for (int i = 0; i < keywordSize; ++i) {
		if (newWord.content == keywords[i]) {
			newWord.type = 1;
		}
	}

	//Check integer
	if (regex_match(newWord.content, integer)) {
		newWord.type = 3;
	}
	//Check float
	if (regex_match(newWord.content, floatRegex)) {
		newWord.type = 4;
	}

	//Check operator
	for (int i = 0; i < operatorSize; ++i) {
		if (newWord.content == operators[i]) {
			newWord.type = 5;
		}
	}

	//Check identifier
	if (regex_match(newWord.content, identifier)) {
		newWord.type = 2;
	}
	return newWord;
}