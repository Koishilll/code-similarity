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
//      * @brief ����һ��Ԫ��, ��������ֵ, ���������λ�úͲ����Ƿ�ɹ�
//      * �������ɹ�, ���ظ�λ�ú� true
//      * �������ɹ�, ���س�ͻ��λ�ú� false
//      * @param value Ҫ����ļ�ֵ��
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
//     // TODO: ���캯��
// }

// template <typename key_t, typename elm_t>
// mymap<key_t, elm_t>::~mymap() {
//     // TODO: ��������
// }

// template <typename key_t, typename elm_t>
// mymap<key_t, elm_t>::pair<iter_t, bool> insert(pair<key_t, elm_t> value) {
//     // TODO: ������Ԫ��, ��ɢ��, ��ȡģ����Ͱ
//     // unsigned hash =
// }

// // �뿴: https://github.com/abrandoned/murmur2/blob/master/MurmurHash2.c
// unsigned MurmurHash2(const void *key, int len, unsigned seed) {
//     // 'm' �� 'r' ���������ɵĻ�ϳ���.
//     // ���ǲ���ʲôħ��, ֻ�Ǹպñ��ֺܺö���.
//     const unsigned m = 0x5bd1e995;
//     const int r = 24;

//     // ��ʼ��ɢ��ֵΪһ��α�����
//     unsigned h = seed ^ len;

//     // ÿ�ν��ĸ��ֽڻ���ɢ��ֵ
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

//     // ������󼸸��ֽ�
//     switch (len) {
//     case 3: h ^= data[2] << 16;
//     case 2: h ^= data[1] << 8;
//     case 1: h ^= data[0];
//         h *= m;
//     };

//     // �ٻ��һ����ȷ����󼸸��ֽڳ�ֻ��
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
