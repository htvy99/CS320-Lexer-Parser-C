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

	fin.open("single.txt");
	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}

	/****************************************************** Lexer **************************************************/
	word newWord;
	bool isFinal = false;
	bool compiled = true;
	bool stringMode = false;

	while (!fin.eof()) {
		while (fin >> newWord.content && compiled == true)
		{
			//Normalize word
			vector<string> normalized = normalize(newWord.content, isFinal);
			for (auto& s : normalized) {
				newWord.content = s;
				newWord.type = checkType(s, stringMode);
				if (newWord.type == 0) {
					cout << "Compiled error at statement " << lines.size() + 1 << endl;
					compiled = false;
					break;
				}
				else if (newWord.type != 9) {
					sentences.push_back(newWord);
				}
			}
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
			cout << ";" << endl << endl;
		}

		/****************************************************** Parser **************************************************/
		for (int i = 0; i < lines.size(); ++i) {
			int level = 0;			//get highest level of statement

			//Assign priority state to operator
			assignPriority(lines[i], level);
			cout << "level = " << level << endl;

			//parse each statement
			myParser(lines[i], 0, lines[i].size(), level, result);
			cout << endl;
			for (int j = 0; j < result.size(); ++j) {
				cout << result[j];
			}
			cout << endl;
			result.clear();
		}
		

		//Print tree
		
	}

	




	return 0;
}