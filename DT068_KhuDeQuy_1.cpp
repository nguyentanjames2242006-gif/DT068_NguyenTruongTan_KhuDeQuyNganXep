// DT068 - Khu de quy duyet cay bang ngan xep tuong minh
// Nguyen Truong Tan - N24DCDT083 - D24CQDT01-N | GV: Ho Nhut Minh
// Giao trinh INT1306, muc 5.3.5 (tr.129-130). Duyet truoc: de quy va stack (day con nguoc).
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <limits>
using namespace std;

const int MAXN = 100;
vector<int> con[MAXN + 1];            // con[u]: danh sach con co thu tu
int n, goc;
vector<int> kq_dq, kq_st, mong_doi;   // ket qua de quy, stack, mong doi tinh tay
bool loi_mong_doi = false, chi_tiet = true;
string nhan_ca, loi_cay;
long long so_goi, dem_push, dem_pop;
int sau_stack, sau_dq;

void in_ds(const vector<int>& d) {
    cout << "[";
    for (size_t i = 0; i < d.size(); i++) cout << d[i] << (i + 1 < d.size() ? "," : "");
    cout << "]";
}
void in_stack(stack<int> s) {
    vector<int> t;
    while (!s.empty()) { t.push_back(s.top()); s.pop(); }
    cout << "  Stack: [";
    for (int i = (int)t.size() - 1; i >= 0; i--) cout << t[i] << (i ? ", " : "");
    cout << "]" << endl;
}
void xoa_cay() { for (auto& v : con) v.clear(); }

// Kiem tra input co dung la mot cay hay khong
bool kiem_tra_cay() {
    if (n < 1 || n > MAXN) { loi_cay = "n = " + to_string(n) + " ngoai mien [1,100]"; return false; }
    if (goc < 1 || goc > n) { loi_cay = "goc = " + to_string(goc) + " ngoai mien [1,n]"; return false; }
    int cha[MAXN + 1] = {0};
    for (int u = 1; u <= n; u++)
        for (int c : con[u]) {
            if (c < 1 || c > n) { loi_cay = "nut con " + to_string(c) + " cua nut " + to_string(u) + " ngoai mien [1,n]"; return false; }
            if (c == goc) { loi_cay = "nut goc " + to_string(goc) + " bi khai bao la con cua nut " + to_string(u); return false; }
            if (cha[c]) { loi_cay = "nut " + to_string(c) + " co nhieu hon mot cha (nut " + to_string(cha[c]) + " va nut " + to_string(u) + ")"; return false; }
            cha[c] = u;
        }
    bool den[MAXN + 1] = {false};
    stack<int> s; s.push(goc); den[goc] = true;
    int dem = 0;
    while (!s.empty()) {
        int u = s.top(); s.pop(); dem++;
        for (int c : con[u]) if (!den[c]) { den[c] = true; s.push(c); }
    }
    if (dem != n) { loi_cay = "chi den duoc " + to_string(dem) + "/" + to_string(n) + " nut tu goc (khong lien thong hoac co chu trinh)"; return false; }
    return true;
}

// Duyet truoc bang de quy
void duyet_de_quy(int u, int depth) {
    so_goi++;
    if (depth + 1 > sau_dq) sau_dq = depth + 1;
    kq_dq.push_back(u);
    if (chi_tiet) {
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << "Tham nut " << u << (con[u].empty() ? " (la)" : "") << " | Ket qua: ";
        in_ds(kq_dq); cout << endl;
    }
    for (int c : con[u]) duyet_de_quy(c, depth + 1);
}

// Duyet truoc bang ngan xep tuong minh: day con theo thu tu NGUOC
void duyet_stack(int root) {
    stack<int> st;
    st.push(root); dem_push++; sau_stack = 1;
    if (chi_tiet) { cout << "Buoc 0: Khoi tao stack voi nut goc " << root << endl; in_stack(st); cout << endl; }
    int buoc = 0;
    while (!st.empty()) {
        int u = st.top(); st.pop(); dem_pop++;
        kq_st.push_back(u);
        if (chi_tiet) {
            cout << "Buoc " << ++buoc << ": Pop nut " << u << " -> Tham" << endl << "  Ket qua: ";
            in_ds(kq_st); cout << endl;
            if (con[u].empty()) cout << "  Nut " << u << " la nut la (khong co con)" << endl;
            else { cout << "  Con cua " << u << ": "; in_ds(con[u]); cout << " -> Push nguoc" << endl; }
        }
        for (int i = (int)con[u].size() - 1; i >= 0; i--) { st.push(con[u][i]); dem_push++; }
        if ((int)st.size() > sau_stack) sau_stack = (int)st.size();
        if (chi_tiet) { in_stack(st); cout << "  Do sau stack: " << st.size() << endl << endl; }
    }
}

bool doc_so(int& x) {
    if (cin >> x) return true;
    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    loi_cay = "gia tri nhap khong phai so nguyen";
    return false;
}
bool nhap_cay() {
    xoa_cay();
    cout << "Nhap n (1..100): ";  if (!doc_so(n)) return false;
    if (n < 1 || n > MAXN) { loi_cay = "n = " + to_string(n) + " ngoai mien [1,100]"; return false; }
    cout << "Nhap nut goc: ";     if (!doc_so(goc)) return false;
    for (int i = 1; i <= n; i++) {
        int sc;
        cout << "Nut " << i << " - So con: "; if (!doc_so(sc)) return false;
        if (sc < 0 || sc > n) { loi_cay = "so con cua nut " + to_string(i) + " ngoai mien [0,n]"; return false; }
        if (sc) cout << "  Nhap " << sc << " nut con: ";
        for (int j = 0; j < sc; j++) { int c; if (!doc_so(c)) return false; con[i].push_back(c); }
    }
    return kiem_tra_cay();
}

vector<int> day(int k) { vector<int> v; for (int i = 1; i <= k; i++) v.push_back(i); return v; }
void dat(const string& nhan, const string& mo_ta, const vector<int>& md) {
    nhan_ca = nhan; mong_doi = md;
    if (chi_tiet) { cout << "[" << nhan << "] " << mo_ta << endl << "Ket qua mong doi: "; in_ds(md); cout << endl; }
}

// tc 1..10: vi du + ca phieu + ca bo sung; tc 11..15: TK01, TK02, BIEN01, BIEN03, LOI01
void thiet_lap(int tc) {
    xoa_cay(); loi_mong_doi = false;
    switch (tc) {
    case 1: n = 4; goc = 1; con[1] = {2, 3}; con[2] = {4};
            dat("VD01", "1:[2,3], 2:[4]", {1, 2, 4, 3}); break;
    case 2: n = 1; goc = 1; dat("VD02", "cay mot nut", {1}); break;
    case 3: n = 1; goc = 1; dat("PHIEU1", "ca phieu 1: cay mot nut (trung VD02)", {1}); break;
    case 4: n = 3; goc = 1; con[1] = {2, 3};
            dat("KT09", "ca phieu 2: 1:[2,3]", {1, 2, 3}); break;
    case 5: n = 4; goc = 1; con[1] = {2}; con[2] = {3}; con[3] = {4};
            dat("KT10", "ca phieu 3: day 1->2->3->4", {1, 2, 3, 4}); break;
    case 6: n = 4; goc = 1; con[1] = {3, 2}; con[3] = {4};
            dat("KT11", "ca phieu 4: 1:[3,2], 3:[4]", {1, 3, 4, 2}); break;
    case 7: n = 5; goc = 1; con[1] = {2, 3}; con[2] = {4, 5};
            dat("KT12", "ca phieu 5: 1:[2,3], 2:[4,5]", {1, 2, 4, 5, 3}); break;
    case 8: n = 6; goc = 1; con[1] = {2, 3, 4, 5, 6};
            dat("KT13", "cay 5 nhanh: 1:[2..6]", day(6)); break;
    case 9: n = 20; goc = 1;
            con[1] = {2, 3, 4}; con[2] = {5, 6}; con[3] = {7, 8, 9}; con[4] = {10}; con[5] = {11, 12};
            con[7] = {13, 14}; con[9] = {15, 16, 17}; con[10] = {18, 19, 20};
            dat("KT14", "cay 20 nut", {1, 2, 5, 11, 12, 6, 3, 7, 13, 14, 8, 9, 15, 16, 17, 4, 10, 18, 19, 20}); break;
    case 10: n = 100; goc = 1; for (int i = 1; i < 100; i++) con[i] = {i + 1};
            dat("BIEN02", "day xich 100 nut", day(100)); break;
    case 11: n = 7; goc = 1; con[1] = {2, 3}; con[2] = {4, 5}; con[3] = {6, 7};
            dat("TK01", "nhi phan day du 7 nut", {1, 2, 4, 5, 3, 6, 7}); break;
    case 12: n = 6; goc = 4; con[4] = {6, 2, 5}; con[6] = {1}; con[2] = {3};
            dat("TK02", "goc=4, 4:[6,2,5], 6:[1], 2:[3]", {4, 6, 1, 2, 3, 5}); break;
    case 13: n = 2; goc = 1; con[1] = {2};
            dat("BIEN01", "n=2, 1:[2]", {1, 2}); break;
    case 14: n = 100; goc = 1; for (int i = 2; i <= 100; i++) con[1].push_back(i);
            dat("BIEN03", "hinh sao n=100: 1:[2..100]", day(100)); break;
    case 15: n = 3; goc = 1; con[1] = {2, 3}; con[2] = {3};
            dat("LOI01", "input sai: 1:[2,3], 2:[3] (nut 3 co hai cha)", {}); loi_mong_doi = true; break;
    }
}

void in_so_sanh(bool giong, bool dung, bool co_md) {
    cout << "\n=== SO SANH KET QUA ===" << endl << "De quy   : "; in_ds(kq_dq);
    cout << endl << "Stack    : "; in_ds(kq_st); cout << endl;
    if (co_md) { cout << "Mong doi : "; in_ds(mong_doi); cout << endl; }
    else cout << "Mong doi : (nhap tay - tu tinh tay va doi chieu voi 2 day tren)" << endl;
    cout << (giong ? ">> TRUNG KHOP! Hai phuong phap cho ket qua giong nhau." : ">> KHONG TRUNG! Co sai khac giua hai phuong phap.") << endl;
    if (co_md) cout << (dung ? ">> DUNG voi ket qua mong doi tinh tay." : ">> SAI so voi ket qua mong doi.") << endl;
    cout << "So nut da tham: " << kq_dq.size() << endl
         << "Bo dem: so_lan_goi=" << so_goi << ", push=" << dem_push << ", pop=" << dem_pop
         << ", do_sau_stack_max=" << sau_stack << ", do_sau_de_quy_max=" << sau_dq << endl;
}

void reset() { kq_dq.clear(); kq_st.clear(); so_goi = dem_push = dem_pop = 0; sau_stack = sau_dq = 0; }

bool chay_test(int tc) {
    reset(); thiet_lap(tc);
    if (!kiem_tra_cay()) {
        cout << ">> TU CHOI input: " << loi_cay << endl;
        cout << ">> KET LUAN " << nhan_ca << ": " << (loi_mong_doi ? "PASS (input sai bi tu choi dung nhu mong doi)" : "FAIL (input hop le nhung bi tu choi)") << endl;
        return loi_mong_doi;
    }
    if (loi_mong_doi) { cout << ">> KET LUAN " << nhan_ca << ": FAIL (input sai nhung khong bi tu choi)" << endl; return false; }
    if (chi_tiet) cout << "\n=== DUYET DE QUY ===" << endl;
    duyet_de_quy(goc, 0);
    if (chi_tiet) { cout << "\nKet qua de quy: "; in_ds(kq_dq); cout << "\n\n=== DUYET STACK ===" << endl; }
    duyet_stack(goc);
    if (chi_tiet) { cout << "Ket qua stack : "; in_ds(kq_st); cout << endl; }
    bool giong = (kq_dq == kq_st), dung = giong && kq_st == mong_doi, ok = giong && dung;
    if (chi_tiet) { in_so_sanh(giong, dung, true); cout << ">> KET LUAN " << nhan_ca << ": " << (ok ? "PASS" : "FAIL") << endl; }
    else cout << nhan_ca << "\t" << (ok ? "PASS" : "FAIL") << "\tn=" << n << "\tnut_tham=" << kq_st.size()
              << "\tgoi=" << so_goi << "\tpush=" << dem_push << "\tpop=" << dem_pop
              << "\tmax_stack=" << sau_stack << "\tmax_de_quy=" << sau_dq << endl;
    return ok;
}

void chay_tat_ca(bool chi_tiet_in) {
    chi_tiet = chi_tiet_in;
    int pass = 0;
    cout << "============ CHAY TAT CA VI DU, CA PHIEU VA CA BO SUNG ============" << endl;
    for (int tc = 1; tc <= 15; tc++) {
        if (chi_tiet) cout << "\n######## TEST CASE " << tc << " ########" << endl;
        if (chay_test(tc)) pass++;
    }
    chi_tiet = true;
    cout << "\n============ TONG KET ============" << endl
         << "So ca chay: 15 | PASS: " << pass << " | FAIL: " << 15 - pass << endl
         << "(Ca PHIEU1 trung input voi VD02 nen so ca doc lap = 14)" << endl;
}

void phan_tich() {
    cout << "\n=== PHAN TICH ===" << endl
         << "- Thoi gian loi: O(n) (moi nut 1 push, 1 pop)." << endl
         << "- Bo nho phu: de quy O(h) khung; stack tuong minh toi da O(n) (cay hinh sao n-1, day xich 1)." << endl
         << "- Day con NGUOC vi stack la LIFO: con dau nam tren dinh, duoc tham truoc." << endl
         << "- Phan IN lan vet la O(n^2), khong thuoc loi thuat toan." << endl;
}

int main() {
    int lc;
    do {
        cout << "\n====== DT068 - KHU DE QUY DUYET CAY BANG NGAN XEP ======" << endl
             << " 1. Nhap cay tu ban phim        2. VD01      3. VD02" << endl
             << " 4-8. Ca phieu 1..5             9. Cay 5 nhanh   10. Cay 20 nut   11. Day xich 100 nut" << endl
             << "12. Chay TAT CA (lan vet)      13. Phan tich" << endl
             << "14. TK01   15. TK02   16. BIEN01   17. BIEN03   18. LOI01" << endl
             << "19. Tong ket gon 15 ca          0. Thoat" << endl << "Lua chon: ";
        if (!(cin >> lc)) break;
        cout << endl;
        chi_tiet = true;
        if (lc == 1) {
            reset();
            if (!nhap_cay()) cout << "\n>> TU CHOI input: " << loi_cay << endl;
            else {
                cout << "\n=== DUYET DE QUY ===" << endl; duyet_de_quy(goc, 0);
                cout << "\n=== DUYET STACK ===" << endl;  duyet_stack(goc);
                in_so_sanh(kq_dq == kq_st, true, false);
            }
        }
        else if (lc >= 2 && lc <= 11) chay_test(lc - 1);
        else if (lc == 12) chay_tat_ca(true);
        else if (lc == 13) phan_tich();
        else if (lc >= 14 && lc <= 18) chay_test(lc - 3);
        else if (lc == 19) chay_tat_ca(false);
    } while (lc != 0);
    return 0;
}
