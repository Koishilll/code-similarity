// ��ϣ��, ���� std::unordered_map

#ifndef __MYMAP__
#define __MYMAP__


#include "pch.h"


using std::string;
using std::wstring;
using std::pair;
using std::move;
using std::initializer_list;


template <typename key_t>
unsigned hash_wrap(const key_t &to_hash, unsigned seed);

unsigned MurmurHash2(const void *key, size_t len, unsigned seed);


// ��ϣ�������
template <typename key_t, typename elm_t>
class _map_iterator {
private:
    using val_t = pair<key_t, elm_t>;
    using val_hash_t = pair<val_t, unsigned>;
    using iterator = _map_iterator<key_t, elm_t>;
    using _list_iter = mylist<val_hash_t>::iterator;

public:
    _map_iterator(_list_iter _it) : _myiter(_it) {};
    _map_iterator(val_hash_t pr) : _myiter(pr) {};

    bool operator==(iterator other) {
        return _myiter == other._myiter;
    }

    val_t &operator*() {
        return _myiter->first;
    }

    val_t *operator->() {
        return &_myiter->first;
    }

    iterator &operator++() {
        ++_myiter;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        ++_myiter;
        return temp;
    }

    iterator &operator--() {
        --_myiter;
        return *this;
    }

    iterator operator--(int) {
        iterator temp = *this;
        --_myiter;
        return temp;
    }

    iterator destroy() {
        _myiter = _myiter.destroy();
        return *this;
    }

// private:
    mylist<val_hash_t>::iterator _myiter;
};


template <typename key_t, typename elm_t>
class mymap {
private:
    using val_t = pair<key_t, elm_t>;
    using val_hash_t = pair<val_t, unsigned>;
    using _self_t = mymap<key_t, elm_t>;

public:
    using iterator = _map_iterator<key_t, elm_t>;

    // ��ʼ�� 128 ��Ͱ
    mymap() : mymap(128) {}

    // ��ʼ��Ͱ��Ϊ 2 ����ʱ, -1 ��������� 000..00111..11
    mymap(size_t bucket_count) {
        unsigned count = 1;
        while (count < bucket_count) { count <<= 1; }
        _mask = count - 1;

        _range.reserve(count);
        iterator head { _table.end() };
        auto null_range = pair { head, head };
        for (size_t i = 0; i < count; ++i) {
            _range.push_back(null_range);
        }
    }

    ~mymap() {}


    /**
     * @brief ���ͷ��������
     * @return iterator
     */
    iterator begin() {
        return _table.begin();
    }


    /**
     * @brief ���β�������
     * @return iterator
     */
    iterator end() {
        return _table.end();
    }


    /**
     * @brief ɾ������Ԫ��
     */
    void clear() {
        _range.clear();
        _table.clear();
    }


    /**
     * @brief ����Ԫ�ظ���
     * @return size_t
     */
    size_t size() {
        return _table.size();
    }


    /**
     * @brief ���Һ�ָ�����ȼ۵�Ԫ��
     * @param key
     * @return iterator ���ҳɹ����ض�Ӧλ�õ�����, ���򷵻� end()
     */
    iterator find(const key_t &key) {
        return _myfind(key, _hash(key));
    }


    /**
     * @brief ����һ����ֵ��, ��������ֵ: ���������λ�úͲ����Ƿ�ɹ�
     * �������ɹ�, ���ظ�λ�ú� true
     * �������ɹ�, ���س�ͻ��λ�ú� false
     * Ϊ�˱�֤����Ч��, ������м�ֵ�Դ���Ͱ��, ����Զ����¹�ϣ
     * @param value Ҫ����ļ�ֵ��
     * @return pair<iterator, bool> ���������λ�úͲ����Ƿ�ɹ�
     */
    pair<iterator, bool> insert(const val_t &value) {
        unsigned hash = _hash(value.first);
        iterator found = _myfind(value.first, hash);

        // �����ڳ�ͻ, ����ʧ��
        if (found != end()) {
            return { found, false };
        }
        size_t max_size = _mask + 1;
        if (max_size <= size()) { _rehash(max_size * 2); }

        // ���뵽��Χ�Ŀ�ͷ
        unsigned bucket = hash & _mask;
        iterator where = _range[bucket].first;
        iterator ins = _table.insert(where._myiter, { value, hash });
        _range[bucket].first = ins;
        return { ins, true };
    }


    /**
     * @brief �����Ѵ��ڵļ�ֵ��, �����ڲ����ڵ�������Զ�����һ��
     * @param key
     * @return elm_t&
     */
    elm_t &operator[](const key_t &key) {
        // auto it = _myfind(key, _hash(key));
        // if (it == end()) {
        //     elm_t elm;
        //     it = insert({ key, elm }).first;
        // }
        // return it->second;
        elm_t elm {};
        return insert({ key, elm }).first->second;
    }


    /**
     * @brief ����Ͱ��, ���Ͱ���Ѿ�������, �ǾͲ����κ���
     * Ϊ�˱�֤����Ч��, ������м�ֵ�Դ���Ͱ��, ����Զ�����.
     * ����Ͱ���ᵼ�����м����¹�ϣ, �⽫���Ѿ޴�!
     * @param new_buk ����Ԥ����Ͱ��, ʵ���ϻ������� 2 ����.
     */
    void reserve(size_t new_buk) {
        size_t max_size = _mask + 1;
        if (max_size >= new_buk) { return; }
        while (max_size < new_buk) { max_size <<= 1; }
        _rehash(max_size);
    }


    // Ϊ�˷������, ��ֹ���Ƹ�ֵ
    _self_t &operator=(const _self_t &) = delete;
    // �������ƶ���ֵ, ���ҽ�ֹ����
    void operator=(_self_t &&other) {
        _table = move(other._table);
        _range = move(other._range);
        _mask = other._mask;
    }


private:
    mylist<val_hash_t> _table;
    myvec<pair<iterator, iterator>> _range;
    unsigned _mask;
    constexpr static unsigned _seed = 114514;

    // ��һ�����Ĺ�ϣֵ
    unsigned _hash(const key_t &to_hash) {
        return hash_wrap(to_hash, _seed);
    }

    // �ڲ�����ϣֵ����
    iterator _myfind(const key_t &key, unsigned hash) {
        unsigned bucket = hash & _mask;
        for (auto it = _range[bucket].first;
                  it != _range[bucket].second; ++it) {
            if (it->first == key) { return it; }
        }
        return end();
    }

    // �ڲ����¹�ϣ
    void _rehash(size_t new_buk) {
        _self_t other { new_buk };
        for (auto elm : *this) {
            other.insert(elm);
        }
        *this = move(other);
    }
};


template <typename key_t>
unsigned hash_wrap(const key_t &to_hash, unsigned seed) {
    return MurmurHash2(&to_hash, sizeof (key_t), seed);
}


template <>
inline unsigned hash_wrap(const string &str, unsigned seed) {
    return MurmurHash2(str.c_str(), str.length(), seed);
}


template <>
inline unsigned hash_wrap(const wstring &wstr, unsigned seed) {
    return MurmurHash2(wstr.c_str(),
        wstr.length() * sizeof (wstring::value_type), seed);
}


#endif /* __MYMAP__ */
