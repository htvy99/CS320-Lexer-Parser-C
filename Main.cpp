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

	fin.open("test2.txt");
	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}

	/****************************************************** Lexer **************************************************/
	word newWord;
	bool isFinal = false;
	bool compiled = true;

	while (!fin.eof()) {
		while (fin >> newWord.content && compiled == true)
		{
			//Normalize word
			vector<string> normalized = normalize(newWord.content, isFinal);
			for (auto& s : normalized) {
				newWord.content = s;
				newWord.type = checkType(s);
				sentences.push_back(newWord);
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
				cout << lines[i][j].type << endl;
			}
			cout << ";" << endl;
		}
	}

	/****************************************************** Parser **************************************************/




	return 0;
}