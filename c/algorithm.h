#ifndef _OBFS_ALGORITHM_H
#define _OBFS_ALGORITHM_H

int ss_md5_hmac_with_key(char *auth, char *msg, int msg_len, uint8_t *auth_key, int key_len);
int ss_sha1_hmac_with_key(char *auth, char *msg, int msg_len, uint8_t *auth_key, int key_len);
int ss_sha1_hmac(char *auth, char *msg, int msg_len, uint8_t *iv, size_t iv_len, uint8_t *key, size_t key_len);
void ss_bytes_to_key_with_size(const char *pass, size_t len, uint8_t *md, size_t md_size);
int ss_aes_128_cbc(char *encrypt, char *out_data, char *key);

#endif
