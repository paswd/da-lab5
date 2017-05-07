#include <iostream>
#include <string>
#include "suffixtree.h"

using namespace std;

int main(void) {
	TSuffixTree tree;
	//tree.Str[0] = "abcabca";
	//cout << "Ptr" << endl;
	//tree.Build(0);
	tree.GetStrings();
	tree.Build();

	return 0;
}
