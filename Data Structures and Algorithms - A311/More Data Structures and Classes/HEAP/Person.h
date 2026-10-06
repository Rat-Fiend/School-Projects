#pragma once
#include <string>
#include <iostream>

using namespace std;

class Person {
private:
    string name;
    int age;

public:
    Person();
    Person(string n, int a);
    ~Person();
    void setName(string n);
    string getName();
    void setAge(int a);
    int getAge();

    friend bool operator< (Person const, Person const);
    friend bool operator> (Person const, Person const);
    friend bool operator== (Person const, Person const);
    friend ostream& operator<< (ostream& os, Person const t);
};