#ifndef TB_FULLADDER_H
#define TB_FULLADDER_H

#include "systemc.h"

SC_MODULE(tb_FullAdder){

    sc_out <bool> A;
    sc_out <bool> B;
    sc_out <bool> Cin;
    sc_in  <bool> S;
    sc_in  <bool> Cout;     

    void source(void);

    unsigned int i, j, k, correctNum;
    sc_uint<2> Golden[8] = {sc_uint<2>(0), 
                            sc_uint<2>(1), 
                            sc_uint<2>(1), 
                            sc_uint<2>(2),
                            sc_uint<2>(1), 
                            sc_uint<2>(2), 
                            sc_uint<2>(2), 
                            sc_uint<2>(3)
                            };
    
    SC_CTOR(tb_FullAdder){
        SC_THREAD(source);

        i = 0;
        j = 0;
        k = 0;
        correctNum = 0;
        
    }

};

#endif // TB_FULLADDER_H