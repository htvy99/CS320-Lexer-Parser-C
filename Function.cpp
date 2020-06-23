#include "Head.h"

//Normalize word
vector<string> normalize(string s, bool& isFinal) {
	int pos = s.length();
	int op = myOpSize;
	cout << s << endl;

	//Check if is final word of statement
	
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
		cout << s << endl;
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
		cout << s << endl;
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
		cout << s << endl;
	}

	std::istringstream buf(s);
	std::istream_iterator<std::string> beg(buf), end;

	vector<std::string> result(beg, end); 
	
	for (auto& s : result)
		cout << s << ",";

	return result;
}

/*word checkType(word& newWord) {
	//Check keyword
	for (int i = 0; i < keywords->size(); ++i) {
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
	for (int i = 0; i < operators->size(); ++i) {
		if (newWord.content == operators[i]) {
			newWord.type = 5;
		}
	}

	//Check identifier
	if (regex_match(newWord.content, identifier)) {
		newWord.type = 2;
	}
	return newWord;
}*/