#include <iostream>
using namespace std;
struct Node
{
	int key;
	Node* left;
	Node* right;
};
typedef Node* Nodeptr;
Nodeptr taoNode(int x) {
	Nodeptr p = new Node;
	p->key = x;
	p->left = p->right = NULL;
	return p;
}
Nodeptr tim(Nodeptr root, int x) {
	if (root == NULL || root->key == x) {
		return root;
	}
	if (root->key < x) {
		return tim(root->right, x);
	}
	return tim(root->left, x);
}

void xoayPhai(Nodeptr &root) {
	if (root == NULL || root->left == NULL)return;
	Nodeptr p = root->left;
	root->left = p->right;
	p->right = root;
	root = p;
}
void xoayTrai(Nodeptr &root) {
	if (root == NULL || root->right == NULL)return;
	Nodeptr p = root->right;
	root->right = p->left;
	p->left = root;
	root = p;
}
Nodeptr loe(Nodeptr &root, Nodeptr q) {
	if (root == NULL)return NULL;
	if (root->left == q) {
		xoayPhai(root);
		return root;
	}
	else if(root->right == q)
	{
		xoayTrai(root);
		return root;
	}
	else
	{
		Nodeptr p;
		if (q->key < root->key) {
			p = root->left;
			if (p == NULL)return NULL;
			if (p->left == q) {
				xoayPhai(root);
				xoayPhai(root);
				return root;
			}
			else if (p->right == q)
			{
				xoayTrai(root->left);
				xoayPhai(root);
				return root;
			}
			else
			{
				return loe(root->left, q);
			}
		}
		else if (q->key>root->key)
		{
			p = root->right;
			if (p == NULL)return NULL;
			if (p->right == q) {
				xoayTrai(root);
				xoayTrai(root);
				return root;
			}
			else if (p->left == q)
			{
				xoayPhai(root->right);
				xoayTrai(root);
				return root;
			}
			else
			{
				return loe(root->right, q);
			}
		}
		else
		{
			return NULL;
		}
	}
}
void loeLenDau(Nodeptr &root, Nodeptr Node) {
	while (Node!=NULL)
	{
		Node = loe(root, Node);
	}
}
Nodeptr timVaLoe(Nodeptr root, int x) {
	Nodeptr Node = tim(root, x);
	loeLenDau(root, Node);
	return Node;
}
Nodeptr chen(Nodeptr& root, int x)
{
	if (root == NULL)
	{
		root = taoNode(x);
		return root;
	}
	if (root->key < x) {
		return chen(root->right, x);
	}
	else if (root->key > x) {
		return chen(root->left, x);
	}
}
Nodeptr chenVaXoay(Nodeptr &root, int x)
{
	Nodeptr p = chen(root, x);
	loeLenDau(root, p);
	return root;
}
Nodeptr xoaNodeVaLoe(Nodeptr& r, int x)
{
	if (r == NULL)
		return NULL;
	Nodeptr timm = tim(r, x);
	loeLenDau(r, timm);
	Nodeptr TL = r->left;
	/*NodePtr TR = r->right;*/
	Nodeptr q = TL;
	while (q->right != NULL)
		q = q->right;
	loeLenDau(r, q);
	r->right = timm->right;
	Nodeptr p = timm;
	delete p;
	return r;
}
void print2DUtil(Node* root, int space) {
	if (root == NULL)
		return;
	space += 10;

	print2DUtil(root->right, space);
	cout << endl;

	for (int i = 0; i < space; i++)
		cout << " ";
	cout << root->key<<"\n";

	print2DUtil(root->left, space);
}

void print2D(Node* root) {
	print2DUtil(root, 0);
}
int main() {
	Nodeptr root;
	root = NULL;
	int x, xoa;
	root = chenVaXoay(root, 24);
	root = chenVaXoay(root, 17);
	root = chenVaXoay(root, 11);
	root = chenVaXoay(root, 53);
	root = chenVaXoay(root, 4);
	root = chenVaXoay(root, 13);
	root = chenVaXoay(root, 15);
	root = chenVaXoay(root, 8);
	root = chenVaXoay(root, 14);
	root = chenVaXoay(root, 27);
	print2D(root);
	cout << "\nNhap x can xoa: ";
	cin >> x;
	xoaNodeVaLoe(root, x);
	print2D(root);
	root = chenVaXoay(root, 10);
	cout << "\nHam sau khi them 10: " << endl;
	print2D(root);
	cout << endl << endl;
	return 0;

}