#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <stack>
const int MAX = 50;
using namespace std;

//MA TRAN KE
struct maTranKe {
	int data[MAX][MAX];
	int n;
};
int docMaTran(maTranKe& a, const char* dothi) {
	FILE* fb;
	fb = fopen(dothi, "r");
	if (fb != NULL) {
		fscanf_s(fb, "%d", &a.n);
		for (int i = 0; i < a.n; i++) {
			for (int j = 0; j < a.n; j++) {
				fscanf_s(fb, "%d", &a.data[i][j]);
			}
		}
		fclose(fb);
		return 1;
	}
	return 0;
}
void inMaTran(maTranKe a) {
	for (int i = 0; i < a.n; i++) {
		cout << "\n";
		for (int j = 0; j < a.n; j++) {
			cout << " " << a.data[i][j];
		}
	}
}
//DANH SACH KE
struct Node {
	int trongso;
	int dinhke;
	Node* link;
};
typedef Node* Nodeptr;
struct danhSachKe {
	Nodeptr dsk[MAX];
	int n;
};
struct CanhDoThi {
	int dinhDau;
	int dinhCuoi;
	int trongSo;
};
struct DanhSachCanh {
	CanhDoThi a[MAX];
	int n;
};
struct DanhSachDinh {
	int ds[MAX];
	int n;
};

int docDsKe(danhSachKe& a, const char* dothi) {
	FILE* fb;
	fb = fopen(dothi, "r");
	if (fb == NULL)
		return 0;
	fscanf_s(fb, "%d", &a.n);
	for (int i = 0; i < a.n; i++) {
		a.dsk[i] = NULL;
	}
	for (int i = 0; i < a.n; i++) {
		int m;
		fscanf_s(fb, "%d", &m);
		for (int j = 0; j < m; j++) {
			Node* p = new Node;
			fscanf_s(fb, "%d%d", &p->dinhke, &p->trongso);
			p->link = a.dsk[i];
			a.dsk[i] = p;
		}
	}
	fclose(fb);
	return 1;
}

void inDsKe(danhSachKe a) {
	for (int i = 0; i < a.n; i++) {
		cout << endl;
		Nodeptr p = a.dsk[i];
		cout << i << ":";
		while (p != NULL) {
			cout << "(" << p->dinhke << "," << p->trongso << ")";
			p = p->link;
		}
	}
}
int soDinhDoThi(danhSachKe a) {
	return a.n;
}
int soCanhDoThi_coHuong(danhSachKe a) {
	int count = 0;
	for (int i = 0; i < a.n; i++) {
		Nodeptr p = a.dsk[i];
		while (p != NULL) {
			if (p->dinhke != NULL)
				count++;
			p = p->link;
		}
	}
	return count;
}
// matran ke
int soCanhDoThi_voHuong(maTranKe a) {
	int count = 0;
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (a.data[i][j] != 0)
				count++;
		}
	}
	return count / 2;
}
int bacCuaDinhU_voHuong(maTranKe a, int u) {
	cout << "\nNhap dinh u can tim bac: "; cin >> u;
	int bac = 0;
	for (int i = 0; i < a.n; i++) {
		if (a.data[u][i] != 0) {
			bac++;
		}
	}
	return bac;
}
// danh sach ke
int soBacVao_coHuong_DsKe(danhSachKe a, int u) { //u la dinh can tim bac
	int bacVao = 0;
	for (int i = 0; i < a.n; i++) {
		Nodeptr p = a.dsk[i];
		while (p != NULL) {
			if (p->dinhke == u)
				bacVao++;
			p = p->link;
		}
	}
	return bacVao;
}
int soBacRa_coHuong_DsKe(danhSachKe a, int u) {
	int bacRa = 0;
	Nodeptr p = a.dsk[u];
	while (p != NULL) {
		if (p->dinhke != NULL)
			bacRa++;
		p = p->link;
	}
	return bacRa;
}

CanhDoThi canhTrongSo_min(danhSachKe a) {
	CanhDoThi k{};
	int min = 0;
	int u = 0, v = 0;
	min = a.dsk[0]->trongso;
	for (int i = 0; i < a.n; i++) {
		Nodeptr p = a.dsk[i];
		while (p != NULL) {
			if (min > p->trongso) {
				min = p->trongso;
				u = i;
				v = p->dinhke;
			}
			p = p->link;
		}
	}
	k.dinhCuoi = v;
	k.dinhDau = u;
	k.trongSo = min;
	return k;
}
// ma tran ke
CanhDoThi trongSoMin_MaTran(maTranKe a) { //CHUA FIX XONG
	CanhDoThi k{};
	int u = 0; int v = 0;
	int min = 0;
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (a.data[i][j] != 0) {
				min = a.data[i][j];
				break;
			}
		}
	}
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (min > a.data[i][j] && a.data[i][j]!=0) {
				min = a.data[i][j];
				u = i;
				v = j;
			}
		}
	}
	k.dinhDau = u;
	k.dinhCuoi = v;
	k.trongSo = min;
	return k;
}
//danh sach ke
CanhDoThi trongSoMax_DsKe(danhSachKe a, CanhDoThi& k) {
	int max=0; int u = 0, v = 0;
	for (int i = 0; i < a.n; i++) {
		Nodeptr p = a.dsk[i];
		while (p != NULL) {
			if (max < p->trongso) {
				max = p->trongso;
				k.dinhDau = i;
				k.dinhCuoi = p->dinhke;
			}
			p = p->link;
		}
	}
	k.trongSo = max;
	return k;
}

//tim dinh ke cua u co trong so nho nhat 
bool timDinhKe_min(maTranKe a, int u, int& v) {
	int flag = false;
	int min{};
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (a.data[i][j] != 0) {
				min = a.data[i][j];
				break;
			}
		}
		break;
	}
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (a.data[i][j] != 0) {
				if (min > a.data[i][j])
					min = a.data[i][j];
			}
		}
	}

	for (int j = 0; j < a.n; j++) {
		if (a.data[u][j] == min) {
			flag = true;
			v = j;
		}
	}
	return flag;
}
//Tong do dai canh di ra tu dinh V
int tongCanh(danhSachKe a, int v) {
	int sum = 0;
	Nodeptr  p = a.dsk[v];
	while (p != NULL)
	{
		if (p->dinhke != NULL) {
			sum += p->trongso;
		}
		p = p->link;
	}
	return sum;
}
int tongCanh_MaTran(maTranKe a, int v) {
	int sum = 0;
	for (int i = 0; i < a.n; i++) {
		if (a.data[v][i] != 0) {
			sum += a.data[v][i];
		}
	}
	return sum;
}
//Tong do dai canh di vao tu dinh V
int tongCanhVao(danhSachKe a, int v) {
	int sum = 0;
	for (int i = 0; i < a.n; i++) {
		Nodeptr p = a.dsk[i];
		while (p != NULL) {
			if (p->dinhke == v)
				sum += p->trongso;
			p = p->link;
		}
	}
	return sum;
}
//dao do thi
maTranKe daoDoThi(maTranKe x, maTranKe& y) {
	y.n = x.n;
	for (int i = 0; i < x.n; i++) {
		for (int j = 0; j < x.n; j++) {
			y.data[j][i] = x.data[i][j];
		}
	}
	return y;
}

//Tim tap canh E cua trong so X
void tapCanh(danhSachKe a, DanhSachCanh& ds) { //DANH SACH KE
	cout << "\nNhap trong so: ";
	int x; cin >> x;
	ds.n = 0;
	for (int i = 0; i < a.n; i++) {
		Nodeptr p = a.dsk[i];
		while (p != NULL) {
			if (p->trongso == x) {
				CanhDoThi k{};
				k.dinhDau = i;
				k.dinhCuoi = p->dinhke;
				k.trongSo = x;
				ds.a[ds.n++] = k;
			}
			p = p->link;
		}
	}
	if (ds.n != 0) {
		cout << "\nCac canh co trong so " << x;
		for (int i = 0; i < ds.n; i++) {
			cout << endl;
			cout << "\n>>Canh thu " << i + 1 << ":";
			cout << "\nTrong so: " << ds.a[i].trongSo;
			cout << "\nDinh dau: " << ds.a[i].dinhDau;
			cout << "\nDinh cuoi: " << ds.a[i].dinhCuoi;
		}
	}
	else cout << "\nCanh co trong so " << x << " khong ton tai";
}

void tapCanhmt(maTranKe a, DanhSachCanh& ds) {
	int x; cout << "\nNhap x:"; cin >> x;
	ds.n = 0;
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (a.data[i][j] == x) {
				CanhDoThi E{};
				E.dinhDau = i;
				E.dinhCuoi = j;
				E.trongSo = x;
				ds.a[ds.n++] = E;
			}
		}
	}
	for (int i = 0; i < ds.n; i++) {
		cout << endl;
		cout << "\n>>Canh thu " << i + 1;
		cout << "\nDinh dau: " << ds.a[i].dinhDau;
		cout << "\nDinh cuoi: " << ds.a[i].dinhCuoi;
		cout << "\nTrong so: " << ds.a[i].trongSo;
	}
}
//tinh bac cua dinh
int tongBac(danhSachKe a, int dinh) {
	int bacVao = soBacVao_coHuong_DsKe(a, dinh);
	int bacRa = soBacRa_coHuong_DsKe(a, dinh);
	return bacVao + bacRa;
}
int dinhCoBacCaoNhat(danhSachKe a) {
	int soBacCaoNhat = tongBac(a, 0); int dinh{};
	for (int i = 1; i < a.n; i++) {
		Nodeptr p = a.dsk[i];
		while (p != NULL) {
			if (tongBac(a, i) > soBacCaoNhat) {
				soBacCaoNhat = tongBac(a, i);
				dinh = i;
			}
			p = p->link;
		}
	}
	return dinh;
}
int tongBacMaTran(maTranKe a, int dinh) { //VO HUONG
	int sum = 0;
	for (int i = 0; i < a.n; i++) {
		if (a.data[dinh][i] != 0)
			sum++;
	}
	return sum;
}
DanhSachDinh dinhCoBacCaoNhat_mt(maTranKe a) {
	DanhSachDinh k{}; k.n = 0;
	int max = 0; int dinh = 0;
	for (int i = 0; i < a.n; i++) {
		if (max < tongBacMaTran(a, i)) {
			max = tongBacMaTran(a, i);
			dinh = i;
		}
	}
	for (int i = 0; i < a.n; i++) {
		if (max == tongBacMaTran(a, i)) {
			k.ds[k.n++] = i;
		}
	}
	return k;
}
//int tongBacMaTran_CH(maTranKe a, int dinh) {
//
//}
//Xoa canh trong do thi
maTranKe xoaCanh(maTranKe& a, int u, int v) {
	if (a.data[u][v] != 0) {
		a.data[u][v] = 0;
		a.data[v][u] = 0; //co huong thi bo cai nay di 
	}
	else cout << "\nKhong ton tai canh (U,V)";
	return a;
}
void  xoaCanhDs(danhSachKe& a, int u, int v) {
	Nodeptr NodeRun = a.dsk[u];
	Nodeptr NodeDau = a.dsk[u];
	for (Nodeptr c = a.dsk[u]; c != NULL; c = c->link) {
		if (NodeDau->dinhke == v) {
			a.dsk[u] = a.dsk[u]->link;
			delete  NodeDau;
			break;
		}
		if (c->dinhke == v) {
			NodeRun->link = c->link;
			delete c;
			break;
		}
		NodeRun = c;
	}
}
void BFS(int u, maTranKe g) {
	queue<int> q;
	bool visited[MAX] = { false };
	//memset(visited, false, sizeof(visited));
	visited[u] = true;
	q.push(u);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		cout << v << " ";
		for (int i = 0; i < g.n; i++) {
			if (g.data[v][i] != 0 && !visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}
}
void DFS(maTranKe x, int u) {
	bool visited[MAX] = { false };
	visited[u] = true;
	cout << u << " ";
	for (int i = 0; i < x.n; i++) {
		if (x.data[u][i] != 0 && !visited[i]) {
			DFS(x, i);
		}
	}
}
void ChuyenDoThi(maTranKe& a, danhSachKe b) {
	a.n = b.n;
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			a.data[i][j] = 0;
		}
	}
	for (int i = 0; i < a.n; i++) {
		Nodeptr p = b.dsk[i];
		while (p != NULL) {
			for (int j = 0; j < a.n; j++) {
				if (j == p->dinhke) {
					a.data[i][j] = p->trongso;
				}
			}
			p = p->link;
		}
	}
}
danhSachKe ChuyenMaTran_sangDanhSachKe(maTranKe a) {
	danhSachKe b{};
	b.n = a.n;
	for (int i = 0; i < a.n; i++) {
		b.dsk[i] = NULL;
	}
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (a.data[i][j] != 0) {
				Nodeptr p = new Node();
				p->dinhke = j;
				p->trongso = a.data[i][j];
				p->link = b.dsk[i];
				b.dsk[i] = p;
			}
		}
	}
	return b;
}
int main() {
	//MA TRAN KE
	maTranKe a;
	docMaTran(a, "Text_b8a.txt");
	inMaTran(a);

	//DANH SACH KE
	danhSachKe b;
	if (docDsKe(b, "Text_b8b.txt") == 1)
	{
		inDsKe(b);
	}
	else cout << "\nCan not read file.";

	//BAI 6
	//So dinh do thi
	cout << "\nSo dinh do thi: " << soDinhDoThi(b);
	 
	//Canh do thi co huong
	cout << "\nSo canh do thi co huong: " << soCanhDoThi_coHuong(b);
	cout << "\nSo canh do thi vo huong: " << soCanhDoThi_voHuong(a);

	//Tim bac cua dinh u
	int u = 0;
	cout << "\nBac cua dinh u: "<<bacCuaDinhU_voHuong(a, u);

	//Tim so bac vao cua do thi co huong
	int u=0;
	cout << "\nNhap u de tinh bac vao: "; cin >> u;
	cout << "\nBac vao cua dinh u: " << soBacVao_coHuong_DsKe(b, u);

	//Tim so bac ra co huong
	int u = 0;
	cout << "\nNhap U tim bac ra: "; cin >> u;
	cout << "\nSo bac ra cua u: "<< soBacRa_coHuong_DsKe(b,u);

	//Canh co trong so nho nhat - danh sach ke
	cout << "\nCanh co trong so nho nhat voi dinh dau, dinh cuoi, trong so: ";
	cout << canhTrongSo_min(b).dinhDau << "," << canhTrongSo_min(b).dinhCuoi << "," << canhTrongSo_min(b).trongSo;
	

	//Canh co trong so nho nhat - ma tran ke -  CHUA FIX XONG
	cout << "\nCanh co trong so nho nhat voi dinh dau, dinh cuoi, trong so: ";
	cout << trongSoMin_MaTran(a).dinhDau << "," << trongSoMin_MaTran(a).dinhCuoi << "," << trongSoMin_MaTran(a).trongSo;
	cout << endl;

	//Dinh ke voi u co trong so nho nhat
	int u;
	int v;
	cout << "u:"; cin >> u;
	cout << timDinhKe_min(a, u, v);

	//Tong trong so dinh v
	/*int v; cout << "\nNhap dinh v:"; cin >> v;*/
	cout << "\nTong canh dinh v:" << tongCanh(b, v);

	cout << "\nTong canh dinh v:" << tongCanh_MaTran(a, v);

	cout << "\nTong canh dinh v :" << tongCanhVao(b, v);

	//Canh co trong so lon nhat - Danh sach ke 
	CanhDoThi k{};
	cout << "\nCap canh trong so max, dau+cuoi+ts:";
	trongSoMax_DsKe(b,k);
	cout << k.dinhDau << " " << k.dinhCuoi << " " << k.trongSo;

	//dao do thi 
	maTranKe y{};
	daoDoThi(a, y);
	inMaTran(y);

	////Tim tap canh E cua trong so X
	DanhSachCanh ds{}; ds.n = 0;
	tapCanh(b, ds);

	DanhSachCanh ds1{}; ds1.n = 0;
	tapCanhmt(a, ds1);

	//Dinh co bac cao nhat
	cout << "\nDinh co bac cao nhat: " << dinhCoBacCaoNhat(b);
	cout << "\nDinh co bac cao nhat: ";
		//Bang ma tran
		DanhSachDinh j = dinhCoBacCaoNhat_mt(a);
		for (int i = 0; i < j.n; i++)
		{
			cout << "\nDinh thu " << i + 1;
			cout << "\n";
		}

	//Xoa tap canh u,v
	int u = 0;
	int v = 0;
	cout << "\nNhap canh muon xoa (u,v): "; cin >> u >> v;
		//Bang ma tran
		xoaCanh(a, u, v);
		inMaTran(a);
		//Bang danh sach ke
		xoaCanhDs(b, u, v);
		inDsKe(b);

	//CHUYEN DOI TU DANH SACH KE QUA MA TRAN KE
	
	maTranKe e;
	ChuyenDoThi(e, b);
	inMaTran(e);


	//CHUYEN DOI TU MA TRAN KE SANG DANH SACH KE

	danhSachKe c;
	c = ChuyenMaTran_sangDanhSachKe(a);
	inDsKe(c);

	// DUYET DO THI THEO CHIEU RONG VA CHIEU SAU BFS - DFS




	cout << endl;
	system("pause");
}