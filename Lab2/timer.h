#include "systemc.h"
#include <string>
#include <iostream>
using namespace std;

SC_MODULE(timer){
    sc_in  <bool> start;
    sc_out <bool> timeout;
    sc_in  <bool> clock;

    sc_signal <unsigned int > counter;
    void runtimer();
    void trace(sc_trace_file* );
    
    timer(sc_module_name name_, unsigned int counter_i):
        sc_module(name_), counterInit(counter_i), moduleName(name_){
            SC_HAS_PROCESS(timer);
            SC_CTHREAD(runtimer, clock.pos());
            reset_signal_is(start, true);
    }

    private:
        const unsigned int counterInit;
        string moduleName;


};