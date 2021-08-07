#include "Usuario.h"
#include <iostream>

using namespace std;

int Usuario::currentId; // To keep the last id value created by the sistem.

Usuario::Usuario(string email, string password, string name){
  this->name = name;
  this->email = email;
  this->password = password;
}

void Usuario::setId(){
  this->id = currentId++;
}

void Usuario::setName(string name){ // TODO: can't have numbers
  this->name = name;
}

void Usuario::setEmail(string email){ //TODO: validation
  this->email = email;
}

void Usuario::setPassword(string password){ // TODO: password size most be bigger than 8 char
  this->password = password;
}

int Usuario::getId(){
  return id;
}

string Usuario::getName(){
  return name;
}

string Usuario::getEmail(){
  return email;
}

string Usuario::getPassword(){
  return password;
}

//bool Usuario::validateName(){
//}

bool Usuario::validatePassword(){
  if(this->password.size() < 8 or
     (this->password.find("!") == string::npos and
     this->password.find("@") == string::npos and
     this->password.find("#") == string::npos and
     this->password.find("$") == string::npos and
     this->password.find("%") == string::npos and
     this->password.find("¨") == string::npos and
     this->password.find("&") == string::npos and
     this->password.find("*") == string::npos and
     this->password.find("(") == string::npos and
     this->password.find(")") == string::npos and
     this->password.find("-") == string::npos and
     this->password.find("_") == string::npos)){
    return false;
  }

  int count = 0;
  for(int i = 0 ; i < 10; i++) {
    if(this->password.find(to_string(i)) != string::npos){
      count++;
    }
  }

  if(count == 0){
    return false;
  }

  return true;
}

bool Usuario::validateEmail(){
  // Locate '@'
  auto atSign = find(this->email.begin(), this->email.end(), '@');
  // Locate '.' after '@'
  auto dot = find(atSign, this->email.end(), '.');
  // make sure both characters are present
  if(atSign == this->email.end() or dot == this->email.end()){
    return false;
  }
  return true;
}
