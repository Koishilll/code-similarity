// 哈希表, 仿制 std::unordered_map

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


// 哈希表迭代器
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

    // 初始化 128 个桶
    mymap() : mymap(128) {}

    // 初始化桶数为 2 的幂时, -1 后二进制是 000..00111..11
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
     * @brief 获得头部迭代器
     * @return iterator
     */
    iterator begin() {
        return _table.begin();
    }


    /**
     * @brief 获得尾后迭代器
     * @return iterator
     */
    iterator end() {
        return _table.end();
    }


    /**
     * @brief 删除所有元素
     */
    void clear() {
        _range.clear();
        _table.clear();
    }


    /**
     * @brief 返回元素个数
     * @return size_t
     */
    size_t size() {
        return _table.size();
    }


    /**
     * @brief 查找和指定键等价的元素
     * @param key
     * @return iterator 查找成功返回对应位置迭代器, 否则返回 end()
     */
    iterator find(const key_t &key) {
        return _myfind(key, _hash(key));
    }


    /**
     * @brief 插入一个键值对, 返回两个值: 即将插入的位置和插入是否成功
     * 如果插入成功, 返回该位置和 true
     * 如果插入成功, 返回冲突的位置和 false
     * 为了保证查找效率, 如果已有键值对大于桶数, 则会自动重新哈希
     * @param value 要插入的键值对
     * @return pair<iterator, bool> 即将插入的位置和插入是否成功
     */
    pair<iterator, bool> insert(const val_t &value) {
        unsigned hash = _hash(value.first);
        iterator found = _myfind(value.first, hash);

        // 键存在冲突, 插入失败
        if (found != end()) {
            return { found, false };
        }
        size_t max_size = _mask + 1;
        if (max_size <= size()) { _rehash(max_size * 2); }

        // 插入到范围的开头
        unsigned bucket = hash & _mask;
        iterator where = _range[bucket].first;
        iterator ins = _table.insert(where._myiter, { value, hash });
        _range[bucket].first = ins;
        return { ins, true };
    }


    /**
     * @brief 访问已存在的键值对, 或者在不存在的情况下自动插入一个
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
     * @brief 增加桶数, 如果桶数已经够多了, 那就不做任何事
     * 为了保证查找效率, 如果已有键值对大于桶数, 则会自动调用.
     * 增加桶数会导致所有键重新哈希, 这将花费巨大!
     * @param new_buk 至少预留的桶数, 实际上会扩大至 2 的幂.
     */
    void reserve(size_t new_buk) {
        size_t max_size = _mask + 1;
        if (max_size >= new_buk) { return; }
        while (max_size < new_buk) { max_size <<= 1; }
        _rehash(max_size);
    }


    // 为了方便起见, 禁止复制赋值
    _self_t &operator=(const _self_t &) = delete;
    // 仅开放移动赋值, 而且禁止传递
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

    // 求一个键的哈希值
    unsigned _hash(const key_t &to_hash) {
        return hash_wrap(to_hash, _seed);
    }

    // 内部带哈希值查找
    iterator _myfind(const key_t &key, unsigned hash) {
        unsigned bucket = hash & _mask;
        for (auto it = _range[bucket].first;
                  it != _range[bucket].second; ++it) {
            if (it->first == key) { return it; }
        }
        return end();
    }

    // 内部重新哈希
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
