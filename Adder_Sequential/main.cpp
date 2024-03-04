#include "systemc.h"
#include "Adder_Sequential.h"
#include "testbench.h"

SC_MODULE( SYSTEM ){

  // Module declaration
  Adder_Sequential    *Adder_Sequential_0;
  testbench           *testbench_0;


  // Local signal declarations
  sc_signal < sc_int<32> >   srcA_i;
  sc_signal < sc_int<32> >   srcB_i;
  sc_signal <bool>          reset_n;
  sc_signal < sc_int<32> > result_o;

  sc_clock clock;

  // SC Constructor
  SC_CTOR( SYSTEM ):clock("clock", 10, SC_NS){

    testbench_0 = new testbench("testbench_0");
    testbench_0->clk(clock);
    testbench_0->rst_n(reset_n);
    testbench_0->input1(srcA_i);
    testbench_0->input2(srcB_i);
    testbench_0->F(result_o);

    Adder_Sequential_0 = new Adder_Sequential("Adder_Sequential_0");
    Adder_Sequential_0->clk(clock);
    Adder_Sequential_0->rst_n(reset_n);
    Adder_Sequential_0->input1(srcA_i);
    Adder_Sequential_0->input2(srcB_i);
    Adder_Sequential_0->F(result_o);
  }

  // Destructor
  ~SYSTEM(){
    delete Adder_Sequential_0;
    delete testbench_0;
  }

};



int sc_main( int argc, char* argv[] ){
  SYSTEM *top = new SYSTEM("top");
  sc_start(SC_ZERO_TIME);

  sc_trace_file *tf = sc_create_vcd_trace_file("RESULT");// generate vcd file

  sc_trace(tf, top->clock, "clock");
  sc_trace(tf, top->srcA_i, "srcA_i");
  sc_trace(tf, top->srcB_i, "srcB_i");
  sc_trace(tf, top->reset_n, "reset_n");
  sc_trace(tf, top->result_o, "result_o");
  sc_start(1, SC_SEC);
  sc_close_vcd_trace_file(tf);
  return 0;

}
