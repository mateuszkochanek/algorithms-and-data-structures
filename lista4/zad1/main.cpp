#include <iostream>
#include <time.h>
#include "DataStructure.h"

using namespace std;

struct Settings
{
    int stuctureType; // 1 - bst, 2 - rbt, 3 - hmap, -1 - wrong type
};
int insertCount, findCount, loadCount, minCount, maxCount, successorCount, deleteCount, inorderCount, maxSize;
Settings setSettings(string sett[], int i);
void runTest(DataStructure* T, int n);

int main(int argc, char *argv[]) {
    insertCount = findCount = loadCount = minCount = maxCount = successorCount = deleteCount = inorderCount = maxSize = 0;
    int n;
    BinarySearchTree *BST;
    RedBlackTree *RBT;
    HashMap *HaT;
    LinkedList *List;
    string sett[argc-1];
    for(int i = 1, j=0; i<argc; i++, j++){
        sett[j] = argv[i];
    }
    Settings settings = setSettings(sett, argc - 1);
    switch ( settings.stuctureType )
    {
        case 1:
            cin >> n;
            BST = new BinarySearchTree();
            runTest(BST, n);
            break;
        case 2:
            cin >> n;
            RBT = new RedBlackTree();
            runTest(RBT, n);
            break;
        case 3:
            cin >> n;
            HaT = new HashMap();
            runTest(HaT, n);
            break;
        case 4:
            cin >> n;
            List = new LinkedList();
            runTest(List, n);
            break;
        default:
            cout << "Zły typ danych! " << endl;
    }
    return 0;
}

Settings setSettings(string sett[], int size) {
    Settings settings;

    for (int i = 0; i < size; i++) {
        if (sett[i] == "--type" && i + 1 < size) {
            if (sett[i + 1] == "bst") {
                settings.stuctureType = 1;
            } else if (sett[i + 1] == "rbt") {
                settings.stuctureType = 2;
            } else if (sett[i + 1] == "hmap") {
                settings.stuctureType = 3;
            } else if (sett[i + 1] == "list") {
                settings.stuctureType = 4;
            } else {
                settings.stuctureType = -1;
                cout << "Nie podano właściwego formatu w jak sortować.";
            }
        }
    }
    return settings;
}

void runTest(DataStructure* T, int n){
    cin.ignore();
    std::string command;
    clock_t start_t, end_t;
    double timeSec;
    start_t = clock();
    for(int i = 0; i < n; i++){
        getline(std::cin, command);
        if(command[0] == 'i'){
            if(command[2] == 's'){
                command = command.erase(0,7);
                T->insert(command);
                insertCount++;
            } else if(command[2] == 'o'){
                T->inorder();
                inorderCount++;
            } else {
                std::cout<<"Nie ma takiej komendy zaczynającej się na i."<<std::endl;
            }
        } else if(command[0] == 'l'){
            command = command.erase(0,5);
            insertCount+=T->load(command);
            loadCount++;
        } else if(command[0] == 'd'){
            command = command.erase(0,7);
            T->del(command);
            deleteCount++;
        } else if(command[0] == 'f'){
            command = command.erase(0,5);
            T->find(command);
            findCount++;
        } else if(command[0] == 's'){
            command = command.erase(0,10);
            T->successor(command);
            successorCount++;
        } else if(command[0] == 'm'){
            if(command[2] == 'x'){
                T->max();
                maxCount++;
            } else if(command[2] == 'n'){
                T->min();
                minCount++;
            } else {
                std::cout<<"Nie ma takiej komendy zaczynającej się na m."<<std::endl;
            }
        } else{
            std::cout<<"Nie ma takiej komendy."<<std::endl;
        }
        maxSize = max(maxSize,T->getSize());
    }
    //T->pprint();
    end_t = clock();
    timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    std::cerr << "Czas: " << timeSec << " | Insert: " << insertCount << " | Find: " << findCount << " | Fnorder: " << inorderCount << " | Load: " << loadCount
                << " | Delete: " << deleteCount << " | Max: " << maxCount << " | Min: " << minCount << " | Succesor: " << successorCount << " | MaxSize: " << maxSize
                << " | Size: " <<T->getSize() << std::endl;

}