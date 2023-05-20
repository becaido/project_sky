inline Mint power(Mint d, long long up) { // need Mint
    if (up < 0) {
        up = -up;
        d = Mint(1) / d;
    }
    Mint re = 1;
    while (up) {
        if (up & 1) {
            re = re * d;
        }
        d = d * d;
        up >>= 1;
    }
    return re;
}
