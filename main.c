/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "config.h"
#include "inc/cavli_log.h"
#include "inc/hello.h"
#include <poll.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef ANDROID_CHANGES

#include <android/log.h>
#include <cutils/sockets.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <private/android_filesystem_config.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#endif

static void terminate(int signal) { exit(1); }

static void terminated() { do_plog(LOG_LV_INFO, "Bye\n"); }

int main(int argc, char **argv) {

  do_plog(LOG_LV_INFO, "Start Sample C/C++ Application... \n");

  signal(SIGHUP, terminate);
  signal(SIGINT, terminate);
  signal(SIGTERM, terminate);
  signal(SIGPIPE, SIG_IGN);
  atexit(terminated);

  while (1) {
    say_hello();
    sleep(5);
  }

  return 0;
}
