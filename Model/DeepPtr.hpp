#ifndef DEEPPTR_HPP
#define DEEPPTR_HPP

/* Contratto:
 * DeepPtr<T> e' un wrapper di T* che estende il concetto di puntatore
 * a T aggiungendo funzionalita' quali costruzione di copia profonda,
 * assegnazione profonda e distruzione profonda a tipi di dato T
 * user-defined che mettano a disposizione un metodo clone() di
 * clonazione polimorfa e distruzione polimorfa
 */

////////////////////////////////////////////////////////////////////////////////
// INTERFACCIA /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T>
class DeepPtr
{
private:
  T *p;

public:
  DeepPtr(T *);
  DeepPtr(const T *);
  DeepPtr(const DeepPtr &);
  DeepPtr(const T &);
  virtual ~DeepPtr();
  
  DeepPtr & operator=(const DeepPtr &);

  const T & operator*() const;
  T & operator*();

  const T * operator->() const;
  T * operator->();

  const T * operator&() const;
  T * operator&();

  bool operator==(const DeepPtr &) const;
  bool operator!=(const DeepPtr &) const;
};
  

////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTAZIONE /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T>
DeepPtr<T>::DeepPtr(T *punt) : p(punt ? punt->clone() : nullptr) {}

template <class T>
DeepPtr<T>::DeepPtr(const T *punt) : DeepPtr(const_cast<T *>(punt)) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr &dp) : p(dp.p ? dp.p->clone() : nullptr) {}

template <class T>
DeepPtr<T>::DeepPtr(const T &a) : p(a.clone()) {}

template <class T>
DeepPtr<T>::~DeepPtr()
{
  delete p;
}

template <class T>
DeepPtr<T> & DeepPtr<T>::operator=(const DeepPtr &dp)
{
  if (*this != dp)
    {
      delete p;
      p = dp.p ? dp.p->clone() : nullptr;
    }

  return *this;
}

template <class T>
const T & DeepPtr<T>::operator*() const
{
  return *p;
}

template <class T>
T & DeepPtr<T>::operator*()
{
  return *p;
}

template <class T>
const T * DeepPtr<T>::operator->() const
{
  return const_cast<const T * const>(p);
}

template <class T>
T * DeepPtr<T>::operator->()
{
  return p;
}

template <class T>
const T * DeepPtr<T>::operator&() const
{
  return const_cast<const T * const>(p);
}

template <class T>
T * DeepPtr<T>::operator&()
{
  return p;
}

template <class T>
bool DeepPtr<T>::operator==(const DeepPtr &dp) const
{
  return p == dp.p;
}

template <class T>
bool DeepPtr<T>::operator!=(const DeepPtr &dp) const
{
  return !operator==(dp);
}

#endif // DEEPPTR_HPP
