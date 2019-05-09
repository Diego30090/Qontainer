#ifndef MODELEXCEPTION_HPP
#define MODELEXCEPTION_HPP

#include <stdexcept>

class ModelException : public std::exception
{
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxNotOpenException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxNotClosedException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxPathNotSetException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

class ModelFileNotAvailableException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

class ModelBadTypeException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

#endif // MODELEXCEPTION_HPP
