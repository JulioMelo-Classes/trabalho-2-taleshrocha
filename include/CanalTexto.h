#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "Mensagem.h"

// TODO: documentation.
// TODO: implement methods.
class CanalTexto{
private:
	std::string name;
	std::vector<Mensagem> messages; // No get set
public:

	/*! The class's constructor.
	  @param name A string containing the text channel's name. */
	CanalTexto(std::string name);

	std::string getName();

	void setName(std::string name);

	/*! Add a user's id to the participantesIds vector.
	  @param id A integer containing a user's id to be added in the participantesIds vector. */
	void addMensage(int id);

	/*! Remove a participant's id of the participantesIds vector.
	  @param id A integer containing a user's id to be added in the participantesIds vector. */
	void removeMensage(int id);
};

#endif
