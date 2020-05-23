/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_common.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_COMMON_H_
#define _RC_CPLUS_INCLUDE_COMMON_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#ifdef CRTC_OS_WIN
#define CRTC_EXPORT __declspec(dllexport)
#define CRTC_NO_EXPORT __declspec(dllimport)
#else
#define CRTC_EXPORT __attribute__((visibility("default")))
#define CRTC_NO_EXPORT __attribute__((visibility("hidden")))
#endif

#ifndef CRTC_STATIC
#define CRTC_STATIC(className)          \
  explicit className() = delete;        \
  className(const className&) = delete; \
  className& operator=(const className&) = delete;
#endif

#ifndef CRTC_PRIVATE
#define CRTC_PRIVATE(className)         \
  className(const className&) = delete; \
  className& operator=(const className&) = delete;
#endif

#endif // _RC_CPLUS_INCLUDE_COMMON_H_