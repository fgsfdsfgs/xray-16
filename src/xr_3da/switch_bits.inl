// assorted nintendo switch crap that has to be in the main binary

// HACK: these don't get exported by default, but they are required by
//       some of the DSOs we load, and linking libstdc++ with --whole-archive
//       breaks other things

#include <cxxabi.h>
#include <sstream>
#include <regex>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

static std::regex re_dummy __attribute__((used));
static std::regex_error rerr_dummy __attribute__((used)) { std::regex_constants::error_collate };
static std::istringstream ss_dummy __attribute__((used));
static std::stringbuf sb_dummy __attribute__((used));
static auto *fp_dummy_1 __attribute__((used)) = &(std::__throw_bad_function_call);
static auto *fp_dummy_2 __attribute__((used)) = &(std::_Hash_bytes);
static __cxxabiv1::__enum_type_info eti_dummy __attribute__((used)) { "eti_dummy_" };
static __cxxabiv1::__array_type_info ati_dummy __attribute__((used)) { "ati_dummy_" };
static bool isprint_dummy __attribute__((used)) = std::isprint('x');

extern "C"
{

#include <switch/services/ssl.h>
#include <switch/runtime/devices/socket.h>
#include <switch/runtime/nxlink.h>
#include <solder.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

extern struct hostent *gethostbyname(const char *name);
extern struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type);
extern int gethostname(char *name, size_t len);

// more symbols
static void *fp_dummy_c[] __attribute__((used)) =
{
    (void *)frexpf,
    (void *)getaddrinfo,
    (void *)freeaddrinfo,
    (void *)inet_addr,
    (void *)inet_ntoa,
    (void *)gethostbyname,
    (void *)gethostbyaddr,
    (void *)gethostname,
};

// we'll need a bigger TLS buffer than default
__thread uint8_t __solder_tls_buffer[0x120000];
uint32_t __solder_tls_buffer_size = sizeof(__solder_tls_buffer);

static int nxlink_sock = -1;

void userAppInit(void)
{
    socketInitializeDefault();
#if defined(DEBUG)
    nxlink_sock = nxlinkStdio();
#endif
}

void userAppExit(void)
{
    solder_quit();
    if (nxlink_sock >= 0)
        close(nxlink_sock);
    socketExit();
}

}

static void switch_init(int argc, char *argv[])
{
    // load and init submodules
    solder_init(SOLDER_MAIN_AUTOLOAD | SOLDER_ALLOW_UNDEFINED);
    // since we're gonna be one level above bin/, add it to search path
    solder_add_search_path("bin");
    // chdir to NRO path, since newlib chdir starts in / by default
    if (argc && argv && argv[0] && argv[0][0])
    {
        string_path cwd = { 0 };
        // strip `sdmc:`
        const char *root = strchr(argv[0], ':');
        if (root)
            xr_strcpy(cwd, root + 1);
        else
            xr_strcpy(cwd, argv[0]);
        // strip filename
        char *last_sep = strrchr(cwd, '/');
        if (last_sep)
        {
            last_sep[0] = 0;
            Msg("Starting directory: %s", cwd);
            Msg("chdir() = %d\n", chdir(cwd));
        }
    }
}
