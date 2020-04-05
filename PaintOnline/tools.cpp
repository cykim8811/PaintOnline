#include "tools.h"

vector<string> split(char* data, char ch) {
	string st = "";
	vector <string> ret;
	for (int i = 0; i < strlen(data); i++) {
		if (data[i] == ch) {
			ret.push_back(st);
			st = "";
		}
		else {
			st += data[i];
		}
	}
	if (st != "")
		ret.push_back(st);
	return ret;
}
