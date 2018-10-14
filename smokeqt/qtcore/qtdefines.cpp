#include <cstdio>
#include "qglobal.h"
int main(int argc, char** argv)
{
#ifdef QT_USE_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_USE_NAMESPACE");
#endif
#ifdef QT_BEGIN_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_BEGIN_NAMESPACE");
#endif
#ifdef QT_END_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_END_NAMESPACE");
#endif
#ifdef QT_BEGIN_INCLUDE_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_BEGIN_INCLUDE_NAMESPACE");
#endif
#ifdef QT_END_INCLUDE_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_END_INCLUDE_NAMESPACE");
#endif
#ifdef QT_BEGIN_MOC_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_BEGIN_MOC_NAMESPACE");
#endif
#ifdef QT_END_MOC_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_END_MOC_NAMESPACE");
#endif
#ifdef QT_END_MOC_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_END_MOC_NAMESPACE");
#endif
#ifdef QT_BEGIN_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_BEGIN_NAMESPACE");
#endif
#ifdef QT_END_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_END_NAMESPACE");
#endif
#ifdef QT_USE_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_USE_NAMESPACE");
#endif
#ifdef QT_BEGIN_INCLUDE_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_BEGIN_INCLUDE_NAMESPACE");
#endif
#ifdef QT_END_INCLUDE_NAMESPACE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_END_INCLUDE_NAMESPACE");
#endif
#ifdef QT_BEGIN_HEADER
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_BEGIN_HEADER");
#endif
#ifdef QT_END_HEADER
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_END_HEADER");
#endif
#ifdef QT_BEGIN_INCLUDE_HEADER
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_BEGIN_INCLUDE_HEADER");
#endif
#ifdef QT_NO_GETIFADDRS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_GETIFADDRS");
#endif
#ifdef QT_LINUXBASE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_LINUXBASE");
#endif
#ifdef QT_VISIBILITY_AVAILABLE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_VISIBILITY_AVAILABLE");
#endif
#ifdef QT_HAVE_ARMV6
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_HAVE_ARMV6");
#endif
#ifdef QT_HAVE_ARMV6
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_HAVE_ARMV6");
#endif
#ifdef QT_NO_STL_WCHAR
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_STL_WCHAR");
#endif
#ifdef QT_NO_ARM_EABI
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_ARM_EABI");
#endif
#ifdef QT_NO_TEMPLATE_TEMPLATE_PARAMETERS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_TEMPLATE_TEMPLATE_PARAMETERS");
#endif
#ifdef QT_NO_TEMPLATE_TEMPLATE_PARAMETERS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_TEMPLATE_TEMPLATE_PARAMETERS");
#endif
#ifdef QT_STATIC_CONST_IMPL
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_STATIC_CONST_IMPL");
#endif
#ifdef QT_DEPRECATED
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_DEPRECATED");
#endif
#ifdef QT_DEPRECATED_VARIABLE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_DEPRECATED_VARIABLE");
#endif
#ifdef QT_DEPRECATED_CONSTRUCTOR
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_DEPRECATED_CONSTRUCTOR");
#endif
#ifdef QT_COMPAT_WARNINGS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_COMPAT_WARNINGS");
#endif
#ifdef QT_COMPAT
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_COMPAT");
#endif
#ifdef QT_MOC_COMPAT
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_MOC_COMPAT");
#endif
#ifdef QT_MOC_COMPAT
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_MOC_COMPAT");
#endif
#ifdef QT_ASCII_CAST_WARN_CONSTRUCTOR
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_ASCII_CAST_WARN_CONSTRUCTOR");
#endif
#ifdef QT_ASCII_CAST_WARN
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_ASCII_CAST_WARN");
#endif
#ifdef QT_ASCII_CAST_WARN_CONSTRUCTOR
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_ASCII_CAST_WARN_CONSTRUCTOR");
#endif
#ifdef QT_FASTCALL
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_FASTCALL");
#endif
#ifdef QT_FASTCALL
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_FASTCALL");
#endif
#ifdef QT_FASTCALL
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_FASTCALL");
#endif
#ifdef QT_ENSURE_STACK_ALIGNED_FOR_SSE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_ENSURE_STACK_ALIGNED_FOR_SSE");
#endif
#ifdef QT_NO_FPU
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_FPU");
#endif
#ifdef QT_NO_COP
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_COP");
#endif
#ifdef QT_NO_LPR
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_LPR");
#endif
#ifdef QT_NO_EXCEPTIONS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_EXCEPTIONS");
#endif
#ifdef QT_NO_EXCEPTIONS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_EXCEPTIONS");
#endif
#ifdef QT_NO_DEBUG
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_DEBUG");
#endif
#ifdef QT_DEBUG
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_DEBUG");
#endif
#ifdef QT_NO_DEBUG_STREAM
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_DEBUG_STREAM");
#endif
#ifdef QT_NO_PAINT_DEBUG
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_PAINT_DEBUG");
#endif
#ifdef QT_NO_WARNINGS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_WARNINGS");
#endif
#ifdef QT_SYMBIAN_SUPPORTS_ADVANCED_POINTER
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_SYMBIAN_SUPPORTS_ADVANCED_POINTER");
#endif
#ifdef QT_SYMBIAN_SUPPORTS_SGIMAGE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_SYMBIAN_SUPPORTS_SGIMAGE");
#endif
#ifdef QT_NO_CONCURRENT
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_CONCURRENT");
#endif
#ifdef QT_NO_QFUTURE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_QFUTURE");
#endif
#ifdef QT_NO_QFUTURE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_QFUTURE");
#endif
#ifdef QT_NO_CONCURRENT_MAP
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_CONCURRENT_MAP");
#endif
#ifdef QT_NO_CONCURRENT_FILTER
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_CONCURRENT_FILTER");
#endif
#ifdef QT_NO_RAWFONT
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_RAWFONT");
#endif
#ifdef QT_ARCH_X86_64
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_ARCH_X86_64");
#endif
#ifdef QT_ARCH_X86_64
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_ARCH_X86_64");
#endif
#ifdef QT_LINKED_OPENSSL
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_LINKED_OPENSSL");
#endif
#ifdef QT_NO_ALSA
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_ALSA");
#endif
#ifdef QT_NO_CUPS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_CUPS");
#endif
#ifdef QT_NO_EGL
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_EGL");
#endif
#ifdef QT_NO_GSTREAMER
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_GSTREAMER");
#endif
#ifdef QT_NO_ICD
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_ICD");
#endif
#ifdef QT_NO_IMAGEFORMAT_JPEG
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_IMAGEFORMAT_JPEG");
#endif
#ifdef QT_NO_IMAGEFORMAT_MNG
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_IMAGEFORMAT_MNG");
#endif
#ifdef QT_NO_IMAGEFORMAT_TIFF
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_IMAGEFORMAT_TIFF");
#endif
#ifdef QT_NO_INOTIFY
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_INOTIFY");
#endif
#ifdef QT_NO_MREMAP
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_MREMAP");
#endif
#ifdef QT_NO_NIS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_NIS");
#endif
#ifdef QT_NO_OPENVG
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_OPENVG");
#endif
#ifdef QT_NO_PHONON
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_PHONON");
#endif
#ifdef QT_NO_S60
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_S60");
#endif
#ifdef QT_NO_STYLE_S60
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_STYLE_S60");
#endif
#ifdef QT_NO_SXE
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_SXE");
#endif
#ifdef QT_NO_WEBKIT
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_WEBKIT");
#endif
#ifdef QT_NO_XVIDEO
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_XVIDEO");
#endif
#ifdef QT_NO_ZLIB
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_NO_ZLIB");
#endif
#ifdef QT_USE_MATH_H_FLOATS
#ifdef QTDEF_MULTI
printf(";");
#endif
#ifndef QTDEF_MULTI
#define QTDEF_MULTI
#endif
printf("QT_USE_MATH_H_FLOATS");
#endif
return 0;
}
