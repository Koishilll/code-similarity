// ˫������, ���� std::list

export module util.mylist;


// ����������, ������
template <typename val_t>
class _list_node {
public:
    _list_node<val_t> *_next;
    _list_node<val_t> *_prev;
    val_t data;
};


// ������, ������
template <typename val_t>
class _iterator {
public:
    using iterator = _iterator<val_t>;

    _iterator(_list_node<val_t> *_n) : _now(_n) {};

    val_t &operator*() {
        return _now->data;
    }

    iterator &operator++() {
        _now = _now->_next;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        _now = _now->_next;
        return temp;
    }

    iterator &operator--() {
        _now = _now->_prev;
        return *this;
    }

    iterator operator--(int) {
        iterator temp = *this;
        _now = _now->_prev;
        return temp;
    }

    iterator destroy() {
        node_t *next = _now->_next;
        node_t *prev = _now->_prev;
        prev->_next = next;
        next->_prev = prev;
        if constexpr (is_class<val_t>::value) {
            ~_now->data;
        }
        _now = next;
        return *this;
    }

private:
    using node_t = _list_node<val_t>;
    node_t *_now;
};


// ��������
export
template <typename val_t>
class mylist {
public:
    using iterator = _iterator<val_t>;

    mylist() {
        _head = new node_t;
        _head->next = _head->prev = _head;
        _size = 0;
    }

    ~mylist() {
        auto next_it = begin();
        while (next_it != end()) {
            auto now_it = next_it++;
            now_it.destroy();
        }
    }


    /**
     * @brief ��β��֮�����һ��Ԫ��
     * @param value
     */
    void push_back(val_t value) {
        // TODO: push_back
    }


    /**
     * @brief ��ͷ��ǰ�����һ��Ԫ��
     * @param value
     */
    void push_front(val_t value);

    /**
     * @brief ɾ��β��Ԫ��
     */
    void pop_back();

    /**
     * @brief ɾ��ͷ��Ԫ��
     */
    void pop_front();

    /**
     * @brief ɾ��������ָ���Ԫ��, �������Ԫ�صĵ�����
     * @param pointer
     * @return iterator ���Ԫ�صĵ�����
     */
    iterator erase(iterator pointer) {
        return pointer.destroy();
    }


    /**
     * @brief ���ͷ��������
     * @return iterator
     */
    iterator begin() {
        return _head->next;
    }


    /**
     * @brief ���β�������
     * @return iterator
     */
    iterator end() {
        return _head;
    }


    /**
     * @brief ����Ԫ�ظ���
     * @return size_t
     */
    size_t size() {
        return _size;
    }


    // Ϊ�˷������, ��ֹ����
    mylist<val_t> &operator=(mylist<val_t>) = delete;
    // Ϊ�˷������, ��ֹ����
    mylist<val_t> &operator=(const mylist<val_t> &) = delete;
    // Ϊ�˷������, ��ֹ����
    mylist<val_t> &operator=(mylist<val_t> &&) = delete;


private:
    using node_t = _list_node<val_t>;
    node_t *_head;
    size_t _size;
    // void _enlarge(size_t new_cap);
};



// template <typename val_t>
// _iterator<val_t>::_iterator(_list_node<val_t> *_n) : _now(_n) {};


// template <typename val_t>
// val_t &_iterator<val_t>::operator*() {
//     return _now->data;
// }

// template <typename val_t>
// _iterator<val_t> &_iterator<val_t>::operator++() {
//     _now = _now->_next;
//     return *this;
// }

// template <typename val_t>
// _iterator<val_t> _iterator<val_t>::operator++(int) {
//     _iterator<val_t> temp = *this;
//     _now = _now->_next;
//     return temp;
// }

// template <typename val_t>
// _iterator<val_t> &_iterator<val_t>::operator--() {
//     _now = _now->_prev;
//     return *this;
// }

// template <typename val_t>
// _iterator<val_t> _iterator<val_t>::operator--(int) {
//     _iterator<val_t> temp = *this;
//     _now = _now->_prev;
//     return temp;
// }



// template <typename val_t>
// mylist<val_t>::mylist() {
//     _head = new _list_node<val_t>;
//     _head->next = _head->prev = _head;
// }

// template <typename val_t>
// mylist<val_t>::~mylist() {
//     // TODO: delete
// }

// template <typename val_t>
// _iterator<val_t> *mylist<val_t>::begin() {
//     return _head->next;
// }

// template <typename val_t>
// _iterator<val_t> *mylist<val_t>::end() {
//     return _head;
// }
