////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{
  namespace ListLab
  {
    struct Node
    {
      int number;             // data portion
      Node *next;             // pointer portion

        // Conversion constructor
      Node(int value)
      {
        number = value;
        next = 0;
      }
    };

    class List
    {
      public:

          // Default constructor
        List();

          // Destructor
        ~List();

          // Adds a node to the front of the list
        void AddToEnd(int value);

          // Adds a node to the end of the list
        void AddToFront(int value);

          // Returns the number of nodes in the list
        int Count() const;

          // Finds an item and returns the node that contains it
        Node *FindItem(int value) const;

          // Inserts a new node at the specified position
        void Insert(int value, int position);

          // Deletes a node with the specified value (first occurrence)
        void Delete(int value);

          // Concatenates two lists
        void Concat(const List& Source);

          // Deletes all of the values in ppList that are it Items
        void Delete(const List& Items);

          // Inserts a new node in the correct position (sorted small to large)
        void Insert(int value);

          // Takes a sorted list and merges the items into the correct locations
          // The lhs (*this) must also be sorted. The rhs list is empty 
          // afterwards.
        void Merge(List& rhs);

          // Takes a sorted list and removes all of the duplicates. In other 
          // words, it removes all but the first element in every consecutive
          // group of equal elements. Returns number of elements that were 
          // removed.
        int RemoveDuplicates();

          // Displays the list
        friend std::ostream& operator<<(std::ostream &os, const List& list);

      private:
        Node *head_;
        Node* MakeNode(int value) const;

          // Other private methods you may need

    };
  } // namespace ListLab
} // namespace CS170
#endif // LIST_H

