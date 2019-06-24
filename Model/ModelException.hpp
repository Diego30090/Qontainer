#ifndef MODELEXCEPTION_HPP
#define MODELEXCEPTION_HPP

#include <stdexcept>

class ModelException : public std::exception
{
public:
  const char * what() const noexcept override;
};

class ModelBoxNotOpenException : public ModelException
{
public:
  const char * what() const noexcept override;
};

class ModelBoxNotClosedException : public ModelException
{
public:
  const char * what() const noexcept override;
};

class ModelBoxPathNotSetException : public ModelException
{
public:
  const char * what() const noexcept override;
};

class ModelFileNotAvailableException : public ModelException
{
public:
  const char * what() const noexcept override;
};

class ModelBadTypeException : public ModelException
{
public:
  const char * what() const noexcept override;
};

class ModelEmptyBoxException : public ModelException
{
public:
  const char * what() const noexcept override;
};

class ModelDuplicateKeyException : public ModelException
{
public:
  const char * what() const noexcept override;
};

class ModelArticleNotFoundException : public ModelException
{
public:
  const char * what() const noexcept override;
};

#endif // MODELEXCEPTION_HPP
