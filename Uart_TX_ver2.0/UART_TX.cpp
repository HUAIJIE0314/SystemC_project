// UART_TX.cpp
#include "UART_TX.h"

void UART_TX::transmitter() {
    // Reset
    uart_txd = 1;
    wait();
    // UART_TX Func
    while(1){
        switch(fstate.read()){
            case IDLE:
                uart_txd = 1;
                if(enable.read() == 1){
                    fstate = START;
                    dataTmp = data_i.read();
                }
                else{
                    fstate = IDLE;
                    dataTmp = 0;
                }
                break;

            case START:
                uart_txd = 0;
                if(BaudCnt.read() == 10416)
                    fstate = SHIFT;
                else
                    fstate = START;
                break;

            case SHIFT:
                uart_txd = dataTmp.read() & 0x01;
                if(BaudCnt.read() == 10416 && counter.read() == 7)
                    fstate = FINISH;
                else
                    fstate = SHIFT;
                break;

            case FINISH:
                uart_txd = 1;
                if(BaudCnt.read() == 10416){
                    fstate = IDLE;
                }
                else{
                    fstate = FINISH;
                }
                break;

            default:
                break;
        }

        // baudCnt
        if(fstate.read() >= START){
            if(BaudCnt.read() < 10416)
                BaudCnt = BaudCnt.read() + 1;
            else
                BaudCnt = 0;
        }

        if(fstate.read() == SHIFT && BaudCnt.read() == 10416){
            counter = counter.read() + 1;
            dataTmp = (dataTmp.read() >> 1);
        }

        wait();
    }

}


void UART_TX::trace(sc_trace_file* tf){
    sc_trace(tf,      clk, "     clk");
    sc_trace(tf,    rst_n, "   rst_n");
    sc_trace(tf,   enable, "  enable");
    sc_trace(tf,   data_i, "  data_i");
    sc_trace(tf, uart_txd, "uart_txd");
    sc_trace(tf,  BaudCnt, " BaudCnt");
    sc_trace(tf,   fstate, "  fstate");
    sc_trace(tf,  counter, " counter");
    sc_trace(tf,  dataTmp, " dataTmp");
}