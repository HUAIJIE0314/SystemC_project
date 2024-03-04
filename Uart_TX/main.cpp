// main.cpp
#include "systemc.h"
#include <time.h>
// include the testbench & design
#include "testbench.h"
#include "UART_TX.h"

SC_MODULE( SYSTEM ){
    // instantiate the module
    UART_TX*          UART_TX_0;
    testbench*      testbench_0; 

    //===============================================================

    // declare the system clock
    sc_clock clk;

    // declare the connection wire
    sc_signal  <bool>         rst_n;
    sc_signal  <bool>        enable;
    sc_signal  <sc_uint<8> > data_i;
    sc_signal  <bool>      uart_txd;

    SC_CTOR( SYSTEM ):clk("clk", 10, SC_NS){

        UART_TX_0 = new UART_TX("UART_TX_0");
        UART_TX_0->clk(clk);
        UART_TX_0->rst_n(rst_n);
        UART_TX_0->enable(enable);
        UART_TX_0->data_i(data_i);
        UART_TX_0->uart_txd(uart_txd);

        testbench_0 = new testbench("testbench_0");
        testbench_0->clk(clk);
        testbench_0->rst_n(rst_n);
        testbench_0->enable(enable);
        testbench_0->data_i(data_i);
        testbench_0->uart_txd(uart_txd);

    }

    //De-Constructor
    ~SYSTEM(){
        delete UART_TX_0;
        delete testbench_0;
    }

};



int sc_main( int argc, char* argv[] ){
    SYSTEM* Top = new SYSTEM("Top");

    sc_trace_file* tf = sc_create_vcd_trace_file("RESULT");// generate the RESULT.vcd
    
    sc_start(SC_ZERO_TIME);
    sc_trace(tf, Top->clk,                   "clk");
    sc_trace(tf, Top->rst_n,               "rst_n");
    sc_trace(tf, Top->enable,             "enable");
    sc_trace(tf, Top->data_i,             "data_i");
    sc_trace(tf, Top->uart_txd,         "uart_txd");
    sc_trace(tf, Top->UART_TX_0->fstate,  "fstate");
    sc_trace(tf, Top->UART_TX_0->BaudCnt,"BaudCnt");

    sc_start();
    //sc_start(300, SC_NS);
    //sc_stop();

    sc_close_vcd_trace_file(tf);

    return 0;
}




