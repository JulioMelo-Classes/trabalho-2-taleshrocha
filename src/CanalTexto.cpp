#include "CanalTexto.h"

using namespace std;

CanalTexto::CanalTexto(std::string name){
  this->name = name;
}

void CanalTexto::setName(string name){
  this->name = name;
}

string CanalTexto::getName(){
  return name;
}
