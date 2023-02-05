#include <stdio.h>
#include "chain.h"

typedef bool (*TEST)();
#define numof(array)   (sizeof(array)/sizeof(array[0]))

bool testSeperate(){
    int workA = 0;
    int workB = 0;
    /*
     * create two seperate chain, they handle seperate work.
     * and check if they are really seperated
     */
    class ChainA:public Link<ChainA>{
    private:
            int* m_work;
    public:
        ChainA(int *work){m_work = work;}
        virtual void Resolve(){
            (*m_work)++;
        }
    };

    class ChainB:public Link<ChainB>{
    private:
            int* m_work;
    public:
        ChainB(int *work){m_work = work;}
        virtual void Resolve(){
            (*m_work)++;
        }
    };

    /* make some links here */
    ChainA A_a(&workA),A_b(&workA),A_c(&workA),A_d(&workA);
    ChainB B_a(&workB),B_b(&workB),B_c(&workB),B_d(&workB);

    /* chain them */
    A_a.Chain(); A_b.Chain(); A_c.Chain(); A_d.Chain();
    B_a.Chain(); B_b.Chain(); B_c.Chain(); B_d.Chain();

    /* see if A chain has done its work */
    ChainA::ResolveChain();
    if(workA != 4) {
        printf("seperate test fail");
        return false;
    }

    /* also check if the work of b chain remain untouched */
    if(workB != 0){
        printf("seperate test fail");
        return false;
    }

    /* and check the reverse case */
    workA = 0;
    ChainB::ResolveChain();
    
    if(workB != 4) {
        printf("seperate test fail");
        return false;
    }

    if(workA != 0){
        printf("seperate test fail");
        return false;
    }

    printf("seperate test OK\n");
    return true;
}

int main(){
    TEST tests[] = {
        testSeperate,
    };
    for(int i=0; i<numof(tests); i++) {
        if(!(tests[i]())){
            return 1;
        }
    }
	return 0;
}
