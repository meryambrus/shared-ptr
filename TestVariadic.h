//
// Created by Ambrus on 2024. 11. 09..
//

#ifndef TESTVARIADIC_H
#define TESTVARIADIC_H

#include <cstdarg>

#include "RefCounted.h"
#include <vector>
#include <string>

class TestVariadic : public RefCounted {
private:
    friend class Tester;
    std::vector<std::string> strings;
public:
    TestVariadic(const std::string& str) {
        strings.push_back(str);
    }
    TestVariadic(const std::string& str1, const std::string& str2) {
        strings.push_back(str1);
        strings.push_back(str2);
    }
    TestVariadic(const std::string& str1, const std::string &str2, const std::string &str3) {
        strings.push_back(str1);
        strings.push_back(str2);
        strings.push_back(str3);
    }
};



#endif //TESTVARIADIC_H
