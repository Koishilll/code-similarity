// 自动扩容数组, 仿制 std::vector

#ifndef __MYVEC__
#define __MYVEC__


#include <type_traits>


template <typename elm_t>
class myvec {
private:
    using _self_t = myvec<elm_t>;

public:
    myvec() {
		// 初始化预留一些空间, 注意: 仅分配空间, 不能构造!
        // _last = _first = new elm_t[16];
        _last = _first = (elm_t *) new char[sizeof (elm_t) * 16];
        _end = _first + 16;
    }

    ~myvec() {
        clear();
        delete[] (char *)_first;
        _first = nullptr;
    }


    /**
     * @brief 在尾部之后插入一个元素
     * @param value
     */
    void push_back(const elm_t &value) {
        if (_last == _end) {
            _enlarge(max_size() * 2);
        }
        // 调用放置构造函数而不是复制, 否则会先进行一次析构, 这会导致异常抛出
        new (_last) elm_t(value);
        ++_last;
    }


    /**
     * @brief 删除尾部元素
     */
    void pop_back() {
        --_last;
        // 如果是类, 就析构
        if constexpr (std::is_class<elm_t>::value) { _last->~elm_t(); }
    }


    /**
     * @brief 删除所有元素
     */
    void clear() {
        size_t times = size();
        for (int i = 0; i < times; ++i) {
            pop_back();
        }
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
        return pointer;
    }


    /**
     * @brief 获得头部迭代器
     * @return elm_t
     */
    elm_t *begin() const {
        return _first;
    }


    /**
     * @brief 获得尾后迭代器
     * @return elm_t
     */
    elm_t *end() const {
        return _last;
    }


    /**
     * @brief 重载 const [] 取出元素, 不可修改, 不检查越界
     * @param index 指定位置
     * @return elm_t&
     */
    const elm_t &operator[](size_t index) const {
        return _first[index];
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
    size_t size() const {
        return _last - _first;
    }


    /**
     * @brief 返回扩容前最大容量
     * @return size_t
     */
    size_t max_size() const {
        return _end - _first;
    }


    /**
     * @brief 扩大预留空间, 如果预留空间已经足够大, 那就不做任何事.
     * @param new_cap 至少预留的空间, 实际上会扩大至 2 的幂.
     */
    void reserve(size_t new_cap) {
        size_t size = _end - _first;
        if (size >= new_cap) { return; }
        while (size < new_cap) { size <<= 1; }
        _enlarge(size);
    }


    // 为了方便起见, 禁止复制赋值
    _self_t &operator=(const _self_t &) = delete;
    // 仅开放移动赋值, 而且禁止传递
    void operator=(_self_t &&other) {
        clear();
        _first = other._first;
        _last = other._last;
        _end = other._end;
        other._first = nullptr;
        other._last = nullptr;
        other._end = nullptr;
    }


private:
    elm_t *_first;
    elm_t *_last;
    elm_t *_end;

    void _enlarge(size_t new_cap) {
        size_t count = size();
        elm_t *temp = (elm_t *) new char[sizeof (elm_t) * new_cap];
        for (size_t i = 0; i < count; ++i) {
            // 调用放置构造函数而不是复制, 否则会先进行一次析构, 这会导致异常抛出
            new (temp + i) elm_t(_first[i]);
            // 如果是类, 就析构
            if constexpr (std::is_class<elm_t>::value) { _first[i].~elm_t(); }
        }
        // 此处如果不转为内置类型, 则会在没有对象的空间调用析构函数, 导致异常抛出
        delete[] (char *)_first;
        _first = temp;
        _last = temp + count;
        _end = temp + new_cap;
    }
};


#endif /* __MYVEC__ */
