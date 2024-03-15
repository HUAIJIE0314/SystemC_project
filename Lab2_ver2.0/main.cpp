// main.cpp
#include "systemc.h"

// include the design
#include "timer.h"
#define timerNum 3

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
    timer*          timer_arr[timerNum];
    testbench*  testbench_arr[timerNum];

    unsigned int count_init_arr[timerNum] = {5, 2, 7};
    //===============================================================

    // declare the system clock
    sc_clock clock;

    // declare the connection wire
    sc_signal <bool>   start[timerNum];
    sc_signal <bool> timeout[timerNum];

    SC_CTOR( SYSTEM ):clock("clock", 10, SC_NS){
        for(int idx=0;idx<timerNum;idx++){
            timer_arr[idx] = new timer( ((string)"timer" + char(idx+0x30)).c_str(), count_init_arr[idx] );
            timer_arr[idx]->start(start[idx]);
            timer_arr[idx]->timeout(timeout[idx]);
            timer_arr[idx]->clock(clock);

            testbench_arr[idx] = new testbench( ((string)"testbench" + char(idx+0x30)).c_str(), count_init_arr[idx] );
            testbench_arr[idx]->start(start[idx]);
            testbench_arr[idx]->timeout(timeout[idx]);
            testbench_arr[idx]->clock(clock);
        }
    }

    //De-Constructor
    ~SYSTEM(){
        for(unsigned int idx=0;idx<timerNum;idx++){
            delete timer_arr[idx];
            delete testbench_arr[idx];
        }
    }

};


int sc_main( int argc, char* argv[] ){
    SYSTEM* Top = new SYSTEM("Top");

    sc_trace_file* tf = sc_create_vcd_trace_file("RESULT");// generate the RESULT.vcd
    
    sc_start(SC_ZERO_TIME);
    
    //trace signal
    for(int idx=0;idx<timerNum;idx++)Top->timer_arr[idx]->trace(tf);
    
    sc_start(300, SC_NS);
    sc_stop();

    sc_close_vcd_trace_file(tf);

    return 0;
}




