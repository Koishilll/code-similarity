// ��̬��������, ���� std::vector

export module util.myvec;


// ��������
export
template <typename val_t>
class myvec {
public:
    myvec() {
        _last = _first = new val_t[16];
        _end = _first + 16;
    }

    ~myvec() {
        delete[] _first;
    }


    /**
     * @brief ��β��֮�����һ��Ԫ��
     * @param value
     */
    void push_back(val_t value) {
        if (_last == _end) {
            _enlarge(max_size() * 2);
        }
        *_last = value;
        ++_last;
    }


    /**
     * @brief ɾ��β��Ԫ��
     */
    void pop_back() {
        --_last;
        // �������, ������
        if constexpr (is_class<val_t>::value) { ~*_last; }
    }


    /**
     * @brief ɾ��ָ��ָ���Ԫ��, �������Ԫ�ص�ָ��
     * @param pointer
     * @return val_t* ���Ԫ�ص�ָ��, ��������¾��Ǵ����ָ��
     */
    val_t *erase(val_t *pointer) {
        while (pointer != _last - 1) {
            *pointer = *(pointer + 1);
            ++pointer;
        }
        pop_back();
    }


    /**
     * @brief ���ͷ��������
     * @return val_t
     */
    val_t *begin() {
        return _first;
    }


    /**
     * @brief ���β�������
     * @return val_t
     */
    val_t *end() {
        return _last;
    }


    /**
     * @brief ���� [] ȡ��Ԫ��, �����Խ��
     * @param index ָ��λ��
     * @return val_t&
     */
    val_t &operator[](size_t index) {
        return _first[index];
    }


    /**
     * @brief ����Ԫ�ظ���
     * @return size_t
     */
    size_t size() {
        return _last - _first;
    }


    /**
     * @brief ��������ǰ�������
     * @return size_t
     */
    size_t max_size() {
        return _end - _first;
    }


    /**
     * @brief Ԥ��һЩ�ռ�, ���Ԥ���ռ���ڵ�ǰ�ռ�������ǰ�ռ�,
     * �������κ���.
     * @param new_cap ����Ԥ���Ŀռ�, ʵ���ϻ������� 2 ����.
     */
    void reserve(size_t new_cap) {
        size_t size = _end - _first;
        if (size >= new_cap) { return; }
        while (size < new_cap) { size <<= 1; }
        _enlarge(size);
    }


    // Ϊ�˷������, ��ֹ����
    myvec<val_t> &operator=(myvec<val_t>) = delete;
    // Ϊ�˷������, ��ֹ����
    myvec<val_t> &operator=(const myvec<val_t> &) = delete;
    // Ϊ�˷������, ��ֹ����
    myvec<val_t> &operator=(myvec<val_t> &&) = delete;


private:
    val_t *_first;
    val_t *_last;
    val_t *_end;

    void _enlarge(size_t new_cap) {
        size_t count = size();
        val_t *temp = new val_t[new_cap];
        for (size_t i = 0; i < count; ++i) {
            temp[i] = _first[i];
        }
        delete[] _first;
        _first = temp;
        _last = temp + count;
        _end = temp + new_cap;
    }
};



// template <typename val_t>
// myvec<val_t>::myvec() {
//     _last = _first = new val_t[16];
//     _end = _first + 16;
// }

// template <typename val_t>
// myvec<val_t>::~myvec() {
//     delete[] _first;
// }

// template <typename val_t>
// void myvec<val_t>::push_back(val_t value) {
//     if (_last == _end) {
//         _enlarge(max_size() * 2);
//     }
//     *_last = value;
//     ++_last;
// }

// template <typename val_t>
// void myvec<val_t>::pop_back() {
//     --_last;
//     // �������, ������
//     if constexpr (is_class<val_t>::value) { ~*_last; }
// }

// template <typename val_t>
// val_t * myvec<val_t>::erase(val_t *pointer) {
//     while (pointer != _last - 1) {
//         *pointer = *(pointer + 1);
//         ++pointer;
//     }
//     pop_back();
// }

// template <typename val_t>
// val_t *myvec<val_t>::begin() {
//     return _first;
// }

// template <typename val_t>
// val_t *myvec<val_t>::end() {
//     return _last;
// }

// template <typename val_t>
// val_t &myvec<val_t>::operator[](size_t index) {
//     return _first[index];
// }

// template <typename val_t>
// size_t myvec<val_t>::size() {
//     return _last - _first;
// }

// template <typename val_t>
// size_t myvec<val_t>::max_size() {
//     return _end - _first;
// }

// template <typename val_t>
// void myvec<val_t>::reserve(size_t new_cap) {
//     size_t size = _end - _first;
//     if (size >= new_cap) { return; }
//     while (size < new_cap) { size <<= 1; }
//     _enlarge(size);
// }

// template <typename val_t>
// void myvec<val_t>::_enlarge(size_t new_cap) {
//     int count = size();
//     val_t *temp = new val_t[new_cap];
//     for (int i = 0; i < count; ++i) {
//         temp[i] = _first[i];
//     }
//     delete[] _first;
//     _first = temp;
//     _last = temp + count;
//     _end = temp + new_cap;
// }
