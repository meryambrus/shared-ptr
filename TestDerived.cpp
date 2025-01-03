//
// Created by Ambrus on 2024. 10. 31..
//

#include "TestDerived.h"

TestDerived::TestDerived() {
    //std::cout << "TestDerived Constructor" << std::endl;
}

TestDerived::TestDerived(const TestDerived &rhs) : TestBase(rhs) {
    //std::cout << "TestDerived Copy Constructor" << std::endl;
}

TestDerived & TestDerived::operator=(const TestDerived &rhs) {
    //std::cout << "TestDerived Copy Assignment operator" << std::endl;
    return *this;
}

TestDerived::TestDerived(TestDerived &&rhs) noexcept {
    //std::cout << "TestDerived Move Constructor" << std::endl;
}

TestDerived & TestDerived::operator=(TestDerived &&rhs) noexcept {
    //std::cout << "TestDerived Move Assignment operator" << std::endl;
    return *this;
}

TestDerived::~TestDerived() {
    //std::cout << "TestDerived Destructor" << std::endl;
}

std::string TestDerived::toString() {
    return "TestDerived";
}

std::string TestDerived::toString() const {
    return "Const TestDerived";
}
