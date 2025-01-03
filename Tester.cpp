//
// Created by Ambrus on 2024. 11. 07..
//

#include "Tester.h"

#include <memory>

bool Tester::testSharedPtrDefaultConstructor() {
    SharedPtr<TestBase> sharedPtr;
    return sharedPtr.ptr == nullptr;
}

bool Tester::testSharedPtrConstructor() {
    auto sharedPtr = make_refcounted<TestBase>();

    return !(sharedPtr.ptr == nullptr) && sharedPtr.ptr->RefCounted::refCount == 1;
}

bool Tester::testSharedPtrCopyConstructor() {
    auto sharedPtr1 = make_refcounted<TestBase>();
    auto sharedPtr2 = SharedPtr<TestBase>(sharedPtr1);

    return sharedPtr1.ptr == sharedPtr2.ptr &&
        sharedPtr1.ptr->RefCounted::refCount == 2;
}

bool Tester::testSharedPtrCopyAssignmentOperator() {
    auto sharedPtr1 = make_refcounted<TestBase>();
    auto sharedPtr2 = sharedPtr1;

    return  sharedPtr1.ptr == sharedPtr2.ptr &&
            sharedPtr1.ptr->RefCounted::refCount == 2;
}

bool Tester::testSharedPtrSelfAssignment() {
    auto sharedPtr = make_refcounted<TestBase>();
    sharedPtr = sharedPtr;

    return sharedPtr.ptr->RefCounted::refCount == 1;
}

bool Tester::testSharedPtrMoveConstructor() {
    auto sharedPtr1 = make_refcounted<TestBase>();
    auto sharedPtr2 = SharedPtr<TestBase>(std::move(sharedPtr1));

    return  sharedPtr1.ptr == nullptr &&
            sharedPtr2.ptr != nullptr &&
            sharedPtr2.ptr->RefCounted::refCount == 1;
}

bool Tester::testSharedPtrMoveAssignmentOperator() {
    auto sharedPtr1 = make_refcounted<TestBase>();
    auto sharedPtr2 = make_refcounted<TestBase>();
    sharedPtr2 = std::move(sharedPtr1);

    return  sharedPtr1.ptr == nullptr &&
            sharedPtr2.ptr != nullptr &&
            sharedPtr2.ptr->RefCounted::refCount == 1;
}

bool Tester::testSharedPtrUpcastingCopyConstructor() {
    auto sharedPtrDerived = make_refcounted<TestDerived>();
    SharedPtr<TestBase> sharedPtrBase = SharedPtr<TestBase>(sharedPtrDerived);

    return sharedPtrBase->toString() == "TestDerived";
}

bool Tester::testSharedPtrUpcastingAssignmentOperator() {
    auto sharedPtrDerived = make_refcounted<TestDerived>();
    SharedPtr<TestBase> sharedPtrBase = sharedPtrDerived;

    return sharedPtrBase->toString() == "TestDerived";
}

bool Tester::testSharedPtrUpcastingMoveConstructor() {
    auto sharedPtrDerived = make_refcounted<TestDerived>();
    auto sharedPtrBase = SharedPtr<TestBase>(std::move(sharedPtrDerived));

    return sharedPtrBase->toString() == "TestDerived";
}

bool Tester::testSharedPtrUpcastingMoveAssignmentOperator() {
    auto sharedPtrDerived = make_refcounted<TestDerived>();
    auto sharedPtrBase = make_refcounted<TestBase>();

    sharedPtrBase = std::move(sharedPtrDerived);

    return sharedPtrBase->toString() == "TestDerived";
}

bool Tester::testSharedPtrReferenceCounting() {
    auto* sharedPtr1 = new SharedPtr<TestBase>(new TestBase());
    auto* sharedPtr2 = new SharedPtr<TestBase>(*sharedPtr1);

    if (sharedPtr2->ptr->RefCounted::refCount != 2) {
        return false;
    }

    auto sharedPtr3 = *sharedPtr2;
    if (sharedPtr3.ptr->RefCounted::refCount != 3) {
        return false;
    }

    delete sharedPtr1;
    if (sharedPtr3.ptr->RefCounted::refCount != 2) {
        return false;
    }

    auto sharedPtr4 = SharedPtr<TestBase>(std::move(*sharedPtr2));
    if (sharedPtr4.ptr->RefCounted::refCount != 2) {
        return false;
    }

    delete sharedPtr2;
    if (sharedPtr4.ptr->RefCounted::refCount != 2) {
        return false;
    }

    sharedPtr3 = make_refcounted<TestBase>();
    if (sharedPtr4.ptr->RefCounted::refCount != 1) {
        return false;
    }

    return true;
}

bool Tester::testSharedPtrWithConstType() {
    auto sharedPtr = SharedPtr<const TestBase>(new const TestBase());

    return sharedPtr->toString() == "Const TestBase";
}

bool Tester::testRefCountedCopyConstructor() {
    auto sharedPtr1 = make_refcounted<TestBase>();
    auto sharedPtr2 = sharedPtr1;

    auto sharedPtr3 = make_refcounted<TestBase>(*sharedPtr1);
    return sharedPtr3.ptr->RefCounted::refCount == 1;
}

bool Tester::testMakeRefCountedMultipleArguments() {
    auto sharedPtr1 = make_refcounted<TestVariadic>("a");

    auto sharedPtr2 = make_refcounted<TestVariadic>("a", "b");

    auto sharedPtr3 = make_refcounted<TestVariadic>("a", "b", "c");

    return  sharedPtr1->strings.size() == 1 &&
            sharedPtr2->strings.size() == 2 &&
            sharedPtr3->strings.size() == 3;
}

bool Tester::testMakeRefCountedWithPointer() {
    auto sharedPtr = make_refcounted<TestVariadic>(new TestVariadic("a", "b"));

    return sharedPtr->RefCounted::refCount == 1 && sharedPtr->strings.size() == 2;
}

void Tester::runTests() {
    unsigned int numTests = 0;
    unsigned int testsPassed = 0;

    numTests++;
    if (testSharedPtrConstructor()) {
        std::cout << "SharedPtrConstructor Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrCopyConstructor()) {
        std::cout << "SharedPtrCopyConstructor Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrCopyAssignmentOperator()) {
        std::cout << "SharedPtrCopyAssignmentOperator Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrSelfAssignment()) {
        std::cout << "SharedPtrSelfAssignment Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrMoveConstructor()) {
        std::cout << "SharedPtrMoveConstructor Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrMoveAssignmentOperator()) {
        std::cout << "SharedPtrMoveAssignmentOperator Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrUpcastingCopyConstructor()) {
        std::cout << "SharedPtrUpcastingCopyConstructor Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrUpcastingAssignmentOperator()) {
        std::cout << "SharedPtrUpcastingAssignmentOperator Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrUpcastingMoveConstructor()) {
        std::cout << "SharedPtrUpcastingMoveConstructor Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrReferenceCounting()) {
        std::cout << "SharedPtrReferenceCounting Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testSharedPtrWithConstType()) {
        std::cout << "SharedPtrWithConstType Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testRefCountedCopyConstructor()) {
        std::cout << "RefCountedCopyConstructor Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testMakeRefCountedMultipleArguments()) {
        std::cout << "MakeRefCountedMultipleArguments Passed" << std::endl;
        testsPassed++;
    }
    numTests++;
    if (testMakeRefCountedWithPointer()) {
        std::cout << "MakeRefCountedWithPointer Passed" << std::endl;
        testsPassed++;
    }
    std::cout << testsPassed << "/" << numTests << " tests passed" << std::endl;
}



































