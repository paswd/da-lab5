#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "suffixtree.h"

using namespace std;

const size_t STRINGS_CNT = 2;

//typedef long long TNumber;

/*
===========
SUFFIX_TREE
===========
*/

TSuffixTree::TSuffixTree(void) {
	this->SubData = TState(0, 0);
	this->Body.resize(1);
}

void TSuffixTree::AddNode(void) {
	this->Body.resize(this->Body.size() + 1);
}
void TSuffixTree::GetStrings(void) {
	getline(cin, this->Str[0]);
	getline(cin, this->Str[1]);
}
void TSuffixTree::Build(void) {
	for (size_t i = 0; i < STRINGS_CNT; i++) {
		this->Build(i);
	}
}
void TSuffixTree::Build(TNumber num) {
	this->StrCurrent = num;
	for (TNumber i = 0; i < this->Str[this->StrCurrent].size(); i++) {
		this->Extend(i);
	}
}
void TSuffixTree::Extend(TNumber pos) {
	while (true) {
		TState zero = this->BeginJob(this->SubData, pos, pos + 1);
		if (zero.Node != -1) {
			this->SubData = zero;
			return;
		}
	 
		TNumber middle = this->Split(this->SubData);
		TNumber leaf = this->Body.size();
		this->AddNode();
		this->Body[leaf] = TSuffixTreeNode(pos, this->Str[this->StrCurrent].size(), middle);
		this->Body[middle].GetChild(this->Str[this->StrCurrent][pos]) = leaf;
	 
		this->SubData.Node = this->GetSuffixLink(middle);
		this->SubData.Position = this->Body[this->SubData.Node].GetLength();
		if (middle == 0) {
			break;
		}
	}
}
TState TSuffixTree::BeginJob(TState sub_data, TNumber left, TNumber right) {
	while (left < right)
		if (sub_data.Position == this->Body[sub_data.Node].GetLength()) {
			sub_data = TState(this->Body[sub_data.Node].GetChild(this->Str[this->StrCurrent][left]), 0);
			if (sub_data.Node == -1) {
				return sub_data;
			}
		} else {
			if (this->Str[this->StrCurrent][this->Body[sub_data.Node].Left + sub_data.Position] != this->Str[this->StrCurrent][left]) {
				return TState(-1, -1);
			}
			if (right - left < this->Body[sub_data.Node].GetLength() - sub_data.Position) {
				return TState(sub_data.Node, sub_data.Position + right - left);
			}
			left += this->Body[sub_data.Node].GetLength() - sub_data.Position;
			sub_data.Position = this->Body[sub_data.Node].GetLength();
		}
	return sub_data;
}
TNumber TSuffixTree::Split(TState sub_data) {
	if (sub_data.Position == this->Body[sub_data.Node].GetLength()) {
		return sub_data.Node;
	}
	if (sub_data.Position == 0) {
		return this->Body[sub_data.Node].Parent;
	}
	TSuffixTreeNode tmp_node = this->Body[sub_data.Node];
	TNumber id = this->Body.size();
	this->AddNode();
	this->Body[id] = TSuffixTreeNode(tmp_node.Left, tmp_node.Left + sub_data.Position, tmp_node.Parent);
	this->Body[tmp_node.Parent].GetChild(this->Str[this->StrCurrent][tmp_node.Left]) = id;
	this->Body[id].GetChild(this->Str[this->StrCurrent][tmp_node.Left + sub_data.Position]) = sub_data.Node;
	this->Body[sub_data.Node].Parent = id;
	this->Body[sub_data.Node].Left += sub_data.Position;
	return id;
}
TNumber TSuffixTree::GetSuffixLink(TNumber node) {
	if (this->Body[node].Link != -1) {
		return this->Body[node].Link;
	}
	if (this->Body[node].Parent == -1) {
		return 0;
	}
	TNumber object = this->GetSuffixLink(this->Body[node].Parent);
	TNumber tmp_summ = 0;
	if (this->Body[node].Parent == 0) {
		tmp_summ = 1;
	}
	this->Body[node].Link = this->Split(BeginJob(TState(object, this->Body[object].GetLength()),
		this->Body[node].Left + tmp_summ, this->Body[node].Right));
	return this->Body[node].Link;
}

/*
================
SUFFIX_TREE_NODE
================
*/

TSuffixTreeNode::TSuffixTreeNode(void) {
	this->Left = 0;
	this->Right = 0;
	this->Parent = -1;
	this->Link = -1;
}
TSuffixTreeNode::TSuffixTreeNode(TNumber left, TNumber right, TNumber parent) {
	this->Left = left;
	this->Right = right;
	this->Parent = parent;
	this->Link = -1;
}
TNumber TSuffixTreeNode::GetLength(void) {
	return this->Right - this->Left;
}
TNumber &TSuffixTreeNode::GetChild(char sym) {
	if (!this->Children.count(sym)) {
		this->Children[sym] = -1;
	}
	return this->Children[sym];
}
 

/*
=====
TSTATE
=====
*/

TState::TState(void) {
	this->Node = 0;
	this->Position = 0;

}
TState::TState(TNumber node, TNumber position) {
	this->Node = node;
	this->Position = position;
}
