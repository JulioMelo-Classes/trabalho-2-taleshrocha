//! @file Servidor.h
#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <string>
#include <vector>
#include "CanalTexto.h"

// TODO: edit canalTexto methods.
class Servidor{
private:
	int usuarioDonoId;
	std::string nome;
	std::string descricao;
	std::string codigoConvite;
	std::vector<CanalTexto> canaisTexto; // No get set
	std::vector<int> participantesIds; // No get set
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

	/*! Add a user's id to the participantesIds vector.
	  @param id A integer containing a user's id to be added in the participantesIds vector. */
	void addTextChannel(CanalTexto canal);

	/*! Remove a participant's id of the participantesIds vector.
	  @param id A integer containing a user's id to be added in the participantesIds vector. */
	void removeParticipant(int id);

	/*! Remove a participant's id of the participantesIds vector.
	  @param id A integer containing a user's id to be added in the participantesIds vector. */
	void removeTextChannel(int id);

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

	/*! See if a user is a server participant.
	  @param id A integer containing some user's id.
	  @return True If the user is in the server. False otherwise. */
	bool existTextChannel(std::string name);

	CanalTexto getChannel(std::string name);

	std::string listTextChannels();
};

#endif
