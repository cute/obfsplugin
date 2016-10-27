#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include "obfs.h"
#include "algorithm.h"

int ss_md5_hmac_with_key(char *auth, char *msg, int msg_len, uint8_t *auth_key, int key_len) {
    uint8_t hash[16];
    HMAC(EVP_md5(), auth_key, key_len, (uint8_t *)msg, msg_len, (uint8_t *)hash, NULL);
    memcpy(auth, hash, 16);
    return 0;
}

int ss_sha1_hmac_with_key(char *auth, char *msg, int msg_len, uint8_t *auth_key, int key_len) {
    uint8_t hash[20];
    HMAC(EVP_sha1(), auth_key, key_len, (uint8_t *)msg, msg_len, (uint8_t *)hash, NULL);
    memcpy(auth, hash, 20);
    return 0;
}

int ss_sha1_hmac(char *auth, char *msg, int msg_len, uint8_t *iv, size_t iv_len, uint8_t *key, size_t key_len) {
    uint8_t hash[ONETIMEAUTH_BYTES * 2];
    uint8_t auth_key[EVP_MAX_IV_LENGTH + EVP_MAX_KEY_LENGTH];
    memcpy(auth_key, iv, iv_len);
    memcpy(auth_key + iv_len, key, key_len);
    HMAC(EVP_sha1(), auth_key, (int)(iv_len + key_len), (uint8_t *)msg, msg_len, (uint8_t *)hash, NULL);
    memcpy(auth, hash, ONETIMEAUTH_BYTES);
    return 0;
}

void ss_bytes_to_key_with_size(const char *pass, size_t len, uint8_t *md, size_t md_size) {
    uint8_t result[128];
    MD5((const unsigned char *)pass, len, result);
    memcpy(md, result, 16);
    for (int i = 16; i < md_size; i += 16) {
        memcpy(result + 16, pass, len);
        MD5(result, 16 + len, result);
        memcpy(md + i, result, 16);
    }
}

int ss_aes_128_cbc(char *encrypt, char *out_data, char *key)
{
    u_char iv[16] = {};
    AES_KEY aes;
    AES_set_encrypt_key((u_char*)key, 128, &aes);
    AES_cbc_encrypt((const u_char *)encrypt, (u_char *)out_data, 16, &aes, iv, AES_ENCRYPT);
    return 0;
}

