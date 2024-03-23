// tb_FullAdder.cpp

#include "tb_FullAdder.h"

void tb_FullAdder::source(void){
    wait(50, SC_NS);
    cout << "============= Testing FullAdder =============" << endl;
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            for(k=0;k<2;k++){
                A = i;
                B = j;
                Cin = k;
                wait(10, SC_NS);
                sc_uint<2> concat_result = (sc_uint<1>(Cout.read()), sc_uint<1>(S.read()));
                if( concat_result == Golden[i*4+j*2+k] ){
                    correctNum += 1;
                    cout << "correct !!!!!" << endl;
                }
                else{
                    cout << "Failed..... Golden (Cout, S) = (" << Golden[i*4+j*2+k][1] << ", " << Golden[i*4+j*2+k][0] << "), yours = (" << Cout.read() << ", " << S.read() << ")" << endl;
                }
            }
        }
    }
    A = 0;
    B = 0;
    Cin = 0;
    if(correctNum == 8){
        cout << endl;
        cout << " ****************************   " << endl;
        cout << " **                        **   " << endl;
        cout << " **  Congratulations !!    **   " << endl;
        cout << " **                        **   " << endl;
        cout << " **  Simulation PASS!!     **   " << endl;
        cout << " **                        **   " << endl;
        cout << " ****************************   " << endl;
        cout << endl;
    }
    else {
        cout << endl;
        cout << " ****************************   " << endl;
        cout << " **                        **   " << endl;
        cout << " **  OOPS!!                **   " << endl;
        cout << " **                        **   " << endl;
        cout << " **  Simulation Failed!!   **   " << endl;
        cout << " **                        **   " << endl;
        cout << " ****************************   " << endl;
        cout << " Correct " << correctNum << " / " << 8 << endl;
        cout << endl;
    }
    
}
