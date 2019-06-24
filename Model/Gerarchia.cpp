#include "Gerarchia.hpp"

// Implementazione Articolo
Articolo::Articolo(std::string NOME, float COSTO, unsigned int SPI)
  : nome(NOME), costo(COSTO), spi(SPI)
{}

std::string Articolo::getNome() const
{
  return nome;
}

void Articolo::setNome(std::string new_nome)
{
  nome = new_nome;
}

float Articolo::getCosto() const
{
  return costo;
}

void Articolo::setCosto(float new_pl)
{
  costo = new_pl;
}

unsigned int Articolo::getSPI() const
{
  return spi;
}

void Articolo::setSPI(unsigned int new_spi)
{
  spi = new_spi;
}

// Implementazione Media
Media::Media(unsigned int ANNO, std::string NOME, float COSTO, unsigned int SPI)
  : Articolo(NOME, COSTO, SPI), anno(ANNO)
{}

unsigned int Media::getAnno() const
{
  return anno;
}

void Media::setAnno(unsigned int new_anno)
{
  anno = new_anno;
}

// Implementazione Elettronica
Elettronica::Elettronica(bool USATO, std::string NOME, float COSTO, unsigned int SPI)
  : Articolo(NOME, COSTO, SPI), usato(USATO)
{}

bool Elettronica::isUsato() const
{
  return usato;
}

void Elettronica::setUsato(bool is_usato)
{
  usato = is_usato;
}

// Implementazione CD
CD::CD(std::string ARTISTA, bool COMPILATION, unsigned int ANNO, std::string NOME, float COSTO, unsigned int SPI)
  : Media(ANNO, NOME, COSTO, SPI), artista(ARTISTA), compilation(COMPILATION)
{}

std::string CD::getArtista() const
{
  return artista;
}

void CD::setArtista(std::string new_artista)
{
  artista = new_artista;
}

bool CD::isCompilation() const
{
  return compilation;
}

void CD::setCompilation(bool is_comp)
{
  compilation = is_comp;
}

float CD::getPrezzo() const
{
  return getCosto() + getCosto() * 0.05f;
}

unsigned int CD::getSconto() const
{
  return getSPI() < 4 ? 0 : (10 * (getSPI() - 3));
}

CD * CD::clone() const
{
  return new CD(*this);
}

// Implementazione Computer
Computer::Computer(bool PORTATILE, bool USATO, std::string NOME, float COSTO, unsigned int SPI)
  : Elettronica(USATO, NOME, COSTO, SPI), portatile(PORTATILE)
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
  return getCosto() + getCosto() * (isUsato() ? 0.10f : 0.20f);
}

unsigned int Computer::getSconto() const
{
  return getSPI() < 8 ? 0 : 5 * (getSPI() - 9);
}

Computer * Computer::clone() const
{
  return new Computer(*this);
}

unsigned int Computer::getWarranty() const
{
  return isUsato() ? 0 : 2;
}

// Implementazione Smartphone
Smartphone::Smartphone(bool IPHONE, bool USATO, std::string NOME, float COSTO, unsigned int SPI)
  : Elettronica(USATO, NOME, COSTO, SPI), iPhone(IPHONE)
{}

bool Smartphone::isiPhone() const
{
  return iPhone;
}

void Smartphone::setiPhone(bool is_iPhone)
{
  iPhone = is_iPhone;
} 

float Smartphone::getPrezzo() const
{
  return getCosto() + getCosto() * (isUsato() ? 0.05f : 0.10f);
}

unsigned int Smartphone::getSconto() const
{
  return getSPI() < 5 ? 0 : 10 * (getSPI() - 6);
}

Smartphone * Smartphone::clone() const
{
  return new Smartphone(*this);
}

unsigned int Smartphone::getWarranty() const
{
  if (isUsato())
    return 0;

  if (isiPhone())
    return 1;

  return 2;
}
