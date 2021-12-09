// 动态扩容数组, 仿制 std::vector

export module util.myvec;


// 导出数组
export
template <typename elm_t>
class myvec {
public:
    myvec() {
        _last = _first = new elm_t[16];
        _end = _first + 16;
    }

    ~myvec() {
        delete[] _first;
    }


    /**
     * @brief 在尾部之后插入一个元素
     * @param value
     */
    void push_back(elm_t value) {
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
        if constexpr (is_class<elm_t>::value) { ~*_last; }
    }


    /**
     * @brief 删除指针指向的元素, 返回随后元素的指针
     * @param pointer
     * @return elm_t* 随后元素的指针, 正常情况下就是传入的指针
     */
    elm_t *erase(elm_t *pointer) {
        while (pointer != _last - 1) {
            *pointer = *(pointer + 1);
            ++pointer;
        }
        pop_back();
    }


    /**
     * @brief 获得头部迭代器
     * @return elm_t
     */
    elm_t *begin() {
        return _first;
    }


    /**
     * @brief 获得尾后迭代器
     * @return elm_t
     */
    elm_t *end() {
        return _last;
    }


    /**
     * @brief 重载 [] 取出元素, 不检查越界
     * @param index 指定位置
     * @return elm_t&
     */
    elm_t &operator[](size_t index) {
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
    myvec<elm_t> &operator=(myvec<elm_t>) = delete;
    // 为了方便起见, 禁止复制
    myvec<elm_t> &operator=(const myvec<elm_t> &) = delete;
    // 为了方便起见, 禁止复制
    myvec<elm_t> &operator=(myvec<elm_t> &&) = delete;


private:
    elm_t *_first;
    elm_t *_last;
    elm_t *_end;

    void _enlarge(size_t new_cap) {
        size_t count = size();
        elm_t *temp = new elm_t[new_cap];
        for (size_t i = 0; i < count; ++i) {
            temp[i] = _first[i];
        }
        delete[] _first;
        _first = temp;
        _last = temp + count;
        _end = temp + new_cap;
    }
};
