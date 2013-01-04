/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=78:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_config_h___
#define js_config_h___

/* Definitions set at build time that affect SpiderMonkey's public API.
   This header file is generated by the SpiderMonkey configure script,
   and installed along with jsapi.h.  */

/* Define to 1 if SpiderMonkey should support multi-threaded clients.  */
/* #undef JS_THREADSAFE */

/* Define to 1 if SpiderMonkey should include ctypes support.  */
/* #undef JS_HAS_CTYPES */

/* Define to 1 if SpiderMonkey should support the ability to perform
   entirely too much GC.  */
/* #undef JS_GC_ZEAL */

/* Define to 1 if the <endian.h> header is present and
   useable.  See jscpucfg.h.  */
/* #undef JS_HAVE_ENDIAN_H */

/* Define to 1 if the <machine/endian.h> header is present and
   useable.  See jscpucfg.h.  */
/* #undef JS_HAVE_MACHINE_ENDIAN_H */

/* Define to 1 if the <sys/isa_defs.h> header is present and
   useable.  See jscpucfg.h.  */
/* #undef JS_HAVE_SYS_ISA_DEFS_H */

/* Define to 1 if the <sys/types.h> defines int8_t, etc. */
/* #undef JS_SYS_TYPES_H_DEFINES_EXACT_SIZE_TYPES */

/* Define to 1 if the N-byte __intN types are defined by the
   compiler.  */
#define JS_HAVE___INTN 1

/* Define to 1 if #including <stddef.h> provides definitions for
   intptr_t and uintptr_t.  */
#define JS_STDDEF_H_HAS_INTPTR_T 1

/* Define to 1 if #including <crtdefs.h> provides definitions for
   intptr_t and uintptr_t.  */
/* #undef JS_CRTDEFS_H_HAS_INTPTR_T */

/* The configure script defines these if it doesn't #define
   JS_HAVE_STDINT_H.  */
/* #undef JS_INT8_TYPE */
/* #undef JS_INT16_TYPE */
/* #undef JS_INT32_TYPE */
/* #undef JS_INT64_TYPE */
/* #undef JS_INTPTR_TYPE */
/* #undef JS_BYTES_PER_WORD */

/* Some mozilla code uses JS-friend APIs that depend on JS_METHODJIT being
   correct. */
#define JS_METHODJIT 1

/* Define to 1 to enable support for E4X (ECMA-357), 0 to disable it. */
#define JS_HAS_XML_SUPPORT 1

#endif /* js_config_h___ */