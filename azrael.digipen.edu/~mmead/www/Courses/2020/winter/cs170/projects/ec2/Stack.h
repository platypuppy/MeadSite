#include <string> // string (for exception message)
#include <list>   // The stack class is composed of a std::list

namespace CS170
{

class StackError
{
  public:
    StackError(const char *errmsg) : message_(errmsg) {};
    const char *what() const {return message_.c_str();};

  private:
    std::string message_;
};

class Stack
{
  public:
      // Default constructor. If maxsize is 0, maxsize is UINT_MAX (constant)
    Stack(size_t maxsize = 0);

      // Non-default constructor. Construct stack from array. (linear)
    Stack(int *array, size_t count);

      // Clears the stack, freeing the underlying memory (linear)
    void clear(); 

      // True if the stack is empty. (constant)
    bool empty() const;

      // Gets the maxsize value (constant)
    size_t get_maxsize() const;

      // Removes the value on the top of the stack (constant)
    void pop();

      // Pushes a value onto the top of the stack (constant)
    void push(int value);

      // Prints the stack, either vertically (default) or horizontally (linear)
    void print(bool vertical = true) const;

      // The number of items on the stack (constant)
    size_t size() const;

      // Swaps this stack with another (constant)
    void swap(Stack& rhs);

      // The value at the top of the stack. Does not remove it. (constant)
    int top() const;

  private:
    std::list<int> stack_; // Composition (aggregation, containment)
    size_t maxsize_;       // If we need to limit the size of the Stack
    size_t size_;          // std::list.size() is linear!!
};

} // namespace CS170
