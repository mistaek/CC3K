#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach(Observer *o){
    observers.emplace_back(o);
}

void Subject::detach(Observer *o){
    for(int i = 0; i < observers.size(); i++){
        if(observers[i] == o){
            observers.erase(observers.begin() +i); 
            break;
        }
    }
}

void Subject::notifyObservers(){
    for(auto it : observers){
        it->notify(*this);
    }
}
