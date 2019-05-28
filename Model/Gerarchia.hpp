#ifndef GERARCHIA_HPP
#define GERARCHIA_HPP

#include <string>

class Articolo
{
private:
  std::string nome;
  float costo;
  unsigned int spi;
  
public:
  Articolo(std::string, float, unsigned int = 0);
  virtual ~Articolo() = default;
  
  std::string getNome() const;
  void setNome(std::string);
  
  float getCosto() const;
  void setCosto(float);

  unsigned int getSPI() const;
  void setSPI(unsigned int);

  virtual float getPrezzo() const = 0;

  virtual unsigned int getSconto() const = 0;

  virtual Articolo * clone() const = 0;
};

class Media : public Articolo
{
private:
  unsigned int anno;

public:
  Media(unsigned int, std::string, float, unsigned int = 0);

  unsigned int getAnno() const;
  void setAnno(unsigned int);

  virtual float getPrezzo() const override = 0;

  virtual unsigned int getSconto() const override = 0;

  virtual Media * clone() const override = 0;
};

class Elettronica : public Articolo
{
private:
  bool usato;

public:
  Elettronica(bool, std::string, float, unsigned int = 0);

  bool isUsato() const;
  void setUsato(bool);

  virtual float getPrezzo() const override = 0;

  virtual unsigned int getSconto() const override = 0;

  virtual Elettronica * clone() const override = 0;

  virtual unsigned int getWarranty() const = 0;
};

class CD : public Media
{
private:
  std::string artista;
  bool compilation;

public:
  CD(std::string, bool, unsigned int, std::string, float, unsigned int = 0);

  std::string getArtista() const;
  void setArtista(std::string);

  bool isCompilation() const;
  void setCompilation(bool);

  virtual float getPrezzo() const override;

  virtual unsigned int getSconto() const override;

  virtual CD * clone() const override;
};


class Computer : public Elettronica
{
private:
  bool portatile;

public:
  Computer(bool, bool, std::string, float, unsigned int = 0);

  bool isPortatile() const;
  void setPortatile(bool);

  virtual float getPrezzo() const override;

  virtual unsigned int getSconto() const override;

  virtual Computer * clone() const override;

  virtual unsigned int getWarranty() const override;
};

class Smartphone : public Elettronica
{
private:
  bool iPhone;

public:
  Smartphone(bool, bool, std::string, float, unsigned int = 0);

  bool isiPhone() const;
  void setiPhone(bool);

  virtual float getPrezzo() const override;

  virtual unsigned int getSconto() const override;

  virtual Smartphone * clone() const override;

  virtual unsigned int getWarranty() const override;
};

#endif // GERARCHIA_HPP
