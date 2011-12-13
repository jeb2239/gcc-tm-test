#ifndef LISTINSERTTEST_H
#define LISTINSERTTEST_H

#include "Test.h"
#include <Utils/LinkedList.h>

class ListInsertTest: public NumbersTest {
public:
    typedef Utils::LinkedList<int> MyList;

    virtual void setup() {
        m_sharedList.clear();
    }

    virtual void teardown() {
        m_sharedList.clear();
    }

    virtual bool check() {
        std::vector<int> inputSorted(m_input);
        std::vector<int> resultSorted;
        resultSorted.reserve(inputSorted.size());

        for(MyList::Iterator it = m_sharedList.begin(); it != m_sharedList.end(); it++) {
            resultSorted.push_back(it.value());
        }

        if (resultSorted.size() != inputSorted.size()) {
            return false;
        }

        std::sort(inputSorted.begin(), inputSorted.end());
        std::sort(resultSorted.begin(), resultSorted.end());

        for (size_t i = 0; i < inputSorted.size(); i++) {
            const int srcValue = inputSorted[i];
            const int listValue = resultSorted[i];

            if (srcValue != listValue) {
                return false;
            }
        }

        return true;
    }

protected:
    virtual void workerSequential(size_t start, size_t end) {
        for(size_t i = start; i < end; i++) {
            m_sharedList.pushFront(m_input[i]);
        }
    }

    virtual void workerThreaded(size_t start, size_t end) {
        for(size_t i = start; i < end; i++) {
            __transaction_atomic {
                m_sharedList.pushFront(m_input[i]);
            }
        }
    }

    MyList m_sharedList;
};


#endif // LISTINSERTTEST_H
