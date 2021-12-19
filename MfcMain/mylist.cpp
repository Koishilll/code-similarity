// ˫��������, ���� std::list

#ifndef __MYLIST__
#define __MYLIST__

// #include "pch.h"


// ����������
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


// ���������
template <typename elm_t>
class _list_iterator {
private:
    using iterator = _list_iterator<elm_t>;
    using node_t = _list_node<elm_t>;

public:
    _list_iterator(const elm_t &elm) : _mynode(new node_t(elm)) {};
    _list_iterator(node_t *_n) : _mynode(_n) {};

    bool operator==(iterator &other) {
        return _mynode == other._mynode;
    }

    elm_t &operator*() {
        return _mynode->data;
    }

    elm_t *operator->() {
        return &_mynode->data;
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

    void insert(iterator other) {
        iterator prv { _mynode->_prev };
        other._mynode->_next = _mynode;
        other._mynode->_prev = prv._mynode;
        prv._mynode->_next = other._mynode;
        _mynode->_prev = other._mynode;
    }

    void destroy() {
        node_t *next = _mynode->_next;
        node_t *prev = _mynode->_prev;
        prev->_next = next;
        next->_prev = prev;
        delete _mynode;
    }

// private:
    node_t *_mynode;
};


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
        clear();
        delete _head;
    }


    /**
     * @brief ���ͷ��������
     * @return iterator
     */
    iterator begin() const {
        return _head->_next;
    }


    /**
     * @brief ���β�������
     * @return iterator
     */
    iterator end() const {
        return _head;
    }


    /**
     * @brief ����Ԫ�ص�ָ��λ��֮ǰ
     * @param pos
     * @param value
     * @return iterator �²���Ԫ�صĵ�����
     */
    iterator insert(iterator pos, const elm_t &value) {
        iterator ins { value };
        pos.insert(ins);
        ++_size;
        return ins;
    }


    /**
     * @brief ɾ��������ָ���Ԫ��, �������Ԫ�صĵ�����
     * @param pointer
     * @return iterator ���Ԫ�صĵ�����
     */
    iterator erase(iterator pos) {
        --_size;
        iterator now = pos++;
        now.destroy();
        return pos;
    }


    /**
     * @brief ɾ������Ԫ��
     */
    void clear() {
        auto next_it = begin();
        while (next_it != end()) {
            auto now_it = next_it++;
            now_it.destroy();
        }
        _size = 0;
    }


    /**
     * @brief ��β��֮�����һ��Ԫ��
     * @param value
     */
    void push_back(const elm_t &value) {
        insert(end(), value);
    }


    /**
     * @brief ��ͷ��ǰ�����һ��Ԫ��
     * @param value
     */
    void push_front(const elm_t &value) {
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
    size_t size() const {
        return _size;
    }


    // Ϊ�˷������, ��ֹ���Ƹ�ֵ
    _self_t &operator=(const _self_t &) = delete;
    // �������ƶ���ֵ, ���ҽ�ֹ����
    void operator=(_self_t &&other) {
        clear();
        auto nohead = _head;
        _head = other._head;
        _size = other._size;
        other._head = nohead;
        other._size = 0;
    }


private:
    node_t *_head;
    size_t _size;
};


#endif /* __MYLIST__ */
