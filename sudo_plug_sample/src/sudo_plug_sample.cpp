#include <sys/stat.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>

#include "sudo_plugin.h"

/*
 * Sample plugin module that allows any user who knows the password
 * ("test") to run any command as root.  Since there is no credential
 * caching the validate and invalidate functions are NULL.
 */

#define sudo_dso_public __attribute__((__visibility__("default")))

#define PACKAGE_VERSION "1.0"
#define ROOT_UID   0
#define ROOT_GID   0

static struct plugin_state {
    char **envp;
    char * const *settings;
    char * const *user_info;
} plugin_state;

static sudo_conv_t sudo_conv;
static sudo_printf_t sudo_log;
//static FILE *input, *output;
static uid_t runas_uid = ROOT_UID;
static gid_t runas_gid = -1;
static int use_sudoedit = false;

/*
 * Plugin policy open function.
 */

static int
policy_open(unsigned int version, sudo_conv_t conversation,
    sudo_printf_t sudo_printf, char * const settings[],
    char * const user_info[], char * const user_env[], char * const plugin_options[], const char **errstr) {
    return 1;
}

/*
 * Plugin policy check function.
 * Simple example that prompts for a password, hard-coded to "test".
 */

static int 
policy_check(int argc, char * const argv[],
    char *env_add[], char **command_info_out[],
    char **argv_out[], char **user_env_out[], const char **errstr) {

    return true;
}

static int
policy_list(int argc, char * const argv[], int verbose, const char *list_user, const char **errstr)
{
    /*
     * List user's capabilities.
     */
    sudo_log(SUDO_CONV_INFO_MSG, "Validated users may run any command\n");
    return true;
}

static int
policy_version(int verbose)
{
    sudo_log(SUDO_CONV_INFO_MSG, "Sample policy plugin version %s\n", PACKAGE_VERSION);
    return true;
}

static void
policy_close(int exit_status, int error)
{
    /*
     * The policy might log the command exit status here.
     * In this example, we just print a message.
     */
    if (error) {
	sudo_log(SUDO_CONV_ERROR_MSG, "Command error: %s\n", strerror(error));
    } else {
        if (WIFEXITED(exit_status)) {
	    sudo_log(SUDO_CONV_INFO_MSG, "Command exited with status %d\n",
		WEXITSTATUS(exit_status));
        } else if (WIFSIGNALED(exit_status)) {
	    sudo_log(SUDO_CONV_INFO_MSG, "Command killed by signal %d\n",
		WTERMSIG(exit_status));
	}
    }
}

sudo_dso_public struct policy_plugin sample_policy = {
    SUDO_POLICY_PLUGIN,
    SUDO_API_VERSION,
    policy_open,
    policy_close,
    policy_version,
    policy_check,
    policy_list,
    NULL, /* validate */
    NULL, /* invalidate */
    NULL, /* init_session */
    NULL, /* register_hooks */
    NULL /* deregister_hooks */
};
