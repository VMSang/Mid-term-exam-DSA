#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    string tenThanhVien;
    string hocHamHocVi;
    int time; //lưu thời gian rảnh
    Node* next; //liên kết thành viên tiếp theo trong cùng khoa
};

struct Khoa {
    Node* head;
    int soLuongThanhVien;
};

void themThanhVien(Khoa& khoa, string ten, string hocVi) {
    Node* newNode = new Node;
    newNode->tenThanhVien = ten;
    newNode->hocHamHocVi = hocVi;

    newNode->next = NULL;

    // Khoa rỗng (thêm thành viên đầu tiên)
    if (khoa.head == NULL) {
        khoa.head = newNode;
    } else {
        // Đã tồn tại ít nhất 1 thành viên => thêm thành viên mới , lien ket voi thanh vien cu
        Node* curr = khoa.head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    khoa.soLuongThanhVien++;
}

int main() {
    cout << "\t-----Chào Mừng bạn đến với hệ thống quản lý hội đồng nghiệm thu-----\n";
    // Tạo 7 khoa
    Khoa danhSachKhoa[7];
    for (int i = 0; i < 7; i++) {
        danhSachKhoa[i].head = NULL;
        danhSachKhoa[i].soLuongThanhVien = 0;
    }
    // mở file thông tin Giảng Viên
    fstream InfFile("/media/minhsang/Data/1_Source Code/Mid-term-exam-DSA/inputInforMember.txt");
    if(!InfFile){
        cout<<"Lỗi Mở File thông tin";
        return -1;
    }
    // luu tru thong tin
    string khoaCuaGiangVien, tenGiangVien, hocVi;
    while (getline(InfFile, khoaCuaGiangVien)) {

        getline(InfFile, tenGiangVien);
        getline(InfFile, hocVi);

        if (khoaCuaGiangVien == "congNgheThongTin") {
            themThanhVien(danhSachKhoa[0], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "luat") {
            themThanhVien(danhSachKhoa[1], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "moiTruong") {
            themThanhVien(danhSachKhoa[2], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "ngheThuat") {
            themThanhVien(danhSachKhoa[3], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "ngoaiNgu") {
            themThanhVien(danhSachKhoa[4], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "quanTriKinhDoanh") {
            themThanhVien(danhSachKhoa[5], tenGiangVien, hocVi);
        } else if (khoaCuaGiangVien == "thuVien_VanPhong") {
            themThanhVien(danhSachKhoa[6], tenGiangVien, hocVi);
        } else {
            cout << "Khong the so sanh du lieu" << endl;
        }

        // Đọc dòng trống sau mỗi nhóm 3 dòng
        string emptyLine;
        getline(InfFile, emptyLine);
    }
    InfFile.close();

    bool nhapTiep = true;
    while (nhapTiep) {
        bool validInput = false;
        int bietBaoNhieuNguoi;
        int chonKhoa;
        int chon = -1;

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
                    cout << "Đây là danh sách các thành viên thuộc khoa Công nghệ Thông tin\n";
                    Node* curr = danhSachKhoa[0].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 2) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Luật\n";
                    Node* curr = danhSachKhoa[1].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 3) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Môi trường\n";
                    Node* curr = danhSachKhoa[2].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 4) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Nghệ thuật\n";
                    Node* curr = danhSachKhoa[3].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 5) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Ngoại ngữ\n";
                    Node* curr = danhSachKhoa[4].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 6) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Quản trị Kinh doanh\n";
                    Node* curr = danhSachKhoa[5].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 7) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Thư viện – Văn phòng\n";
                    Node* curr = danhSachKhoa[6].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                cout<<endl;
                cout<<"Nếu muốn đổi khoa chọn [-1]"<<endl;
                cout << "Bạn đã biết thời gian trống của bao nhiêu người trong danh sách trên: ";
            } while (chon != -1);

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

        cout << "\nMời bạn nhập khung giờ trống cho từng người đã biết\n";
        cout << "Với định dạng sau: [thứ][GiờBắtĐầuRảnh][GiờBận] ví dụ: 30915 (thứ 3, rảnh từ 9 giờ đến 15 giờ)\n";
        cout << endl;
        int chonNguoiThuMay;
        for (int i = 0; i < bietBaoNhieuNguoi; i++){
            cout<<"Người Thứ ";
            cin>>chonNguoiThuMay;
    		bool giaTriTime = false;
    		while (!giaTriTime) {
        		cout << "Thời gian của người thứ " << chonNguoiThuMay << " theo danh sách: ";
                //đi đến nơi lưu thơi gian của người đó
                Node *curr = danhSachKhoa[chonKhoa].head;
                for(int j=0; j<chonNguoiThuMay; j++){
                    curr = curr ->next;
                }
                int time;
                cin>>time;
        		// Kiểm tra định dạng thời gian
        		if (time >= 10000 && time <= 70000) {
                    curr->time = time;
          			giaTriTime = true;
        		} else {
            		cout << "Bạn đã nhập định dạng thời gian không hợp lệ. Vui lòng nhập lại." << endl;
        		}
   			}
}

        cout << "\nBạn có muốn tiếp tục nhập thông tin cho hội đồng không?" << endl;
        cout << "1: Có" << endl;
        cout << "2: Không" << endl;
        cout << "Nhập lựa chọn của bạn: ";

        int luaChon;
        cin >> luaChon;

        if (luaChon != 1)
            nhapTiep = false;
    }

    int option;
    cout << "\n-----------Lựa chọn:-----------" << endl;
    cout << "1: Kiểm tra hai hội đồng bất kỳ (tất cả hội đồng đã được tạo bao gồm khác khoa)" << endl;
    cout << "2: Tìm kiếm hội đồng đang tham gia thông qua khoa nào, tên của giáo viên" << endl;
    cout << "3: Hiển thị thời gian biểu tất cả các lịch đã được tạo của trường" << endl;
    cout << "Nhập lựa chọn của bạn: ";
    cin >> option;

    switch (option) {
        case 1:
            // Code để kiểm tra hai hội đồng bất kỳ
            break;
        case 2:
            // Code để tìm kiếm hội đồng thông qua khoa hoặc tên giáo viên
            break;
        case 3:
            // Code để hiển thị thời gian biểu của các lịch đã được tạo của trường
            break;
        default:
            cout << "Lựa chọn không hợp lệ." << endl;
    }

    return 0;
}
