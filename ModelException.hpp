#ifndef MODELEXCEPTION_HPP
#define MODELEXCEPTION_HPP

#include <stdexcept>

class ModelException : public std::exception
{
public:
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxNotOpenException : public ModelException
{
public:
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxNotClosedException : public ModelException
{
public:
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxPathNotSetException : public ModelException
{
public:
  virtual const char * what() const noexcept; // overriding
};

class ModelFileNotAvailableException : public ModelException
{
public:
  virtual const char * what() const noexcept; // overriding
};

class ModelBadTypeException : public ModelException
{
public:
  virtual const char * what() const noexcept; // overriding
};

#endif // MODELEXCEPTION_HPP
