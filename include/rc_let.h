/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_let.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_LET_H_
#define _RC_CPLUS_INCLUDE_RC_LET_H_

#include "rc_common.h"

namespace crtc {
/// \sa
/// https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Statements/let

template <class T>
class CRTC_EXPORT Let {
 public:
  template <typename... Args>
  inline static Let<T> New(Args&&... args) {
    return Let<T>(new Constructor<Args...>(std::forward<Args>(args)...));
  }

  inline static Let<T> Empty() { return Let<T>(); }

  inline explicit Let() : _ptr(nullptr) {}

  inline ~Let() { Let::RemoveRef(); }

  inline Let(T* ptr) : _ptr(ptr) { Let::AddRef(); }

  inline Let(const Let<T>& src) : _ptr(*src) { Let::AddRef(); }

  template <class S>
  inline Let(Let<S> src) : _ptr((T*)(*src)) {
    Let::AddRef();
  }

  inline Let<T>& operator=(T* src) {
    if (src) {
      src->AddRef();
    }

    Let::RemoveRef();

    _ptr = src;
    return *this;
  }

  template <class S>
  inline static Let<T> Cast(S* src) {
    return Let<T>(static_cast<T*>(src));
  }

  template <class S>
  inline static Let<T> Cast(const Let<S>& src) {
    return Let<T>(reinterpret_cast<T*>(*src));
  }

  inline Let<T>& operator=(const Let<T>& src) { return *this = src._ptr; }
  inline bool IsEmpty() const { return (_ptr == nullptr); }
  inline operator T*() const { return _ptr; }
  inline T* operator*() const { return _ptr; }
  inline T* operator->() const { return _ptr; }

  inline void Dispose() const {
    if (_ptr) {
      T* ptr = _ptr;
      _ptr = nullptr;

      ptr->RemoveRef();
    }
  }

  template <class R>
  inline R& operator[](const size_t index) {
    return _ptr[index];
  }

  template <class R>
  inline const R& operator[](const size_t index) const {
    return _ptr[index];
  }

 private:
  template <typename... Args>
  class Constructor : public T {
   public:
    explicit Constructor(Args&&... args)
        : T(std::forward<Args>(args)...), reference_count(0) {}

   protected:
    inline virtual int AddRef() const {
      return Atomic::Increment(&reference_count);
    }

    inline virtual int RemoveRef() const {
      int res = Atomic::Decrement(&reference_count);

      if (!res) {
        delete this;
      }

      return res;
    }

    inline virtual int RefCount() const {
      return Atomic::AcquireLoad(&reference_count);
    }

    virtual ~Constructor() {}

   private:
    mutable volatile int reference_count = 0;
  };

  inline void AddRef() const {
    if (_ptr) {
      _ptr->AddRef();
    }
  }

  inline void RemoveRef() const {
    if (_ptr) {
      _ptr->RemoveRef();
    }
  }

 protected:
  mutable T* _ptr;
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_LET_H_
