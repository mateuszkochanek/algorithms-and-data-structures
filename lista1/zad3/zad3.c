#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int size;

typedef struct MyListElement {
    int value;
    struct MyListElement * next;
    struct MyListElement * previous;
} MyListElement;

int get_size(MyListElement *list){ //good
    int i;
    if(list == NULL)
        return 0;
    i=1;
    MyListElement *current = list;
    while(current != list->previous){
        i++;
        current = current->next;
    }
    return i;
}

void push_front(MyListElement **list,int val){ //good
    MyListElement *newListElement;
    newListElement=malloc(sizeof(MyListElement));

    if(*list == NULL){
        newListElement->value = val;
        newListElement->next = newListElement;
        newListElement->previous = newListElement;
        *list = newListElement;
    } else {
        newListElement->value = val;
        newListElement->next = *list;
        newListElement->previous = (*list)->previous;
        ((*list)->previous)->next = newListElement;
        (*list)->previous = newListElement;
        *list = newListElement;
    }
    
}

void push_back(MyListElement **list,int val){ //good
    MyListElement *newListElement;
    newListElement=malloc(sizeof(MyListElement));

    if(*list == NULL){
        newListElement->value = val;
        newListElement->next = newListElement;
        newListElement->previous = newListElement;
        *list = newListElement;
    } else {
        newListElement->value = val;
        newListElement->next = *list;
        newListElement->previous = (*list)->previous;
        ((*list)->previous)->next = newListElement;
        (*list)->previous = newListElement;
    }
}

//wkłada element dokładnie w miejsce wskazane, czyli dla indexu 1 doda w miejsce 1, a dla 0 w miejsce 0
void push_index(MyListElement **list,int val,int index){ // good
    MyListElement *newListElement;
    newListElement=malloc(sizeof(MyListElement));


    if(index == 0)
        push_front(list,val);
    else if(index == get_size(*list))
        push_back(list, val);
    else{
        int i;
        MyListElement *current = *list;
        for(i = 0 ; i < index-1 ; i++){
            if(current == (*list)->previous)
               break;
          current = current->next;
        }
        if(current != (*list)->previous && index > 0){
            MyListElement *tempNext = current->next;
            newListElement->value = val;
            newListElement->next = current->next;
            newListElement->previous = current;
            (current->next)->previous = newListElement;
            current->next = newListElement; 
            newListElement->next = tempNext;
        } else {
            printf("Nie znaleziono indexu %d, wartości %d nie dodano\n",index,val);
        }
        
    }
    
}

void pop_front(MyListElement **list){ //good
    MyListElement *tempNext;

    if(*list != NULL){
        tempNext = (*list)->next;
        ((*list)->next)->previous = (*list)->previous;
        ((*list)->previous)->next = (*list)->next;
        free(*list);
        *list = tempNext;
    }
}

void pop_back(MyListElement **list){ //good
    MyListElement *tempPrev;

    if(*list != NULL){
        tempPrev = (*list)->previous;
        (((*list)->previous)->previous)->next = *list;
        (*list)->previous = ((*list)->previous)->previous;
        free(tempPrev);
    }
}

void pop_index(MyListElement **list,int index){ //good
    if(index == 0)
        pop_front(list);
    else if(index == get_size(*list)-1)
        pop_back(list);
    else{
        MyListElement *current;
        int size = get_size(*list);
        int halfSize = size/2;
        int i;
        if(index < halfSize && index > 0){
            current = (*list)->next;
            for(i = 1 ; i < index ; i++){
                current = current->next;
            }
            (current->previous)->next = current->next;
            (current->next)->previous = current->previous;
            free(current);
        } else if (index < size){
            current = (*list)->previous;
            for(i = size-1 ; i > index ; i--){
                current = current->previous;
            }
            (current->previous)->next = current->next;
            (current->next)->previous = current->previous;
            free(current);
        } else {
            printf("Nie znaleziono indexu %d, wartości nie usunięto\n",index);
        }
        
    }
}

int get_value(MyListElement *list,int index){ // good
    MyListElement *current;
    int halfSize = size/2;

    if(index == 0)
        return list->value;
        
    int i;
    if(index < halfSize && index > 0){
        current = list->next;
        for(i = 1 ; i < index ; i++){
            current = current->next;
        }
        return current->value;
    } else if (index < size){
        current = list->previous;
        for(i = size-1 ; i > index ; i--){
            current = current->previous;
        }
        return current->value;
    } else {
        printf("Nie znaleziono indexu %d\n",index);
        return 0;
    }
    
}


void show_MyList(MyListElement *list){ //good

    if(list == NULL)
            printf("list is empty!\n");
    else {
        MyListElement *current = list->next;

        printf("_________________\n");
        printf("Wartość elementu:%d\n",list->value);
        while(current != list){
            printf("Wartość elementu:%d\n",current->value);
            current = current->next;
        }
    }


}

MyListElement* megre(MyListElement *list1,MyListElement *list2){
    MyListElement *list3,*newListElement;
    newListElement=malloc(sizeof(MyListElement));
    list3 = malloc(sizeof(MyListElement));
    newListElement->value = list1->value;
    newListElement->next = newListElement;
    newListElement->previous = newListElement;
    list3 = newListElement;

    MyListElement *current1 = list1->next;
    MyListElement *current2 = list2;
    do{
        MyListElement *newListElement;
        newListElement=malloc(sizeof(MyListElement));
        newListElement->value = current1->value;
        newListElement->next = list3;
        newListElement->previous = list3->previous;
        (list3->previous)->next = newListElement;
        (list3)->previous = newListElement;

        current1 = current1->next;
    } while(current1 != list1);

    do{
        MyListElement *newListElement;
        newListElement=malloc(sizeof(MyListElement));
        newListElement->value = current2->value;
        newListElement->next = list3;
        newListElement->previous = list3->previous;
        (list3->previous)->next = newListElement;
        (list3)->previous = newListElement;

        current2 = current2->next;
    } while(current2 != list2);
    return list3;
}


int main(int argc, char *argv[])
{
    time_t tt;
    clock_t start_t, end_t;
    double total_t;
    int zarodek = time(&tt);
    srand(zarodek);

    MyListElement *list;
    list=malloc(sizeof(MyListElement));
    list=NULL;

    for(int i = 0 ; i < 1000 ; i++){
        push_front(&list,rand());
    }
    size = get_size(list);
    //losowanie 1000 razy elementu z listy
    start_t = clock();
    for(int i = 0 ; i < 1000 ; i++){
        get_value(list,rand()%1000);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Losowo zajęło: %.10f\n",total_t/1000.0);

    start_t = clock();
    for(int i = 0 ; i < 1000 ; i++){
        get_value(list,50);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Tak samo zawsze zajęło: %.10f\n",(total_t/1000.0));

    return 0;
}
//testy list merge-a
    /*MyListElement *list1;
    list1=malloc(sizeof(MyListElement));
    list1=NULL;
    push_front(&list1,5);
    push_front(&list1,4);
    push_front(&list1,3);
    push_front(&list1,2);
    push_front(&list1,1);
    show_MyList(list1);

    MyListElement *list2;
    list2=malloc(sizeof(MyListElement));
    list2=NULL;
    push_back(&list2,5);
    push_back(&list2,4);
    push_back(&list2,3);
    push_back(&list2,2);
    push_back(&list2,1);
    show_MyList(list2);

    MyListElement *list3 = megre(list1,list2);
    show_MyList(list3);
    show_MyList(list1);
    show_MyList(list2);

    push_front(&list1,5);
    push_front(&list1,5);
    push_front(&list1,5);

    push_back(&list2,5);
    push_back(&list2,5);
    push_back(&list2,5);

    show_MyList(list3);
    show_MyList(list1);
    show_MyList(list2);*/

//testy dla funkcji ogólnych push, size, show
   /* show_MyList(list);
    printf("size to:%d\n",get_size(list));
    push_front(&list,5);
    push_front(&list,4);
    push_front(&list,3);
    push_index(&list,2,0);
    show_MyList(list);
    printf("size to:%d\n",get_size(list));
    push_back(&list,1);
    show_MyList(list);
    printf("size to:%d\n",get_size(list));
    pop_front(&list);
    show_MyList(list);
    printf("size to:%d\n",get_size(list));
    pop_back(&list);
    show_MyList(list);
    printf("size to:%d\n",get_size(list));*/

    // testy dla pusha w index
    /*push_front(&list,5);
    push_front(&list,4);
    push_index(&list,2,3);
    push_index(&list,2,-1);
    push_index(&list,2,1);
    push_index(&list,10,3);
    show_MyList(list);*/

    //testy na pop w index i get value
    /*push_front(&list,5);
    push_front(&list,4);
    push_front(&list,3);
    push_front(&list,2);
    push_front(&list,1);
    show_MyList(list);
    pop_index (&list,-1);
    show_MyList(list);
    printf("0 index to:%d\n",get_value(list,0));
    printf("2 index to:%d\n",get_value(list,2));
    printf("1 index to:%d\n",get_value(list,1));
    printf("-1 index to:%d\n",get_value(list,-1));
    printf("6 index to:%d\n",get_value(list,6));*/

//testy czasowe
    /*for(int i = 0 ; i < 1000 ; i++){
        push_front(&list,rand());
    }
    //losowanie 1000 razy elementu z listy
    start_t = clock();
    for(int i = 0 ; i < 1000 ; i++){
        get_value(list,rand()%1000);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Losowo zajęło: %f\n",total_t/1000.0);

    start_t = clock();
    for(int i = 0 ; i < 1000 ; i++){
        get_value(list,500);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Tak samo zawsze zajęło: %f\n",(total_t/1000.0));*/

        /*MyListElement *list;
    list=malloc(sizeof(MyListElement));
    list=NULL;

// testy dla funkcji w dwoch kierunkach
    push_front(&list,5);
    push_front(&list,4);
    push_front(&list,3);
    push_front(&list,2);
    push_front(&list,1);
    push_front(&list,0);
    push_index(&list,-1,0);
    push_index(&list,-1,-5);
    push_index(&list,-1,10);
    push_index(&list,-1,7);
    push_index(&list,-1,4);
    pop_back(&list);
    pop_front(&list);
    show_MyList(list);
    printf("size to:%d\n",get_size(list));
    printf("index 0 to:%d\n",get_value(list,0));
    printf("index 7 to:%d\n",get_value(list,7));
    printf("index 6 to:%d\n",get_value(list,6));
    printf("index 3 to:%d\n",get_value(list,3));
    printf("index 1 to:%d\n",get_value(list,1));
    printf("index 2 to:%d\n",get_value(list,2));
    printf("index 4 to:%d\n",get_value(list,4));
    printf("index 5 to:%d\n",get_value(list,5));
    pop_index(&list,3);
    show_MyList(list);
    push_index(&list,444,3);
    show_MyList(list);*/