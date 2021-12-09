// 双向环形链表, 仿制 std::list

export module util.mylist;


// 链表结点类型, 不导出
template <typename elm_t>
class _list_node {
public:
    using node_t = _list_node<elm_t>;
    node_t *_next;
    node_t *_prev;
    elm_t data;

    _list_node() {};
    _list_node(elm_t e) : data(e) {};
};


// 迭代器, 不导出
template <typename elm_t>
class _iterator {
public:
    using iterator = _iterator<elm_t>;
    using node_t = _list_node<elm_t>;

    _iterator(node_t *_n) : _mynode(_n) {};

    bool operator==(iterator &other) {
        return _mynode == other._mynode;
    }

    elm_t &operator*() {
        return _mynode->data;
    }

    elm_t &operator->() {
        return _mynode->data;
    }

    iterator &operator++() {
        _mynode = _mynode->_next;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        _mynode = _mynode->_next;
        return temp;
    }

    iterator &operator--() {
        _mynode = _mynode->_prev;
        return *this;
    }

    iterator operator--(int) {
        iterator temp = *this;
        _mynode = _mynode->_prev;
        return temp;
    }

    iterator destroy() {
        node_t *next = _mynode->_next;
        node_t *prev = _mynode->_prev;
        prev->_next = next;
        next->_prev = prev;
        delete _mynode;
        _mynode = next;
        return *this;
    }

private:
    node_t *_mynode;
};


// 导出链表
export
template <typename elm_t>
class mylist {
public:
    using iterator = _iterator<elm_t>;
    using node_t = _list_node<elm_t>;

    mylist() {
        _head = new node_t;
        _head->_next = _head->_prev = _head;
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
     * @brief 获得头部迭代器
     * @return iterator
     */
    iterator begin() {
        return _head->_next;
    }


    /**
     * @brief 获得尾后迭代器
     * @return iterator
     */
    iterator end() {
        return _head;
    }


    /**
     * @brief 插入元素到指定位置之前
     * @param pos
     * @param value
     * @return iterator 新插入元素的迭代器
     */
    iterator insert(iterator pos, elm_t value) {
        iterator now = pos--;
        iterator ins { new node_t(value) };
        ins._mynode->_next = now._mynode;
        ins._mynode->_prev = pos._mynode;
        now._mynode->_prev = ins._mynode;
        pos._mynode->_next = ins._mynode;
        ++_size;
        return ins;
    }


    /**
     * @brief 删除迭代器指向的元素, 返回随后元素的迭代器
     * @param pointer
     * @return iterator 随后元素的迭代器
     */
    iterator erase(iterator pointer) {
        --_size;
        return pointer.destroy();
    }


    /**
     * @brief 在尾部之后插入一个元素
     * @param value
     */
    void push_back(elm_t value) {
        insert(end(), value);
    }


    /**
     * @brief 在头部前面插入一个元素
     * @param value
     */
    void push_front(elm_t value) {
        insert(begin(), value);
    }


    /**
     * @brief 删除尾部元素
     */
    void pop_back() {
        erase(--end());
    }

    /**
     * @brief 删除头部元素
     */
    void pop_front() {
        erase(begin());
    }


    /**
     * @brief 返回元素个数
     * @return size_t
     */
    size_t size() {
        return _size;
    }


    // 为了方便起见, 禁止复制
    mylist<elm_t> &operator=(mylist<elm_t>) = delete;
    // 为了方便起见, 禁止复制
    mylist<elm_t> &operator=(const mylist<elm_t> &) = delete;
    // 为了方便起见, 禁止复制
    mylist<elm_t> &operator=(mylist<elm_t> &&) = delete;


private:
    node_t *_head;
    size_t _size;
    // void _enlarge(size_t new_cap);
};
