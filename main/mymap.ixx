// 哈希表, 仿制 std::unordered_map

module;
#include <type_traits>

export module util.mymap;
import std.core;
import util.myvec;
import util.mylist;


using std::string;
using std::pair;


// 哈希表迭代器, 不导出
template <typename key_t, typename elm_t>
class _map_iterator {
private:
    using val_t = pair<key_t, elm_t>;
    using val_hash_t = pair<val_t, unsigned>;
    using iterator = _map_iterator<key_t, elm_t>;
    // using node_t = mylist<val_hash_t>::node_t;

public:
    _map_iterator(mylist<val_hash_t>::iterator _it) : _myiter(_it) {};

    val_t &operator*() {
        return _myiter->data.first;
    }

    val_t &operator->() {
        return _myiter->data.first;
    }

    iterator &operator++() {
        _myiter = _myiter->_next;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        _myiter = _myiter->_next;
        return temp;
    }

    iterator &operator--() {
        _myiter = _myiter->_prev;
        return *this;
    }

    iterator operator--(int) {
        iterator temp = *this;
        _myiter = _myiter->_prev;
        return temp;
    }

    iterator destroy() {
        // node_t *next = _myiter->_next;
        // node_t *prev = _myiter->_prev;
        // prev->_next = next;
        // next->_prev = prev;
        // delete _myiter;
        // _myiter = next;
        _myiter = _myiter.destroy();
        return *this;
    }

private:
    mylist<val_hash_t>::iterator _myiter;
};


// 导出哈希表
export
template <typename key_t, typename elm_t>
class mymap {
private:
    using val_t = pair<key_t, elm_t>;
    using val_hash_t = pair<val_t, unsigned>;
    // using node_t = mylist<val_hash_t>::node_t;

public:
    using iterator = _map_iterator<key_t, elm_t>;

    mymap() {
        // TODO: 构造函数
        _mask = 127; // 初始化为 128 个桶
        iterator head { _table.end() };
        auto null_range = pair { head, head };
        for (int i = 0; i < 128; ++i) {
            _range.push_back(null_range);
        }
    }

    ~mymap() {}


    /**
     * @brief 插入一个键值对, 返回两个值, 即将插入的位置和插入是否成功
     * 如果插入成功, 返回该位置和 true
     * 如果插入成功, 返回冲突的位置和 false
     * @param value 要插入的键值对
     * @return pair<iter_t, bool> 即将插入的位置和插入是否成功
     */
    pair<iterator, bool> insert(val_t value) {
        key_t key = value.first;
        unsigned hash = _hash(key);
        // _table
    }


    // 为了方便起见, 禁止复制
    mymap<key_t, elm_t> &operator=(mymap<key_t, elm_t>) = delete;
    // 为了方便起见, 禁止复制
    mymap<key_t, elm_t> &operator=(const mymap<key_t, elm_t> &) = delete;
    // 为了方便起见, 禁止复制
    mymap<key_t, elm_t> &operator=(mymap<key_t, elm_t> &&) = delete;


private:
    mylist<val_hash_t> _table;
    myvec<pair<iterator, iterator>> _range;
    unsigned _mask;
    constexpr static unsigned _seed = 114514;

    unsigned _hash(key_t to_hash) {
        return MurmurHash2(&to_hash, sizeof (key_t), _seed);
    }
    unsigned _hash(const string &str) {
        return MurmurHash2(str.c_str(), str.length(), _seed);
    }
};



// 请看: https://github.com/abrandoned/murmur2/blob/master/MurmurHash2.c
unsigned MurmurHash2(const void *key, int len, unsigned seed) {
    // 'm' 和 'r' 是离线生成的混合常量.
    // 它们不是什么魔法, 只是刚好表现很好而已.
    const unsigned m = 0x5bd1e995;
    const int r = 24;

    // 初始化散列值为一个伪随机数
    unsigned h = seed ^ len;

    // 每次将四个字节混入散列值
    const unsigned char *data = (const unsigned char *)key;
    while (len >= 4) {
        unsigned k = *(unsigned *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    // 处理最后几个字节
    switch (len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    // 再混合一次以确保最后几个字节充分混合
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}
