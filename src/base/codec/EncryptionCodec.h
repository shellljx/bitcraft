//
// Created by 李金祥 on 2022/5/28.
//

#pragma once

#include "base/io/EncodeStream.h"
#include "base/io/DecodeStream.h"

typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;

namespace bitcraft {

class EncryptionCodec {
 public:
  EncryptionCodec();
  ~EncryptionCodec();

  void setEnable();
  void encode(const unsigned char *in, int length, unsigned char *out, int &outLength);

  std::unique_ptr<ByteData> decode(std::unique_ptr<ByteData> data);

 private:
  EVP_CIPHER_CTX* encryption_context;
  EVP_CIPHER_CTX* decryption_context;
  unsigned int blocksize = 0;
  bool enable = false;
};
}