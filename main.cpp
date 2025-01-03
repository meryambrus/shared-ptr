#include <iostream>

#include "RefCounted.h"
#include <string>

#include "TestBase.h"
#include "TestDerived.h"

#include <memory>

#include "Tester.h"

int main() {
    Tester tester;

    tester.runTests();
}
