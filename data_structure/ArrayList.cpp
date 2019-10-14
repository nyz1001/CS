#include <iostream>
using namespace std;

#define LIST_LEN    100
typedef int LData;

typedef struct __ArrayList {
    LData arr[LIST_LEN];
    int numOfData;
    int curPosition;
} ArrayList;

typedef ArrayList List;

void ListInit(List * plist)
{
    (plist->numOfData) = 0;
    (plist->curPosition) = -1;
}

void LInsert(List * plist, LData data) {
    
    if(plist->numOfData >= LIST_LEN)
    {
        cout << "Full Memory";
        return;
    }
    
    plist->arr[plist->numOfData] = data;
    (plist->numOfData)++;
}

int LFirst(List * plist, LData * pdata) {
    if(plist->numOfData == 0) return false;
    (plist->curPosition) = 0;
    *pdata = plist->arr[0];
    return true;
}

int LNext(List * plist, LData * pdata) {
    if(plist->curPosition >= (plist->numOfData)-1) return false;
    
    (plist->curPosition)++;
    *pdata = plist->arr[plist->curPosition];
    return true;
}

LData LRemove(List * plist) {
    int rpos = plist->curPosition;
    int num = plist->numOfData;
    int i;
    LData rdata = plist->arr[rpos];
    
    // 한칸씩 땡겨오기
    for(i=rpos; i<num-1; i++) plist->arr[i] = plist->arr[i+1];
    
    (plist->numOfData)--;
    (plist->curPosition)--;
    return rdata;
}

int LCount(List * plist) { return plist->numOfData; }

int main(void)
{
    List list;
    int data;
    ListInit(&list);
    
    LInsert(&list, 11); LInsert(&list, 11);
    LInsert(&list, 22); LInsert(&list, 22);
    LInsert(&list, 33);
    
    cout << "연결리스트 노드 수 : " << LCount(&list) << '\n';
    if(LFirst(&list, &data)) {
        cout << data << ' ';
        while(LNext(&list, &data))
            cout << data << ' ';
    }
    cout << '\n' << '\n';
    
    if(LFirst(&list, &data))
    {
        if(data == 22) LRemove(&list);
        
        while(LNext(&list, &data)) {
            if(data == 22) LRemove(&list);
        }
    }
    
    cout << "연결리스트 노드 수 : " << LCount(&list) << '\n';
    if(LFirst(&list, &data)) {
        cout << data << ' ';
        while(LNext(&list, &data))
            cout << data << ' ';
    }
    cout << '\n' << '\n';
    return 0;
}
