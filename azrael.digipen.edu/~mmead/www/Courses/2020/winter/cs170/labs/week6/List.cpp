#include <iostream> // ostream
#include "List.h"

List::List()
{
  head_ = 0;
}

Node* List::MakeNode(int value) const
{
    // The Node constructor sets the value, 
    // and sets next to 0.
  return new Node(value);
}

std::ostream& operator<<(std::ostream &os, const List& rhs)
{
  // Use this line to print out each value in the list.
  // You will need to create a while loop here to walk
  // through all of the nodes.
  os << list->number << "   ";
}

int List::Count() const
{
  int count = 0;
  Node *list = head_;
  
  while (list)
  {
    count++;
    list = list->next;
  }
  
  return count;
}
