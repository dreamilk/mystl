#include "mystl_vector.hpp"
#include "mystl_iterator.hpp"
#include "mystl_algorithm.hpp"
#include <bits/stdc++.h>

using namespace mystl;

struct Node
{
private:
    static int cn;
    static int dcn;

public:
    int key;
    int value;

    explicit Node()
    {
        std::cout << "construct():" << ++cn << std::endl;
        key = 0;
        value = 0;
    }
    explicit Node(int k, int v) : key(k), value(v)
    {
        std::cout << "construct():" << ++cn << std::endl;
    }

    Node(const Node &rhs)
    {
        std::cout << "copy construct():" << ++cn << std::endl;
        this->key = rhs.key;
        this->value = rhs.value;
    }

    Node(Node &&rhs)
    {
        std::cout << "move construct():" << ++cn << std::endl;
        key = rhs.key;
        value = rhs.value;
    }

    Node &operator=(const Node &rhs)
    {
        std::cout << "Node& operator=(const Node& rhs)" << std::endl;
        key = rhs.key;
        value = rhs.value;
        return *this;
    }

    bool operator==(const Node &rhs)
    {
        return rhs.key == key && rhs.value == value;
    }

    Node &operator=(Node &&rhs)
    {
        std::cout << "Node &operator=(Node &&rhs)" << std::endl;
        key = rhs.key;
        value = rhs.value;
        return *this;
    }

    ~Node()
    {
        std::cout << "deconstruct():" << ++dcn << std::endl;
    }
};

int Node::cn = 0;
int Node::dcn = 0;

int main()
{

    {
        std::cout << "std::vector<Node>" << std::endl;
        std::vector<Node> v;
        v.push_back(Node(1, 1));
    }
    {
        std::cout << "mystl::vector<Node>" << std::endl;
        mystl::vector<Node> v;
        v.push_back(Node(1, 1));
    }
    {
        std::cout << "test move" << std::endl;
        Node a = mystl::move(Node(1, 2));
    }
    // std::stack<Node, mystl::vector<Node>> st;
    // for (int i = 0; i < 3; ++i)
    // {
    //     st.push(Node(i, 2 * i));
    // }
    // std::cout << typeid(st).name() << std::endl;

    return 0;
}