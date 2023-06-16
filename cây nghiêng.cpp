#include <iostream>
using namespace std;
struct Node
{
	int info;
	Node* left;
	Node* right;
};
typedef Node* NodePtr;
void khoiTao(NodePtr &r) {
	r->info = 0;
	r->left = NULL;
	r->right = NULL;
}
NodePtr ghep(NodePtr r1, NodePtr r2) {
	NodePtr p = new Node;
	if (r1 == NULL) {
		return r2;
	}
	else if (r2 == NULL) {
		return r1;
	}
	else
	{
		if (r1->info > r2->info) {
			p = r1;
			r1 = r2;
			r2 = p;
		}
		p = r1->left;
		r1->left = r1->right;
		r1->right = p;
		r1->left = ghep(r2, r1->left);
	}
	return r1;
}
NodePtr chen(NodePtr r,int a) {
	NodePtr p = new Node;
	khoiTao(p);
	p->info = a;
	r = ghep(r, p);
	return r;
}
NodePtr xoaMin(NodePtr r) {
	if (r == NULL)
		cout << "\ncay rong";
	NodePtr h1 = NULL;
	NodePtr h2 = NULL;
	h1 = r->left;
	h2 = r->right;
	delete r;
	return ghep(h1, h2);
}
void print2DUtil(Node* root, int space) {
	if (root == NULL)
		return;
	space += 10;
	print2DUtil(root->right, space);
	cout << endl;
	for (int i = 10; i < space; i++)
		cout << " ";
	cout << root->info << "  " << "\n";
	print2DUtil(root->left, space);
}
void print2D(Node* root) {
	print2DUtil(root, 0);
}
void main() {
	NodePtr r = NULL;
	r = chen(r, 24);
	r = chen(r, 17);
	r = chen(r, 11);
	r = chen(r, 53);
	r = chen(r, 4);
	r = chen(r, 13);
	r = chen(r, 38);
	r = chen(r, 43);
	r = chen(r, 31);
	r = chen(r, 22);
	print2D(r);
	cout << "\n==============================";
	r=xoaMin(r);
	print2D(r);
}
