
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

#include <sys/time.h>
#include <sys/timex.h>
#include <linux/rtc.h>
#include <linux/version.h>

#define RTC_DEVICE "/dev/rtc0"
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

#define LOG(x...)do { if (verbose) fprintf(stdout, x); } while (0)

#ifdef USE_OPEN62541
static UA_StatusCode read_ets(void *handle, const UA_NodeId nodeId,
			      UA_Boolean sourceTimeStamp,
			      const UA_NumericRange *range,
			      UA_DataValue *value)
#else /* ndef USE_OPEN62541 */
  static int read_ets(int fd)
#endif /* ndef USE_OPEN62541 */
{

  struct tm tm;
  unsigned long n, *epoch_p;
  int rc=-1;
  char buf[32];
#ifdef USE_OPEN62541
  int fd = *(int *)handle;
  
  if (range) {
    value->hasStatus = true;
    value->status = UA_STATUSCODE_BADINDEXRANGEINVALID;
    return UA_STATUSCODE_GOOD;
  }
#endif /* def USE_OPEN62541 */

  rc = ioctl (fd, RTC_RD_TIME, &tm);
  /* RTC_RD_TIME can fail when the device driver detects
     that the RTC isn't running or contains invalid data.
     Such failure has been detected earlier, unless: We used
     noint_fallback=1 to get busywait_uip_fall() as fallback.
     Or: UIE interrupts do beat, but RTC is invalid. */
  if (rc == -1) {
    fprintf(stderr, "RTC_RD_TIME failed\n");
#ifdef USE_OPEN62541
    value->hasValue = false;
    return UA_STATUSCODE_GOOD;
#else
    return 0;
#endif    
  }
  
  LOG("event at %4d/%.2d/%.2d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  
  snprintf(buf, sizeof(buf), "%4d/%.2d/%.2d-%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour , tm.tm_min, tm.tm_sec);

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

  struct tm tm;
  int rc=-1;

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

  rc = ioctl (fd, RTC_RD_TIME, &tm);
  /* RTC_RD_TIME can fail when the device driver detects
     that the RTC isn't running or contains invalid data.
     Such failure has been detected earlier, unless: We used
     noint_fallback=1 to get busywait_uip_fall() as fallback.
     Or: UIE interrupts do beat, but RTC is invalid. */
  if (rc == -1)
  {
    perror("RTC_RD_TIME ");
#ifdef USE_OPEN62541
    UA_Server_delete(server);
    nl.deleteMembers(&nl);
#endif /* def USE_OPEN62541 */
    return -1;
  }  

  LOG("RTC_RD_TIME event at %4d/%.2d/%.2d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  
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
	  "  -d name     RTC device to open.\n"
	  "     Default: %s\n"
	  "  -h          Print this message and exit.\n"
	  "  -v          Verbose output\n"
	  "",
	  prog_name,
	  RTC_DEVICE);
}

int main(int argc, char *argv[])
{
  char *prog_name, *rtc_dev;
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
  while ((opt = getopt(argc, argv, "d:hv")) != EOF) {
    switch (opt) {
    case 'd':
      rtc_dev = optarg;
      break;
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

  fd = open(rtc_dev, O_RDWR);
  if (fd < 0) {
    fprintf(stderr, "Failed to open %s: %d (%s)\n", rtc_dev, errno, strerror(errno));
    return -1;
  }
  LOG("RTC device: %s\n", rtc_dev);

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
