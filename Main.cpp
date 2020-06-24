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
		/*cout << "Print program\n";
		for (int i = 0; i < lines.size(); ++i) {
			for (int j = 0; j < lines[i].size(); ++j) {
				cout << lines[i][j].content << " ";
				cout << lines[i][j].type << endl;
			}
			cout << ";" << endl << endl;
		}*/

		/****************************************************** Parser **************************************************/
		//Count the number of operator
		int countOp = 0;
		vector <int> pos;
		for (int i = 0; i < lines.size(); ++i) {
			int sn = lines[i].size();
			//Count for each statement
			for (int j = 0; j < sn; ++j) {
				if (lines[i][j].type == 5) {
					++countOp;
					newWord = lines[i][j];
					//get index of operator
					pos.push_back(j);
				}
			}

			if (countOp == 1) {
				if (newWord.content == "=" | newWord.content == "==") {
					//push element before and after index
					parsed.push_back(lines[i][pos[0]]); parsed.push_back(lines[i][pos[0]-1]); parsed.push_back(lines[i][pos[0] + 1]);
					cout << parsed[0].content << " " << parsed[1].content << " " << parsed[2].type << endl;
				}
				else if (newWord.content == "++" | newWord.content == "--") {
					if (pos[0] == 1) { //if index at position 1 => get element before index
						parsed.push_back(lines[i][pos[0]]); parsed.push_back(lines[i][pos[0] - 1]);
					}
					else { //else get element after index (index at position 0)
						parsed.push_back(lines[i][pos[0]]); parsed.push_back(lines[i][pos[0] + 1]);
					}
					cout << parsed[0].content << " " << parsed[1].content << endl;
				}
				tree.push_back(parsed);
			}

			countOp = 0;
		}

		//Print tree
		
	}

	




	return 0;
}