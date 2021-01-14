#include "rocords.h"

QString rocords::NN(){
  _NN.replace(' ', '_');
  return _NN;
}
int rocords::LL(){
  return _LL;
}
int rocords::SS(){
  return _SS;
}

