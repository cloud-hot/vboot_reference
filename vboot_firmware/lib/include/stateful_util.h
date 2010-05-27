/* Copyright (c) 2010 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Helper functions/wrappers for memory allocations, manipulation and
 * comparison.
 */

#ifndef VBOOT_FIRMWARE_LIB_UTILITY_H_
#define VBOOT_FIRMWARE_LIB_UTILITY_H_

#include <stdint.h>
#include <string.h>

#include "utility.h"

/* Track remaining data to be read in a buffer. */
typedef struct MemcpyState {
  void* remaining_buf;
  uint64_t remaining_len;  /* Remaining length of the buffer. */
  uint8_t overrun;  /* Flag set to 1 when an overrun occurs. */
} MemcpyState;

/* Copy [len] bytes into [dst] only if there's enough data to read according
 * to [state].
 * On success, return [dst] and update [state].
 * On failure, return NULL, set remaining len in state to -1.
 *
 * Useful for iterating through a binary blob to populate a struct. After the
 * first failure (buffer overrun), successive calls will always fail.
 */
void* StatefulMemcpy(MemcpyState* state, void* dst, uint64_t len);

/* Like StatefulMemcpy() but copies in the opposite direction, populating
 * data from [src] into the buffer encapsulated in state [state].
 * On success, return [src] and update [state].
 * On failure, return NULL, set remaining_len in state to -1.
 *
 * Useful for iterating through a structure to populate a binary blob. After the
 * first failure (buffer overrun), successive calls will always fail.
 */
const void* StatefulMemcpy_r(MemcpyState* state, const void* src, uint64_t len);

/* Like StatefulMemcpy_r() but fills a portion of the encapsulated buffer with
 * a constant value.
 * On success, return a meaningless but non-NULL pointer and updates [state].
 * On failure, return NULL, set remaining_len in state to -1.
 *
 * After the first failure (buffer overrun), successive calls will always fail.
 */
const void* StatefulMemset_r(MemcpyState* state, const uint8_t val,
                             uint64_t len);

#endif  /* VBOOT_FIRMWARE_LIB_UTILITY_H_ */