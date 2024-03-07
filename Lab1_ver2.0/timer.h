#include "systemc.h"

SC_MODULE(timer){
    sc_in  <bool> start;
    sc_out <bool> timeout;
    sc_in  <bool> clock;

    int count;
    void runtimer();
    void trace(sc_trace_file* );
    
    SC_CTOR(timer){
        SC_THREAD(runtimer);
        sensitive << clock.pos()
                  << start;
        
        count = 0;
    }

};