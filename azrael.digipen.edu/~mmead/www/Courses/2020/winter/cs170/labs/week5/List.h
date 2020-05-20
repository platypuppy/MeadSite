////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

//! namespace CS170
namespace CS170
{
  //! namespace ListLab
  namespace ListLab
  {
    //! Node structure for List class
    struct Node
    {
      
      int number; //!< data portion
      Node *next; //!< pointer portion 

      /*!*******************************************************************
        Conversion constructor

        \param value
          The data for the node
      *********************************************************************/
      Node(int value)
      {
        number = value;
        next = 0;
      }
    };

    //! Single-linked list class for CS170 labs
    class List
    {
      public:
          // Default constructor
        List();

          // Destructor
        ~List();
        
        // Other public methods declarations here ...

      private:
        Node *head_;  //!< Pointer to the front of the list
        Node* MakeNode(int value) const;
        
        // Any other private helper methods you need...
    };
  } // namespace ListLab
} // namespace CS170

#endif // LIST_H
