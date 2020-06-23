#include "Head.h"

/*int isKeyword(char buffer[]) {

	int i, flag = 0;

	for (i = 0; i < 56; ++i) {
		if (strcmp(keywords[i], buffer) == 0) {
			flag = 1;
			break;
		}
	}

	return flag;
}*/

int main() {
	ifstream fin;
	string s;

	fin.open("test.txt");
	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}

	/****************************************************** Lexer **************************************************/
	word newWord;
	word par;
	bool isFinal = false;
	bool compiled = true;

	while (!fin.eof()) {
		while (fin >> newWord.content && compiled == true)
		{
			if (newWord.content.find(';') != std::string::npos) {
				isFinal = true;
				//compiled = true;
				newWord.content.pop_back();
			}
			//Check lpar (
			if (newWord.content.find("(") != string::npos) {
				//push ( into sentence as a separate element
				par.content = "(";
				par.type = 6;
				sentences.push_back(par);

				//remove ( from newWord
				newWord.content.erase(newWord.content.begin() + newWord.content.find("("));
				//cout << newWord.content << endl;
			}

			//Check rpar )
			if (newWord.content.find(")") != string::npos) {
				//push ) into sentence as a separate element
				par.content = ")";
				par.type = 7;

				//remove ( from newWord
				newWord.content.erase(newWord.content.begin() + newWord.content.find(")"));
			}

			newWord = checkType(newWord);

			if (newWord.type == 0) {
				/*for (int i = 0; i < operatorSize; ++i) {
					if (newWord.content.find(operators[i])) {

					}
				}*/
				cout << "Compiled error\n";
				compiled = false;
				break;
			}
			
			sentences.push_back(newWord);
			if (par.content == ")") {
				sentences.push_back(par);
			}
			newWord.type = 0;
			newWord.content = "";
			par.content = "";
			par.type = 0;
			if (isFinal == true) {
				lines.push_back(sentences);
				sentences.clear();
				isFinal = false;
			}
		}
	}
	fin.close();

	//Print program
	if (compiled == true) {
		cout << "Print program\n";
		for (int i = 0; i < lines.size(); ++i) {
			for (int j = 0; j < lines[i].size(); ++j) {
				cout << lines[i][j].content << " ";
				//cout << lines[i][j].type << endl;
			}
			cout << ";" << endl;
		}
	}

	/****************************************************** Parser **************************************************/




	return 0;
}