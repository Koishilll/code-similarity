// ˫��������, ���� std::list

export module util.mylist;


// ����������, ������
template <typename elm_t>
class _list_node {
private:
    using node_t = _list_node<elm_t>;

public:
    node_t *_next;
    node_t *_prev;
    elm_t data;

    _list_node() {};
    _list_node(elm_t e) : data(e) {};
};


// ���������, ������
template <typename elm_t>
class _list_iterator {
private:
    using iterator = _list_iterator<elm_t>;
    using node_t = _list_node<elm_t>;

public:
    _list_iterator(node_t *_n) : _mynode(_n) {};

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

// private:
    node_t *_mynode;
};


// ��������
export
template <typename elm_t>
class mylist {
private:
    using node_t = _list_node<elm_t>;
    using _self_t = mylist<elm_t>;

public:
    using iterator = _list_iterator<elm_t>;

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
     * @brief ���ͷ��������
     * @return iterator
     */
    iterator begin() {
        return _head->_next;
    }


    /**
     * @brief ���β�������
     * @return iterator
     */
    iterator end() {
        return _head;
    }


    /**
     * @brief ����Ԫ�ص�ָ��λ��֮ǰ
     * @param pos
     * @param value
     * @return iterator �²���Ԫ�صĵ�����
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
     * @brief ɾ��������ָ���Ԫ��, �������Ԫ�صĵ�����
     * @param pointer
     * @return iterator ���Ԫ�صĵ�����
     */
    iterator erase(iterator pointer) {
        --_size;
        return pointer.destroy();
    }


    /**
     * @brief ɾ��β��Ԫ��
     */
    void clear() {
        size_t times = size();
        for (int i = 0; i < times; ++i) {
            pop_back();
        }
    }


    /**
     * @brief ��β��֮�����һ��Ԫ��
     * @param value
     */
    void push_back(elm_t value) {
        insert(end(), value);
    }


    /**
     * @brief ��ͷ��ǰ�����һ��Ԫ��
     * @param value
     */
    void push_front(elm_t value) {
        insert(begin(), value);
    }


    /**
     * @brief ɾ��β��Ԫ��
     */
    void pop_back() {
        erase(--end());
    }

    /**
     * @brief ɾ��ͷ��Ԫ��
     */
    void pop_front() {
        erase(begin());
    }


    /**
     * @brief ����Ԫ�ظ���
     * @return size_t
     */
    size_t size() {
        return _size;
    }


    // Ϊ�˷������, ��ֹ����
    _self_t &operator=(_self_t) = delete;
    // Ϊ�˷������, ��ֹ����
    _self_t &operator=(const _self_t &) = delete;
    // Ϊ�˷������, ��ֹ����
    _self_t &operator=(_self_t &&) = delete;


private:
    node_t *_head;
    size_t _size;
    // void _enlarge(size_t new_cap);
};
