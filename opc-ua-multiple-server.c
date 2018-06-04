/******************************************************************************
 *
 * Copyright (c) 2017-2018, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  3. Neither the nme of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <linux/ptp_clock.h>
#include <linux/version.h>

#define DEFAULT_ETS_CHAN 1
#define DEFAULT_ETS_INDEX 1
#define MAX_CHANNELS 2
#define MAX_INDEXES 4

#define USE_OPEN62541

#ifdef USE_OPEN62541
#include "ua_config_standard.h"
#include "ua_network_tcp.h"

// TODO: make the port user changeable
#define DEFAULT_OPC_UA_PORT 4840

UA_Boolean running = 1;
#else /* ndef USE_OPEN62541 */
int running = 1;
#endif /* ndef USE_OPEN62541 */
int verbose;

#define LOG(x...)do { if (verbose) fprintf(stderr, x); } while (0)

#ifdef USE_OPEN62541
static UA_StatusCode read_ets(void *handle, const UA_NodeId nodeId,
			      UA_Boolean sourceTimeStamp,
			      const UA_NumericRange *range,
			      UA_DataValue *value)
#else /* ndef USE_OPEN62541 */
  static int read_ets(int fd)
#endif /* ndef USE_OPEN62541 */
{
  struct pollfd pfd;
  unsigned long n;
  int ready, timeout_ms;
  char buf[32];
  #ifdef USE_OPEN62541
  int fd = *(int *)handle;

  if (range) {
    value->hasStatus = true;
    value->status = UA_STATUSCODE_BADINDEXRANGEINVALID;
    return UA_STATUSCODE_GOOD;
  }
#endif /* def USE_OPEN62541 */

  pfd.fd = fd;
  pfd.events = POLLIN;
  pfd.revents = 0;
  timeout_ms = 100;

  ready = poll(&pfd, 1, timeout_ms);
  if (ready < 0) {
    fprintf(stderr, "Failed to poll: %d (%s)\n", errno, strerror(errno));
    return -1;
  } else if (ready == 0) {
    #ifdef USE_OPEN62541
    value->hasValue = false;
    return UA_STATUSCODE_GOOD;
#else /* ndef USE_OPEN62541 */
    return 0;
#endif /* ndef USE_OPEN62541 */
  }

  while (ready-- > 0) {
    n = read(fd, &e, sizeof(e));
    if (n != sizeof(e)) {
      fprintf(stderr, "read returns %lu bytes, expecting %lu bytes\n", n, sizeof(e));
      return -1;
    }

    LOG("%d event index %d at %lld.%09u\n", ready, e.index, e.t.sec, e.t.nsec);
  }
  snprintf(buf, sizeof(buf), "%lld.%09u", e.t.sec, e.t.nsec);

  #ifdef USE_OPEN62541
  UA_String string = UA_String_fromChars(buf);

  UA_Variant_setScalarCopy(&value->value, &string, &UA_TYPES[UA_TYPES_STRING]);
  value->hasValue = true;
  if (sourceTimeStamp) {
    value->hasSourceTimestamp = true;
    value->sourceTimestamp = UA_DateTime_now();
  }

  return UA_STATUSCODE_GOOD;
#else /* ndef USE_OPEN62541 */
  return 0;
#endif /* ndef USE_OPEN62541 */
}

static int get_ets(int fd, int index)
{

  #ifdef USE_OPEN62541
  /* Init the server. */
  UA_ServerNetworkLayer nl = UA_ServerNetworkLayerTCP(
						      UA_ConnectionConfig_standard, DEFAULT_OPC_UA_PORT);
  UA_ServerConfig config = UA_ServerConfig_standard;

  config.networkLayers = &nl;
  config.networkLayersSize = 1;
  UA_Server *server = UA_Server_new(config);

  /* Add a variable node. */
  /* 1) Set the variable attributes. */
  UA_VariableAttributes attr;

  UA_VariableAttributes_init(&attr);
  attr.description = UA_LOCALIZEDTEXT("en_US", "Time stamp");
  attr.displayName = UA_LOCALIZEDTEXT("en_US", "Time stamp");

  /* 2) Define where the variable shall be added with which browse name. */
  UA_NodeId new_node_id = UA_NODEID_STRING(1, "time.stamp");
  UA_NodeId parent_node_id = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
  UA_NodeId parent_ref_node_id = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
  UA_NodeId variable_type = UA_NODEID_NULL; /* No variable type defined. */
  UA_QualifiedName browse_name = UA_QUALIFIEDNAME(1, "Time stamp");

  UA_DataSource data_source = (UA_DataSource) {
    .handle = &fd,
    .read = read_ets,
    .write = NULL
  };
  UA_NodeId data_source_id;

  /* 3) Add the variable with data source. */
  UA_Server_addDataSourceVariableNode(server, new_node_id,
				      parent_node_id, parent_ref_node_id,
				      browse_name, variable_type, attr,
				      data_source, &data_source_id);
#endif /* def USE_OPEN62541 */

#ifdef USE_OPEN62541
  /* Run the server loop. */
  UA_Server_run(server, &running);
#else  /* ndef USE_OPEN62541 */
  while (running)
    read_ets(fd);
#endif /* ndef USE_OPEN62541 */

  /* Disable the external time stamp feature. */
#ifdef USE_OPEN62541
  UA_Server_delete(server);
  nl.deleteMembers(&nl);
#endif /* def USE_OPEN62541 */

  return 0;
}

static void sig_handler(int sig)
{
  /* Reset signal. */
  signal(sig, sig_handler);
  LOG("Received signal %d\n", sig);
  running = 0;
}

static void usage(char *prog_name)
{
  fprintf(stderr,
	  "Usage: %s [options]\n"
	  "Options:\n"
	  "  -h          Print this message and exit.\n"
	  "  -v          Verbose output\n"
	  "",
	  prog_name);
}

int main(int argc, char *argv[])
{
  char *prog_name;
  clockid_t clk_id;
  int c_ets, i_ets;
  int fd, opt;

  /* Installing signal handlers. */
  signal(SIGHUP, sig_handler);
  signal(SIGINT, sig_handler);
  signal(SIGQUIT, sig_handler);

  c_ets = DEFAULT_ETS_CHAN;
  i_ets = DEFAULT_ETS_INDEX;

  /* Parse command line arguments. */
  while ((opt = getopt(argc, argv, ":hv")) != EOF) {
    switch (opt) {
    case 'h':
      usage(prog_name);
      return 0;
    case 'v':
      verbose++;
      break;
    default: /* '?' */
      usage(prog_name);
      return -1;
    }
  }

  LOG("Hello from %s!\n", prog_name);

  /* These macros are defined in linux/posix-timers.h, but not able to
   * include the file.
   */
  #define CPUCLOCK_MAX            3
  #define CLOCKFD                 CPUCLOCK_MAX
  #define FD_TO_CLOCKID(fd)       ((~(clockid_t) (fd) << 3) | CLOCKFD)
  /* end */
  clk_id = FD_TO_CLOCKID(fd);
  if (clk_id == -1) {
    fprintf(stderr, "Failed to get clock id from %d\n", fd);
    close(fd);
    return -1;
  }

  if (get_ets(fd, i_ets)) {
    fprintf(stderr, "Cannot get external time stamps \n", i_ets);
    /* Fall through for cleanup. */
  }

  close(fd);
  LOG("Bye from %s!\n", prog_name);

  return 0;
}
