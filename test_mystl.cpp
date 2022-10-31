#include "mystl_vector.hpp"
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
        key = rhs.key;
        value = rhs.value;
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
    // vector<Node *> v(3);
    std::vector<Node *> v(3);
    for (int i = 0; i < 3; ++i)
    {
        v[i] = new Node(i, 2 * i);
    }
    std::cout << "-" << std::endl;
    // v.emplace_back(10, 20);
    // std::sort(v.begin(), v.end(), [](const Node &a, const Node &b)
    //           { return a.key > b.key; });
    // v.push_back(Node(10, 11));
    std::cout << "size:" << v.size() << " capacity:" << v.capacity() << std::endl;
    for (auto &n : v)
    {
        std::cout << n->key << "-" << n->value << std::endl;
    }
    std::cout << typeid(v).name() << std::endl;
    return 0;
}