#include <iostream>
#include <string>
#include <string.h>
#include "result.h"

using namespace std;

Result::Result(void) {
	this->First = NULL;
	this->Length = 0;
}
Result::~Result(void) {
	this->Clear();
}
void Result::Clear(void) {
	ResultNode *current = this->First;
	while (current != NULL) {
		ResultNode *next = current->Next;
		delete current;
		current = next;
	}
}
void Result::Add(string str) {
	ResultNode *current = this->First;
	ResultNode *prev = NULL;
	if (str.size() > this->Length) {
		this->Clear();
		this->Length = str.size();
	}

	while (current != NULL) {
		int cmp = strcmp(str.c_str(), current->Value.c_str());
		if (cmp < 0) {
			ResultNode *nw = new ResultNode(str);
			nw->Next = current;
			if (prev != NULL) {
				prev->Next = nw;
			} else {
				this->First = nw;
			}
			return;
		}
		if (cmp == 0) {
			return;
		}
		prev = current;
		current = current->Next;
	}

	ResultNode *nw = new ResultNode(str);
	nw->Next = NULL;
	if (prev != NULL) {
		prev->Next = nw;
	} else {
		this->First = nw;
	}
}
void Result::Print(void) {
	ResultNode *current = this->First;
	while (current != NULL) {
		cout << current->Value << endl;
		current = current->Next;
	}
}

ResultNode::ResultNode(string str) {
	this->Value = str;
}
