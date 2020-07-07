#include <stdio.h>
#include "BinarySearchTree.h"
#include "BinaryTree2.h"

void BSTMakeAndInit(BTreeNode **pRoot) {
	*pRoot = NULL;
}

BSTData BSTGetNodeData(BTreeNode *bst) {
	return GetData(bst);
}

void BSTInsert(BTreeNode **pRoot, BSTData data) {
	BTreeNode *pNode = NULL;	//parent node
	BTreeNode *cNode = *pRoot;	//current node
	BTreeNode *nNode = NULL;	//new node
	//새 노드가 들어갈 위치 찾기
	while (cNode != NULL) {
		if (data == GetData(cNode)) //값이 동일해서는 안됨
			return;

		pNode = cNode;

		if (GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}
	//새 노드 세팅
	nNode = MakeBTreeNode();
	SetData(nNode, data);

	if (pNode != NULL) {
		if (data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode);
		else
			MakeRightSubTree(pNode, nNode);
	}
	else
		*pRoot = nNode;
}

BTreeNode *BSTSearch(BTreeNode *bst, BSTData target) {
	BTreeNode *cNode = bst; //current node
	BSTData cd;

	while (cNode != NULL) {
		cd = GetData(cNode);

		if (target == cd)
			return cNode;
		else if (target < cd)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	return NULL; //탐색 대상이 없음
}

BTreeNode *BSTRemove(BTreeNode **pRoot, BSTData target) {

	BTreeNode *pVRoot = MakeBTreeNode();//가상 루트 노트
	BTreeNode *pNode = pVRoot;	//parent node
	BTreeNode *cNode = *pRoot;	//current node
	BTreeNode *dNode;			//delete node

	ChangeRightSubTree(pVRoot, *pRoot);

	//search where the target is
	while (cNode != NULL && GetData(cNode) != target) {
		pNode = cNode;

		if (target < GetData(cNode))
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	if (cNode == NULL)
		return NULL;

	dNode = cNode;

	//First: target is a leaf node, just delete the node with doing nothing
	if (GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL) {
		if (GetLeftSubTree(pNode) == dNode)
			RemoveLeftSubTree(pNode);
		else
			RemoveRightSubTree(pNode);
	}

	//Second: target has a single child node
	else if (GetLeftSubTree(dNode) || GetRightSubTree(dNode) == NULL) {
		BTreeNode *dcNode; //the child of target

		if (GetLeftSubTree(dNode) != NULL) //it has a left child
			dcNode = GetLeftSubTree(dNode);
		else
			dcNode = GetRightSubTree(dNode);

		if (GetLeftSubTree(pNode) == dNode)//connect to parent of target with child of target (Grandparent and child)
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode);
	}
	//Third: target has both children, have to uplift the smallest one from the right branch
	else { //Change deleted node to the smallest node of right branch
		BTreeNode *mNode = GetRightSubTree(dNode); //alternative node
		BTreeNode *mpNode = dNode; //the parent of alternative node
		int delData;

		while (GetLeftSubTree(mNode) != NULL) {
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}

		delData = GetData(dNode);
		SetData(dNode, GetData(mNode)); 
		//Actually, don't delete the node but change the data of deleted node.

		if (GetLeftSubTree(mpNode) == mNode)
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
		else //there are no children of deleted node
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

		dNode = mNode; //Data of mNode used, so must delete
		SetData(dNode, delData); //You could think about Heap!
	}

	//if deleted node is a root node
	if (GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot);

	free(pVRoot);
	return dNode;
}

void ShowIntData(int data) {
	printf("%d ", data);
}

void BSTShowAll(BTreeNode *bst) {
	InorderTraverse(bst, ShowIntData);
}