// timer.cpp
#include "timer.h"

void timer::runtimer() {
    counter = counterInit;
    timeout = 0;
    while(1){
        wait();
        if(counter.read() == 0){
            timeout = 1;
        }
        else {
            counter = counter.read() - 1;
            timeout = 0;
        }
    }

}

void timer::trace(sc_trace_file* tf){
    sc_trace(tf, clock,   moduleName + "_clock");
    sc_trace(tf, start,   moduleName + "_start");
    sc_trace(tf, timeout, moduleName + "_timeout");
    sc_trace(tf, counter, moduleName + "_counter");
}