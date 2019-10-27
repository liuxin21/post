// 要使用哈希表，必须要有对应的计算散列值的算法以及判断两个值（或对象）是否相等的方法。
// 在 Java 中，Object 类里有两个重要方法：hashCode 和 equals 方法。
// 其中 hashCode 方法便是为散列存储结构服务的，用来计算散列值；
// 而 equals 方法则是用来判断两对象是否等价。
// 由于所有的类都继承自 java.lang.Object 类，因此所有类相当于都拥有了这两个方法。

// 而在 C++ 中没有自动声明这类函数，STL 只为 C++ 常用类提供了散列函数，
// 因此如果想在 unordered_map 中使用自定义的类，
// 则必须为此类提供一个哈希函数和一个判断对象是否相等的函数（e.g. 重载 == 运算符）。

// hashCode 方法及 equals 方法的规范
// https://www.sczyh30.com/posts/Java/java-hashcode-equal/

#include <iostream>
#include <unordered_map>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;

class Person {
public:
    string phone;
    string name;
    string address;
    explicit Person() {}
    explicit Person(string name, string phone, string address): name(name), phone(phone), address(address) {}
    // overload operator==
    bool operator==(const Person& p) {
        return this->phone == p.phone && this->name == p.name
            && this->address == p.address;
    }
    inline friend std::ostream& operator<<(std::ostream& os, Person& p) {
        os << "[Person] -> (" << p.name << ", " << p.phone << ", "
           << p.address << ")";
        return os;
    }
};
// declare hash<Person>
namespace std {
 template <>
 struct hash<Person> {
     std::size_t operator()(const Person& p) const {
      using std::size_t;
      using std::hash;
      using std::string;
      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      return ((hash<string>()(p.phone)
        ^ (hash<string>()(p.name) << 1)) >> 1)
        ^ (hash<string>()(p.address) << 1);
     }
 };
}
unordered_map<string, Person> phoneMap;
void selectByPhone() {
    string phone;
    cout << "Input the phone number: "; cin >> phone;
    unordered_map<string, Person>::iterator it;
    int size = phoneMap.size();
    for(int pc = 0; pc < size; pc++) {
        if((it = phoneMap.find(phone)) != phoneMap.end()) {
            cout << "Query result: " << it->second << endl;
            return;
        }
    }
    cout << "Query result : target_not_found" << endl;
}