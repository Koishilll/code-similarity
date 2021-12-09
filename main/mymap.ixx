export module util.mymap;
import util.myvec;
import <ctime>;

// export
// template <typename key_t, typename elm_t>
// class mymap {
// public:
//     using value_type = pair<key_t, elm_t>;

//     mymap();
//     ~mymap();

//     /**
//      * @brief 插入一个元素, 返回两个值, 即将插入的位置和插入是否成功
//      * 如果插入成功, 返回该位置和 true
//      * 如果插入成功, 返回冲突的位置和 false
//      * @param value 要插入的键值对
//      * @return pair<iter_t, bool>
//      */
//     pair<iter_t, bool> insert(pair<key_t, elm_t> value);

// private:
//     myvec<myvec<value_type>> _hashtable;
//     int _capacity = 128;
//     unsigned _hash(key_t to_hash);
// };



// module :private;

// static unsigned _seed;

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

// // 请看: https://github.com/abrandoned/murmur2/blob/master/MurmurHash2.c
// unsigned MurmurHash2(const void *key, int len, unsigned seed) {
//     // 'm' 和 'r' 是离线生成的混合常量.
//     // 它们不是什么魔法, 只是刚好表现很好而已.
//     const unsigned m = 0x5bd1e995;
//     const int r = 24;

//     // 初始化散列值为一个伪随机数
//     unsigned h = seed ^ len;

//     // 每次将四个字节混入散列值
//     const unsigned char *data = (const unsigned char *)key;
//     while (len >= 4) {
//         unsigned k = *(unsigned *)data;

//         k *= m;
//         k ^= k >> r;
//         k *= m;

//         h *= m;
//         h ^= k;

//         data += 4;
//         len -= 4;
//     }

//     // 处理最后几个字节
//     switch (len) {
//     case 3: h ^= data[2] << 16;
//     case 2: h ^= data[1] << 8;
//     case 1: h ^= data[0];
//         h *= m;
//     };

//     // 再混合一次以确保最后几个字节充分混合
//     h ^= h >> 13;
//     h *= m;
//     h ^= h >> 15;

//     return h;
// }

// template <typename key_t, typename elm_t>
// mymap<key_t, elm_t>::unsigned _hash(key_t to_hash) {
//     int size = sizeof (key_t);
//     char *mem = (char *)&to_hash;
//     return MurmurHash2({ to_hash, sizeof (key_t), _seed });
// }
