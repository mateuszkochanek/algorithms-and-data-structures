#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct MyQueue {
    int capacity;
    int size;
    struct MyQueueElement * first;
} MyQueue;

typedef struct MyQueueElement {
    int value;
    struct MyQueueElement * next;
} MyQueueElement;

void setCapacity(MyQueue **queue,int val){
    if(val > 0)
        (*queue)->capacity = val;
    else
        printf("Capasity musi być większe niż 0!");
}

void push(MyQueue **queue,int val){
    MyQueueElement *newQueueElement;
    newQueueElement=malloc(sizeof(MyQueueElement));

    newQueueElement->value = val;
    newQueueElement->next = NULL;

    if(*queue == NULL){
        printf("NULL");
    } else if((*queue)->first == NULL && (*queue)->capacity > 0) {
        (*queue)->first = newQueueElement;
        (*queue)->size = 1;
    } else if ((*queue)->size < (*queue)->capacity) {
        MyQueueElement *current = (*queue)->first;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newQueueElement;
        ((*queue)->size)++;
    } else {
        printf("Kolejka przepełniona, nie dodano elementu");
    }
}


int pop(MyQueue **queue){
    MyQueueElement *tempNext;
    int val=0;

    if(*queue == NULL){
        printf("NULL");
        return -1;
    }else if ((*queue)->first != NULL){
        tempNext = ((*queue)->first)->next;
        val=((*queue)->first)->value;
        free((*queue)->first);
        (*queue)->first = tempNext;
        ((*queue)->size)--;
        return  val;
    } else {
        printf("Kolejka jest pusta");
        return -1;
    }
}

int front(MyQueue **queue){
    if(*queue == NULL){
        printf("NULL");
        return -1;
    }else if ((*queue)->first != NULL){
        return  ((*queue)->first)->value;
    } else {
        printf("Kolejka jest pusta");
        return -1;
    }
}

bool isEmpty(MyQueue *queue){
    if(queue == NULL ){
        //printf("NULL");
        return false;
    }else if(queue->first != NULL){
        return false; 
    } else {
        //printf("kolejka jest pusta!");
        return true;
    }
}

bool isFull(MyQueue *queue){
    if(queue == NULL ){
        //printf("NULL");
        return false;
    }else if(queue->first != NULL){
        if(queue->size == queue->capacity)
            return true; 
        return false;
    } else {
        //printf("kolejka jest pusta!");
        return false;
    }
}

int getSize(MyQueue *queue){
    if(queue == NULL)
        return -1;
    int i;
    i=0;
    MyQueueElement *current = queue->first;
    while(current != NULL){
        i++;
        current = current->next;
    }
    return i;
}

void showQueue(MyQueue *queue){

    if(queue == NULL ){
        printf("NULL");
    }else if(queue->first != NULL){
        MyQueueElement *current = queue->first;
        printf("_________________\n");
        while(current != NULL){
            printf("Wartość elementu:%d\n",current->value);
            current = current->next;
        } 
    } else {
        printf("lista jest pusta");
    }
}



int main(int argc, char *argv[])
{
    MyQueue *myQueue;
    myQueue = malloc(sizeof(MyQueue));
    setCapacity(&myQueue, 10);
    printf("Size:%d\n",getSize(myQueue));
    printf("Czy pelne:%d\n",isFull(myQueue));
    printf("Czy puste:%d\n",isEmpty(myQueue));
    push(&myQueue,1);
    push(&myQueue,2);
    push(&myQueue,3);
    push(&myQueue,4);
    push(&myQueue,5);
    push(&myQueue,6);
    push(&myQueue,7);
    push(&myQueue,8);
    push(&myQueue,9);
    push(&myQueue,10);
    

    printf("Czy pelne:%d\n",isFull(myQueue));
    printf("Czy puste:%d\n",isEmpty(myQueue));
    printf("Size:%d\n",getSize(myQueue));
    showQueue(myQueue);
    printf("Wartość elementu pop:%d\n",pop(&myQueue));
    printf("Wartość elementu pop:%d\n",pop(&myQueue));
    printf("Size:%d\n",getSize(myQueue));
    showQueue(myQueue);
    printf("Wartość elementu front:%d\n",pop(&myQueue));
    printf("Czy pelne:%d\n",isFull(myQueue));
    printf("Czy puste:%d\n",isEmpty(myQueue));

    return 0;
}
