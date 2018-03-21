#include"BTNode.h"
#include"BTNodeLib.h"
#include<queue>
#include<iostream>
#include<vector>
using namespace std;
int main() {
	
	char*iL = "HDIBJEAFKCGM";
	char*pL = "HIDJEBKFMGCA";
	BTNode<char>*root = HZMakeLined(pL, iL,12);
	PrintBTree(root, 40);
}