// �Զ���������, ���� std::vector

#ifndef __MYVEC__
#define __MYVEC__


#include <type_traits>


template <typename elm_t>
class myvec {
private:
    using _self_t = myvec<elm_t>;

public:
    myvec() {
		// ��ʼ��Ԥ��һЩ�ռ�, ע��: ������ռ�, ���ܹ���!
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
     * @brief ��β��֮�����һ��Ԫ��
     * @param value
     */
    void push_back(const elm_t &value) {
        if (_last == _end) {
            _enlarge(max_size() * 2);
        }
        // ���÷��ù��캯�������Ǹ���, ������Ƚ���һ������, ��ᵼ���쳣�׳�
        new (_last) elm_t(value);
        ++_last;
    }


    /**
     * @brief ɾ��β��Ԫ��
     */
    void pop_back() {
        --_last;
        // �������, ������
        if constexpr (std::is_class<elm_t>::value) { _last->~elm_t(); }
    }


    /**
     * @brief ɾ������Ԫ��
     */
    void clear() {
        size_t times = size();
        for (int i = 0; i < times; ++i) {
            pop_back();
        }
    }


    /**
     * @brief ɾ��ָ��ָ���Ԫ��, �������Ԫ�ص�ָ��
     * @param pointer
     * @return elm_t* ���Ԫ�ص�ָ��, ��������¾��Ǵ����ָ��
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
     * @brief ���ͷ��������
     * @return elm_t
     */
    elm_t *begin() const {
        return _first;
    }


    /**
     * @brief ���β�������
     * @return elm_t
     */
    elm_t *end() const {
        return _last;
    }


    /**
     * @brief ���� const [] ȡ��Ԫ��, �����޸�, �����Խ��
     * @param index ָ��λ��
     * @return elm_t&
     */
    const elm_t &operator[](size_t index) const {
        return _first[index];
    }


    /**
     * @brief ���� [] ȡ��Ԫ��, �����Խ��
     * @param index ָ��λ��
     * @return elm_t&
     */
    elm_t &operator[](size_t index) {
        return _first[index];
    }


    /**
     * @brief ����Ԫ�ظ���
     * @return size_t
     */
    size_t size() const {
        return _last - _first;
    }


    /**
     * @brief ��������ǰ�������
     * @return size_t
     */
    size_t max_size() const {
        return _end - _first;
    }


    /**
     * @brief ����Ԥ���ռ�, ���Ԥ���ռ��Ѿ��㹻��, �ǾͲ����κ���.
     * @param new_cap ����Ԥ���Ŀռ�, ʵ���ϻ������� 2 ����.
     */
    void reserve(size_t new_cap) {
        size_t size = _end - _first;
        if (size >= new_cap) { return; }
        while (size < new_cap) { size <<= 1; }
        _enlarge(size);
    }


    // Ϊ�˷������, ��ֹ���Ƹ�ֵ
    _self_t &operator=(const _self_t &) = delete;
    // �������ƶ���ֵ, ���ҽ�ֹ����
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
            // ���÷��ù��캯�������Ǹ���, ������Ƚ���һ������, ��ᵼ���쳣�׳�
            new (temp + i) elm_t(_first[i]);
            // �������, ������
            if constexpr (std::is_class<elm_t>::value) { _first[i].~elm_t(); }
        }
        // �˴������תΪ��������, �����û�ж���Ŀռ������������, �����쳣�׳�
        delete[] (char *)_first;
        _first = temp;
        _last = temp + count;
        _end = temp + new_cap;
    }
};


#endif /* __MYVEC__ */
