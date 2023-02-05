#pragma once
#include "chain.h"
#include <stdio.h>

typedef bool (*TEST)();

class Testing:public Link<Testing> {
    TEST m_test;
    const char* m_name;
    public:
        Testing(const char* testname,TEST test) {
            m_test = test;
            m_name = testname;
            Chain();
        }

        virtual void Resolve() {
            bool is_success = m_test();
            if (!is_success) {
                printf("%s fail!\n", m_name);
                return;
            }
            printf("%s OK\n", m_name);
        }
};
#define REGISTER_TEST(testname) Testing test##testname(" "#testname" ",testname)

