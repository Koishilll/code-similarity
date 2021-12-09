// 动态扩容数组, 仿制 std::vector

export module util.myvec;


// 导出数组
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
     * @brief 在尾部之后插入一个元素
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
     * @brief 删除尾部元素
     */
    void pop_back() {
        --_last;
        // 如果是类, 就析构
        if constexpr (is_class<val_t>::value) { ~*_last; }
    }


    /**
     * @brief 删除指针指向的元素, 返回随后元素的指针
     * @param pointer
     * @return val_t* 随后元素的指针, 正常情况下就是传入的指针
     */
    val_t *erase(val_t *pointer) {
        while (pointer != _last - 1) {
            *pointer = *(pointer + 1);
            ++pointer;
        }
        pop_back();
    }


    /**
     * @brief 获得头部迭代器
     * @return val_t
     */
    val_t *begin() {
        return _first;
    }


    /**
     * @brief 获得尾后迭代器
     * @return val_t
     */
    val_t *end() {
        return _last;
    }


    /**
     * @brief 重载 [] 取出元素, 不检查越界
     * @param index 指定位置
     * @return val_t&
     */
    val_t &operator[](size_t index) {
        return _first[index];
    }


    /**
     * @brief 返回元素个数
     * @return size_t
     */
    size_t size() {
        return _last - _first;
    }


    /**
     * @brief 返回扩容前最大容量
     * @return size_t
     */
    size_t max_size() {
        return _end - _first;
    }


    /**
     * @brief 预留一些空间, 如果预留空间大于当前空间则增大当前空间,
     * 否则不做任何事.
     * @param new_cap 至少预留的空间, 实际上会扩大至 2 的幂.
     */
    void reserve(size_t new_cap) {
        size_t size = _end - _first;
        if (size >= new_cap) { return; }
        while (size < new_cap) { size <<= 1; }
        _enlarge(size);
    }


    // 为了方便起见, 禁止复制
    myvec<val_t> &operator=(myvec<val_t>) = delete;
    // 为了方便起见, 禁止复制
    myvec<val_t> &operator=(const myvec<val_t> &) = delete;
    // 为了方便起见, 禁止复制
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
//     // 如果是类, 就析构
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
