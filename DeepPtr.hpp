#ifndef DEEPPTR_HPP
#define DEEPPTR_HPP

/* Contratto:
 * Si assume che il tipo T abbia un metodo T * clone();
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
  DeepPtr();
  DeepPtr(T *);
  DeepPtr(const DeepPtr &);
  ~DeepPtr();
  
  DeepPtr & operator=(const DeepPtr &);
  T & operator*() const;
  T * operator->() const;

  bool operator==(const DeepPtr &) const; // se punta allo stesso T
  bool operator!=(const DeepPtr &) const;
};
  

////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTAZIONE /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T>
DeepPtr<T>::DeepPtr() : p(nullptr) {}

template <class T>
DeepPtr<T>::DeepPtr(T *punt) : p(punt ? punt->clone() : nullptr) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr &dp) : p(dp.p ? dp.p->clone() : nullptr) {}

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
      p(dp.p ? dp.p->clone() : nullptr);
    }

  return *this;
}

template <class T>
T & DeepPtr<T>::operator*() const
{
  return *p;
}

template <class T>
T * DeepPtr<T>::operator->() const
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
};

#endif // DEEPPTR_HPP
