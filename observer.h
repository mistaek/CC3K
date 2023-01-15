#ifndef __observer_h__
#define __observer_h__

class Subject; 

class Observer{
    public:
        virtual void notify(Subject &whoFrom) = 0;
};

#endif

