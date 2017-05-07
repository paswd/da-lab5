#ifndef SUFFIXTREE_H
#define SUFFIXTREE_H

#include <iostream>
#include <string>
#include <map>

//const size_t MAX_CNT = 4096

typedef long long TNumber;

class TSuffixTree;
class TSuffixTreeNode;
class TState;

class TSuffixTreeNode {
public:
	TNumber Left;
	TNumber Right;
	TNumber Parent;
	TNumber Link;
	std::map <char, TNumber> Children;
 	
 	TSuffixTreeNode(void);
 	TSuffixTreeNode(TNumber left, TNumber right, TNumber parent);
	TNumber GetLength(void);
	TNumber &GetChild(char sym);
};
 
class TState {
public:
	TNumber Node
	TNumber Position;
	TState(TNumber node, TNumber position);
};

class TSuffixTree {
private:
	//TSuffixTreeNode Body[MAX_NUM];
	std::vector <TSuffixTreeNode> Body;
	TState SubData;
	TNumber StrCurrent;
public:
	std::string Str[2];

	TSuffixTree(void);
	void AddNode(void);
	void GetStrings(void);
	void Build(void);
	void Build(TNumber num);
	void Extend(TNumber pos);
	TState BeginJob(TState sub_data, TNumber left, TNumber right);
	TNumber Split(TState sub_data);
	TNumber GetSuffixLink(TNumber node);
};

#endif
