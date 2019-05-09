#include "ModelException.hpp"

const char * ModelException::what() const noexcept
{
  return "Errore sconosciuto Modello";
}

const char * ModelBoxNotOpenException::what() const noexcept
{
  return "Si è cercato di effettuare un'operazione a box chiuso";
}

const char * ModelBoxNotClosedException::what() const noexcept
{
  return "Si è cercato di effettuare un'operazione a box aperto";
}

const char * ModelBoxPathNotSetException::what() const noexcept
{
  return "Non è stato impostato un percorso per il box";
}

const char * ModelFileNotAvailableException::what() const noexcept
{
  return "Errore nell'apertura del file";
}

const char * ModelBadTypeException::what() const noexcept
{
  return "Operazione non consentita su questo tipo di dato";
}
