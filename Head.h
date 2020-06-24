#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <vector>
#include <regex>
#include <sstream>
#include <iterator>

using namespace std;

class word {
public:
	string content;
	int type;
	bool visited = false;
	int priority = 0;
	//0 - invalid or { or }
	//1 - keyword
	//2 - identifier
	//3 - integer
	//4 - float
	//5 - operator
	//6 - lpar (
	//7 - rpar )
	//8 - string
	//9 - curly bracket { } 
};

class Node {

};

class intNode {
};

class operatorNode : Node {
	Node leftNode;
	Node rightNode;
};



static int myOpSize = 20;
static int myKwSize = 58;
static string myOp[20]= { "+", "-", "*", "/", "%", "^", "**", "=", "+=", "-=", "*=",
					"/=", "%=", "<", ">", "==", ">=", "<=", "++", "--"};
static string myKeyword[58] = { "abstract","and","array()","as","break","callable","case",
						"catch","class","clone","const","continue","declare","default","die",
						"do","echo","else","elseif","empty()","endfor",
						"endif","endswitch","endwhile","eval","exit()",
						"extends","final","for","foreach", "function", "global", "goto", "if", "implements",
						"include", "instanceof", "interface", "isset()", "list()",
						"namespace", "new", "or", "print", "private", "protected", "public", "require", "return", "static",
						"switch", "throw", "try", "use", "var", "while", "TRUE", "FALSE"};
static regex integer("[0-9]+");
static regex floatRegex("([-]?[0-9]*\\.[0-9]*)");
static regex identifier("(\\$[a-zA-Z_][a-zA-Z0-9_]*)");
static regex startString("\"(.)*");
static regex endString("(.)*\"");

static vector<word> sentences;
static vector<vector<word>> lines;
static vector <string> result;
static int level;


vector<string> normalize(string s, bool& isFinal);
int checkType(string s, bool& stringMode);
void assignPriority(vector<word>& statement, int &level);
void myParser(vector <word> &statement, int start, int end, vector<string> &result);