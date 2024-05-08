/* 
MSSV: 3123411257 
Họ và tên: Võ Minh Sang 
lớp: DCT123C5, Đại Học Sàì Gòn 
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//===================== Khai báo các cấu trúc dữ liệu =====================

struct KhoangThoiGianRanh {
    int thu;
    int gioBatDau;
    int gioKetThuc;
};

struct chuyenDoiTime {
    vector<vector<KhoangThoiGianRanh>> danhSachThoiGianRanh; // Vector 2 chiều lưu trữ danh sách khoảng thời gian rảnh cho mỗi ngày
};

struct nodeGiangVien {
    string tenThanhVien;
    string hocHamHocVi;
    chuyenDoiTime time;
    nodeGiangVien* next = nullptr;
};

struct nodeHoiDong {
    string tenKhoa;
    chuyenDoiTime thoiGianToChuc;
    nodeGiangVien* danhSachThanhVien[3]; // Mảng chứa con trỏ đến 3 thành viên trong hội đồng
    nodeHoiDong* next; //liên kết đến hội đồng tiếp theo cùng khoa
};

struct Khoa {
    nodeGiangVien* head;
    int soLuongThanhVien;
    nodeHoiDong* danhSachHoiDong;
};

//============================== Các hàm xử lý ==============================

void themThanhVienVaoKhoa(Khoa& khoa, string ten, string hocVi) {
    nodeGiangVien* newNode = new nodeGiangVien;
    newNode->tenThanhVien = ten;
    newNode->hocHamHocVi = hocVi;

    // Khoa rỗng (thêm thành viên đầu tiên)
    if (khoa.head == nullptr) {
        khoa.head = newNode;
    } else {
        // Đã tồn tại ít nhất 1 thành viên => thêm thành viên mới, liên kết với thành viên cũ
        nodeGiangVien* curr = khoa.head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    khoa.soLuongThanhVien++;
}

vector<KhoangThoiGianRanh> timGiaoThoiGianRanh(chuyenDoiTime time1, chuyenDoiTime time2, chuyenDoiTime time3, int thu) {
    vector<KhoangThoiGianRanh> giaoDanhSachThoiGianRanh;
    int index = thu - 2; // Chỉ số của ngày trong tuần (thứ 2 có chỉ số 0, thứ 3 có chỉ số 1, ...)
    if (index < time1.danhSachThoiGianRanh.size() && index < time2.danhSachThoiGianRanh.size() && index < time3.danhSachThoiGianRanh.size()) {
        for (KhoangThoiGianRanh khoang1: time1.danhSachThoiGianRanh[index]) {
            for (KhoangThoiGianRanh khoang2: time2.danhSachThoiGianRanh[index]) {
                for (KhoangThoiGianRanh khoang3: time3.danhSachThoiGianRanh[index]) {
                    double gioBatDauGiao = max(khoang1.gioBatDau, max(khoang2.gioBatDau, khoang3.gioBatDau));
                    double gioKetThucGiao = min(khoang1.gioKetThuc, min(khoang2.gioKetThuc, khoang3.gioKetThuc));

                    // Một cuộc họp diễn ra trong 30 phút
                    if (gioKetThucGiao - gioBatDauGiao >= 0.5) {
                        KhoangThoiGianRanh khoangGiao = {thu, static_cast<int>(gioBatDauGiao),static_cast<int>(gioKetThucGiao)};
                        giaoDanhSachThoiGianRanh.push_back(khoangGiao);
                    }
                }
            }
        }
    }
    return giaoDanhSachThoiGianRanh;
}

bool kiemTraTrungLich(nodeHoiDong* hoiDong1, nodeHoiDong* hoiDong2) {
    for (const auto& danhSachThuX1 : hoiDong1->thoiGianToChuc.danhSachThoiGianRanh) {
        for (const auto& khoangThoiGian1 : danhSachThuX1) {
            for (const auto& danhSachThuX2 : hoiDong2->thoiGianToChuc.danhSachThoiGianRanh) {
                for (const auto& khoangThoiGian2 : danhSachThuX2) {
                    if (khoangThoiGian1.thu == khoangThoiGian2.thu &&
                        khoangThoiGian1.gioBatDau <= khoangThoiGian2.gioKetThuc &&
                        khoangThoiGian2.gioBatDau <= khoangThoiGian1.gioKetThuc) {
                        return true; // Trùng lịch
                    }
                }
            }
        }
    }
    return false; // Không trùng lịch
}

void taoHoiDong(Khoa& khoa, string tenKhoa, nodeGiangVien* thanhVien1, nodeGiangVien* thanhVien2, nodeGiangVien* thanhVien3) {
    for (int thu = 2; thu <= 6; thu++) {
        vector<KhoangThoiGianRanh> giaoDanhSachThoiGianRanh = timGiaoThoiGianRanh(thanhVien1->time, thanhVien2->time, thanhVien3->time, thu);
        for (KhoangThoiGianRanh khoangThoiGian : giaoDanhSachThoiGianRanh) {
            chuyenDoiTime thoiGianToChuc;
            thoiGianToChuc.danhSachThoiGianRanh.push_back({khoangThoiGian});

            nodeHoiDong* hoiDongMoi = new nodeHoiDong;
            hoiDongMoi->tenKhoa = tenKhoa;
            hoiDongMoi->thoiGianToChuc = thoiGianToChuc;
            hoiDongMoi->danhSachThanhVien[0] = thanhVien1;
            hoiDongMoi->danhSachThanhVien[1] = thanhVien2;
            hoiDongMoi->danhSachThanhVien[2] = thanhVien3;
            hoiDongMoi->next = nullptr;

            // Kiểm tra xem thời gian tổ chức của hội đồng mới có trùng với thời gian tổ chức của bất kỳ hội đồng nào khác trong cùng một khoa hay không
            nodeHoiDong* curr = khoa.danhSachHoiDong;
            bool trungLich = false;
            while (curr != nullptr) {
                if (kiemTraTrungLich(hoiDongMoi, curr)) {
                    trungLich = true;
                    break;
                }
                curr = curr->next;
            }

            // Nếu không trùng lịch, thêm hội đồng mới vào danh sách
            if (!trungLich) {
                if (khoa.danhSachHoiDong == nullptr) {
                    khoa.danhSachHoiDong = hoiDongMoi;
                } else {
                    nodeHoiDong* curr1 = khoa.danhSachHoiDong;
                    while (curr1->next != nullptr) {
                        curr1 = curr1->next;
                    }
                    curr1->next = hoiDongMoi;
                }
            } else {
                // Nếu trùng lịch, tìm một khoảng thời gian rảnh khác
                bool timThayKhoangThoiGianRanhKhac = false;
                for (KhoangThoiGianRanh khoangThoiGianKhac : giaoDanhSachThoiGianRanh) {
                    if (khoangThoiGianKhac.gioBatDau != khoangThoiGian.gioBatDau || khoangThoiGianKhac.gioKetThuc != khoangThoiGian.gioKetThuc) {
                        hoiDongMoi->thoiGianToChuc.danhSachThoiGianRanh[0][0] = khoangThoiGianKhac;
                        nodeHoiDong* curr2 = khoa.danhSachHoiDong;
                        bool trunglich2 = false;
                        while (curr2 != nullptr) {
                            if (kiemTraTrungLich(hoiDongMoi, curr2)) {
                                trunglich2 = true;
                                break;
                            }
                            curr2 = curr2->next;
                        }
                        if (!trunglich2) {
                            timThayKhoangThoiGianRanhKhac = true;
                            break;
                        }
                    }
                }
                if (timThayKhoangThoiGianRanhKhac) {
                    if (khoa.danhSachHoiDong == nullptr) {
                        khoa.danhSachHoiDong = hoiDongMoi;
                    } else {
                        nodeHoiDong* curr3 = khoa.danhSachHoiDong;
                        while (curr3->next != nullptr) {
                            curr3 = curr3->next;
                        }
                        curr3->next = hoiDongMoi;
                    }
                }
            }
        }
    }
}

void timKiemHoiDongTheoGiangVien(Khoa* danhSachKhoa, int soLuongKhoa, int chonKhoa, int chonThanhVien) {
    if (chonKhoa < 1 || chonKhoa > soLuongKhoa) {
        cout << "Không có khoa thứ " << chonKhoa << " trong danh sách." << endl;
        return;
    }

    nodeGiangVien* curr = danhSachKhoa[chonKhoa - 1].head;
    for (int i = 1; i < chonThanhVien; i++) {
        if (curr == nullptr) {
            cout << "Không có thành viên thứ " << chonThanhVien << " trong danh sách hội đồng." << endl;
            return;
        }
        curr = curr->next;
    }

    if (curr == nullptr) {
        cout << "Không có thành viên thứ " << chonThanhVien << " trong danh sách hội đồng." << endl;
        return;
    }

    string tenGiangVien = curr->tenThanhVien;

    for (int i = 0; i < soLuongKhoa; i++) {
        nodeHoiDong* currHoiDong = danhSachKhoa[i].danhSachHoiDong;
        while (currHoiDong != nullptr) {
            for (int j = 0; j < 3; j++) {
                if (currHoiDong->danhSachThanhVien[j]->tenThanhVien == tenGiangVien) {
                    // Hiển thị thông tin hội đồng
                    cout << "Hội đồng của khoa " << currHoiDong->tenKhoa << " gồm các thành viên sau:" << endl;
                    for (int k = 0; k < 3; k++) {
                        cout << "   - " << currHoiDong->danhSachThanhVien[k]->tenThanhVien << " (" << currHoiDong->danhSachThanhVien[k]->hocHamHocVi << ")" << endl;
                    }
                    cout << "Thời gian tổ chức hội đồng:" << endl;
                    for (const auto& danhSachThuX : currHoiDong->thoiGianToChuc.danhSachThoiGianRanh) {
                        for (const auto& khoangThoiGian : danhSachThuX) {
                            cout << "Thứ " << khoangThoiGian.thu << ": từ " << khoangThoiGian.gioBatDau << " đến " << khoangThoiGian.gioBatDau + 0.5 << endl;
                        }
                    }
                    break;
                }
            }
            currHoiDong = currHoiDong->next;
        }
    }
}

void hienThiThoiGianBieu(Khoa* danhSachKhoa, int soLuongKhoa) {
    bool coHoiDong = false;
    for (int i = 0; i < soLuongKhoa; i++) {
        nodeHoiDong* curr = danhSachKhoa[i].danhSachHoiDong;
        if (curr != nullptr) {
            coHoiDong = true;
            while (curr != nullptr) {
                cout << "Hội đồng của " << curr->tenKhoa << " gồm các thành viên sau:" << endl;
                for (int j = 0; j < 3; j++) {
                    cout << "   - " << curr->danhSachThanhVien[j]->tenThanhVien << " (" << curr->danhSachThanhVien[j]->hocHamHocVi << ")" << endl;
                }
                cout << "Thời gian tổ chức hội đồng: ";
                for (const auto& danhSachThuX : curr->thoiGianToChuc.danhSachThoiGianRanh) {
                    for (const auto& khoangThoiGian : danhSachThuX) {
                        cout << "Thứ " << khoangThoiGian.thu << ": từ " << khoangThoiGian.gioBatDau << " đến " << khoangThoiGian.gioBatDau + 0.5 << endl;
                    }
                }
                curr = curr->next;
            }
        }
    }
    if (!coHoiDong) {
        cout << "Không có hội đồng nào." << endl;
        exit (0);
    }
}

int main() {
    cout << "\t\t          @@@@@@          @@@@         @@       @@\n";
    cout << "\t\t         @@      @@      @@    @@      @@       @@\n";
    cout << "\t\t         @              @@             @@       @@\n";
    cout << "\t\t           @@@@@@       @@   @@@@      @@       @@\n";
    cout << "\t\t                 @@     @@      @@     @@       @@\n";
    cout << "\t\t         @@      @       @@    @@      @@       @@\n";
    cout << "\t\t           @@@@@@          @@@@         @@@@@@@@@\n";
    cout << "\t\t\t╔═══════════════════════════════════════════════════╗" << endl;
    cout << "\t\t\t║   Chào Mừng bạn đến với Hệ Thống Quản Lý Hội Đồng ║" << endl;
    cout << "\t\t\t╚═══════════════════════════════════════════════════╝\n\n";

    // Tạo 7 khoa
    Khoa danhSachKhoa[7];
    for (int i = 0; i < 7; i++) {
        danhSachKhoa[i].head = nullptr;
        danhSachKhoa[i].soLuongThanhVien = 0;
    }
    // mở file thông tin Giảng Viên
    fstream InfFile("/home/minhsang/Documents/DSA/inputInforMember.txt");
    if(!InfFile){
        cout<<"Lỗi Mở File thông tin";
        return -1;
    }
//---------------------------------Đọc File Thông Tin Giảng Viên---------------------------------
    string khoaCuaGiangVien, tenGiangVien, hocVi;
    while (getline(InfFile, khoaCuaGiangVien)) {

        getline(InfFile, tenGiangVien);
        getline(InfFile, hocVi);
        if (khoaCuaGiangVien == "congNgheThongTin") {
            themThanhVienVaoKhoa(danhSachKhoa[0], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "luat") {
            themThanhVienVaoKhoa(danhSachKhoa[1], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "moiTruong") {
            themThanhVienVaoKhoa(danhSachKhoa[2], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "ngheThuat") {
            themThanhVienVaoKhoa(danhSachKhoa[3], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "ngoaiNgu") {
            themThanhVienVaoKhoa(danhSachKhoa[4], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "quanTriKinhDoanh") {
            themThanhVienVaoKhoa(danhSachKhoa[5], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "thuVien_VanPhong") {
            themThanhVienVaoKhoa(danhSachKhoa[6], tenGiangVien, hocVi);
        } else {
            cout << "Khong the so sanh du lieu" << endl;
        }

        // Đọc dòng trống sau mỗi nhóm 3 dòng
        string emptyLine;
        getline(InfFile, emptyLine);
    }
    InfFile.close();
//---------------------------------Nhập Thông Tin Chọn Khoa, Số người đã biết---------------------------------
    vector<nodeGiangVien*> nguoiDuocChon;
    int chonkhoa2 = -1;
    bool nhapTiep = true;
    while (nhapTiep) {
        bool validInput = false;
        int bietBaoNhieuNguoi;

        while (!validInput) {
            do{
                cout << "Mời bạn chọn khoa muốn tạo hội đồng:\n";
                cout << "\t1. Khoa Công nghệ Thông tin" << endl;
                cout << "\t2. Khoa Luật" << endl;
                cout << "\t3. Khoa Môi trường" << endl;
                cout << "\t4. Khoa Nghệ thuật" << endl;
                cout << "\t5. Khoa Ngoại ngữ" << endl;
                cout << "\t6. Khoa Quản trị Kinh doanh" << endl;
                cout << "\t7. Khoa Thư viện – Văn phòng" << endl;
                cout << "Khoa số: ";

                cin >> chonkhoa2;
                if (chonkhoa2 == 1) {
                    cout << "\n┌─────────────────────────────────────────────────────────────┐" << endl;
                    cout << "│       Danh sách các thành viên khoa Công nghệ Thông tin     │" << endl;
                    cout << "├───────────────┬─────────────────────────────────────────────┤" << endl;
                    cout << "│   STT         │                 Họ và Tên                   │" << endl;
                    cout << "├───────────────┼─────────────────────────────────────────────┤" << endl;
                    nodeGiangVien* curr = danhSachKhoa[0].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────────────────────────┘" << endl;
                }

                if (chonkhoa2 == 2) {
                    cout << "\n┌─────────────────────────────────────────┐" << endl;
                    cout << "│     Danh sách các thành viên khoa Luật  │" << endl;
                    cout << "├───────────────┬─────────────────────────┤" << endl;
                    cout << "│   STT         │        Họ và Tên        │" << endl;
                    cout << "├───────────────┼─────────────────────────┤" << endl;
                    nodeGiangVien* curr = danhSachKhoa[1].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────┘" << endl;
                }

                if (chonkhoa2 == 3) {
                    cout << "\n┌───────────────────────────────────────────────────┐" << endl;
                    cout << "│     Danh sách các thành viên khoa Môi trường      │" << endl;
                    cout << "├───────────────┬───────────────────────────────────┤" << endl;
                    cout << "│   STT         │        Họ và Tên                  │" << endl;
                    cout << "├───────────────┼───────────────────────────────────┤" << endl;
                    nodeGiangVien* curr = danhSachKhoa[2].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴───────────────────────────────────┘" << endl;
                }

                if (chonkhoa2 == 4) {
                    cout << "\n┌───────────────────────────────────────────────────┐" << endl;
                    cout << "│       Danh sách các thành viên khoa Nghệ thuật      │" << endl;
                    cout << "├───────────────┬─────────────────────────────────────┤" << endl;
                    cout << "│      STT      │              Họ và Tên              │" << endl;
                    cout << "├───────────────┼─────────────────────────────────────┤" << endl;
                    nodeGiangVien* curr = danhSachKhoa[3].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────────────────┘" << endl;
                }

                if (chonkhoa2 == 5) {
                    cout << "\n┌─────────────────────────────────────────────────────┐" << endl;
                    cout << "│       Danh sách các thành viên khoa Ngoại ngữ       │" << endl;
                    cout << "├───────────────┬─────────────────────────────────────┤" << endl;
                    cout << "│      STT      │            Họ và Tên                │" << endl;
                    cout << "├───────────────┼─────────────────────────────────────┤" << endl;
                    nodeGiangVien* curr = danhSachKhoa[4].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────────────────┘" << endl;
                }

                if (chonkhoa2 == 6) {
                    cout << "┌───────────────────────────────────────────────────────────────────────┐" << endl;
                    cout << "│           Danh sách các thành viên khoa Quản trị Kinh doanh           │" << endl;
                    cout << "├───────────────┬───────────────────────────────────────────────────────┤" << endl;
                    cout << "│   STT         │                      Họ và Tên                        │" << endl;
                    cout << "├───────────────┼───────────────────────────────────────────────────────┤" << endl;
                    nodeGiangVien* curr = danhSachKhoa[5].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴───────────────────────────────────────────────────────┘" << endl;
                }

                if (chonkhoa2 == 7) {
                    cout << "┌─────────────────────────────────────────────────────────────────┐" << endl;
                    cout << "│           Danh sách các thành viên khoa Thư viện – Văn phòng    │" << endl;
                    cout << "├───────────────┬─────────────────────────────────────────────────┤" << endl;
                    cout << "│      STT      │                  Họ và Tên                      │" << endl;
                    cout << "├───────────────┼─────────────────────────────────────────────────┤" << endl;
                    nodeGiangVien* curr = danhSachKhoa[6].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────────────────────────────┘" << endl;
                }
                if(chonkhoa2 > 0 && chonkhoa2 < 8){
                    cout << "Bạn đã biết thời gian trống của bao nhiêu người trong danh sách trên (-1 để đổi khoa): ";
                }
            } while (chonkhoa2 == -1);
            cin >> bietBaoNhieuNguoi;
            if (bietBaoNhieuNguoi >= 3 && bietBaoNhieuNguoi <= 10) {
                validInput = true;
            } else if (bietBaoNhieuNguoi < 3) {
                cout << "Số lượng thành viên đã biết quá ít, không đủ để tạo hội đồng cho khoa đã chọn" << endl;
            } else {
                cout << "Cơ sở dữ liệu của chúng tôi có tối đa 10 thành viên cho mỗi khoa\n";
                cout << "Để mở rộng cơ sở dữ liệu xin liên hệ phòng kỹ thuật của chúng tôi qua E-Mail: techsupportMinhSang@softtechsolutions.com" << endl;
            }
        }
//---------------------------------Nhập Thông Tin Thời Gian Rảnh ---------------------------------
        cout << "┌───────────────────────────────────────────────────────────┐" << endl;
        cout << "│   Mời bạn nhập khung giờ trống cho từng người đã biết:    │" << endl;
        cout << "└───────────────────────────────────────────────────────────┘\n";
        int chonNguoiThuMay;
        cout << "[Option] Nhập -1 để kết thúc nhập thời gian rảnh của thứ đó, -2 để bỏ qua tất cả thứ còn lại" << endl;
        for (int i = 0; i < bietBaoNhieuNguoi; i++) {
            cout << "Chọn người thứ ";
            cin >> chonNguoiThuMay;
            if (chonNguoiThuMay < 1 || chonNguoiThuMay > danhSachKhoa[chonkhoa2 - 1].soLuongThanhVien) {
                cout << "Không có người thứ " << chonNguoiThuMay << " trong danh sách của khoa" << endl;
                i--;
                continue;
            }
            bool giaTriTime = false;
            while (!giaTriTime) {
                //gan curr la GV dau tien trong khoa, for di den nguoi duoc chon
                nodeGiangVien* curr = danhSachKhoa[chonkhoa2 - 1].head;
                for (int j = 1; j < chonNguoiThuMay; j++) {
                    curr = curr->next;
                }
                //luu cac nguoi duoc chon trong khoa hien tai
                nguoiDuocChon.push_back(curr);

                cout << "\t\t┌───────────────────────────────────────────────────────────┐" << endl;
                cout <<"\t\t"<< "|\t\t" <<curr->hocHamHocVi << ": " << curr->tenThanhVien <<endl;
                cout << "\t\t└───────────────────────────────────────────────────────────┘\n";
                chuyenDoiTime tmpTime;
                bool quaNguoiTiepTheo = false;
                for (int thu = 2; thu <= 6; thu++) {
                    if (quaNguoiTiepTheo) {
                        // Không nhập thời gian rảnh cho các thứ còn lại
                        continue;
                    }
                    cout << "Thời gian rảnh vào thứ " << thu << " bắt đầu lúc: ";
                    int gioBatDau, gioKetThuc;
                    //vector luu nhieu thoi gian ranh theo thu cua mot GV
                    vector<KhoangThoiGianRanh> danhSachThoiGianRanhThuX;
                    bool nhapDungThoiGian;
                    do {
                        nhapDungThoiGian = true;
                        cin >> gioBatDau;
                        if (gioBatDau == -2) {
                            // Bỏ qua tất cả các thứ còn lại
                            if (thu == 2) {
                                cout << "Bạn không thể bỏ qua tất cả các thứ ngay từ thứ đầu tiên. Vui lòng nhập lại." << endl;
                                thu--; // Quay lại thứ hiện tại
                                continue;
                            }
                            quaNguoiTiepTheo = true;
                            continue;
                        } else if (gioBatDau == -1) {
                            // Không nhập thêm khoảng thời gian cho thứ này
                            continue;
                        }
                        cout << "Cho đến: ";
                        cin >> gioKetThuc;
                        //kiem tra input thoi gian, neu dung thi them vao theo thu cua GV
                        if (gioBatDau >= 8 && gioBatDau < 17 && gioKetThuc > gioBatDau && gioKetThuc <= 17) {
                            KhoangThoiGianRanh khoangThoiGian = {thu, gioBatDau, gioKetThuc};
                            danhSachThoiGianRanhThuX.push_back(khoangThoiGian);
                        } else {
                            cout << "Bạn đã nhập định dạng thời gian không hợp lệ. Vui lòng nhập lại." << endl;
                            cout<<"bắt đầu lúc: ";
                            nhapDungThoiGian = false;
                        }
                    } while (!nhapDungThoiGian);
                    tmpTime.danhSachThoiGianRanh.push_back(danhSachThoiGianRanhThuX);
                }
                //kiem tra cac thu co thu nao ranh khong
                bool coKhoangThoiGianRanh = false;
                for (vector<KhoangThoiGianRanh> danhSachThuX : tmpTime.danhSachThoiGianRanh) {
                    if (!danhSachThuX.empty()) {
                        coKhoangThoiGianRanh = true;
                        break;
                    }
                }
                if (coKhoangThoiGianRanh) {
                    curr->time = tmpTime;
                    giaTriTime = true;
                } else {
                    cout << "Bạn chưa nhập thời gian rảnh nào." << endl;
                }
            }
        }
        //doi khoa
        cout << "\nBạn có muốn tiếp tục nhập thông tin cho những người đã biết nữa không?" << endl;
        cout << "1: Có" << endl;
        cout << "2: Không" << endl;
        cout << "Nhập lựa chọn của bạn: ";

        int luaChon;
        cin >> luaChon;

        if (luaChon != 1)
            nhapTiep = false;
    }
    // Tạo hội đồng từ thông tin đã nhập
    for (int i = 0; i < nguoiDuocChon.size(); i += 3) {
        taoHoiDong(danhSachKhoa[i/3], "Khoa " + to_string(i/3 + 1), nguoiDuocChon[i], nguoiDuocChon[i+1], nguoiDuocChon[i+2]);
    }
//---------------------------------Lựa chọn---------------------------------
    int luaChon;
    do {
        cout << "\n╔═══════════════ Lựa chọn ══════════════════════╗" << endl;
        cout << "║ 1. Kiểm tra hai hội đồng bất kỳ có trùng lịch  ║" << endl;
        cout << "║ 2. Tìm kiếm hội đồng theo tên giảng viên       ║" << endl;
        cout << "║ 3. Hiển thị thời gian biểu các hội đồng        ║" << endl;
        cout << "║ 4. Thoát chương trình                          ║" << endl;
        cout << "╚═════════════════════════════════════════════╝" << endl;
        cout << "Nhập lựa chọn của bạn: ";
        cin >> luaChon;
        switch (luaChon) {
            case 1: {
                int chonKhoa1, chonKhoa2;
                cout << "Nhập số thứ tự hội đồng 1: ";
                cin >> chonKhoa1;
                cout << "Nhập số thứ tự hội đồng 2: ";
                cin >> chonKhoa2;

                if (chonKhoa1 < 1 || chonKhoa1 > 7 || chonKhoa2 < 1 || chonKhoa2 > 7) {
                    cout << "Không có khoa thứ " << chonKhoa1 << " hoặc " << chonKhoa2 << " trong danh sách." << endl;
                    break;
                }

                nodeHoiDong* hoiDong1 = danhSachKhoa[chonKhoa1 - 1].danhSachHoiDong;
                nodeHoiDong* hoiDong2 = danhSachKhoa[chonKhoa2 - 1].danhSachHoiDong;

                if (hoiDong1 != nullptr && hoiDong2 != nullptr) {
                    if (kiemTraTrungLich(hoiDong1, hoiDong2)) {
                        cout << "Hai hội đồng của khoa " << chonKhoa1 << " và " << chonKhoa2 << " có trùng lịch." << endl;
                    } else {
                        cout << "Hai hội đồng của khoa " << chonKhoa1 << " và " << chonKhoa2 << " không trùng lịch." << endl;
                    }
                } else {
                    cout << "Không tìm thấy hội đồng của một hoặc cả hai khoa đã nhập." << endl;
                }
                break;
            }
            case 2: {
                int chonKhoa, chonThanhVien;
                cout << "Nhập số thứ tự khoa: ";
                cin >> chonKhoa;
                cout << "Nhập số thứ tự giảng viên: ";
                cin >> chonThanhVien;

                if (chonKhoa < 1 || chonKhoa > 7) {
                    cout << "Không có khoa thứ " << chonKhoa << " trong danh sách." << endl;
                    break;
                }

                timKiemHoiDongTheoGiangVien(danhSachKhoa, 7, chonKhoa, chonThanhVien);
                break;
            }
            case 3:
                hienThiThoiGianBieu(danhSachKhoa, 7);
                break;
            case 4:
                cout << "Thoát chương trình." << endl;
                break;
            default:
                cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại." << endl;
        }
    } while (luaChon != 4);

    return 0;
}