// FullAdder.cpp

#include "FullAdder.h"

void FullAdder::xorFunc(void){
  Cout = ( (c1.read() | c2.read()) );
}

void FullAdder::trace(sc_trace_file* tf){
    sc_trace(tf, A,         "Full_adder_A");
    sc_trace(tf, B,         "Full_adder_B");
    sc_trace(tf, Cin,     "Full_adder_Cin");
    sc_trace(tf, S,         "Full_adder_S");
    sc_trace(tf, Cout,   "Full_adder_Cout");
}