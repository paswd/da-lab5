#ifndef RESULT_H
#define RESULT_H

#include <string>

class Result {
private:
	ResultNode *First;
public:
	size_t Length;
	Result(void);
	~Result(void);

	void Clear(void);
	void Add(string str);
	void Print(void);
}
class ResultNode {
public:
	string Value;

	ResultNode *Next;
	//ResultNode *Prev;

	ResultNode(string str);
	~ResultNode(void);
}

#endif
