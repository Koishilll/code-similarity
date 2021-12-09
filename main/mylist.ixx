// 双向链表, 仿制 std::list

export module util.mylist;


// 链表结点类型, 不导出
template <typename val_t>
class _list_node {
public:
    _list_node<val_t> *_next;
    _list_node<val_t> *_prev;
    val_t data;
};


// 迭代器, 不导出
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


// 导出链表
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
     * @brief 在尾部之后插入一个元素
     * @param value
     */
    void push_back(val_t value) {
        // TODO: push_back
    }


    /**
     * @brief 在头部前面插入一个元素
     * @param value
     */
    void push_front(val_t value);

    /**
     * @brief 删除尾部元素
     */
    void pop_back();

    /**
     * @brief 删除头部元素
     */
    void pop_front();

    /**
     * @brief 删除迭代器指向的元素, 返回随后元素的迭代器
     * @param pointer
     * @return iterator 随后元素的迭代器
     */
    iterator erase(iterator pointer) {
        return pointer.destroy();
    }


    /**
     * @brief 获得头部迭代器
     * @return iterator
     */
    iterator begin() {
        return _head->next;
    }


    /**
     * @brief 获得尾后迭代器
     * @return iterator
     */
    iterator end() {
        return _head;
    }


    /**
     * @brief 返回元素个数
     * @return size_t
     */
    size_t size() {
        return _size;
    }


    // 为了方便起见, 禁止复制
    mylist<val_t> &operator=(mylist<val_t>) = delete;
    // 为了方便起见, 禁止复制
    mylist<val_t> &operator=(const mylist<val_t> &) = delete;
    // 为了方便起见, 禁止复制
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
