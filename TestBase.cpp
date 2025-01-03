//
// Created by Ambrus on 2024. 10. 31..
//

#include "TestBase.h"

TestBase::TestBase() {
    //std::cout << "TestBase Constructor" << std::endl;
}

TestBase::TestBase(const TestBase &rhs) : RefCounted(rhs) {
    //std::cout << "TestBase Copy Constructor" << std::endl;
}

TestBase& TestBase::operator=(const TestBase &rhs) {
    //std::cout << "TestBase Copy Assignment operator" << std::endl;
    return *this;
}

TestBase::TestBase(TestBase &&rhs) noexcept {
    //std::cout << "TestBase Move Constructor" << std::endl;
}

TestBase& TestBase::operator=(TestBase &&rhs) noexcept {
    //std::cout << "TestBase Move Assignment operator" << std::endl;
    return *this;
}

TestBase::~TestBase() {
    //std::cout << "TestBase Destructor" << std::endl;
}

std::string TestBase::toString() {
    return "TestBase";
}

std::string TestBase::toString() const {
    return "Const TestBase";
}
