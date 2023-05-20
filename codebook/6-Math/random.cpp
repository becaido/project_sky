mt19937 seed(time(NULL));
template<typename T = int>
inline T rnd(T l, T r) {
    return uniform_int_distribution<T>(l, r)(seed);
}
template<typename T = double>
inline T srnd(T l, T r) {
    return uniform_real_distribution<T>(l, r)(seed);
}
