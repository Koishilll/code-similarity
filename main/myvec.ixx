// ��̬��������, ���� std::vector

export module util.myvec;


// ��������
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
     * @brief ��β��֮�����һ��Ԫ��
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
     * @brief ɾ��β��Ԫ��
     */
    void pop_back() {
        --_last;
        // �������, ������
        if constexpr (is_class<elm_t>::value) { ~*_last; }
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
    }


    /**
     * @brief ���ͷ��������
     * @return elm_t
     */
    elm_t *begin() {
        return _first;
    }


    /**
     * @brief ���β�������
     * @return elm_t
     */
    elm_t *end() {
        return _last;
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
    myvec<elm_t> &operator=(myvec<elm_t>) = delete;
    // Ϊ�˷������, ��ֹ����
    myvec<elm_t> &operator=(const myvec<elm_t> &) = delete;
    // Ϊ�˷������, ��ֹ����
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
