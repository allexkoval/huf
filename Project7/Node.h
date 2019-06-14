#pragma once
#include <iostream>

class Node
{
public:
	int a;
	char c;
	Node *left, *right;

	Node() { left = right = NULL; }

	Node(Node *L, Node *R) {
		left = L;
		right = R;
		a = L->a + R->a;
	}
};