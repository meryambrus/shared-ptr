//
// Created by Ambrus on 2024. 10. 31..
//

#ifndef TESTDERIVED_H
#define TESTDERIVED_H

#include "TestBase.h"

#include <string>

class TestDerived final : public TestBase {
private:
    friend class Tester;
public:
    TestDerived();
    TestDerived(const TestDerived& other);
    TestDerived& operator=(const TestDerived& other);
    TestDerived(TestDerived&& other) noexcept;
    TestDerived& operator=(TestDerived&& other) noexcept;
    ~TestDerived() override;
private:
    std::string toString() override;
    std::string toString() const override;
};



#endif //TESTDERIVED_H
