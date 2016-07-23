#ifndef ORDEREDVECTOR_H
#define ORDEREDVECTOR_H

#include <vector>

template <typename T, typename Cmp_type>
class OrderedVector
{
private:
    std::vector<T> _data;
    Cmp_type _cmp;

    void sift_down() {
        int i = _data.size() - 1;
        T temp;
        while (i > 0) {
            if ((*_cmp)(_data[i], _data[i - 1])) return;
            temp = _data[i];
            _data[i] = _data[i - 1];
            _data[i - 1] = temp;
            i--;
        }
    }

public:
    OrderedVector(Cmp_type cmp) {
        _data.resize(0);
        _cmp = cmp;
    }

    void push(T element) {
        _data.push_back(element);
        sift_down();
    }

    T top() {
        return _data[_data.size() - 1];
    }

    T pop() {
        T return_value = _data[_data.size() - 1];
        _data.resize(_data.size() - 1);

        return return_value;
    }

    bool empty() {
        return _data.empty();
    }

    int size() {
        return _data.size();
    }

    bool find(const T & element) {
        int lo = 0,
            hi = _data.size(),
            mid;

        while (hi - lo > 1) {
            mid = (hi + lo) / 2;
            if (_data[mid] > element) hi = mid;
            else                      lo = mid;
        }

        return (_data[lo] == element);
    }
};

#endif // ORDEREDVECTOR_H
