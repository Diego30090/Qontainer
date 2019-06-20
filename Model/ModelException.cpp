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

const char * ModelEmptyBoxException::what() const noexcept
{
  return "Si sta cercando di eseguire un'operazione a box vuoto";
}

const char * ModelDuplicateKeyException::what() const noexcept
{
  return "Si sta cercando di inserire un Articolo con chiave identica a quella un articolo già esistente";
}

const char * ModelArticleNotFoundException::what() const noexcept
{
  return "ID non trovato";
}
