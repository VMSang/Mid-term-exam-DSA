#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int soLuongLine = 10*7*4-1; //10 người 7 khoa, mỗi người 4 hàng, trừ 1 hàng của người đầu tiên không có khoảng trống

struct ThongTinThanhVien {
    string tenThanhVien;
    string hocHamHocVi;
    int a[4]; //lưu thời gian rảnh
};

struct Node {
    ThongTinThanhVien thanhVien;
    Node* next; //liên kết thành viên tiếp theo trong cùng khoa
};

struct Khoa {
    Node* head;
    int soLuongThanhVien;
};

void themThanhVien(Khoa& khoa, ThongTinThanhVien thanhVien) {
    Node* newNode = new Node;
    newNode->thanhVien = thanhVien;
    newNode->next = NULL;

    // Khoa rỗng (thêm thành viên đầu tiên)
    if (khoa.head == NULL) {
        khoa.head = newNode;
    } else {
        // Đã tồn tại ít nhất 1 thành viên => thêm thành viên mới
        Node* curr = khoa.head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    khoa.soLuongThanhVien++;
}

int main() {
    cout << "\n\t\t\t-----------Chào Mừng bạn đến với hệ thống quản lý hội đồng nghiệm thu-----------\n\n";

    // Tạo 7 khoa
    Khoa danhSachKhoa[7];
    for (int i = 0; i < 7; i++) {
        danhSachKhoa[i].head = NULL;
        danhSachKhoa[i].soLuongThanhVien = 0;
    }

    ifstream InfFile("inputInforMember.txt");
    if(!InfFile) return -1;

    for(int i=0; i<soLuongLine; i++){
        string khoaCuaGiangVien;
        getline(InfFile, khoaCuaGiangVien);

        if (khoaCuaGiangVien == "congNgheThongTin") {
            string tenGiangVienIT;
            getline(InfFile, tenGiangVienIT);
            string hocHamGiangVien;
            getline(InfFile, hocHamGiangVien);
            ThongTinThanhVien tmp;
            tmp.tenThanhVien = tenGiangVienIT;
            tmp.hocHamHocVi = hocHamGiangVien;
            themThanhVien(danhSachKhoa[0], tmp);
        }

        if (khoaCuaGiangVien == "luat") {
            string tenGiangVienLuatSu;
            getline(InfFile, tenGiangVienLuatSu);
            string hocViLuatSu;
            getline(InfFile, hocViLuatSu);
            ThongTinThanhVien tmp;
            tmp.tenThanhVien = tenGiangVienLuatSu;
            tmp.hocHamHocVi = hocViLuatSu;
            themThanhVien(danhSachKhoa[1], tmp);
        }

        if (khoaCuaGiangVien == "moiTruong") {
            string tenGiangVienMoiTruong;
            getline(InfFile, tenGiangVienMoiTruong);
            string hocViMoiTruong;
            getline(InfFile, hocViMoiTruong);
            ThongTinThanhVien tmp;
            tmp.tenThanhVien = tenGiangVienMoiTruong;
            tmp.hocHamHocVi = hocViMoiTruong;
            themThanhVien(danhSachKhoa[2], tmp);
        }

        if (khoaCuaGiangVien == "ngheThuat") {
            string tenGiangVienNgeThua;
            getline(InfFile, tenGiangVienNgeThua);
            string hocViNgheNhan;
            getline(InfFile, hocViNgheNhan);
            ThongTinThanhVien tmp;
            tmp.tenThanhVien = tenGiangVienNgeThua;
            tmp.hocHamHocVi = hocViNgheNhan;
            themThanhVien(danhSachKhoa[3], tmp);
        }

        if (khoaCuaGiangVien == "ngoaiNgu") {
            string tenGiaoVienNgoaiNgu;
            getline(InfFile, tenGiaoVienNgoaiNgu);
            string hocHamNgoaiNgu;
            getline(InfFile, hocHamNgoaiNgu);
            ThongTinThanhVien tmp;
            tmp.tenThanhVien = tenGiaoVienNgoaiNgu;
            tmp.hocHamHocVi = hocHamNgoaiNgu;
            themThanhVien(danhSachKhoa[4], tmp);
        }

        if (khoaCuaGiangVien == "quanTriKinhDoanh") {
            string tenGiangVienQTKD;
            getline(InfFile, tenGiangVienQTKD);
            string hocViQTKD;
            getline(InfFile, hocViQTKD);
            ThongTinThanhVien tmp;
            tmp.tenThanhVien = tenGiangVienQTKD;
            tmp.hocHamHocVi = hocViQTKD;
            themThanhVien(danhSachKhoa[5], tmp);
        }

        if (khoaCuaGiangVien == "thuVien_VanPhong") {
            string tenGiangVienVanPhong;
            getline(InfFile, tenGiangVienVanPhong);
            string hocViVanPhong;
            getline(InfFile, hocViVanPhong);
            ThongTinThanhVien tmp;
            tmp.tenThanhVien = tenGiangVienVanPhong;
            tmp.hocHamHocVi = hocViVanPhong;
            themThanhVien(danhSachKhoa[6], tmp);
        }
    }


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
                    for(int i=1; curr != NULL; i++) {
                        cout <<i<<". " <<curr->thanhVien.tenThanhVien << endl;
                        curr = curr->next;
                    }
                }
                if (chonKhoa == 1) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Công nghệ Thông tin\n";
                    Node* curr = danhSachKhoa[0].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->thanhVien.tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 2) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Luật\n";
                    Node* curr = danhSachKhoa[1].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->thanhVien.tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 3) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Môi trường\n";
                    Node* curr = danhSachKhoa[2].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->thanhVien.tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 4) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Nghệ thuật\n";
                    Node* curr = danhSachKhoa[3].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->thanhVien.tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 5) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Ngoại ngữ\n";
                    Node* curr = danhSachKhoa[4].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->thanhVien.tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 6) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Quản trị Kinh doanh\n";
                    Node* curr = danhSachKhoa[5].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->thanhVien.tenThanhVien << endl;
                        curr = curr->next;
                    }
                }

                if (chonKhoa == 7) {
                    cout << "Đây là danh sách các thành viên thuộc khoa Thư viện – Văn phòng\n";
                    Node* curr = danhSachKhoa[6].head;
                    for (int i = 1; curr != NULL; i++) {
                        cout << i << ". " << curr->thanhVien.tenThanhVien << endl;
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
                cout << "Để mở rộng cơ sở dữ liệu xin liên hệ phòng kỹ thuật của chúng tôi qua E-Mail: techsupport@softtechsolutions.com" << endl;
            }
        }

        cout << "Vâng, đã biết " << bietBaoNhieuNguoi << " người\n";
        cout << "\nMời bạn nhập khung giờ trống cho từng người đã biết:\n";
        cout << "Với định dạng sau: [thứ][giờBắtĐầu][GiờBận] ví dụ: 30915 (thứ 3, rảnh từ 9 giờ đến 15 giờ)\n";
        cout << endl;

        for (int i = 0; i < bietBaoNhieuNguoi; i++){
    		bool giaTriTime = false;
    		while (!giaTriTime) {
        		cout << "Thời gian của người thứ " << i + 1 << ": ";
                //xu ly thoi gian o day
                int n; cin>>n;
        		// Kiểm tra định dạng thời gian
        		if (n >= 10000 && n <= 70000) {
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