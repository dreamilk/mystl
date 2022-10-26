#include "mystl_vector.h"
#include <bits/stdc++.h>

using namespace mystl;

struct Node
{
    int key;
    int value;
    Node(int k = 0, int v = 0) : key(k), value(v) {}
};

struct LinkNode
{
    LinkNode *next;
    int val;
    LinkNode(int v, LinkNode *nx = nullptr) : val(v), next(nx) {}
};

int main()
{
    vector<Node> v(5);
    for (int i = 0; i < 3; ++i)
    {
        v[i] = Node(i, 2 * i);
    }
    v.push_back(Node(10, 11));
    std::cout << "capacity:" << v.capacity() << std::endl;
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i].key << "-" << v[i].value << std::endl;
    }
    std::vector<LinkNode> vn(10);
    return 0;
}