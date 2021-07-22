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
  for(const auto& [key, value] : usuariosLogados)
    cout << key << " " << value.first << " " << value.second << endl;

  if(usuariosLogados.contains(id)){
    auto el = usuariosLogados.find(id);
    usuariosLogados.erase(el);
    return "disconnect: usuário desconectado com sucesso.";
  }
  return "disconnect: usuário não conectado!";
}

string Sistema::create_server(int id, const string nome) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    Servidor server(id, nome);
    for(Servidor server : servidores) // Seek for a existing server name in the user domain
      if(nome == server.getName() and id == server.getId())
        return "create_server: já existe um servidor com esse nome!";

    servidores.push_back(server);
    return "create-server: servidor criado com sucesso.";
  }
  else return "create-server: usuário não existente ou não conectado!";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(Servidor server : servidores){ // Seek for a existing server name in the user domain
      if(nome == server.getName()){
        if(id == server.getId()){
          server.setDesc(descricao);
          return "set_server_desc: descrição do servidor [" + nome + "] modificada.";
        }
        else return "set_server_desc: você não pode alterar a descrição de um servidor que não foi criado por você!";
      }
      else return "set_server_desc: servidor [" + nome + "] não existe!";
    }
  }
  return "set_server_desc: usuário não existe ou não conectado!";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if(usuariosLogados.contains(id)){ // See if the user is logged
    for(Servidor server : servidores){ // Seek for a existing server name in the user domain
      if(nome == server.getName()){
        if(id == server.getId()){
          server.setInviteCode(codigo);
          if(codigo.empty()) return "set_server_invite_code: codigo de convite do servidor [" + nome + "] removido.";
          else return "set_server_invite_code: codigo de convite do servidor [" + nome + "] modificado.";
        }
        else return "set_server_invite_code: você não pode alterar o convite de um servidor que não foi criado por você!";
      }
      else return "set_server_invite_code: servidor [" + nome + "] não existe!";
    }
  }
  return "set_server_invite_code: usuário não existe ou não conectado!";
}

string Sistema::list_servers(int id) {
  stringstream ss;

  for(auto &server : servidores)
    if(server.getId() == id) ss << server.getName() << endl;

  string s = ss.str();

  if(s.empty()) return "list_servers: não foram encontrados servidores para esse usuário!";
  s.pop_back(); // Removes the last endl
  return "list_servers: \n" + s;
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
