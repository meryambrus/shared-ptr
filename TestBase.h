//
// Created by Ambrus on 2024. 10. 31..
//

#ifndef TESTBASE_H
#define TESTBASE_H

#include <iostream>

#include "RefCounted.h"

class TestBase : public RefCounted {
private:
    int refCount = 0;
    friend class Tester;
public:
    TestBase();
    TestBase(const TestBase& rhs);
    TestBase& operator=(const TestBase& rhs);
    TestBase(TestBase&& other) noexcept ;
    TestBase& operator=(TestBase&& rhs) noexcept;
    virtual ~TestBase();
private:
    virtual std::string toString();
    virtual std::string toString() const;
};



#endif //TESTBASE_H
