namespace CS170
{

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// static members

template <typename T>
int List<T>::Node::nodes_alive = 0;

template <typename T>
int List<T>::node_count(void)
{
  return Node::nodes_alive;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// List::Node methods
template <typename T>
List<T>::Node::Node(T value) : data(value)
{
  nodes_alive++;
}

template <typename T>
List<T>::Node::~Node()
{
  nodes_alive--;
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// public methods

/////////////////////////////////////////////////////////////////////////
// Function: List::clear
//  Purpose: Removes all of the nodes in the list.
//   Inputs: None
//  Outputs: None
/////////////////////////////////////////////////////////////////////////
template <typename T>
void List<T>::clear()
{
  while (!empty())
    pop_front();
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// private methods

/////////////////////////////////////////////////////////////////////////
// Function: new_node
//  Purpose: Allocate a node, initialize the data and next pointer
//   Inputs: data - the data to put in the node
//  Outputs: A pointer to the node
/////////////////////////////////////////////////////////////////////////
template <typename T>
typename List<T>::Node *List<T>::new_node(const T& data) const
{
  Node *node = new Node(data); // create the node
  node->next = 0;              // no next pointer yet
  
  return node;
}

} // namespace CS170


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// non-members

#include <iomanip>

/*!**********************************************************************
  Outputs all of the data in a list to an output stream.

  \param os
    The stream to output the list to.

  \param list
    The list to output to the stream.

  \return
    The ouput stream (ref) that was passed in (for chaining)
************************************************************************/
template <typename T>
std::ostream &CS170::operator<<(std::ostream & os, const CS170::List<T> &list)
{
    // Start at the beginning
  typename CS170::List<T>::Node *pnode = list.head_;

    // Print each item
  while (pnode != 0)
  {
    os << std::setw(4) << pnode->data;
    pnode = pnode->next;
  }
  os << std::endl;
  
  return os;
}

