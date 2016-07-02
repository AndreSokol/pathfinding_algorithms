#ifndef MINQUEUE_H
#define MINQUEUE_H

#include <vector>
#include "../utils.h"

typedef bool(*ComparatorType)(const Utils::CoordsContainer &, const Utils::CoordsContainer &);

template<ComparatorType _cmp>
class MinQueue
{
public:
    MinQueue(/*CmpType cmp*/)
    {
        //_cmp = cmp;
        _data.resize(0);
    }

    int size(){
        return _data.size();
    }

    void push(const Utils::CoordsContainer & new_element) {
        _data.push_back(new_element);
        sift_up(size() - 1);
    }

    Utils::CoordsContainer top() {
        return _data[0];
    }

    void pop() {
        _data[0] = _data[size() - 1];
        _data.resize(size() - 1);
        sift_down(0);
    }

    bool empty()
    {
        return _data.size() == 0;
    }
private:
    void swap_elements(int i, int j) {
        Utils::CoordsContainer temp = _data[i];
        _data[i] = _data[j];
        _data[j] = temp;
    }

    void sift_up(int x) {
        int i = x, parent;
        while(i > 0) {
            parent = (i - 1) / 2;
            if ((this->*_cmp)( _data[i], _data[parent] )) return;
            swap_elements(i, parent);
            i = parent;
        }
    }

    void sift_down(int x) {
        int i = x, biggest_son, right_son, left_son;
        while (2 * i + 1 < _data.size()) { // while there is at least one son
            left_son = 2 * i + 1;
            right_son = 2 * i + 2;

            biggest_son = left_son;
            if (right_son < _data.size() && (*_cmp)( _data[right_son], _data[left_son] )) {
                biggest_son = right_son;
            }

            //if ((*_cmp)[ _data(i) ], _data[biggest_son] )) return;

            swap_elements(i, biggest_son);
            i = biggest_son;
        }
    }

    //CmpType _cmp;
    std::vector<Utils::CoordsContainer> _data;
};


#endif // MINQUEUE_H
