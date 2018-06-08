#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double convert(char *s /* hex str of wei */) {
    size_t len = strlen(s);
    if (s[0] == '0' && s[1] == 'x') {
        len -= 2;
        s += 2;
    }

    if (len > 30) {
        printf("too lang to calc.\n");
        return 0.0;
    }

    double d = 0.0;
    double I18 = 1000000000000000000L;
    double F15 = (double) 0xFFFFFFFFFFFFFFF / I18;

    if (len > 15) {
        char *s1 = s + len - 15;
        int64_t v1 = strtoll(s1, NULL, 16);
        double d1 = (double) v1 / I18;

        char s2[16] = {0};
        strncpy(s2, s, len - 15);
        int64_t v2 = strtoll(s2, NULL, 16);
        double d2 = v2 * F15;

        d = d1 + d2;

    } else if (len <= 15) {
        int64_t v = strtoll(s, NULL, 16);
        d = (double) v / I18;
    }
    return d;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("give me a hex value.\n");
        return 1;
    }
    double d = convert(argv[1]);
    printf("%lf\n", d);
    return 0;

}