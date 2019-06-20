#ifndef MODELEXCEPTION_HPP
#define MODELEXCEPTION_HPP

#include <stdexcept>

class ModelException : public std::exception
{
public:
  virtual const char * what() const noexcept override;
};

class ModelBoxNotOpenException : public ModelException
{
public:
  virtual const char * what() const noexcept override;
};

class ModelBoxNotClosedException : public ModelException
{
public:
  virtual const char * what() const noexcept override;
};

class ModelBoxPathNotSetException : public ModelException
{
public:
  virtual const char * what() const noexcept override;
};

class ModelFileNotAvailableException : public ModelException
{
public:
  virtual const char * what() const noexcept override;
};

class ModelBadTypeException : public ModelException
{
public:
  virtual const char * what() const noexcept override;
};

class ModelEmptyBoxException : public ModelException
{
public:
  virtual const char * what() const noexcept override;
};

class ModelDuplicateKeyException : public ModelException
{
public:
  virtual const char * what() const noexcept override;
};

class ModelArticleNotFoundException : public ModelException
{
public:
  virtual const char * what() const noexcept override;
};

#endif // MODELEXCEPTION_HPP
