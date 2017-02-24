
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Local Variable Declarations */
static const char* sig_cs = "MEGware";
static const int cs_timeout = 1000;
static const int cs_ttl = 10;
static char* cs_host = "localhost";
static unsigned short cs_port = 2010;
static char * cs_password = "";
static int cs_inited = 0;
static int * cs_outlets = 0;

/* static functions */
static inline unsigned char * cs_toArray(
  unsigned short value)
{
  static unsigned char result[2];

  result[0] = (unsigned short) (value >> 8);
  result[1] = (unsigned short) (value >> 0);

	return result;
}

static inline unsigned char cs_calculateChecksum(
  const unsigned char * array,
  int length)
{
  int i = 0;
	unsigned char result = 0;
	// Simply add up all bytes in the input array.
	for (i;i<length;i++) {
		result += array[i];
	}
	return result;
}

static inline int cs_checPrefix(
  unsigned char * array,
  const unsigned char *prefix)
  {
	// Check if array starts with the expected prefix.
  int aL, pL;
  aL = strlen(array);
  pL = strlen(prefix);

  if(aL>pL){
    return (strncmp(prefix, array, pL) == 0);
  }else{
    return 0;
  }
}
/* exported functions */

void cs_init_static(
  cs_config_t* config
) {
	// Read and parse the "host" option
	if (config->host) {
		cs_host = config->host;
	}
	// Read and parse the "port" option
	if (config->port) {
		assert(((config->port) >=1) && ((config->port) <=65536));
    cs_port = config->port;
	}
	// Read and parse the "password" option
	if (config->password ) {
    cs_password = config->password;
	}

	// Read and parse the "outlets" option
  if (config->outlets) {
    assert(!cs_outlets);
    int i;
    cs_outlets = (int*) malloc ((config->num_outlets)*sizeof(int));
    memcpy(cs_outlets, config->outlets, (config->num_outlets)*sizeof(int));
	}

	context.info("Using following values for ClustSafe");
	context.info("Host = " + Main::host);
	context.info("Port = :" + QString::number(Main::port));
	QString outlets = "";
	for (const auto &elem : Main::outlets) outlets += QString::number(elem);
	context.info("Outlets = " + outlets);
}
