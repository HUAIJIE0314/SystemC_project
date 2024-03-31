#ifndef FIR16_H
#define FIR16_H

#include "systemc.h"

#define FIR_STAGE 16


SC_MODULE(FIR16){

  sc_in  <bool>         clk;
  sc_in  <bool>         rst;
  sc_in  <sc_uint<32> >   x;
  sc_out <sc_uint<32> >   y;

  void FIR16_Func(void);
  void trace(sc_trace_file* );

  
  sc_signal <sc_uint<32> > FIR_REG [FIR_STAGE];
  sc_uint<64> sum;
  sc_uint<64> product;

  SC_CTOR(FIR16){
    SC_CTHREAD(FIR16_Func, clk.pos());            
    reset_signal_is(rst, true);

    sum = 0;
    for(int i=0;i<FIR_STAGE;i++)FIR_REG[i] = 0;

  }

};

#endif // FIR16_H