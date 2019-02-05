#ifndef GERARCHIA_HPP
#define GERARCHIA_HPP

#include <string>

class Articolo
{
private:
  std::string id;
  std::string nome;
  float prezzoListino;
  unsigned int spi;
  std::string imgPath;
  
public:
  Articolo(std::string, std::string, float, unsigned int = 0, std::string = "");
  virtual ~Articolo() = default;
  
  std::string getId() const;

  std::string getNome() const;
  void setNome(std::string);
  
  float getPrezzoListino() const;
  void setPrezzoListino(float);

  unsigned int getSPI() const;
  void setSPI(unsigned int);

  std::string getImgPath() const;
  void setImgPath(std::string);

  virtual float getPrezzo() const = 0;

  virtual Articolo * clone() const = 0;
};

class Album : public Articolo
{
private:
  std::string artista;
  bool compilation;
  
public:
  Album(std::string, bool, std::string, std::string, float, unsigned int = 0, std::string = "");

  std::string getArtista() const;
  void setArtista(std::string);

  bool isCompilation() const;
  void setCompilation(bool);

  virtual float getPrezzo() const;

  virtual Album * clone() const;
};

class ElettBruno : public Articolo
{
private:
  bool usato;

public:
  ElettBruno(bool, std::string, std::string, float, unsigned int = 0, std::string = "");

  bool isUsato() const;
  void setUsato(bool);

  virtual float getPrezzo() const = 0;

  virtual ElettBruno * clone() const = 0;
};

class Computer : public ElettBruno
{
private:
  bool portatile;

public:
  Computer(bool, bool, std::string, std::string, float, unsigned int = 0, std::string = "");

  bool isPortatile() const;
  void setPortatile(bool);

  virtual float getPrezzo() const;

  virtual Computer * clone() const;
};

class Smartphone : public ElettBruno
{
private:
  bool extendedWarranty;

public:
  Smartphone(bool, bool, std::string, std::string, float, unsigned int = 0, std::string = "");

  bool hasExtendedWarranty() const;
  void setExtendedWarranty(bool);

  virtual float getPrezzo() const;

  virtual Smartphone * clone() const;
};

#endif // GERARCHIA_HPP
