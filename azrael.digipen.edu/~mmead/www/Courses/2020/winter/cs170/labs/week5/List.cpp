#include <iostream> // cout, endl
#include "List.h"

/*******************************************************************/
/*******************************************************************/
namespace CS170
{
  namespace ListLab
  {
    List::List()
    {
      head_ = 0;
    }

    Node* List::MakeNode(int value) const
    {
        // The Node constructor sets the value, and sets next to 0.
      return new Node(value);
    }

    void List::PrintList() const
    {
      Node *list = head_;
      while (list)
      {
        std::cout << list->number << "   ";
        list = list->next;
      }
      std::cout << std::endl;
    }
  }
}
