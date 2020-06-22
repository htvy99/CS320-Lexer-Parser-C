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

	fin.open("program.txt");
	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}

	while (!fin.eof()) {
		word newWord;
		while (fin >> newWord.content)
		{
			if (newWord.content.find(';') != std::string::npos || newWord.content.find(',') != std::string::npos) {
				newWord.content.pop_back();
				sentences.push_back(newWord);
				lines.push_back(sentences);
				sentences.clear();
			}
			else {
				sentences.push_back(newWord);
			}
			//cout << newWord.content << " ";

			//Check keyword
			for (int i = 0; i < 56; ++i) {
				if (newWord.content == keywords[i]) {
					newWord.type = 1;
				}
			}

			//Check number
			int tmp = 0;
			for (int i = 0; i < newWord.content.length(); ++i) {
				if (isdigit(newWord.content[i])) {
					++tmp;
				}
			}
			if (tmp == newWord.content.length()) {
				newWord.type = 3;
				tmp = 0;
			}
			
			//Check operator
			for (int i = 0; i < 12; ++i) {
				if (newWord.content == operators[i]) {
					newWord.type = 4;
				}
			}


		}

		//Print program
		/*cout << "Print program\n";
		for (int i = 0; i < lines.size(); ++i) {
			for (int j = 0; j < lines[i].size(); ++j) {
				cout << lines[i][j].content << " Type: ";
				cout << lines[i][j].type << endl;
			}
			cout << endl;
		}*/

		/*for (i = 0; i < 6; ++i) {
			if (ch == operators[i])
				cout << ch << " is operator\n";
		}

		if (isalnum(ch)) {
			buffer[j++] = ch;
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0)) {
			buffer[j] = '\0';
			j = 0;

			if (isKeyword(buffer) == 1)
				cout << buffer << " is keyword\n";
			else
				cout << buffer << " is indentifier\n";
		}*/

	}

	fin.close();

	return 0;
}