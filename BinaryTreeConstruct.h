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
	//ǰ�������һ���ڵ���Ǹ��ڵ�
	int rootValue = startPre[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->_value = rootValue;
	root->_pleft = root->_pright = NULL;

	//�ݹ����
	if (startPre == endPre)
	{
		//���Ǹ�������������ȷ�Ķ�����
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

	//���Ǹ��Ķ��������ܲ���ȷ
	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw exception("Invalid Input!");

	int leftLength = rootInorder - startInorder;
	int* leftPreEnd = startPre + leftLength;

	//�ݹ鹹��������
	if (leftLength > 0)
		root->_pleft = ConstructCore(startPre + 1, leftPreEnd, startInorder, rootInorder - 1);

	//�ݹ鹹��������
	if (leftLength + startPre < endPre)
		root->_pright = ConstructCore(leftPreEnd + 1, endPre, rootInorder + 1, endInorder);

	return root;
}


#endif //__CONSTRUCTCORE_H__