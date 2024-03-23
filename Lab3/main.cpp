// include the design
#include "tb_HalfAdder.h"
//#include "HalfAdder.h"

#include "tb_FullAdder.h"
#include "FullAdder.h"

SC_MODULE( SYSTEM ){
    // instantiate the module
    HalfAdder*          HalfAdder0;
    tb_HalfAdder*    tb_HalfAdder0;

    FullAdder*          FullAdder0;
    tb_FullAdder*    tb_FullAdder0;
    //===============================================================

    // declare the connection wire
    sc_signal <bool> Half_adder_A;
    sc_signal <bool> Half_adder_B;
    sc_signal <bool> Half_adder_Sum;
    sc_signal <bool> Half_adder_Carry;    

    sc_signal <bool> Full_adder_A;
    sc_signal <bool> Full_adder_B;
    sc_signal <bool> Full_adder_Cin;
    sc_signal <bool> Full_adder_S;
    sc_signal <bool> Full_adder_Cout;    

    SC_CTOR( SYSTEM ){
        // ------- HalfAdder --------
        HalfAdder0 = new HalfAdder("HalfAdder");
        HalfAdder0->A(Half_adder_A);
        HalfAdder0->B(Half_adder_B);
        HalfAdder0->Sum(Half_adder_Sum);
        HalfAdder0->Carry(Half_adder_Carry);

        tb_HalfAdder0 = new tb_HalfAdder("tb_HalfAdder");
        tb_HalfAdder0->A(Half_adder_A);
        tb_HalfAdder0->B(Half_adder_B);
        tb_HalfAdder0->Sum(Half_adder_Sum);
        tb_HalfAdder0->Carry(Half_adder_Carry);

        // ------- FullAdder --------
        FullAdder0 = new FullAdder("FullAdder");
        FullAdder0->A(Full_adder_A);
        FullAdder0->B(Full_adder_B);
        FullAdder0->Cin(Full_adder_Cin);
        FullAdder0->S(Full_adder_S);
        FullAdder0->Cout(Full_adder_Cout);

        tb_FullAdder0 = new tb_FullAdder("tb_FullAdder");
        tb_FullAdder0->A(Full_adder_A);
        tb_FullAdder0->B(Full_adder_B);
        tb_FullAdder0->Cin(Full_adder_Cin);
        tb_FullAdder0->S(Full_adder_S);
        tb_FullAdder0->Cout(Full_adder_Cout);
    }

    //De-Constructor
    ~SYSTEM(){
        delete HalfAdder0;
        delete tb_HalfAdder0;

        delete FullAdder0;
        delete tb_FullAdder0;
    }

};



int sc_main( int argc, char* argv[] ){
    SYSTEM* Top = new SYSTEM("Top");

    sc_trace_file* tf = sc_create_vcd_trace_file("RESULT");// generate the RESULT.vcd
    
    sc_start(SC_ZERO_TIME);
    
    //trace signal
    Top->HalfAdder0->trace(tf);
    Top->FullAdder0->trace(tf);
    
    sc_start(140, SC_NS);
    sc_stop();

    sc_close_vcd_trace_file(tf);

    return 0;
}
