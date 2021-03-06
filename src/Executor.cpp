#include "Executor.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

string Executor::restoDe(istringstream &ss) {
  string resto;
  getline(ss, resto, '\0'); // ler o resto da linha
  if (resto != "" && (resto[0] == ' ' || resto[0] == '\t')) {
    resto = resto.substr(1); // o primeiro caractere é um espaço, descartar
  }
  return resto;
}

Executor::Executor(Sistema &sistema) {
  this->sair = false;
  this->sistema = &sistema;
}

void Executor::iniciar(istream &inputStream, ostream &outputStream) {
  cout << R"(
   ██████╗ ██████╗ ███╗   ██╗ ██████╗ ██████╗ ██████╗ ██████╗
  ██╔════╝██╔═══██╗████╗  ██║██╔════╝██╔═══██╗██╔══██╗██╔══██╗
  ██║     ██║   ██║██╔██╗ ██║██║     ██║   ██║██████╔╝██║  ██║
  ██║     ██║   ██║██║╚██╗██║██║     ██║   ██║██╔══██╗██║  ██║
  ╚██████╗╚██████╔╝██║ ╚████║╚██████╗╚██████╔╝██║  ██║██████╔╝
  ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝
                    Concord's Not Discord

)";

  sistema->load_users();

  string linha, saida;
  this->sair = false;
  while (! this->sair)
    {
      if (std::getline(inputStream, linha)) {
        saida = processarLinha(linha);
        outputStream << saida << endl;
      }
    }
}

string Executor::processarLinha(string linha) {
  istringstream buf(linha);
  string nomeComando;
  buf >> nomeComando;

  if (nomeComando.empty()) {
    return "Comando Inválido <vazio>";
  }

  if (nomeComando == "quit") {
    if(sistema->quit()){
      this->sair = true;
      return "Saindo...";
    }
    // To clean the buffer
    string s;
    getline(cin, s);
    return "Comando cancelado!";
  }

  else if (nomeComando == "create-user") {
    string email, senha, nome;
    buf >> email;
    buf >> senha;
    nome = restoDe(buf);
    return sistema->create_user(email, senha, nome);
  }

  else if (nomeComando == "login") {
    string email, senha;
    buf >> email;
    buf >> senha;
    return sistema->login(email, senha);
  }


  int id;
  if(buf >> id){

    if (nomeComando == "disconnect") {
      return sistema->disconnect(id);
    }

    else if (nomeComando == "create-server") {
      string nome;
      buf >> nome;
      return sistema->create_server(id, nome);
    }

    else if (nomeComando == "set-server-desc") {
      string nome, descricao;
      buf >> nome;
      descricao = restoDe(buf);
      return sistema->set_server_desc(id, nome, descricao);
    }

    else if (nomeComando == "set-server-invite-code") {
      string nome, codigo;
      buf >> nome;
      buf >> codigo;
      return sistema->set_server_invite_code(id, nome, codigo);
    }

    else if (nomeComando == "list-servers") {
      return sistema->list_servers(id);
    }

    else if (nomeComando == "remove-server") {
      string nome;
      buf >> nome;
      return sistema->remove_server(id, nome);
    }

    else if (nomeComando == "enter-server") {
      string nome, codigo;
      buf >> nome;
      buf >> codigo;
      return sistema->enter_server(id, nome, codigo);
    }

    else if (nomeComando == "leave-server") {
      string nome;
      buf >> nome;
      return sistema->leave_server(id, nome);
    }

    else if (nomeComando == "list-participants") {
      return sistema->list_participants(id);
    }

    else if (nomeComando == "list-channels") {
      return sistema->list_channels(id);
    }

    else if (nomeComando == "create-channel") {
      string nome;
      buf >> nome;
      return sistema->create_channel(id, nome);
    }

    else if (nomeComando == "enter-channel") {
      string nome;
      buf >> nome;
      return sistema->enter_channel(id, nome);
    }

    else if (nomeComando == "leave-channel") {
      return sistema->leave_channel(id);
    }

    else if (nomeComando == "send-message") {
      string mensagem;
      mensagem = restoDe(buf);
      return sistema->send_message(id, mensagem);
    }

    else if (nomeComando == "list-messages") {
      return sistema->list_messages(id);
    }
    else {
      return "Comando não reconhecido [" + nomeComando + "]";
    }
  }

  else {
    return "Comando precisa ser precedido de um id [" + nomeComando + "]";
  }
}
