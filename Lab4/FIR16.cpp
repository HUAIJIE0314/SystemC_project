// FIR16.cpp

#include "FIR16.h"

void FIR16::FIR16_Func(void){
    // reset
    for(int i=0;i<FIR_STAGE;i++){
      FIR_REG[i] = 0;
    }

    while(true){
      wait();

      for(int i=0;i<FIR_STAGE;i++){
        if(i==0){ // register 0
          FIR_REG[i] = x;
        }
        else { // register 1-31
          FIR_REG[i] = FIR_REG[i-1].read();
        }
      }

      sum = x.read() * sc_uint<32>(0x00000F0F);
      for(int i=0;i<FIR_STAGE;i++){
        product = FIR_REG[i].read() * sc_uint<32>(0x00000F0F);
        sum += product;
      }
      y = sum.range(16+32-1, 16);
      //cout << "=========== sum: " << sum << " ==============" << endl;
      //cout << endl;
    }
}

void FIR16::trace(sc_trace_file* tf){
    sc_trace(tf, clk,         "clk");
    sc_trace(tf, rst,         "rst");
    sc_trace(tf, x,             "x");
    sc_trace(tf, y,             "y");
    //sc_trace(tf, product, "product");
    //sc_trace(tf, sum,         "sum");
    /*
    for(int i=0;i<FIR_STAGE;i++){
      sc_trace(tf, FIR_REG[i], "FIR_REG_" + std::to_string(i));
    }
    */
}
