#ifndef CONTAINEREXCEPTION_HPP
#define CONTAINEREXCEPTION_HPP

#include <stdexcept>

// Eccezioni lanciabili da Container
class ContainerException : public std::exception
{
public:
  virtual const char * what() const noexcept; // overriding
};

class ContainerCellNotFoundException : public ContainerException
{
public:
  virtual const char * what() const noexcept; // overriding
};

class ContainerDuplicateKeyException : public ContainerException
{
public:
  virtual const char * what() const noexcept; // overriding
};

class ContainerEmptyTableException : public ContainerException
{
public:
  virtual const char * what() const noexcept; // overriding
};

#endif // CONTAINEREXCEPTION_HPP
