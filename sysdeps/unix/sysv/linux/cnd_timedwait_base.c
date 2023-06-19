/* C11 threads conditional timed wait implementation - Linux variant.
   Copyright (C) 2020-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <time.h>
#include <shlib-compat.h>
#include "thrd_priv.h"

int
__cnd_timedwait_base64 (cnd_t *restrict cond, mtx_t *restrict mutex,
                        int time_base,
                        const struct __timespec64 *restrict time_point)
{
  int err_code = __pthread_cond_clockwait64 ((pthread_cond_t *) cond,
                                             (pthread_mutex_t *) mutex,
                                             time_base, time_point);
  return thrd_err_map (err_code);
}

#if __TIMESIZE == 64
strong_alias (__cnd_timedwait_base64, ___cnd_timedwait_base)
#else
libc_hidden_def (__cnd_timedwait_base64)

int
___cnd_timedwait_base (cnd_t *restrict cond, mtx_t *restrict mutex,
                       int time_base,
                       const struct timespec *restrict time_point)
{
  struct __timespec64 ts64 = valid_timespec_to_timespec64 (*time_point);

  return __cnd_timedwait_base64 (cond, mutex, time_base, &ts64);
}
#endif /* __TIMESIZE == 64 */
versioned_symbol (libc, ___cnd_timedwait_base, cnd_timedwait_base, GLIBC_2_34);

#if OTHER_SHLIB_COMPAT (libpthread, GLIBC_2_28, GLIBC_2_34)
compat_symbol (libpthread, ___cnd_timedwait_base, cnd_timedwait_base, GLIBC_2_28);
#endif
