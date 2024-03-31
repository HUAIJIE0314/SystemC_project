// include the design

#include "tb_FIR16.h"
#include "FIR16.h"

SC_MODULE( SYSTEM ){
    // instantiate the module
    FIR16*          FIR16_0;
    tb_FIR16*    tb_FIR16_0;

    //===============================================================

    // declare the connection wire
    
    sc_clock clk;

    sc_signal  <bool>         rst;
    sc_signal  <sc_uint<32> >   x;
    sc_signal  <sc_uint<32> >   y;


    SC_CTOR( SYSTEM ):clk("clk", 5, SC_NS){

        FIR16_0 = new FIR16("FIR16");
        FIR16_0->clk(clk);
        FIR16_0->rst(rst);
        FIR16_0->x(x);
        FIR16_0->y(y);

        tb_FIR16_0 = new tb_FIR16("tb_FIR16");
        tb_FIR16_0->clk(clk);
        tb_FIR16_0->rst(rst);
        tb_FIR16_0->x(x);
        tb_FIR16_0->y(y);

    }

    //De-Constructor
    ~SYSTEM(){
        delete FIR16_0;
        delete tb_FIR16_0;
    }

};



int sc_main( int argc, char* argv[] ){
    SYSTEM* Top = new SYSTEM("Top");

    sc_trace_file* tf = sc_create_vcd_trace_file("RESULT");// generate the RESULT.vcd
    
    sc_start(SC_ZERO_TIME);
    
    //trace signal
    Top->FIR16_0->trace(tf);
    
    //sc_start(140, SC_NS);
    //sc_start(5*66, SC_NS);
    sc_start();
    sc_stop();

    sc_close_vcd_trace_file(tf);

    return 0;
}
