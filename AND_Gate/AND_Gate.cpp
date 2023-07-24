// hello.cpp

#include "AND_Gate.h"

// sc_main in top level function like in C++ main
int sc_main(int argc, char *argv[]){
  // instantiate
  AND_Gate AND_Gate1("AND_Gate1");
  // declarate signal
  sc_signal <bool> a ,b, c;
  // connect signal
  AND_Gate1.input1(a);
  AND_Gate1.input2(b);
  AND_Gate1.F(c);

  // ========================== testbench ==========================
  //sc_initialize();

  sc_start(SC_ZERO_TIME);

  sc_trace_file *tf = sc_create_vcd_trace_file("trace");// generate vcd file

  sc_trace(tf, a, "a");
  sc_trace(tf, b, "b");
  sc_trace(tf, c, "c");

  a=0;b=0;

  for(int i=0;i<4;i++){
    b = ((i & 0x1) != 0);
    a = ((i & 0x2) != 0);
    sc_start(20, SC_NS);
  }

  sc_close_vcd_trace_file(tf);

  return (0);
}


