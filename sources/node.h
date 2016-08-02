#ifndef NODE_H
#define NODE_H

struct Node
{
    int i, j;
    double F, g, H;
    const Node *parent = nullptr;
    Node(){}
    Node(int i, int j){this->i=i;this->j=j;}

    friend bool operator==(const Node & a, const Node & b) {
        return a.i == b.i && a.j == b.j;
    }

    friend bool operator<(const Node & a, const Node & b) {
        if(a.i == b.i) return a.j < b.j;
        return a.i < b.i;
    }

    friend bool operator>(const Node & a, const Node & b) {
        if(a.i == b.i) return a.j > b.j;
        return a.i > b.i;
    }
};

#endif
