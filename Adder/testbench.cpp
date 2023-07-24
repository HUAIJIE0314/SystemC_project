// hello.cpp

#include "Adder.h"

// sc_main in top level function like in C++ main
int sc_main(int argc, char *argv[]){
  // instantiate
  Adder Adder1("Adder1");
  // declarate signal

  sc_signal < sc_int<32> > input1;
  sc_signal < sc_int<32> > input2;
  sc_signal < sc_int<32> > F;     

  // connect signal
  Adder1.input1(input1);
  Adder1.input2(input2);
  Adder1.F(F);

  // ========================== testbench ==========================
  //sc_initialize();

  sc_start(SC_ZERO_TIME);

  sc_trace_file *tf = sc_create_vcd_trace_file("trace");// generate vcd file

  sc_trace(tf, input1, "input1");
  sc_trace(tf, input2, "input2");
  sc_trace(tf, F, "F");
  
  for(int i=0;i<100;i++){
    for(int j=0;j<100;j++){
      input1 = i;
      input2 = j;
      sc_start(20, SC_NS);
    }
  }

  sc_close_vcd_trace_file(tf);

  return (0);
}


