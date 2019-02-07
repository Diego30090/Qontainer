#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>
#include <functional>
#include "ContainerException.hpp"

////////////////////////////////////////////////////////////////////////////////
// INTERFACCIA /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Forwarding
template <class T, class K>
class iterator;

// Container
template <class T, class K = std::string>
class Container
{
  friend class iterator<T, K>;
  
private:
  
  // Nodi nel bucket
  class node
  {
    friend class iterator<T, K>;
    
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

  // table
  static const unsigned int INIT_TABLE_LENGTH = 5;

  static const unsigned int INIT_TABLE_THRESHOLD = INIT_TABLE_LENGTH * 2;
  
  node **table;
  
  unsigned int tableLength;

  unsigned int tableThreshold;

  unsigned int tableSize;

  std::hash<K> keyHash;
  
  unsigned int getIndex(const K &) const;

  void checkResize();
  
  void resize();

public:
  
  Container();
  Container(const Container &);
  ~Container();

  // Container & operator=(const Container &); // DA FARE

  unsigned int size() const;

  bool empty() const;

  // bool operator==(const Container &) const; // DA FARE

  T & get(const K &) const;

  void put(const K &, const T &);

  void remove(const K &);

  class iterator
  {
    friend class Container<T, K>;
    
  private:
    Container<T, K> const * const ref;
    node ** itArray;
    unsigned int const itArrayLength;
    unsigned int itPos;
    bool end;
    
  public:
    iterator(Container<T, K> const *);
    iterator(const iterator &);
    ~iterator();
    
    T & operator*();
    T * operator->();
    
    K getKey();
    bool isEnd();
    iterator & operator++();
    iterator operator++(int);
    bool operator==(const iterator &);
    bool operator!=(const iterator &);
  };

  // Metodi per la gestione degli iteratori
  iterator begin() const;

  //iterator end();

  //class const_iterator //DA FARE  
};

////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTAZIONI /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// IMPLEMENTAZIONE BUCKET
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

// IMPLEMENTAZIONE TABLE
template <class T, class K>
unsigned int Container<T, K>::getIndex(const K &k) const
{
  return keyHash(k) % tableLength;
}

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
  for (unsigned int i = 0; i < tableSize; ++i)
    destroy(table[i]);

  delete[] table;
}

// template <class T, class K>
// bool Container<T, K>::operator==(const Container &c) const
// {
//   //DA FARE
// }

// template <class T, class K>
// Container<T, K> & Container<T, K>::operator=(const Container &c)
// {
//   //DA FARE
// }

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
T & Container<T, K>::get(const K &k) const
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
  
  remove(tmp);
  tableSize--;
  //checkResize();
}

// IMPLEMENTAZIONE ITERATORI
template <class T, class K>
Container<T, K>::iterator::iterator(Container<T, K> const *c) : ref(c),
								itArray(new node*[c->tableSize]),
								itArrayLength(c->tableSize),
								itPos(0),
								end(false)
{
  if (c->empty())
    throw ContainerIteratorEmptyTableException();
  
  int j = 0;
  for (unsigned int i = 0; i < c->tableLength; ++i)
    {
      node *tmp = c->table[i];
      while (tmp)
	{
	  itArray[j++] = tmp;
	  tmp = tmp->next;
	}
    }
}

template <class T, class K>
Container<T, K>::iterator::iterator(const Container<T, K>::iterator &it) :
  ref(it.ref),
  itArray(new node*[it.itArrayLength]),
  itArrayLength(it.itArrayLength),
  itPos(it.itPos),
  end(it.end)
{
  for (unsigned int i = 0; i < itArrayLength; ++i)
    itArray[i] = it.itArray[i];
}

template <class T, class K>
Container<T, K>::iterator::~iterator()
{
  delete[] itArray;
}

template <class T, class K>
T & Container<T, K>::iterator::operator*()
{
  return itArray[itPos]->info;
}

template <class T, class K>
T * Container<T, K>::iterator::operator->()
{
  return &(itArray[itPos]->info);
}

template <class T, class K>
K Container<T, K>::iterator::getKey()
{
  return itArray[itPos]->key;
}

template <class T, class K>
bool Container<T, K>::iterator::isEnd()
{
  return end;
}

template <class T, class K>
typename Container<T, K>::iterator & Container<T, K>::iterator::operator++()
{  
  if (++itPos >= itArrayLength)
    end = true;

  return *this;
}

template <class T, class K>
typename Container<T, K>::iterator Container<T, K>::iterator::operator++(int)
{
  auto tmp(*this);
  operator++();
  return tmp;
}

template <class T, class K>
bool Container<T, K>::iterator::operator==(const Container<T, K>::iterator &i)
{
  return ref == i.ref && itPos == i.itPos;
}

template <class T, class K>
bool Container<T, K>::iterator::operator!=(const Container<T, K>::iterator &i)
{
  return !operator==(i);
}

template <class T, class K>
typename Container<T, K>::iterator Container<T, K>::begin() const
{
  return iterator(this);
}

#endif // CONTAINER_HPP
