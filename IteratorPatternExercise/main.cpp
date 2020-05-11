
//
//   Iterator Coding Exercise
//
//      Given the following definition of a Node<T>, please implement preorder traversal that returns a sequence of Ts. I have greatly simplified the
//      problem by adding an accumulator argument into the preorder_traversal() function.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
struct Node
{
    T value;
    Node *left{nullptr}, *right{nullptr}, *parent{nullptr};

    Node(T value) : value(value) {}

    Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right) {
      left->parent = right->parent = this;
    }

    // traverse the node and its children preorder
    // and put all the results into `result`
    void preorder_traversal(vector<Node<T>*>& result)
    {
        for(auto it = this->begin(); it != this->end(); ++it)
        {
            result.push_back(&(*it));
        }
    }

    class Iterator
    {
    public:
        Iterator(Node<T>* current)
        : current{current}
        {
        }

        bool operator!=(const Iterator& rhs) const
        {
            return current != rhs.current;
        }

        Iterator& operator++()
        {
            Node<T>* p = current->parent;
            if(current->left)
            {
                current = current->left;
            }
            else if(current->right)
            {
                current = current->right;
            }
            else
            {
                while(p && (!p->right || current == p->right))
                {
                    current = p;
                    p = current->parent;
                }
                if(p)
                {
                    current = p->right;
                }
                else
                {
                    current = nullptr;
                }
            }
            
            return *this;
        }

        Iterator& operator+=(int rhs)
        {
           while(rhs != 0)
           {
               this->operator++();
               --rhs;
           }
           return *this;
        }

        Iterator operator+(const int rhs)
        {
           *this += rhs;
           return *this;
        }

        Node<T>& operator*()
        {
            return *current;
        }
    private:
        Node<T>* current;
    };

    Iterator begin()
    {
        Node<T>* n = this;
        if(n)
        {
            while(n->parent)
            {
                n = n->parent;
            }
        }
        return Iterator{n};
    }

    Iterator end()
    {
        return Iterator{nullptr};
    }
};

int main(int argc, char* argv[])
{
        Node<char> c{'c'};
      Node<char> d{'d'};
      Node<char> e{'e'};
      Node<char> b{'b', &c, &d};
      Node<char> a{'a', &b, &e};

      vector<Node<char>*> results;
      a.preorder_traversal(results);
    cout << results.size() << endl;
    for(auto result : results)
    {
        cout << result->value << endl;
    }

    return 0;
}
