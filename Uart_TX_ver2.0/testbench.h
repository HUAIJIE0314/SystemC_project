#include "systemc.h"
#include "time.h"

SC_MODULE(testbench){
    sc_in  <bool>             clk;
    sc_out <bool>           rst_n;
    sc_out <bool>          enable;
    sc_out <sc_uint<8> >   data_i;
    sc_in  <bool>        uart_txd;

    //output to timer module
    void source();
    void trace(sc_trace_file* );
    
    int rx_data;
    int tx_data;
    int correctNum;

    SC_CTOR(testbench){
        SC_THREAD( source );
        sensitive << clk.pos(); 
        //cycle = 0;
        rx_data = 0;
        tx_data = 0;
        correctNum = 0;
    }

};


