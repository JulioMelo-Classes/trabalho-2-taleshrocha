#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  Usuario user(email, senha, nome);
  string notOk = user.Is_User_Ok();
  if(notOk != "All ok") return notOk;

  for(Usuario u : usuarios){ //<! Checks if the user name or email already exists
    if(user.Get_Name() == u.Get_Name()) return "create_user: nome de usuário já existente.";
    else if(user.Get_Email() == u.Get_Email()) return "create_user: email já usado.";
  }

  user.Set_Id();
  //cout << user.Get_Id() << endl;
  //cout << user.Get_Name() << endl;
  //cout << user.Get_Email() << endl;
  //cout << user.Get_Keyword() << endl;
  usuarios.push_back(user); //<! Adds the user in the Sistema's usuarios vector only if he doesn't exists
  return "create_user: usuário criado com sucesso.";
}

string Sistema::login(const string email, const string senha) {
  for(Usuario u : usuarios)
    if(email == u.Get_Email() and senha == u.Get_Keyword()){ //<! Checks if the user email and keyword exists
      usuariosLogados.insert(make_pair(u.Get_Id(), make_pair("--", "--")));
      return "login: logado como " + email;
      }

  return "login: senha ou usuário inválidos"; //<! In case the user doesn't exists
}

string Sistema::disconnect(int id) {
  for(const auto& [key, value] : usuariosLogados){
    cout << key << " " << value.first << " " << value.second << endl;
    //cout << 1 << endl;
  }

  if(usuariosLogados.contains(id)){
    auto el = usuariosLogados.find(id);
    usuariosLogados.erase(el);
    return "disconnect: usuário desconectado com sucesso.";
  }
  return "disconnect: usuário não conectado!";
}

string Sistema::create_server(int id, const string nome) {
  return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers(int id) {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(int id, const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
