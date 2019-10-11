#include <iostream>
#define MAX_ELEMENT 200
using namespace std;

typedef struct {
    int key;
} element;

typedef struct queue{
    int head;
    int tail;
    element arr[MAX_ELEMENT];
} QueueType;

int queue_empty(QueueType);
void enqueue(QueueType *, element);
int dequeue(QueueType *);

int main(void)
{
    QueueType Q;
    
    Q.head = 0;
    Q.tail = 0;
    
    int size;
    cin >> size;
    for(int i=0, x; i<size; ++i) {
        cin >> x;
        element item;
        item.key = x;
        enqueue(&Q, item);
    }
    
    while(!queue_empty(Q)) {
        dequeue(&Q);
    }
    
}

int queue_empty(QueueType q)
{
    if(q.head == q.tail) return true;
    return false;
}

void enqueue(QueueType *q, element item) {
    q->arr[q->head++].key = item.key;
    cout << "ENQUEUE : " << item.key << '\n';
    q->head = q->head % MAX_ELEMENT;
}

int dequeue(QueueType *q)
{
    int data;
    if(queue_empty(*q))
    {
        cout << "the queue is empty" << '\n';
        return -1;
    }
    
    data = q->arr[q->tail++].key;
    cout << "DEQUEUE : " << data << '\n';
    q->tail = q->tail % MAX_ELEMENT;
    
    return data;
}
