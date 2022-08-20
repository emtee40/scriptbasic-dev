// WebExt - Web Utility Functions

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../../basext.h"
#include "hmac_sha256.h"


besVERSION_NEGOTIATE
  return (int)INTERFACE_VERSION;
besEND

besSUB_START
besEND

besSUB_FINISH
besEND


#define SHA256_HASH_SIZE 32

static int mod_table[] = {0, 2, 1};
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};


besFUNCTION(base64_encode)
  const unsigned char *data;
  size_t input_length;
  size_t output_length;

  besARGUMENTS("z")
    &data
  besARGEND

  input_length = strlen(data);
  output_length = 4 * ((input_length + 2) / 3);

  char *encoded_data = malloc(output_length);
  if (encoded_data == NULL) return NULL;

  for (int i = 0, j = 0; i < input_length;) {

    uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
    uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
    uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

    uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

    encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
  }

  for (int i = 0; i < mod_table[input_length % 3]; i++)
    encoded_data[output_length - 1 - i] = '=';

  output_length  = output_length - 1 + mod_table[input_length % 3];
  encoded_data[output_length] = 0;

  besRETURN_STRING(encoded_data);
  free(encoded_data);

besEND


besFUNCTION(base64_decode)
  const char *data;
  size_t input_length;
  size_t output_length;

  char *decoding_table = malloc(256);
  for (int i = 0; i < 64; i++)
    decoding_table[(unsigned char) encoding_table[i]] = i;

  besARGUMENTS("z")
    &data
  besARGEND

  input_length = strlen(data);
  if (input_length % 4 != 0) return NULL;
  output_length = input_length / 4 * 3;
  if (data[input_length - 1] == '=') (output_length)--;
  if (data[input_length - 2] == '=') (output_length)--;

  unsigned char *decoded_data = malloc(output_length);
  if (decoded_data == NULL) return NULL;

  for (int i = 0, j = 0; i < input_length;) {
    uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

    uint32_t triple = (sextet_a << 3 * 6)
      + (sextet_b << 2 * 6)
      + (sextet_c << 1 * 6)
      + (sextet_d << 0 * 6);

    if (j < output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
    if (j < output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
    if (j < output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
  }

  decoded_data[output_length] = 0;

  besRETURN_STRING(decoded_data);
  free(decoding_table);
  free(decoded_data);

besEND


besFUNCTION(hmacsha256)
  const char* str_data;
  const char* str_key;
  uint8_t out[SHA256_HASH_SIZE];
  char out_str[SHA256_HASH_SIZE * 2 + 1];
  unsigned i;

  besARGUMENTS("zz")
    &str_data, &str_key
  besARGEND

  hmac_sha256(str_key, strlen(str_key),
              str_data, strlen(str_data),
              &out, sizeof(out));

  memset(&out_str, 0, sizeof(out_str));
  for (i = 0; i < sizeof(out); i++) {
    snprintf(&out_str[i*2], 3, "%02x", out[i]);
  }

  besRETURN_STRING(out_str);

besEND
