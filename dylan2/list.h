/*
 +------------------------------------------------------------------
 | FILENAME  : list.h
 | DATE      :
 |
 | ABSTRACT  : template definitie van een lijst
 |             De verschillende lijst operaties zijn :    
 |             -) create
 |             -) delete v.e element
 |             -) append v.e. element
 |             -) update v.e. element
 |             -) copie v.e. lijst
 |             -) opvragen v.e. element
 |             -) doorlopen v.e. lijst
 |             -) zoeken v.e. element
 |             -) bijelkaar voegen van lijsten
 | CHANGES   :
 +------------------------------------------------------------------
*/
#ifndef _LIST
#define _LIST

#include <stdio.h>

template <class T>
class List : public gc
{
   private :
       struct Node 
       {
          T  Item ;
          Node *prev ;
          Node *next ;
       } ;
       Node *InternalList ;
       int   ItemCount ;
       int   CurrPos ;
   public :
       List() ;
       ~List() ;
       List( const List &L ) ;
       void Dump() ;
       List<T>& operator=( const List<T> &L) ;
       void AppendItem( T item ) ;
       void UpdateItem( T item ) ;
       T GetItem() { return InternalList->Item ; }
       void NextItem() ;
       void PrevItem() ;
       void MoveTo(int Pos) ;
       void Delete() ;
       int GetSize( ) { return ItemCount ; }
       int SearchItem( int (*g)( T item, T item2 ), T x ) ;
       void Reset() ;
       void PrintList() ;
       void Join( const List<T> *L ) ;
} ;

template <class T>
List<T>::List()
{
  InternalList = new (GC) Node  ;
  InternalList->prev = NULL ;
  InternalList->next = NULL ;
  ItemCount = 0 ;
  CurrPos = 0 ;
}

template <class T>
List<T>::~List()
{
  T Object ;

  if ( ItemCount == 0 ) return ;
  MoveTo( ItemCount ) ;

  while ( InternalList->prev != NULL )
  {
     Object = InternalList->Item ;
     InternalList = InternalList->prev ;
     delete Object ;
  }
  //delete InternalList ;
}

template <class T>
void List<T>::Reset()
{
  Node *Object ;

  while ( InternalList->next != NULL )
  {
     InternalList = InternalList->next ;
  }

  while ( InternalList->prev != NULL )
  {
     Object = InternalList ;
     InternalList = InternalList->prev ;
     delete Object ;
  }
  ItemCount = 0 ;
  CurrPos   = 0 ;
  //delete InternalList ;
}

template <class T>
void List<T>::AppendItem( T item )
{
   Node *Object ;

   while ( InternalList->next != NULL )
   {
      InternalList = InternalList->next ;
   }

   Object = new (GC) Node ;
   Object->next = NULL ;
   Object->prev = NULL ;
   InternalList->next = Object ;
   Object->prev = InternalList ;
   Object->Item = item ;
   InternalList = Object ;
   ItemCount++ ;
   CurrPos = ItemCount ;
} ;

template <class T>
void List<T>::Delete( )
{
   Node *Object ;

   Object = InternalList ;

   if ( InternalList->prev != NULL )
   {
       InternalList->prev->next = InternalList->next ;
       InternalList->Item = InternalList->prev->Item ;
   }
   if ( InternalList->next != NULL )
   {
       InternalList->next->prev = InternalList->prev ;
       InternalList = InternalList->next ;
   }
   else
   {
       InternalList = InternalList->prev ;
   }
   // delete Object ;
   ItemCount-- ;
   if ( CurrPos > ItemCount ) CurrPos = ItemCount ;
}

template <class T>
void List<T>::UpdateItem( T item )
{
   InternalList->Item = item ;
} ;

template <class T>
void List<T>::PrevItem()
{
   if ( InternalList->prev != NULL )
   {
       InternalList = InternalList->prev ;
       CurrPos-- ;
   }
}

template <class T>
void List<T>::NextItem()
{
   if ( InternalList->next != NULL )
   {
       InternalList = InternalList->next ;
       CurrPos++ ;
   }
}

template <class T>
void List<T>::MoveTo(int Pos)
{
   if ( Pos == CurrPos ) return ;

   if ( CurrPos < Pos )
   {
      while ( CurrPos != Pos ) NextItem() ;
   }
   else
   {
      while ( CurrPos != Pos ) PrevItem() ;
   }
}

template <class T>
int List<T>::SearchItem(int (*g)(T item, T item2), T x )
{
   int i ;

   for ( i = ItemCount; i >= 1; i-- )
   {
      MoveTo(i) ;
      if ( g( InternalList->Item, x ) ) return i ;
   }
   return -1 ;
}

template <class T>
List<T>& List<T>::operator =( const List<T> &L)
{
  int i ;
  Node *Object ;

  if ( this == &L ) return *this ;
  Object = L.InternalList ;
  while ( Object->prev != NULL )
  {
    Object = Object->prev ;
  }

  for( i = 1; i <= L.ItemCount; i++ )
  {
    Object = Object->next ;
    this->AppendItem( Object->Item ) ;
  } 
  return *this ;
}

template <class T>
List<T>::List( const List<T> &L)
{
  int i ;
  Node *Object ;

  this->InternalList = new (GC) Node  ;
  this->InternalList->prev = NULL ;
  this->InternalList->next = NULL ;
  this->ItemCount = 0 ;
  this->CurrPos   = 0 ;
  Object = L.InternalList ;
  while( Object->prev != NULL )
  {
     Object = Object->prev ;
  }

  for( i = 1; i <= L.ItemCount; i++ )
  {
    Object = Object->next ; 
    this->AppendItem( Object->Item ) ;
  } 
  while( Object->prev != NULL )
  {
     Object = Object->prev ;
  }
}

template <class T>
void List<T>::Dump()
{
   int i ;
   printf ( "ItemCount = %d, %d\n", ItemCount, CurrPos ) ;
   for ( i = 1; i <= ItemCount; i++ )
   {
      MoveTo(i) ;
      printf( "<%x> <%x> <%x> <%x>\n", InternalList, InternalList->Item, InternalList->prev, InternalList->next ) ;
   }
}

template <class T>
void List<T>::PrintList()
{
   int i ;
   int x ;
   x = 0 ;
   if ( ItemCount > 1 ) printf( "#( " ) ;
   for ( i = 1; i <= ItemCount; i++ )
   {
      MoveTo(i) ;
      InternalList->Item->Print(&x) ;
      if ( i < ItemCount ) printf( ", ") ;
   }
   if ( ItemCount > 1 ) printf( " )" ) ;
}

template <class T>
void List<T>::Join( const List<T> *L)
{
  Node *Object ;

  while ( InternalList->next != NULL )
  {
     InternalList = InternalList->next ;
  }

  Object = L->InternalList ;

  while ( Object->prev != NULL )
  {
    Object = Object->prev ;
  }
  Object = Object->next ;

  Object->prev = InternalList ;
  InternalList->next = Object ;
  ItemCount += L->ItemCount  ;
}
#endif
