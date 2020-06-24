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

