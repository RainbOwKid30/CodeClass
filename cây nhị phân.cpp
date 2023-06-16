#include <iostream>
using namespace std;

struct NODE
{
	int Data;
	NODE *Left;
	NODE *Right;
};
typedef NODE* NODEPTR;
typedef NODEPTR BST;
void chen(BST &root, int a) {
	if (root == NULL) {
		BST p = new NODE;
		p->Data = a;
		p->Left = NULL;
		p->Right = NULL;
		root = p;
	}
	else if(a>root->Data)
	{
		chen(root->Right, a);
	}
	else if(a<root->Data)	
	{
		chen(root->Left,a);
	}
}
void PreOrder(BST root)
{
	if (root != NULL)
	{
		cout << root->Data << " ";
		PreOrder(root->Left);
		PreOrder(root->Right);
	}
}
void InOrder(BST root)
{
	if (root != NULL)
	{
		InOrder(root->Left);
		cout << root->Data << "  ";
		InOrder(root->Right);
	}
}
void PostOrder(BST root) {
	if (root == NULL)
		return;
	PostOrder(root->Left);
	PostOrder(root->Right);
	cout << root->Data << " ";
}
NODEPTR tim(BST r, int a) {
	if (r == NULL) return NULL;
	else if (r->Data == a) return r;
	else if (r->Data > a) return tim(r->Left, a);
	else return tim(r->Right, a);
}
void xoa(BST& r, int a) {
	if (r == NULL) return;
	if (a < r->Data) xoa(r->Left, a);
	else if (a > r->Data) xoa(r->Right, a);
	else {
		BST q;
		if (r->Left == NULL) {
			q = r;
			r = r->Right;
			delete q;
		}
		else if (r->Right == NULL) {
			q = r;
			r = r->Left;
			delete q;
		}
		else {
			q = r->Right;
			while (q->Left != NULL)
				q = q->Left;
			r->Data = q->Data;
			xoa(r->Right, q->Data);
		}
	}
}
int DemNode(BST root) {
	if (root == NULL) {
		return 0;
	}
	else
	{
		return 1 + DemNode(root->Left) + DemNode(root->Right);
	}
}
int DemLa(BST root) {
	if (root == NULL) {
		return 0;
	}
	else if (root->Left == NULL && root->Right == NULL) {
		return 1;
	}
	else if(root->Left!=NULL||root->Right!=NULL)
	{
		return DemLa(root->Left) + DemLa(root->Right);
	}
}
void main() {
	const int MAX = 15;
	int day[MAX] = { 24,17,11,7,53,4,13,12,8,43,31,22,14,27,48 };
	BST root = NULL;
	for (int i = 0; i < MAX; i++)
	{
		chen(root, day[i]);
	}
	cout << "\nPreOrder: ";
	PreOrder(root);
	cout << "\nInOrder: ";
	InOrder(root);
	cout << "\nPostOrder: ";
	PostOrder(root);
	cout << "\nnhap nut can tim: ";
	int a;
	cin >> a;
	if (tim(root, a))
		cout << "\ntim thay";
	else
		cout << "\nkhong tim thay";
	cout << "\nnhap nut can xoa: ";
	cin >> a;
	xoa(root, a);
	PreOrder(root);
	cout << "\n so nut la :" << DemNode(root);
	cout << "\n so la la: " << DemLa(root);
}