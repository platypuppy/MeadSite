////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // ostream

namespace CS170
{

  class List
  {
    public:
        // Three constructors
        // Destructor
        
        // Seven methods:
        //   push_front, adds the item to the front of the list
        //   push_back, adds the item to the end of the list
        //   pop_front, removes the first item in the list
        //   front, returns the first item in the list
        //   size, returns the number of items in the list
        //   empty, returns true if empty, else false
        //   clear, clears the list (removes all of the nodes)

        // Five operators: 
        //   operator=
        //   operator+=
        //   operator+
        //   operator[] (2 of these)

        // Output operator for printing lists (<<)
      friend std::ostream & operator<<(std::ostream & os, const List &list);

        // Returns the number of Lists that have been created
      static int list_count();

        // Returns the number of Nodes that are still alive
      static int node_count();

    private:

        // used to build a linked list of integers
      struct Node
      {
        Node(int);              // constructor
        ~Node();                // destructor
        Node *next;             // pointer to the next Node
        int data;               // the actual data in the node
        static int nodes_alive; // count of nodes still allocated
      };

      Node *head_; // pointer to the head of the list
      Node *tail_; // pointer to the last node
      int size_;   // number of items on the list

      static int list_count_;         // number of Lists created
      Node *new_node(int data) const; // allocate node, initialize data/next
  };

} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
