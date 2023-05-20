namespace atcoder_fenwick_tree {

namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename conditional<is_same<T, __int128_t>::value ||
                                  is_same<T, __int128>::value,
                              true_type,
                              false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename conditional<is_same<T, __uint128_t>::value ||
                                  is_same<T, unsigned __int128>::value,
                              true_type,
                              false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename conditional<is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral = typename conditional<is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              true_type,
                                              false_type>::type;

template <class T>
using is_signed_int = typename conditional<(is_integral<T>::value &&
                                                 is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                true_type,
                                                false_type>::type;

template <class T>
using is_unsigned_int =
    typename conditional<(is_integral<T>::value &&
                               is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              true_type,
                              false_type>::type;

template <class T>
using to_unsigned = typename conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename conditional<is_signed<T>::value,
                              make_unsigned<T>,
                              common_type<T>>::type>::type;

#else

template <class T> using is_integral = typename is_integral<T>;

template <class T>
using is_signed_int =
    typename conditional<is_integral<T>::value && is_signed<T>::value,
                              true_type,
                              false_type>::type;

template <class T>
using is_unsigned_int =
    typename conditional<is_integral<T>::value &&
                                  is_unsigned<T>::value,
                              true_type,
                              false_type>::type;

template <class T>
using to_unsigned = typename conditional<is_signed_int<T>::value,
                                              make_unsigned<T>,
                                              common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = enable_if_t<is_unsigned_int<T>::value>;

template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

// 0-base, left close right open
template <class T> struct fenwick_tree {
    using U = internal::to_unsigned_t<T>;

  public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += U(x);
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

  private:
    int _n;
    vector<U> data;

    U sum(int r) {
        U s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};

}  // namespace atcoder_fenwick_tree
