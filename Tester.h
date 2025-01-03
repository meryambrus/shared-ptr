//
// Created by Ambrus on 2024. 11. 07..
//

#ifndef TESTER_H
#define TESTER_H

#include "TestBase.h"
#include "TestDerived.h"
#include "TestVariadic.h"

class Tester {
private:
    bool testSharedPtrDefaultConstructor();
    bool testSharedPtrConstructor();
    bool testSharedPtrCopyConstructor();
    bool testSharedPtrCopyAssignmentOperator();
    bool testSharedPtrSelfAssignment();
    bool testSharedPtrMoveConstructor();
    bool testSharedPtrMoveAssignmentOperator();
    bool testSharedPtrUpcastingCopyConstructor();
    bool testSharedPtrUpcastingAssignmentOperator();
    bool testSharedPtrUpcastingMoveConstructor();
    bool testSharedPtrUpcastingMoveAssignmentOperator();
    bool testSharedPtrReferenceCounting();

    bool testSharedPtrWithConstType();

    bool testRefCountedCopyConstructor();

    bool testMakeRefCountedMultipleArguments();
    bool testMakeRefCountedWithPointer();

public:
    void runTests();
};



#endif //TESTER_H
