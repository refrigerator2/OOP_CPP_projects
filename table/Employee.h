#include <iostream>
#include <string>

class Employee {
public:
    std::string fullname;
    std::string position;
    unsigned int age;

    Employee(const std::string &f = "", const std::string &p = "", unsigned int a = 0)
        : fullname(f), position(p), age(a) {}

    
};
std::ostream& operator<<(std::ostream& o, const Employee& e) {
        o << "fullname: " << e.fullname 
          << " position: " << e.position 
          << " age: " << e.age << std::endl;
        return o;
    }
