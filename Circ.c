#include <stdio.h>

#define max 6

int QUEUE[max];
int front = -1, rear = -1;

int Overflow() {
    return ((rear+1)%max) == front;
}

int Underflow() {
    return front == -1;
}

void enqueue(int element) {
    if (Overflow()) {
        printf("Queue is full!!\n");
    } else {
        if (front == -1) {
            front = 0;
            rear=0;
        }
        else{
        rear=(rear+1)% max;}
       
        QUEUE[rear] = element;
        printf("\nElement has been added successfully \n");
    }
}

void dequeue() {
    if (Underflow()) {
        printf("Queue is empty!!\n");
    } else {
        printf("Deleted element is %d\n", QUEUE[front]);
       
        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else{
        front=(front+1)%max;}

    }
}

void display() {
    if (Underflow()) {
        printf("Queue is empty!!\n");
    } else {
        printf("Queue elements: ");
        int i = front;
        while (1) {
            printf("%d\t", QUEUE[i]);
            if (i == rear) break;
            i = (i + 1) % max;
        }
        printf("\n");
    }
}

int main() {
    int flow = 1;
    while (flow == 1) {
        int option;
        printf("\nChoose the operations for queue:\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nOption: ");
        scanf("%d", &option);
        switch (option) {
            case 1: {
                int element;
                printf("Enter the element to be added: ");
                scanf("%d", &element);
                enqueue(element);
                break;
            }
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                flow = 0;
                break;
            default:
                printf("Wrong Option.\n");
                flow = 0;
                break;
        }
    }
    return 0;
}
