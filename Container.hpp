#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>
#include <functional>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
// INTERFACCIA /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Eccezioni lanciabili da Container
class ContainerException : public std::exception
{
public:
  virtual const char * what() const noexcept;
};

class ContainerCellNotFoundException : public ContainerException
{
public:
  virtual const char * what() const noexcept;
};

class ContainerDuplicateKeyException : public ContainerException
{
public:
  virtual const char * what() const noexcept;
};

template <class T, class K>
class cIterator; // forwarding

// CONTAINER
template <class T, class K = std::string>
class Container
{
  friend class cIterator<T, K>;
  
private:
  // Nodi nel bucket
  class node
  {
    friend class cIterator<T, K>;
    
  public:
    K key;
    T info;
    node *next;

    node(const K &, const T &, node * = nullptr);
  };

  // Metodi per la gestione dei bucket
  static void destroy(node *&);
  static node * search(node *, const K &);
  static void insert(node *&, const K &, const T &);
  static void remove(node *&);
  static node * copy(node *);

  // TABLE
  static const unsigned int INIT_TABLE_LENGTH = 5;

  static const unsigned int INIT_TABLE_THRESHOLD = INIT_TABLE_LENGTH * 3;
  
  node **table;
  
  unsigned int tableLength;

  unsigned int tableThreshold;

  unsigned int tableSize;

  std::hash<K> keyHash;
  
  unsigned int getIndex(const K &);

  void checkResize();
  
  void resize();
  
public:
  
  Container();
  Container(const Container &);
  ~Container();

  Container & operator=(const Container &); // DA FARE

  unsigned int size() const;

  bool empty() const;

  bool operator==(const Container &) const; // DA FARE

  T & get(const K &);

  // const T & get(cost K &) const;
  
  void put(const K &, const T &);

  void remove(const K &);

  cIterator<T, K> begin();

  cIterator<T, K> end();

  //class const_iterator //DA FARE  
};

template <class T, class K>
class cIterator
{
private:
  node *p;
  unsigned int tablePos;
    
public:
  cIterator();
  cIterator(node *);
  cIterator(const cIterator &);
  cIterator(const Container<T, K> &);
    
  T & operator*();
  cIterator & operator++();
  cIterator operator++(int);
  bool operator==(const cIterator &);
  bool operator!=(const cIterator &);
};

////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTAZIONI /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// IMPLEMENTAZIONI BUCKET
template <class T, class K>
Container<T, K>::node::node(const K &k, const T &obj, node *n) : key(k), info(obj), next(n) {}

template <class T, class K>
void Container<T, K>::destroy(node *&n)
{
  if (!n) return;
  
  if (n->next) destroy(n->next);

  delete n;

  n = nullptr;
}

template <class T, class K>
typename Container<T, K>::node * Container<T, K>::search(node *n, const K &k)
{
  if (!n) return nullptr;
  
  if (n->key == k)
    return n;
  else
    return search(n->next, k);
}

template <class T, class K>
void Container<T, K>::insert(node *&n, const K &k, const T &obj)
{
  if (!n)
    n = new node(k, obj);
  else
    n = new node(k, obj, n);
}

template <class T, class K>
void Container<T, K>::remove(node *&n)
{
  if (!n) return;

  node *tmp = n->next;
  delete n;
  n = tmp;
}

template <class T, class K>
typename Container<T, K>::node * Container<T, K>::copy(node *n)
{
  if (!n) return nullptr;

  return new node(n->key, n->info, copy(n->next));
}

// IMPLEMENTAZIONI TABLE
template <class T, class K>
Container<T, K>::Container() : table(new node*[INIT_TABLE_LENGTH]),
			       tableLength(INIT_TABLE_LENGTH),
			       tableThreshold(INIT_TABLE_THRESHOLD),
			       tableSize(0)
{
  for (unsigned int i = 0; i < tableLength; ++i)
    table[i] = nullptr;
}

template <class T, class K>
Container<T, K>::Container(const Container &c) : table(new node*[c.tableLength]),
						 tableLength(c.tableLength),
						 tableThreshold(c.tableThreshold),
						 tableSize(c.tableSize)
{
  for (unsigned int i = 0; i < tableSize; ++i)
    table[i] = copy(c.table[i]);
}

template <class T, class K>
Container<T, K>::~Container()
{
  for (int i = 0; i < tableSize; ++i)
    destroy(table[i]);

  delete[] table;
}

template <class T, class K>
bool Container<T, K>::operator==(const Container &) const
{
  //DA FARE
}

template <class T, class K>
Container<T, K> & Container<T, K>::operator=(const Container &)
{
  //DA FARE
}

template <class T, class K>
unsigned int Container<T, K>::size() const
{
  return tableSize;
}

template <class T, class K>
bool Container<T, K>::empty() const
{
  return tableSize == 0;
}

template <class T, class K>
unsigned int Container<T, K>::getIndex(const K &k)
{
  return keyHash(k) % tableLength;
}

template <class T, class K>
T & Container<T, K>::get(const K &k)
// THROWS: ContainerCellNotFoundException
{
  //unsigned long h = keyHash(k);
  //int i = getIndex(k);

  node *tmp = search(table[getIndex(k)], k);

  if (!tmp) throw ContainerCellNotFoundException();

  return tmp->info;
}

template <class T, class K>
void Container<T, K>::put(const K &k, const T &obj)
// THROWS: ContainerDuplicateKeyExeption
{
  //unsigned long h = keyHash(k);
  //int i = getIndex(k);

  if(search(table[getIndex(k)], k)) throw ContainerDuplicateKeyException();
  
  insert(table[getIndex(k)], k, obj);
  tableSize++;
  //checkResize();
}

template <class T, class K>
void Container<T, K>::remove(const K &k)
{
  node *tmp = search(table[getIndex(k)], k);

  if (!tmp) throw ContainerCellNotFoundException();
  
  remove(tmp, k);
  tableSize--;
  //checkResize();
}

// IMPLEMENTAZIONE ECCEZIONI
const char* ContainerException::what() const noexcept
{
  return "Errore sconosciuto Container";
}

const char* ContainerCellNotFoundException::what() const noexcept
{
  return "Nessuna voce trovata con la chiave inserita";
}

const char* ContainerDuplicateKeyException::what() const noexcept
{
  return "Inserimento di una chiave duplicata";
}

// IMPLEMENTAZIONE ITERATORI
// template <class T, class K>
// Container<T, K>::iterator::iterator() : p(table[0]) {}

// template <class T, class K>
// T & Container<T, K>::iterator::operator*()
// {
//   return p->info;
// }

// template <class T, class K>
// bool Container<T, K>::iterator::operator==(const Container<T, K>::iterator &i)
// {
//   return p == i.p;
// }


#endif // CONTAINER_HPP
