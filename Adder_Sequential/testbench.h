
#include <systemc.h>
#include <time.h>

int correctNum = 0;

SC_MODULE(testbench){
  sc_in  <bool> clk;// clock in
  sc_out <bool> rst_n;    
  sc_out < sc_int<32> > input1;
  sc_out < sc_int<32> > input2;
  sc_in  < sc_int<32> > F; 

  sc_int<32> tempA;
  sc_int<32> tempB;

  // output to circuit
  void source();

  // input from circuit
  void checkAns();

  //delay
  void delay();

  SC_CTOR(testbench){
    SC_CTHREAD( source, clk.pos() );
    SC_CTHREAD( delay, clk.pos() );
    SC_CTHREAD( checkAns, clk.neg() );
  }

};

void testbench::source(){
  // random seed
  srand( time(NULL) );
  //Reset
  input1 = 0;
  input2 = 0;
  rst_n = 0;
  wait(2);
  rst_n = 1;
  for(int i=0;i<100;i++){
    for (int j=0;j<100;j++){
      input1 = rand() % 100;
      input2 = rand() % 100;
      wait();
    }
  }
  wait();
  if(correctNum == 100*100){
    cout << endl;
    cout << endl;
    cout << "        ****************************   " << endl;
    cout << "        **                        **   " << endl;
    cout << "        **  Congratulations !!    **   " << endl;
    cout << "        **                        **   " << endl;
    cout << "        **  Simulation PASS!!     **   " << endl;
    cout << "        **                        **   " << endl;
    cout << "        ****************************   " << endl;
    cout << endl;
  }
  else {
    cout << "        ****************************   " << endl;
    cout << "        **                        **   " << endl;
    cout << "        **  OOPS!!                **   " << endl;
    cout << "        **                        **   " << endl;
    cout << "        **  Simulation Failed!!   **   " << endl;
    cout << "        **                        **   " << endl;
    cout << "        ****************************   " << endl;
    cout << "         Correct " << correctNum << " / " << 100*100  << endl;
    cout << endl;
  }
  sc_stop();
}

void testbench::checkAns(){
  sc_int<32> resultData;
  correctNum = 0;
  int rowNum = 0;
  wait(3);
  while( true ){
    resultData = F.read();
    if(resultData.to_int() != tempA.to_int() + tempB.to_int()){
      cout << "Error.... No." << rowNum << " -> " << tempA << " + " << tempB << " = " << resultData.to_int() << endl;
    }
    else{
      correctNum += 1;
    }
    wait();
    rowNum += 1;
  }
}

void testbench::delay(){
  while( true ){
    tempA = input1.read();
    tempB = input2.read();
    wait();
  }
}