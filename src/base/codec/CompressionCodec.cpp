//
// Created by 李金祥 on 2022/5/28.
//

#include "CompressionCodec.h"
#include <zlib.h>
#include <string>

namespace bitcraft {

CompressionCodec::CompressionCodec() : compressionThreshold(-1) {}
std::unique_ptr<ByteData> CompressionCodec::decode(DecodeStream &in) const {
  if (compressionThreshold > 0) {
    auto dataLength = in.readVarInt();
    if (dataLength <= 0) {
      //datalength is zero without compression
      auto length = in.bytesAvailable();
      return ByteData::MakeWithoutCopy(in.readBytes(length).data(), length);
    } else {
      return deCompression(in, dataLength);
    }
  } else {
    auto length = in.bytesAvailable();
    return ByteData::MakeWithoutCopy(in.readBytes(length).data(), length);
  }
}

std::unique_ptr<ByteData> CompressionCodec::encode(std::unique_ptr<ByteData> data) const {
  if (compressionThreshold > 0) {
    auto stream = EncodeStream();
    if (data->length() < compressionThreshold) {
      stream.writeVarInt(0);
      stream.writeByteData(data.get());
    } else {
      stream.writeVarInt(data->length());
      auto compressedData = compression(std::move(data));
      stream.writeByteData(compressedData.get());
    }
    return stream.release();
  }
  return data;
}

std::unique_ptr<ByteData> CompressionCodec::compression(std::unique_ptr<ByteData> data) {
  int ret;
  int chunk = 1024 * 6;
  unsigned have;
  z_stream strm;
  memset(&strm, 0, sizeof(strm));
  ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
  if (ret != Z_OK) {
    throw std::runtime_error("deflate init error");
  }
  unsigned char input[data->length()];
  memcpy(input, data->data(), data->length());
  unsigned char output[chunk];
  EncodeStream outStream;

  strm.avail_in = data->length();
  strm.next_in = input;
  do {
    strm.avail_out = chunk;
    strm.next_out = output;
    ret = deflate(&strm, Z_FINISH);
    have = chunk - strm.avail_out;
    outStream.writeBytes(output, have);
  } while (strm.avail_out == 0);
  deflateEnd(&strm);
  return outStream.release();
}

std::unique_ptr<ByteData> CompressionCodec::deCompression(DecodeStream &in, int uLength) {
  int ret;
  int chunk = 1024 * 6;
  auto buffer = new unsigned char [chunk];
  z_stream strm;
  memset(&strm, 0, sizeof(strm));
  strm.next_in = const_cast<unsigned char *>(in.data()+in.position());
  strm.avail_in = in.bytesAvailable();
  strm.next_out = buffer;
  strm.avail_out = static_cast<unsigned int>(chunk);

  ret = inflateInit(&strm);
  if (ret != Z_OK) {
    throw std::runtime_error("zlib init failed");
  }

  EncodeStream outStream(512);
  for (;;) {
    ret = inflate(&strm, Z_NO_FLUSH);
    switch (ret) {
      case Z_OK:outStream.writeBytes(buffer, chunk - strm.avail_out);
        strm.next_out = buffer;
        strm.avail_out = static_cast<unsigned int>(chunk);
        if (strm.avail_in == 0) {
          inflateEnd(&strm);
          return outStream.release();
        }
        break;
      case Z_STREAM_END:outStream.writeBytes(buffer, chunk - strm.avail_out);
        inflateEnd(&strm);
        return outStream.release();
        break;
      default:inflateEnd(&strm);
        throw std::runtime_error("Inflate decompression failed: " + std::string(strm.msg));
        break;
    }
  }
}
}