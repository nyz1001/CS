#include <iostream>
#define MAX_ELEMENT 200
using namespace std;

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void insert_max_heap(HeapType *, element);
element delete_max_heap(HeapType *);

int main(void)
{
    HeapType H;
    H.heap_size = 0;
    int size;
    cin >> size;
    
    for(int i=0, x; i<size; ++i) {
        cin >> x;
        element elem;
        elem.key = x;
        insert_max_heap(&H, elem);
    }
    
    size = H.heap_size;
    for(int i=0; i<size; ++i) {
        cout << delete_max_heap(&H).key << '\n';
    }
    
}

void insert_max_heap(HeapType *h, element item){
    int i;
    i = ++(h->heap_size);
    while((i != 1) && (item.key < h->heap[i/2].key)){
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_max_heap(HeapType *h){
    int parent, child;
    element item, temp;
    
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    
    while(child <= h->heap_size) {
        
        if( (child < h->heap_size) && ((h->heap[child].key) > h->heap[child+1].key) ) {
            child++;
        }
        
        if( temp.key <= h->heap[child].key ) {
            break;
        }
        
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    
    h->heap[parent] = temp;
    return item;
}
