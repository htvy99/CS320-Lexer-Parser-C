#include "Head.h"

//Normalize word
vector<string> normalize(string s, bool& isFinal) {
	int pos = s.length();
	int op = myOpSize;

	//Check final word of statement
	if (s.find(';') != std::string::npos) {
		isFinal = true;
		s.pop_back();
	}

	//Check if word contains ( or )
	if (s.find("(") != string::npos) {
		pos = s.find("(");

		//split
		if (pos > 0) {
			s.insert(pos, " ");
			++pos;
		}
		if (pos < s.length()-1) {
			s.insert(pos + 1, " ");
		}
	}
	if (s.find(")") != string::npos) {
		pos = s.find(")");

		//split
		if (pos > 0) {
			s.insert(pos, " ");
			++pos;
		}
		if (pos < s.length() - 1) {
			s.insert(pos + 1, " ");
		}
	}

	//Check if word contains operation
	for (int i = 0; i < myOpSize; ++i) {
		if (s.find(myOp[i]) != string::npos) {
			pos = s.find(myOp[i]);
			op = i;
		}
	}

	//Found operator in word
	if (op < myOpSize) {
		//split
		if (pos > 0) {
			s.insert(pos, " ");
			++pos;
		}
		if (pos < s.length() - 1) {
			s.insert(pos + myOp[op].length(), " ");
		}
	}

	std::istringstream buf(s);
	std::istream_iterator<std::string> beg(buf), end;

	vector<std::string> result(beg, end); 

	return result;
}

int checkType(string s, bool &stringMode) {
	//Check keyword
	for (int i = 0; i < myKwSize; ++i) {
		if (s == myKeyword[i]) {
			return 1;
		}
	}

	//Check integer
	if (regex_match(s, integer)) {
		return 3;
	}
	//Check float
	if (regex_match(s, floatRegex)) {
		return 4;
	}

	//Check operator
	for (int i = 0; i < myOpSize; ++i) {
		if (s == myOp[i]) {
			return 5;
		}
	}

	//Check identifier
	if (regex_match(s, identifier)) {
		return 2;
	}

	//Check string
	if (regex_match(s, startString) | regex_match(s, endString)) {
		stringMode = true;
		if (regex_match(s, endString))
			stringMode = false;
		return 8;
	}

	if (stringMode == true)
		return 8;

	//Check lpar & rpar
	if (s == "(")
		return 6;
	if (s == ")")
		return 7;

	//Check curly bracket
	if (s == "{" | s == "}")
		return 9;


	return 0;
}

//Convert grammar rule into code
//The factor -> look for an int or a float and return a number node
//The term -> look for a factor first, if the current token is the mul|div token, we will look for another factor

//Parser function
void myParser(vector <word> &statement, int start, int end, vector<string> &result) {
	for (int i = start; i < end; ++i) {
		if (statement[i].content == "++") {
			result.push_back("increase");
			result.push_back("(id)");
			//cout << "++";
		}
		if (statement[i].content == "=") {
			result.push_back("assign(");
			result.push_back("variable,");
			statement[i].visited = true;
			statement[i - 1].visited = true;
			myParser(statement, i - 1, i, result);
			myParser(statement, i + 1, end, result);
		}
		if (statement[i].type == 3 && statement[i].visited==false) {
			//cout << statement[i].content << endl;
			result.push_back("int");
			statement[i].visited = true;
			if (i == end - 1)
				result.push_back(")");
		}
		if (statement[i].type == 2 && statement[i].visited == false && i >= 2) {
			result.push_back("variable");
			statement[i].visited = true;
			if (i == end - 1)
				result.push_back(")");
		}
	}
}