#ifndef __CONSTRUCTCORE_H__
#define __CONSTRUCTCORE_H__
#include <iostream>
using namespace std;

struct BinaryTreeNode
{
	int _value;
	BinaryTreeNode* _pleft;
	BinaryTreeNode* _pright;
};

BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
	if (preorder == NULL || inorder == NULL || length <= 0)
	{
		return NULL;
	}

	return ConstructCore(preorder, preorder + length - 1,
						 inorder, inorder + length - 1);
}

BinaryTreeNode* ConstructCore(int* startPre, int* endPre,
							  int* startInorder, int* endInorder)
{
	//前序遍历第一个节点就是根节点
	int rootValue = startPre[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->_value = rootValue;
	root->_pleft = root->_pright = NULL;

	//递归出口
	if (startPre == endPre)
	{
		//考虑给的树并不是正确的二叉树
		if (startInorder == endInorder && *startInorder == *endInorder)
			return root;

		else
		{
			throw exception("Incalid Input!");
		}
	}

	int* rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		++rootInorder;

	//考虑给的二叉树可能不正确
	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw exception("Invalid Input!");

	int leftLength = rootInorder - startInorder;
	int* leftPreEnd = startPre + leftLength;

	//递归构建左子树
	if (leftLength > 0)
		root->_pleft = ConstructCore(startPre + 1, leftPreEnd, startInorder, rootInorder - 1);

	//递归构建右子树
	if (leftLength + startPre < endPre)
		root->_pright = ConstructCore(leftPreEnd + 1, endPre, rootInorder + 1, endInorder);

	return root;
}


#endif //__CONSTRUCTCORE_H__