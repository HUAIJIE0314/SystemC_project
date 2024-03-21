// HalfAdder.cpp

#include "HalfAdder.h"

void HalfAdder::HalfAdder_Func(void){
  Sum   = ( (A.read() ^ B.read()) );
  Carry = ( (A.read() & B.read()) );
}

void HalfAdder::trace(sc_trace_file* tf){
    sc_trace(tf, A,         "Half_adder_A");
    sc_trace(tf, B,         "Half_adder_B");
    sc_trace(tf, Sum,     "Half_adder_Sum");
    sc_trace(tf, Carry, "Half_adder_Carry");
}