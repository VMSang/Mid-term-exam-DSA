#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct ThongTinThanhVien {
    string tenThanhVien;
    string hocHamHocVi;
    int a[4]; // Giả sử mỗi thành viên có 4 khoảng thời gian trống
};

struct Node {
    ThongTinThanhVien thanhVien;
    Node* next;
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
    cout << "\n\t\t\t\t\t-----------Chào Mừng bạn đến với hệ thống quản lý hội đồng nghiệm thu-----------\n\n";

    // Tạo 7 khoa
    Khoa danhSachKhoa[7];
    for (int i = 0; i < 7; i++) {
        danhSachKhoa[i].head = NULL;
        danhSachKhoa[i].soLuongThanhVien = 0;
    }

    bool nhapTiep = true;
    while (nhapTiep) {
        bool validInput = false;
        int bietBaoNhieuNguoi;
        int chonKhoa;

        while (!validInput) {
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
            chonKhoa--; // Vì mảng bắt đầu từ 0

            cout << "Bạn đã biết thời gian trống của bao nhiêu người: ";
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
        		int n;
        		cin >> n;

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