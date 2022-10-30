#include "mystl_vector.hpp"
#include <bits/stdc++.h>

using namespace mystl;

struct Node
{
    int key;
    int value;
    Node(int k = 0, int v = 0) : key(k), value(v) {}
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
    int sum = std::count_if(v.begin(), v.end(), [](const Node &node)
                            {
        if(node.key==0) return true;
        return false; });
    std::cout << "count: " << sum << std::endl;
    return 0;
}