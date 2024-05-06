#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct KhoangThoiGianRanh {
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
    NodeGiangVien* next{};
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

NodeHoiDong* danhSachHoiDong = NULL;

void themThanhVienVaoKhoa(Khoa& khoa, string ten, string hocVi) {
    NodeGiangVien* newNode = new NodeGiangVien;
    newNode->tenThanhVien = ten;
    newNode->hocHamHocVi = hocVi;

    newNode->next = NULL;

    // Khoa rỗng (thêm thành viên đầu tiên)
    if (khoa.head == NULL) {
        khoa.head = newNode;
    } else {
        // Đã tồn tại ít nhất 1 thành viên => thêm thành viên mới , lien ket voi thanh vien cu
        NodeGiangVien* curr = khoa.head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    khoa.soLuongThanhVien++;
}

vector<KhoangThoiGianRanh> timGiaoThoiGianRanh(chuyenDoiTime time1, chuyenDoiTime time2, chuyenDoiTime time3, int thu) {
    vector<KhoangThoiGianRanh> giaoDanhSachThoiGianRanh;
    int index = thu - 2; // Chỉ số của ngày trong tuần (thứ 2 có chỉ số 0, thứ 3 có chỉ số 1, ...)

    for (const auto& khoang1 : time1.danhSachThoiGianRanh[index]) {
        for (const auto& khoang2 : time2.danhSachThoiGianRanh[index]) {
            for (const auto& khoang3 : time3.danhSachThoiGianRanh[index]) {
                int gioBatDauGiao = max(khoang1.gioBatDau, max(khoang2.gioBatDau, khoang3.gioBatDau));
                int gioKetThucGiao = min(khoang1.gioKetThuc, min(khoang2.gioKetThuc, khoang3.gioKetThuc));

                if (gioKetThucGiao - gioBatDauGiao >= 0.5) {
                    KhoangThoiGianRanh khoangGiao = {gioBatDauGiao, gioBatDauGiao + 0.5};
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
            thoiGianToChuc.thu = thu;
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
        newNode->next = NULL;

        if (danhSachHoiDong == NULL) {
            danhSachHoiDong = newNode;
        } else {
            NodeHoiDong* curr = danhSachHoiDong;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
    } else {
        cout << "Khong tim thay thoi gian hop le de to chuc hoi dong cho khoa " << tenKhoa << endl;
    }
}

void timKiemHoiDongTheoGiangVien(string tenGiangVien) {
    NodeHoiDong* curr = danhSachHoiDong;
    while (curr != NULL) {
        for (int i = 0; i < 3; i++) {
            if (curr->hoiDong->danhSachThanhVien[i]->tenThanhVien == tenGiangVien) {
                cout << "Giảng viên " << tenGiangVien << " tham gia hội đồng của khoa " << curr->hoiDong->tenKhoa << " vào thời gian "
                     << curr->hoiDong->thoiGianToChuc.thu << " "
                     << curr->hoiDong->thoiGianToChuc.gioBatDau << " - "
                     << curr->hoiDong->thoiGianToChuc.gioKetThuc << endl;
            }
        }
        curr = curr->next;
    }
}
int main() {
    cout << "\n\t\t\t-----------Chào Mừng bạn đến với hệ thống quản lý hội đồng nghiệm thu-----------\n\n";
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
                if(chonKhoa < 1 || chonKhoa > 7){
                    cout<<"Không có khoa thứ "<<chonKhoa<<" mời bạn chọn lại"<<endl;
                    chonKhoa = -1;
                }
                if (chonKhoa == 1) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Công nghệ Thông tin\n";
                    NodeGiangVien* curr = danhSachKhoa[0].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 2) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Luật\n";
                    NodeGiangVien* curr = danhSachKhoa[1].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout <<"\t"<< i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 3) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Môi trường\n";
                    NodeGiangVien* curr = danhSachKhoa[2].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout <<"\t"<< i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 4) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Nghệ thuật\n";
                    NodeGiangVien* curr = danhSachKhoa[3].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout <<"\t"<< i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 5) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Ngoại ngữ\n";
                    NodeGiangVien* curr = danhSachKhoa[4].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout <<"\t"<< i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 6) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Quản trị Kinh doanh\n";
                    NodeGiangVien* curr = danhSachKhoa[5].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout <<"\t"<< i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 7) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Thư viện – Văn phòng:\n";
                    NodeGiangVien* curr = danhSachKhoa[6].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout <<"\t"<< i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
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
        cout << "\nMời bạn nhập khung giờ trống cho từng người đã biết\n";
        cout << "Với định dạng sau: [thứ][GiờBắtĐầuRảnh][GiờBận] ví dụ: 30915 (thứ 3, rảnh từ 9 giờ đến 15 giờ)\n";
        int chonNguoiThuMay;
        for (int i = 0; i < bietBaoNhieuNguoi; i++){
            cout<<"Chọn người thứ ";
            cin>>chonNguoiThuMay;
            if(chonNguoiThuMay < 1 || chonNguoiThuMay > danhSachKhoa[chonKhoa - 1].soLuongThanhVien){
                cout<<"Không có người thứ "<<chonNguoiThuMay<<" trong danh sách của khoa"<<endl;
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
                cout << "Nhập -1 để kết thúc nhập thời gian rảnh" << endl;
                for (int thu = 2; thu <= 6; thu++) {
                    cout << "Thời gian rảnh vào thứ " << thu << ":" << endl;
                    int gioBatDau, gioKetThuc;
                    vector<KhoangThoiGianRanh> danhSachThoiGianRanhThuX;
                    do {
                        cout << "Thời gian bắt đầu rảnh (8-16): ";
                        cin >> gioBatDau;
                        if (gioBatDau == -1) break;
                        cout << "Thời gian kết thúc rảnh (9-17): ";
                        cin >> gioKetThuc;
                        if (gioBatDau >= 8 && gioBatDau < 17 && gioKetThuc > gioBatDau && gioKetThuc <= 17) {
                            KhoangThoiGianRanh khoangThoiGian = {gioBatDau, gioKetThuc};
                            danhSachThoiGianRanhThuX.push_back(khoangThoiGian);
                        } else {
                            cout << "Bạn đã nhập định dạng thời gian không hợp lệ. Vui lòng nhập lại." << endl;
                        }
                    } while (gioBatDau != -1);
                    tmpTime.danhSachThoiGianRanh.push_back(danhSachThoiGianRanhThuX);
                }

                bool coKhoangThoiGianRanh = false;
                for (const auto& danhSachThuX : tmpTime.danhSachThoiGianRanh) {
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
//---------------------------------Lựa chọn---------------------------------
    int option;
    cout << "\n-----------Lựa chọn:-----------" << endl;
    cout << "1: Kiểm tra hai hội đồng bất kỳ (tất cả hội đồng đã được tạo bao gồm khác khoa) có trùng lịch nhau hay không" << endl;
    cout << "2: Tìm kiếm hội đồng đang tham gia thông qua khoa và tên của giảng viên" << endl;
    cout << "3: Hiển thị thời gian biểu tất cả các lịch đã được tạo của trường" << endl;
    cout << "Nhập lựa chọn của bạn: ";
    cin >> option;

    switch (option) {
        case 1:
            string khoa1, khoa2;
            cout << "Nhập tên khoa 1: ";
            cin >> khoa1;
            cout << "Nhập tên khoa 2: ";
            cin >> khoa2;


            break;
        case 2:
            string tenMuonTimKiem;
            cin>>tenMuonTimKiem;
            timKiemHoiDongTheoGiangVien(tenMuonTimKiem);
            break;
        case 3:
            // Code để hiển thị thời gian biểu của các lịch đã được tạo của trường

            break;
        default:
            cout << "Lựa chọn không hợp lệ." << endl;
    }

    return 0;
}