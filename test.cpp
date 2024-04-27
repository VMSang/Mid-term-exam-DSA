#include <iostream>
#include <fstream>
using namespace std;

struct thongtinthanhvien{
	string tenThanhVien;
	string hocHamHocVi;

};

struct node{
	thongtinthanhvien thanhvien;
	node *next;
};

struct khoa{
	*node head;
	int soLuongThanhVien;
};

void themThanhVien(khoa &*chonKhoa, thongtinthanhvien thanhvien){
	node newthanhvien = new node;

	if(chonKhoa -> head == NULL){
		chonKhoa -> head = newthanhvien;
		return;
	}
	else{
		node curr = chonKhoa -> head;
		while(curr -> next != NULL){
			curr = curr -> next;
		}
		curr -> next = newthanhvien;
	}
	chonkhoa -> soLuongThanhVien++;
}
int main() {    
 	//tao 7 khoa
 	khoa danhSachKhoa[7];
 	for(int i=0; i<7; i++){
 		danhSachKhoa[i] -> head = NULL;
 		danhSachKhoa[i] -> soLuongThanhVien = 0;
 	}
 	
    return 0;
}