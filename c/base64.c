#include <stdlib.h>

static const char *base64_string = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64_encode(const char *raw, int len, char *enc) {
    u_char inblk[3];
    int i;
    i = 0;
    char *p = raw + len;
    while (raw < p) {
        inblk[i] = (u_char)*raw;
        i++;
        if (i == 3) {
            enc[0] = base64_string[(inblk[0] & 0xfc) >> 2];
            enc[1] = base64_string[((inblk[0] & 0x03) << 4) + ((inblk[1] & 0xf0) >> 4)];
            enc[2] = base64_string[((inblk[1] & 0x0f) << 2) + ((inblk[2] & 0xc0) >> 6)];
            enc[3] = base64_string[(inblk[2] & 0x3f)];
            i = 0;
            enc += 4;
        }
        raw++;
    }
    switch (i) {
    case 2:
        enc[0] = base64_string[(inblk[0] & 0xfc) >> 2];
        enc[1] = base64_string[((inblk[0] & 0x03) << 4) + ((inblk[1] & 0xf0) >> 4)];
        enc[2] = base64_string[((inblk[1] & 0x0f) << 2)];
        enc[3] = '=';
        enc += 4;
        break;
    case 1:
        enc[0] = base64_string[(inblk[0] & 0xfc) >> 2];
        enc[1] = base64_string[((inblk[0] & 0x03) << 4)];
        enc[2] = '=';
        enc[3] = '=';
        enc += 4;
        break;
    }
    enc[0] = '\0';
    return 0;
}
