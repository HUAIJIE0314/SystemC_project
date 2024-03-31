#ifndef TB_FIR16_H
#define TB_FIR16_H

#include "systemc.h"
#define FIR_STAGE 16
#define GOLEN_NUM 64

SC_MODULE(tb_FIR16){

  sc_in  <bool>         clk;
  sc_out <bool>         rst;
  sc_out <sc_uint<32> >   x;
  sc_in  <sc_uint<32> >   y;

  void source(void);
  void checkData(void);

  sc_uint<32> InputData [GOLEN_NUM];
  sc_uint<32> Golden    [GOLEN_NUM];

  int correctNum = 0;

  SC_CTOR(tb_FIR16){
    SC_THREAD(source);
    sensitive << clk.pos();
    SC_THREAD(checkData);
    sensitive << clk.pos();

    for(int i=0;i<GOLEN_NUM;i++){
      InputData[i] = 0;
      Golden[i] = 0;
    }
  }

};

#endif // TB_FIR16_H