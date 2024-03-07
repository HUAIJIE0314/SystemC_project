// main.cpp
#include "systemc.h"

// include the testbench & design
#include "testbench.h"
#include "timer.h"

SC_MODULE( SYSTEM ){
    // instantiate the module
    timer*          timer_0;
    testbench*  testbench_0; 

    //===============================================================

    // declare the system clock
    sc_clock clock;

    // declare the connection wire
    sc_signal <bool> start;
    sc_signal <bool> timeout;

    SC_CTOR( SYSTEM ):clock("clock", 10, SC_NS){

        timer_0 = new timer("timer_0");
        timer_0->start(start);
        timer_0->timeout(timeout);
        timer_0->clock(clock);

        testbench_0 = new testbench("testbench_0");
        testbench_0->start(start);
        testbench_0->timeout(timeout);
        testbench_0->clock(clock);

    }

    //De-Constructor
    ~SYSTEM(){
        delete timer_0;
        delete testbench_0;
    }

};



int sc_main( int argc, char* argv[] ){
    SYSTEM* Top = new SYSTEM("Top");

    sc_trace_file* tf = sc_create_vcd_trace_file("RESULT");// generate the RESULT.vcd
    
    sc_start(SC_ZERO_TIME);
    
    Top->timer_0->trace(tf);

    sc_start(300, SC_NS);
    sc_stop();

    sc_close_vcd_trace_file(tf);

    return 0;
}




