/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRPROC_H
#define CRPROC_H

#include <stddef.h>

#include <crerr.h>
#include <crplat.h>
#include <crunit.h>

#if CR_PLAT_WINDOWS
#    include <windows.h>
#elif CR_PLAT_POSIX
#    include <sys/types.h>
#endif

#ifndef CR_PROC_MAX_ARGS
#    define CR_PROC_MAX_ARGS 16U
#endif

#if (CR_PROC_MAX_ARGS < 1U) || (CR_PROC_MAX_ARGS > 255U)
#    error "CR_PROC_MAX_ARGS must be between 1 and 255"
#endif

#ifndef CR_PROC_REQ_MAX_BYTES
#    define CR_PROC_REQ_MAX_BYTES CR_KB((size_t)4U)
#endif

enum cr_proc_child_state
{
    CR_PROC_CHILD_EMPTY,
    CR_PROC_CHILD_ACTIVE,
    CR_PROC_CHILD_RESULT,
    CR_PROC_CHILD_LOST
};

enum cr_proc_term
{
    CR_PROC_TERM_UNKNOWN,
    CR_PROC_EXITED,
    CR_PROC_SIGNALED
};

enum cr_proc_lookup
{
    CR_PROC_LOOKUP_ABSOLUTE,
    CR_PROC_LOOKUP_PATH
};

enum cr_proc_wait_mode
{
    CR_PROC_WAIT_POLL,
    CR_PROC_WAIT_BLOCK
};

/* Holds the information about a child process. */
struct cr_proc_child
{
    /* Current state of the child process. */
    enum cr_proc_child_state state;
    enum cr_proc_term term;
    int term_signal;
    /*
     * Native error code from the most recent operation performed on the child
     * process.
     */
    int native_err;
    int exit_code;

#if CR_PLAT_WINDOWS
    HANDLE process_handle;
    HANDLE thread_handle;
#elif CR_PLAT_POSIX
    pid_t pid;
#endif
};

/*
 * Holds the information for running a new child process. Initialize new
 * requests with crpexe and add arguments (besides the executable to run) with
 * crparg.
 */
struct cr_proc_req
{
    char buf[CR_PROC_REQ_MAX_BYTES];
    size_t used;
    unsigned char argc;
    enum cr_proc_lookup lookup;
};

/*
 * Initialize a process request, i.e. the object that holds the name of the
 * executable and the arguments for creating the child process. Arguments are
 * added using crparg.
 *
 * This function also invalidates all previous data in req.
 */
enum cr_err crpexe(struct cr_proc_req *req, const char *exe,
                   enum cr_proc_lookup lookup);

/* Add an argument to a process request. */
enum cr_err crparg(struct cr_proc_req *req, const char *arg);

/* Initialize the child process object. child must not be NULL. */
void crpinit(struct cr_proc_child *child);

/*
 * Start the requested process and store its information in child. The current
 * environment is inherited and read before the startup. The caller must ensure
 * that no other thread is writing to it when calling this function.
 *
 * The child must be initialized with crpinit before calling this and it should
 * have the CR_PROC_CHILD_EMPTY state. The function may return
 * CR_ERR_PROC_INVALID_REQUEST, CR_ERR_PROC_INVALID_STATE, and
 * CR_ERR_PROC_START_FAILED and sets the native_err in child if the OS returns
 * an error. On POSIX, it is set to errno. The return value is set to CR_ERR_OK
 * on success. However, the native_err may still be set if the process is
 * successfully started but cleanup fails in the function.
 *
 * In addition to the current environment, the child process inherits the
 * current working directory and umask. It will get an empty signal mask.
 * SIGPIPE is reset to the default action.
 */
enum cr_err crpstart(struct cr_proc_child *child, struct cr_proc_req *req);
enum cr_err crpwait(struct cr_proc_child *child, enum cr_proc_wait_mode mode);
enum cr_err crpclose(struct cr_proc_child *child);

#endif
