// main.cpp
#include "systemc.h"

// include the testbench & design
//#include "testbench.h"
#include "timer.h"


SC_MODULE(testbench){
  sc_in  <bool>   clock;
  sc_out <bool>   start;
  sc_in  <bool> timeout;

  //output to timer module
  void source();

  testbench(sc_module_name name_, unsigned int threshold_i):
        sc_module(name_), threshold(threshold_i){
            SC_HAS_PROCESS(testbench);
            SC_CTHREAD(source, clock.pos());
    }

    private:
        const unsigned int threshold;

};

void testbench::source(){
  // Reset
  start = 1;
  wait(3);
  start = 0;
  // test pattern
  for(int times=0;times<2;times++){
    wait(threshold+times);// during counting reset the timer "before" count reaches 0
    start = 1;
    wait(1);
    start = 0;
  }

  for(int times=0;times<3;times++){
    wait(threshold+2+times);// during counting reset the timer "after" count reaches 0
    start = 1;
    wait(1);
    start = 0;
  }

}

SC_MODULE( SYSTEM ){
    // instantiate the module
    timer*          timer0;
    testbench*  testbench0;

    timer*          timer1;
    testbench*  testbench1; 

    timer*          timer2;
    testbench*  testbench2; 

    //===============================================================

    // declare the system clock
    sc_clock clock;

    // declare the connection wire
    sc_signal <bool>   start0;
    sc_signal <bool> timeout0;
    sc_signal <bool>   start1;
    sc_signal <bool> timeout1;
    sc_signal <bool>   start2;
    sc_signal <bool> timeout2;

    SC_CTOR( SYSTEM ):clock("clock", 10, SC_NS){

        // ============== timer0 & testbench0 ==============
        timer0 = new timer("timer0", 5);
        timer0->start(start0);
        timer0->timeout(timeout0);
        timer0->clock(clock);

        testbench0 = new testbench("testbench0", 5);
        testbench0->start(start0);
        testbench0->timeout(timeout0);
        testbench0->clock(clock);

        // ============== timer1 & testbench1 ==============
        timer1 = new timer("timer1", 2);
        timer1->start(start1);
        timer1->timeout(timeout1);
        timer1->clock(clock);

        testbench1 = new testbench("testbench1", 2);
        testbench1->start(start1);
        testbench1->timeout(timeout1);
        testbench1->clock(clock);

        // ============== timer2 & testbench2 ==============
        timer2 = new timer("timer2", 7);
        timer2->start(start2);
        timer2->timeout(timeout2);
        timer2->clock(clock);

        testbench2 = new testbench("testbench2", 7);
        testbench2->start(start2);
        testbench2->timeout(timeout2);
        testbench2->clock(clock);
    }

    //De-Constructor
    ~SYSTEM(){
        delete timer0;
        delete testbench0;

        delete timer1;
        delete testbench1;

        delete timer2;
        delete testbench2;
    }

};



int sc_main( int argc, char* argv[] ){
    SYSTEM* Top = new SYSTEM("Top");

    sc_trace_file* tf = sc_create_vcd_trace_file("RESULT");// generate the RESULT.vcd
    
    sc_start(SC_ZERO_TIME);
    
    Top->timer0->trace(tf);
    Top->timer1->trace(tf);
    Top->timer2->trace(tf);

    sc_start(300, SC_NS);
    sc_stop();

    sc_close_vcd_trace_file(tf);

    return 0;
}




