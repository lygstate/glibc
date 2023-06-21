/* Basic tests for timespec_get.
   Copyright (C) 2021-2023 Free Software Foundation, Inc.
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
#include <support/check.h>

static void
test_timespec_get (int timebase)
{
    struct timespec ts;
    TEST_COMPARE (timespec_get (&ts, timebase), timebase);
    TEST_VERIFY (ts.tv_nsec >= 0);
    TEST_VERIFY (ts.tv_nsec < 1000000000);
}

static void
test_timespec_get_not_support(int timebase)
{
    struct timespec ts;
    TEST_COMPARE (timespec_get (&ts, timebase), 0);
}

static int
do_test (void)
{
  {
    struct timespec ts;
    TEST_COMPARE (timespec_get (&ts, 0), 0);
  }

  {
    test_timespec_get (TIME_UTC);
    test_timespec_get (TIME_MONOTONIC);
    test_timespec_get (TIME_ACTIVE);
    test_timespec_get (TIME_THREAD_ACTIVE);
  }

  {
    test_timespec_get (TIME_MONOTONIC_RAW);
    test_timespec_get (TIME_UTC_COARSE);
    test_timespec_get (TIME_MONOTONIC_COARSE);
  }

  {
#ifdef CLOCK_BOOTTIME
    test_timespec_get (TIME_BOOTTIME);
#else
    test_timespec_get_not_support (TIME_BOOTTIME);
#endif
#ifdef CLOCK_REALTIME_ALARM
    test_timespec_get (TIME_UTC_ALARM);
#else
    test_timespec_get_not_support (TIME_UTC_ALARM);
#endif
#ifdef CLOCK_BOOTTIME_ALARM
    test_timespec_get (TIME_BOOTTIME_ALARM);
#else
    test_timespec_get_not_support (TIME_BOOTTIME_ALARM);
#endif
#ifdef CLOCK_SGI_CYCLE
    test_timespec_get (TIME_SGI_CYCLE);
#else
    test_timespec_get_not_support (TIME_SGI_CYCLE);
#endif
#ifdef CLOCK_TAI
    test_timespec_get (TIME_TAI);
#else
    test_timespec_get_not_support (TIME_TAI);
#endif
  }

  return 0;
}

#include <support/test-driver.c>
