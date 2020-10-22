#include "Structures.h"
int main() {
    int n,x,p,index;
    std::string command;
    Queue* q = new Queue();
    std::cin>>n;
    std::cin.ignore();

    for(int i = 0; i < n; i++){
        getline(std::cin, command);
        if(command[0] == 'i'){ // insert x p
            command = command.erase(0,7);
            index = command.find(" ");
            x=std::stoi(command.substr(0,index));
            p=std::stoi(command.substr(index+1,command.size()-index-1));
            q->insert(x,p);
        } else if(command[0] == 'e'){ //empty
            q->empty();
        } else if(command[0] == 't'){ //top
            q->top();
        } else if(command[0] == 'p'){ //na p
            if(command[1] == 'o'){//pop
                q->pop();
            } else if(command[3] == 'o'){ //priority x p
                command = command.erase(0,9);
                index = command.find(" ");
                x=std::stoi(command.substr(0,index));
                p=std::stoi(command.substr(index+1,command.size()-index-1));
                q->priority(x,p);
            }else if(command[3] == 'n'){ //print
                q->print();
            } else {
                std::cout<<"Nie ma takiej komendy zaczynającej się na p."<<std::endl;
            }
        } else{
            std::cout<<"Nie ma takiej komendy."<<std::endl;
        }
    }
    return 0;
}
