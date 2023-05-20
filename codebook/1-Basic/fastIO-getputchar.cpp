#define GU getchar()
#define PU putchar

template<typename T = int>
T in() {
    T re = 0;
    char c = GU;
    while (c == ' ' || c == '\n') {
        c = GU;
    }
    while (c >= '0' && c <= '9') {
        re = (re << 3) + (re << 1) + c - '0';
        c = GU;
    }
}

template<typename T = int>
void out(T x) {
    char s[20];
    int p = 0;
    do {
        s[p++] = x % 10 + '0';
        x /= 10;
    } while (x);
    for (int i = p - 1; i >= 0; i--) {
        PU(s[i]);
    }
    PU('\n');
}
