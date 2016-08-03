#ifndef OPENCONTAINER_H
#define OPENCONTAINER_H

#include <set>

template <typename T, typename Cmp_type>
class OpenContainer
{
private:
    std::set<T> _data;
    Cmp_type _cmp;

public:
    OpenContainer(Cmp_type cmp) {
        _cmp = cmp;
    }

    bool find(const T &el) {
        return (_data.find(el) != _data.end());
    }

    void push(T el) {
        auto it = _data.find(el);

        if (it == _data.end()) _data.insert(el);
    }

    T pop() {
        auto it = ++_data.begin();
        auto max_element_it = _data.begin();

        while (it != _data.end()) {
            if ((*_cmp)(*it, *max_element_it)) {
                max_element_it = it;
            }
            it++;
        }

        T max_element = *max_element_it;
        _data.erase(max_element_it);

        return max_element;
    }

    bool empty() {
        return _data.empty();
    }

    unsigned int size() {
        return _data.size();
    }
};

#endif // OPENCONTAINER_H
