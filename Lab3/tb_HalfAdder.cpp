// tb_HalfAdder.cpp

#include "tb_HalfAdder.h"

void tb_HalfAdder::source(void){
    cout << "============= Testing HalfAdder =============" << endl;
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            A = i;
            B = j;
            wait(10, SC_NS);
            sc_uint<2> concat_result = (sc_uint<1>(Carry.read()), sc_uint<1>(Sum.read()));
            //sc_uint<2> concat_result = ((Carry.read()), (Sum.read()));
            if( concat_result == Golden[i*2+j] ){
                correctNum += 1;
                cout << "correct !!!!!" << endl;
            }
            else{
                cout << "Failed..... Golden (Carry, Sum) = (" << concat_result[1] << ", " << concat_result[0] << "), yours = (" << Carry.read() << ", " << Sum.read() << ")" << endl;
            }
        }
    }
    A = 0;
    B = 0;
    
    if(correctNum == 4){
        cout << endl;
        cout << endl;
        cout << " **************************   " << endl;
        cout << " **                      **   " << endl;
        cout << " **  Congratulations !!  **   " << endl;
        cout << " **                      **   " << endl;
        cout << " **  Simulation PASS!!   **   " << endl;
        cout << " **                      **   " << endl;
        cout << " **************************   " << endl;
        cout << endl;
    }
    else {
        cout << " **************************   " << endl;
        cout << " **                      **   " << endl;
        cout << " **  OOPS!!              **   " << endl;
        cout << " **                      **   " << endl;
        cout << " **  Simulation Failed!  **   " << endl;
        cout << " **                      **   " << endl;
        cout << " **************************   " << endl;
        cout << " Correct " << correctNum << " / " << 4  << endl;
        cout << endl;
    }
    
    
}
