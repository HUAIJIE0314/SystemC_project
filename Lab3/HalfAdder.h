#include "systemc.h"

SC_MODULE(HalfAdder){

  sc_in  <bool> A;
  sc_in  <bool> B;
  sc_out <bool> Sum;
  sc_out <bool> Carry;     

  void HalfAdder_Func(void);
  void trace(sc_trace_file* );

  SC_CTOR(HalfAdder){
    SC_METHOD(HalfAdder_Func);            
    sensitive << A << B;
  }

};