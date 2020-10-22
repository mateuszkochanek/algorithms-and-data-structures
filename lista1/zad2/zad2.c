#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct MyListElement {
    int value;
    struct MyListElement * next;
} MyListElement;

void push_front(MyListElement **list,int val){
    MyListElement *newListElement;
    newListElement=malloc(sizeof(MyListElement));


    newListElement->value = val;
    newListElement->next = *list;
    *list = newListElement;
}

void push_back(MyListElement **list,int val){
    MyListElement *newListElement;
    newListElement=malloc(sizeof(MyListElement));

    newListElement->value = val;
    newListElement->next = NULL;

    if(*list == NULL)
            *list = newListElement;
    else{
        MyListElement *current = *list;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newListElement;
    }
}

//wkłada element dokładnie w miejsce wskazane, czyli dla indexu 1 doda w miejsce 1, a dla 0 w miejsce 0
void push_index(MyListElement **list,int val,int index){
    MyListElement *newListElement;
    newListElement=malloc(sizeof(MyListElement));

    newListElement->value = val;
    newListElement->next = NULL;

    if(index == 0)
        push_front(list,val);
    else{
        int i;
        MyListElement *current = *list;
        for(i = 0 ; i < index-1 ; i++){
            if(current == NULL)
               break;
          current = current->next;
        }
        if(current != NULL && index > 0){
            MyListElement *tempNext = current->next;
            current->next = newListElement; 
            newListElement->next = tempNext;
        } else {
            printf("Nie znaleziono indexu %d, wartości %d nie dodano\n",index,val);
        }
        
    }
    
}

void pop_front(MyListElement **list){
    MyListElement *tempNext;

    if(*list != NULL){
        tempNext = (*list)->next;
        free(*list);
        *list = tempNext;
    }
}

void pop_back(MyListElement **list){
    if(*list != NULL){
        MyListElement *current = *list;
        if(current->next != NULL){
            while((current->next)->next != NULL){
            current = current->next;
            }
            free(current->next);
            current->next = NULL;
        } else {
           *list = NULL; 
        }
        
    }
}

void pop_index(MyListElement **list,int index){
    if(index == 0)
        pop_front(list);
    else {
        int i;
        MyListElement *current = *list;
        for(i = 0 ; i < index-1 ; i++){
            if(current->next == NULL)
               break;
          current = current->next;
        }
        if(current->next != NULL && index > 0){
            MyListElement *tempNext = (current->next)->next;
            free(current->next); 
            current->next = tempNext;
        } else {
            printf("Nie znaleziono indexu %d, wartości nie usunięto\n",index);
        }
        
    }
}

int get_value(MyListElement *list,int index){
    if(index == 0)
        return list->value;
    int i;
    MyListElement *current = list;
    for(i = 0 ; i < index ; i++){
        if(current == NULL)
            break;
        current = current->next;
    }
    if(current != NULL && index > 0){
        return current->value;
    } else {
        printf("Nie znaleziono indexu %d\n",index);
        return 0;
    }
}

int get_size(MyListElement *list){
    int i;
    i=0;
    MyListElement *current = list;
    while(current != NULL){
        i++;
        current = current->next;
    }
    return i;
}

void show_MyList(MyListElement *list){

    if(list == NULL)
            printf("list is empty!\n");
    else {
        MyListElement *current = list;
        printf("_________________\n");
        while(current != NULL){
            printf("Wartość elementu:%d\n",current->value);
            current = current->next;
        }
    }


}

MyListElement* megre(MyListElement *list1,MyListElement *list2){
    MyListElement *list3;
    list3 = malloc(sizeof(MyListElement));
    list3->value = list1->value;
    list3->next = NULL;

    MyListElement *current1 = list1->next;
    MyListElement *current2 = list2;
    MyListElement *current3 = list3;
    while(current1 != NULL){
        MyListElement *newTemp = malloc(sizeof(MyListElement));
        newTemp->value = current1->value;
        newTemp->next = NULL;

        current3->next = newTemp;

        current3 = current3->next;
        current1 = current1->next;
    }
    while(current2 != NULL){
        MyListElement *newTemp = malloc(sizeof(MyListElement));
        newTemp->value = current2->value;
        newTemp->next = NULL;

        current3->next = newTemp;

        current3 = current3->next;
        current2 = current2->next;
    }
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