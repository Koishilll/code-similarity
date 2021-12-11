// ��ϣ��, ���� std::unordered_map

module;
#include <type_traits>

export module util.mymap;
import std.core;
import util.myvec;
import util.mylist;


using std::string;
using std::pair;


// ��ϣ�������, ������
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


// ������ϣ��
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
        // TODO: ���캯��
        _mask = 127; // ��ʼ��Ϊ 128 ��Ͱ
        iterator head { _table.end() };
        auto null_range = pair { head, head };
        for (int i = 0; i < 128; ++i) {
            _range.push_back(null_range);
        }
    }

    ~mymap() {}


    /**
     * @brief ����һ����ֵ��, ��������ֵ, ���������λ�úͲ����Ƿ�ɹ�
     * �������ɹ�, ���ظ�λ�ú� true
     * �������ɹ�, ���س�ͻ��λ�ú� false
     * @param value Ҫ����ļ�ֵ��
     * @return pair<iter_t, bool> ���������λ�úͲ����Ƿ�ɹ�
     */
    pair<iterator, bool> insert(val_t value) {
        key_t key = value.first;
        unsigned hash = _hash(key);
        // _table
    }


    // Ϊ�˷������, ��ֹ����
    mymap<key_t, elm_t> &operator=(mymap<key_t, elm_t>) = delete;
    // Ϊ�˷������, ��ֹ����
    mymap<key_t, elm_t> &operator=(const mymap<key_t, elm_t> &) = delete;
    // Ϊ�˷������, ��ֹ����
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



// �뿴: https://github.com/abrandoned/murmur2/blob/master/MurmurHash2.c
unsigned MurmurHash2(const void *key, int len, unsigned seed) {
    // 'm' �� 'r' ���������ɵĻ�ϳ���.
    // ���ǲ���ʲôħ��, ֻ�Ǹպñ��ֺܺö���.
    const unsigned m = 0x5bd1e995;
    const int r = 24;

    // ��ʼ��ɢ��ֵΪһ��α�����
    unsigned h = seed ^ len;

    // ÿ�ν��ĸ��ֽڻ���ɢ��ֵ
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

    // ������󼸸��ֽ�
    switch (len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    // �ٻ��һ����ȷ����󼸸��ֽڳ�ֻ��
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}
