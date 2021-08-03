#include "Mensagem.h"
#include <iostream>
#include <sstream>

using namespace std;

Mensagem::Mensagem(int owner, string date, string content){
  this->owner = owner;
  this->date = date;
  this->content = content;
}

void Mensagem::setContent(std::string content){
  this->content = content;
}

//std::string getDate();

//int getOwner();

//std::string getContent();
