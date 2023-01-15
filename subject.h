#ifndef __subject_h__
#define __subject_h__
#include <vector>

class Observer; 

class Subject{
    std::vector<Observer*> observers; 
    public:
        void attach(Observer *o);
        void detach(Observer *o);
        void notifyObservers();
        virtual std::pair<std::pair<int, int>, char> getInfo() = 0;

};
#endif
