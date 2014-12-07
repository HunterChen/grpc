/*
 *
 * Copyright 2014, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __GRPC_SUPPORT_TIME_H__
#define __GRPC_SUPPORT_TIME_H__
/* Time support.
   We use gpr_timespec, which is typedefed to struct timespec on platforms which
   have it. On some machines, absolute times may be in local time.  */

/* Platform specific header declares gpr_timespec.
   gpr_timespec contains:
      time_t tv_sec;  // seconds since start of 1970
      int tv_nsec;    // nanoseconds;  always in 0..999999999; never negative.
 */

#include <grpc/support/port_platform.h>

#if defined(GPR_POSIX_TIME)
#include <grpc/support/time_posix.h>
#elif defined(GPR_WIN32)
#include <grpc/support/time_win32.h>
#else
#error could not determine platform for time
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Time constants. */
extern const gpr_timespec gpr_time_0;     /* The zero time interval. */
extern const gpr_timespec gpr_inf_future; /* The far future */
extern const gpr_timespec gpr_inf_past;   /* The far past. */

#define GPR_MS_PER_SEC 1000
#define GPR_US_PER_SEC 1000000
#define GPR_NS_PER_SEC 1000000000
#define GPR_NS_PER_MS 1000000
#define GPR_NS_PER_US 1000
#define GPR_US_PER_MS 1000

/* Return the current time measured from the system's default epoch. */
gpr_timespec gpr_now(void);

/* Return -ve, 0, or +ve according to whether a < b, a == b, or a > b
   respectively.  */
int gpr_time_cmp(gpr_timespec a, gpr_timespec b);

/* Add and subtract times.  Calculations saturate at infinities. */
gpr_timespec gpr_time_add(gpr_timespec a, gpr_timespec b);
gpr_timespec gpr_time_sub(gpr_timespec a, gpr_timespec b);

/* Return a timespec representing a given number of microseconds.  LONG_MIN is
   interpreted as gpr_inf_past, and LONG_MAX as gpr_inf_future.  */
gpr_timespec gpr_time_from_micros(long x);
gpr_timespec gpr_time_from_nanos(long x);
gpr_timespec gpr_time_from_millis(long x);
gpr_timespec gpr_time_from_seconds(long x);
gpr_timespec gpr_time_from_minutes(long x);
gpr_timespec gpr_time_from_hours(long x);

/* Return 1 if two times are equal or within threshold of each other,
   0 otherwise */
int gpr_time_similar(gpr_timespec a, gpr_timespec b, gpr_timespec threshold);

/* Sleep until at least 'until' - an absolute timeout */
void gpr_sleep_until(gpr_timespec until);

struct timeval gpr_timeval_from_timespec(gpr_timespec t);

gpr_timespec gpr_timespec_from_timeval(struct timeval t);

#ifdef __cplusplus
}
#endif

#endif  /* __GRPC_SUPPORT_TIME_H__ */