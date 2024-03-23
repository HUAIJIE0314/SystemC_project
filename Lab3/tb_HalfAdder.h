#ifndef TB_HALFADDER_H
#define TB_HALFADDER_H

#include "systemc.h"

SC_MODULE(tb_HalfAdder){

    sc_out <bool> A;
    sc_out <bool> B;
    sc_in  <bool> Sum;
    sc_in  <bool> Carry;     

    void source(void);

    unsigned int i, j, correctNum;
    sc_uint<2> Golden[4] = {sc_uint<2>(0), sc_uint<2>(1), sc_uint<2>(1), sc_uint<2>(2)};
    
    SC_CTOR(tb_HalfAdder){
        SC_THREAD(source);

        i = 0;
        j = 0;
        correctNum = 0;
        
    }

};

#endif // TB_HALFADDER_H