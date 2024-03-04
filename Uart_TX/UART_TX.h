#include "systemc.h"

SC_MODULE(UART_TX){
    sc_in  <bool>           clk;
    sc_in  <bool>         rst_n;
    sc_in  <bool>        enable;
    sc_in  <sc_uint<8> > data_i;
    sc_out <bool>      uart_txd;

    sc_signal<sc_uint<14> > BaudCnt;
    sc_signal<sc_uint<2> >   fstate;
    sc_signal<sc_uint<3> >  counter;
    sc_signal<sc_uint<8> >  dataTmp;
    
    enum state{
        IDLE,
        START,
        SHIFT,
        FINISH
    };

    void transmitter();

    SC_CTOR(UART_TX){
        SC_CTHREAD(transmitter, clk.pos());
        reset_signal_is(rst_n, false);
        
        // initial state
        BaudCnt = 0;
        counter = 0;
        dataTmp = 0;
        fstate = IDLE;
    }

};