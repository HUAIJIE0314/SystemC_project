// tb_FIR16.cpp

#include "tb_FIR16.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void tb_FIR16::source(void){

    // Reset
    rst = 0;
    wait(3);
    rst = 1;

    int idx = 0;
    //  ================ read firData file ================
    std::ifstream infile1("firData");
    if (!infile1.is_open()) {
        std::cerr << "Failed to open firData" << std::endl;
    }

    //  ================ read goldenData file ================
    std::ifstream infile2("goldenData");
    if (!infile2.is_open()) {
        std::cerr << "Failed to open goldenData" << std::endl;
    }

    string hex_value;

    std::string line1;
    while (std::getline(infile1, line1)) {
        std::istringstream iss(line1);
        while (iss >> hex_value) {
            try {
                int decimal_value = stoi(hex_value, 0, 16);
                InputData[idx] = decimal_value;
                idx += 1;
                //cout << "Hex: " << hex_value << ", Decimal: " << decimal_value << endl;
            } catch (const invalid_argument& ia) {
                //cerr << "Invalid argument: " << ia.what() << endl;
            } catch (const out_of_range& oor) {
                //cerr << "Out of range: " << oor.what() << endl;
            }
        }
    }

    
    std::string line2;
    idx = 0;
    while (std::getline(infile2, line2)) {
        std::istringstream iss(line2);
        while (iss >> hex_value) {
            try {
                int decimal_value = stoi(hex_value, 0, 16);
                Golden[idx] = decimal_value;
                idx += 1;
                //cout << "Hex: " << hex_value << ", Decimal: " << decimal_value << endl;
            } catch (const invalid_argument& ia) {
                //cerr << "Invalid argument: " << ia.what() << endl;
            } catch (const out_of_range& oor) {
                //cerr << "Out of range: " << oor.what() << endl;
            }
        }
    }

    infile1.close();
    infile2.close();
    

    for(int patIdx=0;patIdx<GOLEN_NUM;patIdx++){
      x = InputData[patIdx];
      wait(1);
    }
}

void tb_FIR16::checkData(void){
    wait(3);
    for(int patIdx=0;patIdx<GOLEN_NUM;patIdx++){
      wait();
      if(y.read() == Golden[patIdx]){
        correctNum += 1;
        cout << "PASS!!!!" << Golden[patIdx] << endl;
      }
      else{
        cout << "No. " << patIdx << " -> Expect output y: " << Golden[patIdx] << ", Your output y: " << y.read() << endl;
      }
    }

    //print the test result
    if(correctNum == GOLEN_NUM){
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
    else{
      cout << endl;
      cout << "        ****************************   " << endl;
      cout << "        **                        **   " << endl;
      cout << "        **  OOPS!!                **   " << endl;
      cout << "        **                        **   " << endl;
      cout << "        **  Simulation Failed!!   **   " << endl;
      cout << "        **                        **   " << endl;
      cout << "        ****************************   " << endl;
      cout << "         Correct " << correctNum << " / " << GOLEN_NUM  << endl;
      cout << endl;
    }
    sc_stop();
}

