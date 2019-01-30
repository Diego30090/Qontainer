#include "Gerarchia.hpp"

// Implementazione Articolo
Articolo::Articolo(std::string ID, std::string NOME,
		   float PREZZO, unsigned int SPI,
		   std::string IMG_PATH) : id(ID), nome(NOME), prezzoListino(PREZZO),
					   spi(SPI), imgPath(IMG_PATH)
{}

Articolo::~Articolo() {}

std::string Articolo::getId() const
{
  return id;
}

std::string Articolo::getNome() const
{
  return nome;
}

void Articolo::setNome(std::string new_nome)
{
  nome = new_nome;
}

float Articolo::getPrezzoListino() const
{
  return prezzoListino;
}

void Articolo::setPrezzoListino(float new_pl)
{
  prezzoListino = new_pl;
}

unsigned int Articolo::getSPI() const
{
  return spi;
}

void Articolo::setSPI(unsigned int new_spi)
{
  spi = new_spi;
}

std::string Articolo::getImgPath() const
{
  return imgPath;
}

void Articolo::setImgPath(std::string new_ip)
{
  imgPath = new_ip;
}

// Implementazione Album
Album::Album(std::string ARTISTA, bool COMPILATION,
	     std::string ID, std::string NOME,
	     float PREZZO, unsigned int SPI,
	     std::string IMG_PATH) : Articolo(ID, NOME, PREZZO, SPI, IMG_PATH),
				     artista(ARTISTA),
				     compilation(COMPILATION)
{}

std::string Album::getArtista() const
{
  return artista;
}

void Album::setArtista(std::string new_artista)
{
  artista = new_artista;
}

bool Album::isCompilation() const
{
  return compilation;
}

void Album::setCompilation(bool is_comp)
{
  compilation = is_comp;
}

float Album::getPrezzo() const
{
  return getSPI() < 4
		    ? getPrezzoListino()
		    : getPrezzoListino() - (getPrezzoListino() * 0.1f * (getSPI() - 3));
}

Album * Album::clone() const
{
  return new Album(*this);
}

// Implementazione ElettBruno
ElettBruno::ElettBruno(bool USATO,
		       std::string ID, std::string NOME,
		       float PREZZO, unsigned int SPI,
		       std::string IMG_PATH) : Articolo(ID, NOME, PREZZO, SPI, IMG_PATH),
					       usato(USATO)
{}

bool ElettBruno::isUsato() const
{
  return usato;
}

void ElettBruno::setUsato(bool is_usato)
{
  usato = is_usato;
}

// Implementazione Computer
Computer::Computer(bool PORTATILE, bool USATO,
		   std::string ID, std::string NOME,
		   float PREZZO, unsigned int SPI,
		   std::string IMG_PATH) : ElettBruno(USATO, ID, NOME, PREZZO, SPI, IMG_PATH),
					   portatile(PORTATILE)
{}

bool Computer::isPortatile() const
{
  return portatile;
}

void Computer::setPortatile(bool is_portatile)
{
  portatile = is_portatile;
} 

float Computer::getPrezzo() const
{
  float res = getPrezzoListino();
  
  if(getSPI() >= 8)
    res -= (getPrezzoListino() * 0.2f * (getSPI() - 9));

  if(isUsato())
    res *= 2 / 3;

  return res;
}

Computer * Computer::clone() const
{
  return new Computer(*this);
}

// Implementazione Smartphone
Smartphone::Smartphone(bool EXT_WARRANTY, bool USATO,
		       std::string ID, std::string NOME,
		       float PREZZO, unsigned int SPI,
		       std::string IMG_PATH) : ElettBruno(USATO, ID, NOME, PREZZO, SPI, IMG_PATH),
					       extendedWarranty(EXT_WARRANTY)
{}

bool Smartphone::hasExtendedWarranty() const
{
  return extendedWarranty;
}

void Smartphone::setExtendedWarranty(bool has_exw)
{
  extendedWarranty = has_exw;
} 

float Smartphone::getPrezzo() const
{
  float res = getPrezzoListino();
  
  if(getSPI() >= 4)
    res -= (getPrezzoListino() * 0.2f * (getSPI() - 3));

  if(isUsato())
    res /= 2;

  return res;
}

Smartphone * Smartphone::clone() const
{
  return new Smartphone(*this);
}
