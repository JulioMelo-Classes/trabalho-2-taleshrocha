//! @file Servidor.h
#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <string>
#include <vector>
#include <memory>
#include "CanalTexto.h"

// TODO: finish documentation.

/*
Cp2 ok
documentação 0.8, faltou documentar os atributos
*/
class Servidor{
private:
	int usuarioDonoId;
	std::string nome;
	std::string descricao;
	std::string codigoConvite;
	std::vector<std::shared_ptr<CanalTexto>> canaisTexto;
	std::vector<int> participantesIds;
public:

	/*! The class's constructor.
	  @param usuarioDonoId A integer containing the server's owner id.
	  @param nome A string containing the server's name. */
	Servidor(int usuarioDonoId, std::string nome);

	/*! Set the server's description.
	  @param descricao A string containing the description to be setted in the server. */
	void setDesc(std::string descricao);

	/*! Set the server's invite code.
	  @param codigoConvite A string containing the invite code to be setted in the server. */
	void setInviteCode(std::string codigoConvite);

	/*! Add a user's id to the participantesIds vector.
	  @param id A integer containing a user's id to be added in the participantesIds vector. */
	void addParticipant(int id);

	/*! Adds a text channel in the vector canaisTexto
	  @param canal A pointer of a CanalTexto */
	void addTextChannel(std::shared_ptr<CanalTexto> canal);

	/*! Remove a participant's id of the participantesIds vector.
	  @param id A integer containing a user's id to be added in the participantesIds vector. */
	void removeParticipant(int id);

	/*! Get the server's owner id.
	  @return A integer containing the server's owner id. */
	int getId();

	/*! Get the server's name.
	  @return A string containing the server's name. */
	std::string getName();

	/*! Get the server's description.
	  @return A string containing the server's description. */
	std::string getDesc();

	/*! Get the server's invite code.
	  @return A string containing the server's invite code. */
	std::string getInviteCode();

	/*! See if a user is a server participant.
	  @param id A integer containing some user's id.
	  @return True If the user is in the server. False otherwise. */
	bool existParticipant(int id);

	/*! See if a text channel is in the server.
	  @param name A string containing the text channel name.
	  @return True If the text channel is in the server. False otherwise. */
	bool existTextChannel(std::string name);

	/*! Get a smart pointer to a text channel.
	  @param name A string containing the text channel name.
	  @return A pointer to the desired text channel. */
	std::shared_ptr<CanalTexto> getChannel(std::string name);

	/*! Prints all text channels in the server.
	  @return True If there is text channels in the server. False otherwise. */
	bool listTextChannels();
};

#endif
