#ifndef NODE_H
#define NODE_H

struct Node
{
    int i, j;
    double F, g, H;
    Node *parent;
    int parent_i, parent_j;

    bool operator==(const Node & other) {
        return i == other.i && j == other.j;
    }

    friend bool operator<(const Node & a, const Node & b) {
        if(a.i == b.i) return a.j < b.j;
        return a.i < b.i;
    }
};

#endif
