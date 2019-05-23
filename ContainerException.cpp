#include "ContainerException.hpp"

const char * ContainerException::what() const noexcept
{
  return "Errore sconosciuto Container";
}

const char * ContainerCellNotFoundException::what() const noexcept
{
  return "Nessuna voce trovata con la chiave inserita";
}

const char * ContainerDuplicateKeyException::what() const noexcept
{
  return "Inserimento di un valore chiave duplicato";
}

const char * ContainerEmptyTableException::what() const noexcept
{
  return "Si è cercato di dichiarare un iteratore su un Container vuoto";
}
