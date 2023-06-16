#include <iostream>
using namespace std;
#define COUNT 10
struct Node {
	int data;
	Node *left;
	Node *right;
	int height;
};

int Max(int a, int b) {
	return(a > b) ? a : b;
}
int tinhChieuCao(Node* root) {
	if (root == NULL)
		return 0;
	return 1 + Max(tinhChieuCao(root->left), tinhChieuCao(root->right));
	return root->height;
}

Node* xoayPhai(Node* root) {
	Node* x = root->left;
	root->left = x->right;
	x->right = root;
	root->height = 1 + Max(tinhChieuCao(root->left), tinhChieuCao(root->right));
	x->height = 1 + Max(tinhChieuCao(x->left), tinhChieuCao(x->right));
	return x;
}

Node* xoayTrai(Node* root) {
	Node* y = root->right;
	root->right = y->left;
	y->left = root;
	root->height = 1 + Max(tinhChieuCao(root->left), tinhChieuCao(root->right));
	y->height = 1 + Max(tinhChieuCao(y->left), tinhChieuCao(y->right));
	return y;
}

Node* chen(Node* root, int giatri) {
	if (root == NULL)
		return new Node{ giatri, NULL, NULL, 1 }; 
	if (giatri > root->data)
		root->right = chen(root->right, giatri);
	else if (giatri < root->data)
		root->left = chen(root->left, giatri);
	else
		return root;
	root->height = 1 + Max(tinhChieuCao(root->left), tinhChieuCao(root->right));
	int heSoCB = tinhChieuCao(root->left) - tinhChieuCao(root->right);
	if (heSoCB > 1 && giatri < root->left->data)
		return xoayPhai(root);
	if (heSoCB < -1 && giatri > root->right->data)
		return xoayTrai(root);
	if (heSoCB > 1 && giatri > root->left->data) {
		root->left = xoayTrai(root->left);
		return xoayPhai(root);
	}
	if (heSoCB < -1 && giatri < root->right->data) {
		root->right = xoayPhai(root->right);
		return xoayTrai(root);
	}

	return root;
}
Node* giaTriLonNhat(Node* root)
{
	Node* p = root;
	while (p->right != NULL)
		p = p->right;
	return p;
}
int giatriCB(Node* root) {
	if (root == NULL)
		return 0;
	return tinhChieuCao(root->left) - tinhChieuCao(root->right);
}
Node* xoaNode(Node* root, int a) {
	if (root == NULL)
		return root;
	if (a > root->data)
		root->right = xoaNode(root->right, a);
	else if (a < root->data)
		root->left = xoaNode(root->left, a);
	else {
		if (root->left == NULL || root->right == NULL) {
			Node* p = root->left;
			if (root->right != NULL)
				p = root->right;
			if (p == NULL) {
				p = root;
				root = NULL;
				delete p;
			}
			else {
				*root = *p;
				delete p;
			}
		}
		else {
			Node* temp = giaTriLonNhat(root->left);
			root->data = temp->data;
			root->right = xoaNode(root->right, temp->data);
		}
	}
	if (root == NULL)
		return root;
	root->height = 1 + Max(tinhChieuCao(root->left), tinhChieuCao(root->right));
	int hesoCB = giatriCB(root);
	if (hesoCB > 1 && giatriCB(root->left) >= 0)
		return xoayPhai(root);
	if (hesoCB < -1 && giatriCB(root->right) <= 0)
		return xoayTrai(root);
	if (hesoCB > 1 && giatriCB(root->left) < 0) {
		root->left = xoayTrai(root->left);
		return xoayPhai(root);
	}
	if (hesoCB < -1 && giatriCB(root->right) > 0) {
		root->right = xoayPhai(root->right);
		return xoayTrai(root);
	}

	return root;
}
void xuat(Node* root, int space) {
	if (root == NULL)
		return;
	space += COUNT;

	xuat(root->right, space);
	cout <<endl;

	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->data << " (" << root->height << ") " << "\n";

	xuat(root->left, space);
}

void xuatCay(Node* root) {
	xuat(root, 0);
}
void NLR(Node*root) {
	if (root != NULL) {
		cout << " " << root->data;
		NLR(root->left);
		NLR(root->right);
	}
}
void LNR(Node*root) {
	if (root != NULL) {
		LNR(root->left);
		cout << " " << root->data;
		LNR(root->right);
	}
}
void LRN(Node*root) {
	if (root != NULL) {
		LRN(root->left);
		LRN(root->right);
		cout << " " << root->data;
	}
}

int main() {
	struct Node *root = NULL;
	Node* tree = NULL;
	root = chen(root, 24);
	root = chen(root, 17);
	root = chen(root, 11);
	root = chen(root, 27);
	root = chen(root, 53);
	root = chen(root, 4);
	root = chen(root, 8);
	root = chen(root, 40);
	root = chen(root, 63);
	root = chen(root, 71);
	root = chen(root, 32);
	root = chen(root, 15);
	root = chen(root, 20);
	root = chen(root, 48);
	root = chen(root, 50);
	root = chen(root, 46);
	root = chen(root, 44);
	xuatCay(root);
	cout << "PreOrder:" << endl;
	NLR(root);
	cout << endl;
	cout << "InOrder:" << endl;
	LNR(root);
	cout << endl;
	cout << "PostOrder:" << endl;
	LRN(root);
	cout << endl;
	root = xoaNode(root, 8);
	xuatCay(root);
	cout << "--------------------------------" << endl;
	root = xoaNode(root, 63);
	xuatCay(root);
	int a;
	cout << "nhap gia tri can xoa: " << endl;
	cin >> a;
	root = xoaNode(root, a);
	xuatCay(root);
}