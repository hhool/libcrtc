/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_type_aray.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_TYPE_ARRAY_H_
#define _RC_CPLUS_INCLUDE_RC_TYPE_ARRAY_H_

#include "rc_common.h"
namespace crtc {

/// \sa
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/TypedArray

template <typename T>
class CRTC_EXPORT TypedArray {
 public:
  explicit TypedArray(size_t length = 0)
      : TypedArray(ArrayBuffer::New(length * sizeof(T))) {}

  TypedArray(const T* data, size_t length = 0)
      : TypedArray(ArrayBuffer::New(data, length * sizeof(T))) {}

  TypedArray(const TypedArray<T>& typedArray)
      : _empty(0),
        _data(typedArray._data),
        _length(typedArray._length),
        _byteOffset(typedArray._byteOffset),
        _byteLength(typedArray._byteLength),
        _buffer(typedArray._buffer) {}

  template <typename N>
  TypedArray(const TypedArray<N>& typedArray)
      : TypedArray(typedArray.Buffer()) {}

  TypedArray(const Let<ArrayBuffer>& buffer,
             size_t byteOffset = 0,
             size_t byteLength = 0)
      : _empty(0),
        _data(nullptr),
        _length(0),
        _byteOffset(0),
        _byteLength(0),
        _buffer(buffer) {
    if (_buffer.IsEmpty()) {
      _buffer = ArrayBuffer::New(byteLength - byteOffset);
    }

    byteLength = (!byteLength) ? _buffer->ByteLength() : byteLength;
    byteLength -= byteOffset;

    if (byteLength && (byteLength % sizeof(T)) == 0) {
      _data = reinterpret_cast<T*>(buffer->Data() + byteOffset);
      _byteOffset = byteOffset;
      _byteLength = byteLength;
      _length = byteLength / sizeof(T);
    }
  }

  inline size_t Length() const { return _length; }

  inline size_t ByteOffset() const { return _byteOffset; }

  inline size_t ByteLength() const { return _byteLength; }

  inline Let<ArrayBuffer> Buffer() const { return _buffer; }

  inline Let<ArrayBuffer> Slice(size_t begin = 0, size_t end = 0) const {
    if (_length) {
      return _buffer->Slice(begin * sizeof(T), end * sizeof(T));
    }

    return ArrayBuffer::New();
  }

  inline T* Data() { return (_length) ? _data : nullptr; }

  inline const T* Data() const { return (_length) ? _data : nullptr; }

  inline T& Get(const size_t index) {
    if (index < _length) {
      return _data[index];
    }

    return _empty;
  }

  inline const T& Get(const size_t index) const {
    if (index < _length) {
      return _data[index];
    }

    return TypedArray<T>::empty;
  }

  inline void Set(const size_t index, const T& value) {
    if (index < _length) {
      _data[index] = index;
    }
  }

  inline T& operator[](const size_t index) {
    if (index < _length) {
      return _data[index];
    }

    return _empty;
  }

  inline const T& operator[](const size_t index) const {
    if (index < _length) {
      return _data[index];
    }

    return TypedArray<T>::empty;
  }

 protected:
  static const T empty = 0;

  T _empty;
  T* _data;
  size_t _length;
  size_t _byteOffset;
  size_t _byteLength;
  Let<ArrayBuffer> _buffer;
};

/// \sa
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Int8Array

typedef TypedArray<int8_t> Int8Array;

/// \sa
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Uint8Array

typedef TypedArray<uint8_t> Uint8Array;

/// \sa
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Int16Array

typedef TypedArray<int16_t> Int16Array;

/// \sa
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Uint16Array

typedef TypedArray<uint16_t> Uint16Array;

/// \sa
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Int32Array

typedef TypedArray<int32_t> Int32Array;

/// \sa
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Uint32Array

typedef TypedArray<uint32_t> Uint32Array;

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_TYPE_ARRAY_H_