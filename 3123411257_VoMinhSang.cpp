#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//=============== Khai báo các cấu trúc dữ liệu ===============

struct KhoangThoiGianRanh {
    int thu;
    int gioBatDau;
    int gioKetThuc;
};

struct chuyenDoiTime {
    vector<vector<KhoangThoiGianRanh>> danhSachThoiGianRanh; // Vector 2 chiều lưu trữ danh sách khoảng thời gian rảnh cho mỗi ngày
};

struct NodeGiangVien {
    string tenThanhVien;
    string hocHamHocVi;
    chuyenDoiTime time;
    NodeGiangVien* next = nullptr;
};

struct Khoa {
    NodeGiangVien* head;
    int soLuongThanhVien;
};

struct HoiDong {
    string tenKhoa;
    chuyenDoiTime thoiGianToChuc;
    NodeGiangVien* danhSachThanhVien[3]; // Mảng chứa con trỏ đến 3 thành viên trong hội đồng
};

struct NodeHoiDong {
    HoiDong* hoiDong;
    NodeHoiDong* next;
};

NodeHoiDong* danhSachHoiDong = nullptr;

//=============== Các hàm xử lý ===============

void themThanhVienVaoKhoa(Khoa& khoa, string ten, string hocVi) {
    NodeGiangVien* newNode = new NodeGiangVien;
    newNode->tenThanhVien = ten;
    newNode->hocHamHocVi = hocVi;

    // Khoa rỗng (thêm thành viên đầu tiên)
    if (khoa.head == nullptr) {
        khoa.head = newNode;
    } else {
        // Đã tồn tại ít nhất 1 thành viên => thêm thành viên mới, liên kết với thành viên cũ
        NodeGiangVien* curr = khoa.head;
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

    for (auto khoang1 : time1.danhSachThoiGianRanh[index]) {
        for (auto khoang2 : time2.danhSachThoiGianRanh[index]) {
            for (auto khoang3 : time3.danhSachThoiGianRanh[index]) {
                int gioBatDauGiao = max(khoang1.gioBatDau, max(khoang2.gioBatDau, khoang3.gioBatDau));
                int gioKetThucGiao = min(khoang1.gioKetThuc, min(khoang2.gioKetThuc, khoang3.gioKetThuc));

                // Một cuộc họp diễn ra trong 1 giờ
                if (gioKetThucGiao - gioBatDauGiao >= 1) {
                    KhoangThoiGianRanh khoangGiao = {thu, gioBatDauGiao, gioBatDauGiao + 1};
                    giaoDanhSachThoiGianRanh.push_back(khoangGiao);
                }
            }
        }
    }

    return giaoDanhSachThoiGianRanh;
}

void taoHoiDong(string tenKhoa, NodeGiangVien* thanhVien1, NodeGiangVien* thanhVien2, NodeGiangVien* thanhVien3) {
    chuyenDoiTime thoiGianToChuc;

    for (int thu = 2; thu <= 6; thu++) {
        vector<KhoangThoiGianRanh> giaoDanhSachThoiGianRanh = timGiaoThoiGianRanh(thanhVien1->time, thanhVien2->time, thanhVien3->time, thu);
        if (!giaoDanhSachThoiGianRanh.empty()) {
            thoiGianToChuc.danhSachThoiGianRanh.push_back(giaoDanhSachThoiGianRanh);
            break; // Tìm thấy thời gian tổ chức hội đồng, thoát vòng lặp
        }
    }

    if (!thoiGianToChuc.danhSachThoiGianRanh.empty()) {
        HoiDong* hoiDongMoi = new HoiDong;
        hoiDongMoi->tenKhoa = tenKhoa;
        hoiDongMoi->thoiGianToChuc = thoiGianToChuc;
        hoiDongMoi->danhSachThanhVien[0] = thanhVien1;
        hoiDongMoi->danhSachThanhVien[1] = thanhVien2;
        hoiDongMoi->danhSachThanhVien[2] = thanhVien3;

        NodeHoiDong* newNode = new NodeHoiDong;
        newNode->hoiDong = hoiDongMoi;
        newNode->next = nullptr;

        if (danhSachHoiDong == nullptr) {
            danhSachHoiDong = newNode;
        } else {
            NodeHoiDong* curr = danhSachHoiDong;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
    } else {
        cout << "Không tìm thấy thời gian hợp lệ để tổ chức hội đồng cho khoa " << tenKhoa << endl;
    }
}

void hienThiMenu() {
    cout << "\n╔═══════════════ Lựa chọn ══════════════════════╗" << endl;
    cout << "║ 1. Kiểm tra hai hội đồng bất kỳ có trùng lịch  ║" << endl;
    cout << "║ 2. Tìm kiếm hội đồng theo tên giảng viên       ║" << endl;
    cout << "║ 3. Hiển thị thời gian biểu các hội đồng        ║" << endl;
    cout << "║ 4. Thoát chương trình                          ║" << endl;
    cout << "╚═════════════════════════════════════════════╝" << endl;
    cout << "Nhập lựa chọn của bạn: ";
}

bool kiemTraTrungLich(HoiDong* hoiDong1, HoiDong* hoiDong2) {
    for (const auto& danhSachThuX1 : hoiDong1->thoiGianToChuc.danhSachThoiGianRanh) {
        for (const auto& khoangThoiGian1 : danhSachThuX1) {
            for (const auto& danhSachThuX2 : hoiDong2->thoiGianToChuc.danhSachThoiGianRanh) {
                for (const auto& khoangThoiGian2 : danhSachThuX2) {
                    if (khoangThoiGian1.thu == khoangThoiGian2.thu &&
                        khoangThoiGian1.gioBatDau < khoangThoiGian2.gioKetThuc &&
                        khoangThoiGian2.gioBatDau < khoangThoiGian1.gioKetThuc) {
                        return true; // Trùng lịch
                    }
                }
            }
        }
    }
    return false; // Không trùng lịch
}

void timKiemHoiDongTheoGiangVien(string tenGiangVien) {
    NodeHoiDong* curr = danhSachHoiDong;
    while (curr != NULL) {
        for (int i = 0; i < 3; i++) {
            if (curr->hoiDong->danhSachThanhVien[i]->tenThanhVien == tenGiangVien) {
                cout << "Giảng viên " << tenGiangVien << " tham gia hội đồng của khoa " << curr->hoiDong->tenKhoa << " vào các thời gian sau:" << endl;
                for (const auto& danhSachThuX : curr->hoiDong->thoiGianToChuc.danhSachThoiGianRanh) {
                    for (const auto& khoangThoiGian : danhSachThuX) {
                        cout << "Thứ " << khoangThoiGian.thu << " từ " << khoangThoiGian.gioBatDau << " đến " << khoangThoiGian.gioKetThuc << endl;
                    }
                }
            }
        }
        curr = curr->next;
    }
}

void hienThiThoiGianBieu() {
    cout << "\n╔═══════════ Thời gian biểu các hội đồng ══════════════╗" << endl;
    NodeHoiDong* curr = danhSachHoiDong;
    while (curr != nullptr) {
        HoiDong* hoiDong = curr->hoiDong;
        cout << "║ Khoa: " << hoiDong->tenKhoa << endl;
        cout << "║ Thành viên:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "║   - " << hoiDong->danhSachThanhVien[i]->tenThanhVien << " (" << hoiDong->danhSachThanhVien[i]->hocHamHocVi << ")" << endl;
        }
        cout << "║ Thời gian tổ chức hội đồng:" << endl;
        for (const auto& danhSachThuX : hoiDong->thoiGianToChuc.danhSachThoiGianRanh) {
            for (const auto& khoangThoiGian : danhSachThuX) {
                cout << "║   ▪ Thứ " << khoangThoiGian.thu << " từ " << khoangThoiGian.gioBatDau << " đến " << khoangThoiGian.gioKetThuc << endl;
            }
        }
        cout << "╚═════════════════════════════════════════════════════════╝" << endl;
        curr = curr->next;
    }
}
int main() {
    cout << "\n\t\t\t╔═══════════════════════════════════════════════════╗" << endl;
    cout << "\t\t\t║   Chào Mừng bạn đến với Hệ Thống Quản Lý Hội Đồng ║" << endl;
    cout << "\t\t\t╚═══════════════════════════════════════════════════╝\n\n";
    // Tạo 7 khoa
    Khoa danhSachKhoa[7];
    for (int i = 0; i < 7; i++) {
        danhSachKhoa[i].head = NULL;
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
    bool nhapTiep = true;
    while (nhapTiep) {
        bool validInput = false;
        int bietBaoNhieuNguoi;
        int chonKhoa = -1;
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
                cout << "Khoa: ";

                cin >> chonKhoa;
                if (chonKhoa == 1) {
                    cout << "\n┌─────────────────────────────────────────────────────────────┐" << endl;
                    cout << "│       Danh sách các thành viên khoa Công nghệ Thông tin     │" << endl;
                    cout << "├───────────────┬─────────────────────────────────────────────┤" << endl;
                    cout << "│   STT         │                 Họ và Tên                   │" << endl;
                    cout << "├───────────────┼─────────────────────────────────────────────┤" << endl;
                    NodeGiangVien* curr = danhSachKhoa[0].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────────────────────────┘" << endl;
                }

                if (chonKhoa == 2) {
                    cout << "\n┌─────────────────────────────────────────┐" << endl;
                    cout << "│     Danh sách các thành viên khoa Luật  │" << endl;
                    cout << "├───────────────┬─────────────────────────┤" << endl;
                    cout << "│   STT         │        Họ và Tên        │" << endl;
                    cout << "├───────────────┼─────────────────────────┤" << endl;
                    NodeGiangVien* curr = danhSachKhoa[1].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────┘" << endl;
                }

                if (chonKhoa == 3) {
                    cout << "\n┌───────────────────────────────────────────────────┐" << endl;
                    cout << "│     Danh sách các thành viên khoa Môi trường      │" << endl;
                    cout << "├───────────────┬───────────────────────────────────┤" << endl;
                    cout << "│   STT         │        Họ và Tên                  │" << endl;
                    cout << "├───────────────┼───────────────────────────────────┤" << endl;
                    NodeGiangVien* curr = danhSachKhoa[2].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴───────────────────────────────────┘" << endl;
                }

                if (chonKhoa == 4) {
                    cout << "\n┌───────────────────────────────────────┐" << endl;
                    cout << "│           Danh sách các thành viên khoa Nghệ thuật           │" << endl;
                    cout << "├───────────────┬─────────────────────────┤" << endl;
                    cout << "│   STT         │        Họ và Tên        │" << endl;
                    cout << "├───────────────┼─────────────────────────┤" << endl;
                    NodeGiangVien* curr = danhSachKhoa[3].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << "   │" << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────┘" << endl;
                }

                if (chonKhoa == 5) {
                    cout << "\n┌───────────────────────────────────────┐" << endl;
                    cout << "│           Danh sách các thành viên khoa Ngoại ngữ           │" << endl;
                    cout << "├───────────────┬─────────────────────────┤" << endl;
                    cout << "│   STT         │        Họ và Tên        │" << endl;
                    cout << "├───────────────┼─────────────────────────┤" << endl;
                    NodeGiangVien* curr = danhSachKhoa[4].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << "   │" << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────┘" << endl;
                }

                if (chonKhoa == 6) {
                    cout << "\n┌───────────────────────────────────────┐" << endl;
                    cout << "│           Danh sách các thành viên khoa Quản trị Kinh doanh           │" << endl;
                    cout << "├───────────────┬─────────────────────────┤" << endl;
                    cout << "│   STT         │        Họ và Tên        │" << endl;
                    cout << "├───────────────┼─────────────────────────┤" << endl;
                    NodeGiangVien* curr = danhSachKhoa[5].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << "   │" << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────┘" << endl;
                }

                if (chonKhoa == 7) {
                    cout << "\n┌───────────────────────────────────────┐" << endl;
                    cout << "│           Danh sách các thành viên khoa Thư viện – Văn phòng           │" << endl;
                    cout << "├───────────────┬─────────────────────────┤" << endl;
                    cout << "│   STT         │        Họ và Tên        │" << endl;
                    cout << "├───────────────┼─────────────────────────┤" << endl;
                    NodeGiangVien* curr = danhSachKhoa[6].head;
                    int i = 1;
                    while (curr != nullptr) {
                        cout << "│      " << i << "\t\t│   " << curr->tenThanhVien << "   │" << endl;
                        curr = curr->next;
                        i++;
                    }
                    cout << "└───────────────┴─────────────────────────┘" << endl;
                }
                if(chonKhoa != -1){
                    cout << "Bạn đã biết thời gian trống của bao nhiêu người trong danh sách trên (-1 để đổi khoa): ";
                }
            } while (chonKhoa == -1);
            cin >> bietBaoNhieuNguoi;
            if (bietBaoNhieuNguoi >= 3 && bietBaoNhieuNguoi <= 10) {
                validInput = true;
            } else if (bietBaoNhieuNguoi < 3) {
                cout << "Số lượng thành viên đã biết quá ít, không đủ để tạo hội đồng" << endl;
            } else {
                cout << "Cơ sở dữ liệu của chúng tôi có tối đa 10 thành viên cho mỗi khoa\n";
                cout << "Để mở rộng cơ sở dữ liệu xin liên hệ phòng kỹ thuật của chúng tôi qua E-Mail: techsupportMinhSang@softtechsolutions.com" << endl;
            }
        }
        cout << "Vâng, đã biết " << bietBaoNhieuNguoi << " người\n";
//---------------------------------Nhập Thông Tin Thời Gian Rảnh ---------------------------------
        cout << "\t\t\nMời bạn nhập khung giờ trống cho từng người đã biết\n";
        int chonNguoiThuMay;
        for (int i = 0; i < bietBaoNhieuNguoi; i++) {
            cout << "Chọn người thứ ";
            cin >> chonNguoiThuMay;
            if (chonNguoiThuMay < 1 || chonNguoiThuMay > danhSachKhoa[chonKhoa - 1].soLuongThanhVien) {
                cout << "Không có người thứ " << chonNguoiThuMay << " trong danh sách của khoa" << endl;
                i--;
                continue;
            }
            bool giaTriTime = false;
            while (!giaTriTime) {
                NodeGiangVien* curr = danhSachKhoa[chonKhoa - 1].head;
                for (int j = 1; j < chonNguoiThuMay; j++) {
                    curr = curr->next;
                }
                cout << curr->hocHamHocVi << ": " << curr->tenThanhVien << endl;
                chuyenDoiTime tmpTime;
                cout << "Nhập -1 để kết thúc nhập thời gian rảnh của thứ đó, -2 để bỏ qua tất cả thứ còn lại" << endl;
                bool skipRemainingDays = false;
                for (int thu = 2; thu <= 6; thu++) {
                    if (skipRemainingDays) {
                        // Không nhập thời gian rảnh cho các thứ còn lại
                        continue;
                    }
                    cout << "Thời gian rảnh vào thứ " << thu << ":" << endl;
                    int gioBatDau, gioKetThuc;
                    vector<KhoangThoiGianRanh> danhSachThoiGianRanhThuX;
                    cout << "Thời gian bắt đầu rảnh (8-16): ";
                    cin >> gioBatDau;
                    if (gioBatDau == -2) {
                        // Bỏ qua tất cả các thứ còn lại
                        skipRemainingDays = true;
                        continue;
                    } else if (gioBatDau == -1) {
                        // Không nhập thêm khoảng thời gian cho thứ này
                        continue;
                    }
                    cout << "Thời gian kết thúc rảnh (9-17): ";
                    cin >> gioKetThuc;
                    if (gioBatDau >= 8 && gioBatDau < 17 && gioKetThuc > gioBatDau && gioKetThuc <= 17) {
                        KhoangThoiGianRanh khoangThoiGian = {thu, gioBatDau, gioKetThuc};
                        danhSachThoiGianRanhThuX.push_back(khoangThoiGian);
                    } else {
                        cout << "Bạn đã nhập định dạng thời gian không hợp lệ. Vui lòng nhập lại." << endl;
                    }
                    tmpTime.danhSachThoiGianRanh.push_back(danhSachThoiGianRanhThuX);
                }
                //kiem tra cac thu co thu nao ranh khong
                bool coKhoangThoiGianRanh = false;
                for (auto danhSachThuX : tmpTime.danhSachThoiGianRanh) {
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

        cout << "\nBạn có muốn tiếp tục nhập thông tin cho những người đã biết nữa không?" << endl;
        cout << "1: Có" << endl;
        cout << "2: Không" << endl;
        cout << "Nhập lựa chọn của bạn: ";

        int luaChon;
        cin >> luaChon;

        if (luaChon != 1)
            nhapTiep = false;
    }
//-----

//---------------------------------Lựa chọn---------------------------------
    int luaChon;
    do {
        hienThiMenu();
        cin >> luaChon;

        switch (luaChon) {
            case 1: {
                string tenKhoa1, tenKhoa2;
                cout << "Nhập tên khoa 1: ";
                cin >> tenKhoa1;
                cout << "Nhập tên khoa 2: ";
                cin >> tenKhoa2;

                NodeHoiDong* curr1 = danhSachHoiDong;
                NodeHoiDong* curr2 = danhSachHoiDong;
                HoiDong* hoiDong1 = nullptr;
                HoiDong* hoiDong2 = nullptr;

                // Tìm hội đồng của khoa 1
                while (curr1 != NULL) {
                    if (curr1->hoiDong->tenKhoa == tenKhoa1) {
                        hoiDong1 = curr1->hoiDong;
                        break;
                    }
                    curr1 = curr1->next;
                }

                // Tìm hội đồng của khoa 2
                while (curr2 != NULL) {
                    if (curr2->hoiDong->tenKhoa == tenKhoa2) {
                        hoiDong2 = curr2->hoiDong;
                        break;
                    }
                    curr2 = curr2->next;
                }

                if (hoiDong1 != nullptr && hoiDong2 != nullptr) {
                    if (kiemTraTrungLich(hoiDong1, hoiDong2)) {
                        cout << "Hai hội đồng của khoa " << tenKhoa1 << " và " << tenKhoa2 << " có trùng lịch." << endl;
                    } else {
                        cout << "Hai hội đồng của khoa " << tenKhoa1 << " và " << tenKhoa2 << " không trùng lịch." << endl;
                    }
                } else {
                    cout << "Không tìm thấy hội đồng của một hoặc cả hai khoa đã nhập." << endl;
                }
                break;
            }
            case 2: {
                string tenGiangVien;
                cout << "Nhập tên giảng viên muốn tìm kiếm: ";
                cin >> tenGiangVien;
                timKiemHoiDongTheoGiangVien(tenGiangVien);
                break;
            }
            case 3:
                hienThiThoiGianBieu();
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