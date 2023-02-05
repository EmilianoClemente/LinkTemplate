#include <stdio.h>
#include "testing.h"

int main(){
    Testing::ResolveChain();
	return 0;
}


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
        return false;
    }

    /* also check if the work of b chain remain untouched */
    if(workB != 0){
        return false;
    }

    /* and check the reverse case */
    workA = 0;
    ChainB::ResolveChain();
    
    if(workB != 4) {
        return false;
    }

    if(workA != 0){
        return false;
    }

    return true;
}
REGISTER_TEST(testSeperate);

bool testSubClass(){
    /* only define a chain.the implementation of resolve is in the subclass */
    class RealChain:public Link<RealChain>{};

    class SubA:public RealChain{
    private:
        int* m_work;
    public:
        SubA(int* work){m_work = work;}
        virtual void Resolve(){
            (*m_work)++;
        }
    };

    class SubB:public RealChain{
    private:
        int* m_work;
    public:
        SubB(int* work){m_work = work;}
        virtual void Resolve(){
            (*m_work)++;
        }
    };

    int workA = 0;
    int workB = 0;

    /* make some links here */
    SubA A_a(&workA),A_b(&workA),A_c(&workA),A_d(&workA);
    SubB B_a(&workB),B_b(&workB),B_c(&workB),B_d(&workB);

    /* chain them */
    A_a.Chain(); A_b.Chain(); A_c.Chain(); A_d.Chain();
    RealChain::ResolveChain();
    if(4 != workA){
        return false;
    }

    if(0 != workB){
        return false;
    }

    B_a.Chain(); B_b.Chain(); B_c.Chain(); B_d.Chain();
    RealChain::ResolveChain();
    if(4 != workB){
        return false;
    }

    if(4 != workA){
        return false;
    }

    A_a.Chain(); A_b.Chain(); A_c.Chain(); A_d.Chain();
    B_a.Chain(); B_b.Chain(); B_c.Chain(); B_d.Chain();
    RealChain::ResolveChain();
    if(8 != workB){
        return false;
    }
    if(8 != workA){
        return false;
    }

    return true;
}
REGISTER_TEST(testSubClass);
