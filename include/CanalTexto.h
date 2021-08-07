//! @file CanalTexto.h
#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include <memory>
#include "Mensagem.h"

class CanalTexto{
private:
	std::string name;
	std::vector<std::shared_ptr<Mensagem>> messages;
public:

	/*! The class's constructor.
	  @param name A string containing the text channel's name. */
	explicit CanalTexto(std::string name);

	/*! get the class's name.
	  @return a string containing the text channel's name. */
	std::string getName();

	/*! Add a user's id to the participantesIds vector.
	  @param id A integer containing a user's id to be added in the participantesIds vector. */
	void addMessage(std::shared_ptr<Mensagem> message);

	//! List all the channel's messages with cout.
	void listMessages();
};

#endif
