# DT068 - Khu de quy duyet cay bang ngan xep tuong minh

Sinh vien: Nguyen Truong Tan - N24DCDT083 - D24CQDT01-N. GV: Ho Nhut Minh. Hoc phan INT13185, nhom 03.

## Bien dich va chay (Windows, g++)
    g++ -std=c++17 -o DT068_KhuDeQuy DT068_KhuDeQuy_1.cpp
    DT068_KhuDeQuy.exe

## Menu chinh
| Chon | Noi dung |
|------|----------|
| 1 | Nhap cay tu ban phim (co kiem tra input) |
| 2, 3 | Vi du 1 (VD01), Vi du 2 (VD02) |
| 4-8 | Nam ca tren phieu |
| 9, 10, 11 | Cay 5 nhanh, cay 20 nut, day xich 100 nut |
| 12 | Chay TAT CA 15 ca, in lan vet day du |
| 13 | Phan tich va nhan xet |
| 14, 15, 16, 17 | TK01, TK02, BIEN01, BIEN03 |
| 18 | LOI01 - input sai (nut co hai cha) |
| 19 | Tong ket gon 15 ca (PASS/FAIL + bo dem) |

Ket qua mong doi: dong cuoi cua muc 19 la `So ca chay: 15 | PASS: 15 | FAIL: 0`.

## Chay lai tu ban clone sach
    git clone https://github.com/nguyentanjames2242006-gif/DT068_NguyenTruongTan_KhuDeQuyNganXep.git clone_test
    cd clone_test
    git checkout 6b0a39437988f4c95fc1358153c0020ee652fc6b
    git rev-parse HEAD
    g++ -std=c++17 -o DT068_KhuDeQuy DT068_KhuDeQuy_1.cpp
    DT068_KhuDeQuy.exe

Nhap 2 (VD01 -> [1,2,4,3]), 3 (VD02 -> [1]), 19 (PASS: 15, FAIL: 0), roi 0 de thoat.
