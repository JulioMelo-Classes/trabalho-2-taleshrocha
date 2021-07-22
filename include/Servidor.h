#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <string>
#include <vector>

class Servidor{
private:
	int usuarioDonoId;
	std::string nome;
	std::string descricao;
	std::string codigoConvite;
	//std::vector<CanalTexto> canaisTexto; // No get set
	std::vector<int> participantesIds; // No get set
public:
	Servidor(int usuarioDonoId, std::string nome);

	int getId();

	std::string getName();
};

#endif
