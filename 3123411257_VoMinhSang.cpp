#include <iostream>
using namespace  std;

struct thanhvien{
    string khoa;
    string tenthanhvien;
    string hochamhocvi;
    int khunggio[4];
};

struct node{
    thanhvien data;
    node *next;
};

node* createNode(string khoa, string tenthanhvien, string hochamhocvi){
    node *newNode = new node;

    newNode->data.khoa = khoa;
    newNode->data.tenthanhvien = tenthanhvien;
    newNode->data.hochamhocvi = hochamhocvi;
    newNode->next = NULL;
    return newNode;
}

void themcuoi(node *&head, string &khoa, string &tenthanhvien, string &hochamhocvi){
    getline(cin, khoa);
    getline(cin, tenthanhvien);
    getline(cin, hochamhocvi);

    node *newnode = createNode(khoa, tenthanhvien, hochamhocvi);
    node *tmp = head;
    if(head == NULL){
        head = newnode;
        return;
    }
    while(tmp->next != NULL){
        tmp = tmp -> next;
    }
    tmp -> next = newnode;
}
void duyet(node *head){
    while (head != NULL){
        cout<<head->data.khoa<<endl;
        cout<<head->data.tenthanhvien<<endl;
        cout<<head->data.hochamhocvi<<endl;
        head = head -> next;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    node *head = NULL;
    string khoa;
    string tenthanhvien;
    string hochamhocvi;
    //giả sử tổng các khoa có 20 thành viên
    for(int i=0; i<20; i++){
        themcuoi(head, khoa, tenthanhvien, hochamhocvi);
    }
    duyet(head);

    return 0;
}
