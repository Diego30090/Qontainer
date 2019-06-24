#ifndef CONTAINEREXCEPTION_HPP
#define CONTAINEREXCEPTION_HPP

#include <stdexcept>

// Eccezioni lanciabili da Container
class ContainerException : public std::exception
{
public:
  const char * what() const noexcept override;
};

class ContainerCellNotFoundException : public ContainerException
{
public:
  const char * what() const noexcept override;
};

class ContainerDuplicateKeyException : public ContainerException
{
public:
  const char * what() const noexcept override;
};

class ContainerEmptyTableException : public ContainerException
{
public:
  const char * what() const noexcept override;
};

#endif // CONTAINEREXCEPTION_HPP
