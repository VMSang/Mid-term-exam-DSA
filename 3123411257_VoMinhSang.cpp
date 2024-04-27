#include <iostream>
using namespace  std;

struct thanhvien{
    string khoa;
    string tenThanhVien;
    string hocHamHocVi;
    int khungGioRanh[4];
};

struct khoa{
    thanhvien data;
    khoa *next;
};

khoa* createkhoa(string khoa, string tenThanhVien, string hocHamHocVi){
    khoa *newkhoa = new khoa;

    newkhoa->data.khoa = khoa;
    newkhoa->data.tenThanhVien = tenThanhVien;
    newkhoa->data.hocHamHocVi
    newkhoa->next = NULL;
    return newkhoa;
}

void themcuoi(khoa *&head, string &khoa, string &tenThanhVien, string &hocHamHocVi){
    getline(cin, khoa);
    getline(cin, tenThanhVien);
    getline(cin, hocHamHocVi);

    khoa *newkhoa = createkhoa(khoa, tenThanhVien, hocHamHocVi);
    khoa *tmp = head;
    if(head == NULL){
        head = newkhoa;
        return;
    }
    while(tmp->next != NULL){
        tmp = tmp -> next;
    }
    tmp -> next = newkhoa;
}
void duyet(khoa *head){
    while (head != NULL){
        cout<<head->data.khoa<<endl;
        cout<<head->data.tenThanhVien<<endl;
        cout<<head->data.hocHamHocVi<<endl;
        head = head -> next;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    khoa *head = NULL;
    string khoa;
    string tenThanhVien;
    string hocHamHocVi;
    //giả sử tổng các khoa có 20 thành viên
    for(int i=0; i<20; i++){
        themcuoi(head, khoa, tenThanhVien, hocHamHocVi);
    }

    return 0;
}
