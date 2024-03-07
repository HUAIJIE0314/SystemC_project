// timer.cpp
#include "timer.h"

void timer::runtimer() {
    
    while(1){
        if( start.read() ){
            cout << "Timer: timer start detected " << endl;
            count = 5;
            timeout.write(0);
        }
        else{
            if(count == 0){
                timeout.write(1);
            }
            else {
                count --;
                timeout.write(0);
            }
        }
        wait();
    }

}

void timer::trace(sc_trace_file* tf){
    sc_trace(tf, clock,     "clock");
    sc_trace(tf, start,     "start");
    sc_trace(tf, timeout, "timeout");
    sc_trace(tf, count,     "count");
}