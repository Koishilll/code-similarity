// 哈希表, 仿制 std::unordered_map

export module util.mymap;
import std.core;
import util.myvec;
import util.mylist;


using std::string;
using std::pair;

// 导出哈希表
export
template <typename key_t, typename elm_t>
class mymap {
public:
    using val_t = std::pair<key_t, elm_t>;
    using node_t = mylist<elm_t>::node_t;
    using node_hash_t = std::pair<node_t *, unsigned>;

    mymap() {
        // TODO: 构造函数
        _mask = 127; // 初始化为 128 个桶
    }

    ~mymap() {}


    /**
     * @brief 插入一个元素, 返回两个值, 即将插入的位置和插入是否成功
     * 如果插入成功, 返回该位置和 true
     * 如果插入成功, 返回冲突的位置和 false
     * @param value 要插入的键值对
     * @return pair<iter_t, bool>
     */
    // pair<iter_t, bool> insert(pair<key_t, elm_t> value);

private:
    mylist<val_t> _hashtable;
    myvec<node_hash_t> _hash_vec;
    unsigned _mask;
    constexpr static unsigned _seed = 114514;

    unsigned _hash(key_t to_hash) {
        return MurmurHash2(&to_hash, sizeof (key_t), _seed);
    }
    unsigned _hash(const std::string &str) {
        return MurmurHash2(str.c_str(), str.length(), _seed);
    }
};



// template <typename key_t, typename elm_t>
// mymap<key_t, elm_t>::mymap() {
//     if (_seed == 0) {
//         _seed = time(nullptr);
//     }
//     _hashtable.reverse(128);
//     // TODO: 构造函数
// }

// template <typename key_t, typename elm_t>
// mymap<key_t, elm_t>::~mymap() {
//     // TODO: 析构函数
// }

// template <typename key_t, typename elm_t>
// mymap<key_t, elm_t>::pair<iter_t, bool> insert(pair<key_t, elm_t> value) {
//     // TODO: 插入新元素, 先散列, 再取模放入桶
//     // unsigned hash =
// }

// 请看: https://github.com/abrandoned/murmur2/blob/master/MurmurHash2.c
unsigned MurmurHash2(const void *key, size_t len, unsigned seed) {
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
