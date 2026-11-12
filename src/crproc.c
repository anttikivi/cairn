/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <crproc.h>

#include <stddef.h>

#include <crdbg.h>
#include <crerr.h>
#include <crplat.h>
#include <crstr.h>

#if CR_PLAT_OSX
#    include <crt_externs.h>
#endif

#if CR_PLAT_POSIX
#    include <errno.h>
#    include <signal.h>
#    include <spawn.h>
#    include <sys/types.h>
#    include <sys/wait.h>
#endif

#if CR_PLAT_POSIX && !CR_PLAT_OSX
extern char **environ;
#endif

#if CR_PLAT_POSIX
static char **
proc_env(void)
{
#    if CR_PLAT_OSX
    return *_NSGetEnviron();
#    else
    return environ;
#    endif
}

static int
init_spawn_attr(posix_spawnattr_t *attr)
{
    int err;
    sigset_t mask;
    sigset_t def;

    err = posix_spawnattr_init(attr);

    if (err == 0)
    {
        if (sigemptyset(&mask) != 0)
        {
            err = errno;
        }

        if (err == 0)
        {
            if (sigemptyset(&def) != 0)
            {
                err = errno;
            }
        }

        if (err == 0)
        {
            if (sigaddset(&def, SIGPIPE) != 0)
            {
                err = errno;
            }
        }

        if (err == 0)
        {
            if (sigaddset(&def, SIGCHLD) != 0)
            {
                err = errno;
            }
        }

        if (err == 0)
        {
            err = posix_spawnattr_setsigmask(attr, &mask);
        }

        if (err == 0)
        {
            err = posix_spawnattr_setsigdefault(attr, &def);
        }

        if (err == 0)
        {
            err = posix_spawnattr_setflags(
                attr, (short)(POSIX_SPAWN_SETSIGMASK | POSIX_SPAWN_SETSIGDEF));
        }

        if (err != 0)
        {
            (void)posix_spawnattr_destroy(attr);
        }
    }

    return err;
}
#endif

static enum cr_err
validate_exe(const char *exe, enum cr_proc_lookup lookup)
{
    enum cr_err err = CR_ERR_OK;
    size_t l;

    CR_ASSERT(exe != NULL);

    l = crsnlen(exe, CR_PROC_REQ_MAX_BYTES);

    if (exe[0] == '\0')
    {
        err = CR_ERR_PROC_INVALID_REQUEST;
    }
    else
    {
        if (lookup == CR_PROC_LOOKUP_ABSOLUTE)
        {
            /* TODO: Windows */
            if (exe[0] != '/')
            {
                err = CR_ERR_PROC_INVALID_REQUEST;
            }
        }
        else if (lookup == CR_PROC_LOOKUP_PATH)
        {
            if (crsnchr(exe, '/', l) != NULL)
            {
                err = CR_ERR_PROC_INVALID_REQUEST;
            }
        }
        else
        {
            err = CR_ERR_PROC_INVALID_REQUEST;
        }
    }

    return err;
}

/* Append a null-terminated string at the end of the request buffer. */
static enum cr_err
req_push(struct cr_proc_req *req, const char *s)
{
    enum cr_err err = CR_ERR_OK;
    size_t room;
    size_t l;

    CR_ASSERT(req != NULL);
    CR_ASSERT(s != NULL);

    room = CR_PROC_REQ_MAX_BYTES - req->used;
    l = crsnlen(s, room);

    if (l >= room)
    {
        err = CR_ERR_PROC_ARG_OVERFLOW;
    }

    if (err == CR_ERR_OK)
    {
        size_t i;

        for (i = 0U; i < l; i++)
        {
            req->buf[req->used + i] = s[i];
        }

        req->buf[req->used + l] = '\0';
        req->used += l + 1U;
    }

    return err;
}

static enum cr_err
validate_proc_req(const struct cr_proc_req *req)
{
    enum cr_err err = CR_ERR_OK;

    CR_ASSERT(req != NULL);

    if ((req->used == 0U) || (req->used > CR_PROC_REQ_MAX_BYTES) ||
        (req->argc == 0U) || (req->argc > CR_PROC_MAX_ARGS) ||
        (req->buf[req->used - 1U] != '\0'))
    {
        err = CR_ERR_PROC_INVALID_REQUEST;
    }
    else
    {
        size_t i;
        size_t n = 0U;

        for (i = 0U; i < req->used; i++)
        {
            if (req->buf[i] == '\0')
            {
                n++;
            }
        }

        if (n != req->argc)
        {
            err = CR_ERR_PROC_INVALID_REQUEST;
        }
    }

    if (err == CR_ERR_OK)
    {
        err = validate_exe(req->buf, req->lookup);
    }

    return err;
}

enum cr_err
crpexe(struct cr_proc_req *req, const char *exe, enum cr_proc_lookup lookup)
{
    enum cr_err err = CR_ERR_OK;

    CR_ASSERT(req != NULL);

    req->used = 0U;
    req->argc = 0U;
    req->lookup = lookup;

    if (exe == NULL)
    {
        err = CR_ERR_PROC_INVALID_REQUEST;
    }
    else
    {
        err = validate_exe(exe, lookup);
    }

    if (err == CR_ERR_OK)
    {
        err = req_push(req, exe);
    }

    if (err == CR_ERR_OK)
    {
        req->argc = 1U;
    }

    return err;
}

enum cr_err
crparg(struct cr_proc_req *req, const char *arg)
{
    enum cr_err err = CR_ERR_OK;

    CR_ASSERT(req != NULL);

    if ((arg == NULL) || (req->used == 0U) || (req->argc == 0U))
    {
        err = CR_ERR_PROC_INVALID_REQUEST;
    }
    else if (req->argc >= CR_PROC_MAX_ARGS)
    {
        err = CR_ERR_PROC_ARG_OVERFLOW;
    }
    else
    {
        err = req_push(req, arg);
    }

    if (err == CR_ERR_OK)
    {
        req->argc++;
    }

    return err;
}

void
crpinit(struct cr_proc_child *child)
{
    CR_ASSERT(child != NULL);

    child->state = CR_PROC_CHILD_EMPTY;

    /* TODO: Clean up the reset when we know the full API. */
    child->term = CR_PROC_TERM_UNKNOWN;
    child->exit_code = 0;
    child->term_signal = 0;
    child->native_err = 0;

#if CR_PLAT_WINDOWS
    child->process_handle = NULL;
    child->thread_handle = NULL;
#elif CR_PLAT_POSIX
    child->pid = (pid_t)0;
#endif
}

enum cr_err
crpstart(struct cr_proc_child *child, struct cr_proc_req *req)
{
    enum cr_err err = CR_ERR_OK;

#if CR_PLAT_POSIX
    pid_t pid = 0;
#endif

    CR_ASSERT(child != NULL);
    CR_ASSERT(req != NULL);

    err = validate_proc_req(req);

    if ((err == CR_ERR_OK) && (child->state != CR_PROC_CHILD_EMPTY))
    {
        err = CR_ERR_PROC_INVALID_STATE;
    }

#if CR_PLAT_POSIX

    if (err == CR_ERR_OK)
    {
        int posix_err = 0;
        posix_spawnattr_t attr;
        int destroy_err;
        size_t i;
        size_t n = 0U;
        char *argv[CR_PROC_MAX_ARGS + 1U];

        argv[0] = &req->buf[0];

        for (i = 0U; i < (req->used - 1U); i++)
        {
            if (req->buf[i] == '\0')
            {
                n++;
                argv[n] = &req->buf[i + 1U];
            }
        }

        argv[n + 1U] = NULL;

        posix_err = init_spawn_attr(&attr);

        if (posix_err == 0)
        {
            if (req->lookup == CR_PROC_LOOKUP_ABSOLUTE)
            {
                posix_err =
                    posix_spawn(&pid, argv[0], NULL, &attr, argv, proc_env());
            }
            else if (req->lookup == CR_PROC_LOOKUP_PATH)
            {
                posix_err =
                    posix_spawnp(&pid, argv[0], NULL, &attr, argv, proc_env());
            }
            else
            {
                /* The flow should never reach this point. */
                err = CR_ERR_UNEXPECTED;
            }

            destroy_err = posix_spawnattr_destroy(&attr);

            /*
             * Arguably it is more important to return error if the spawn fails.
             */
            if (posix_err == 0)
            {
                child->native_err = destroy_err;
            }
        }

        if (posix_err != 0)
        {
            child->native_err = posix_err;
            err = CR_ERR_PROC_START_FAILED;
        }
    }

    if (err == CR_ERR_OK)
    {
        child->pid = pid;
        child->state = CR_PROC_CHILD_ACTIVE;
    }

#else
    err = CR_ERR_UNSUPPORTED;
#endif

    return err;
}

enum cr_err
crpwait(struct cr_proc_child *child, enum cr_proc_wait_mode mode)
{
    enum cr_err err = CR_ERR_OK;

    CR_ASSERT(child != NULL);

    if ((mode != CR_PROC_WAIT_POLL) && (mode != CR_PROC_WAIT_BLOCK))
    {
        err = CR_ERR_ARGS_INVALID;
    }

#if CR_PLAT_POSIX
    if (err == CR_ERR_OK)
    {
        if (child->state == CR_PROC_CHILD_RESULT)
        {
            ; /* no-op: we already have a result, no further action needed */
        }
        else if (child->state == CR_PROC_CHILD_LOST)
        {
            child->native_err = ECHILD;
            err = CR_ERR_PROC_CHILD_LOST;
        }
        else if (child->state == CR_PROC_CHILD_ACTIVE)
        {
            pid_t waited;
            int status = 0;
            int options = 0;
            int posix_err = 0;

            if (mode == CR_PROC_WAIT_POLL)
            {
                options = WNOHANG;
            }

            errno = 0;
            waited = waitpid(child->pid, &status, options);

            /*
             * The return value on error should always be exactly -1. However,
             * we check if the return value is less than or equal to -1 to have
             * all of the integer cases handled.
             */
            if (waited <= (pid_t)-1)
            {
                posix_err = errno;
                child->native_err = posix_err;

                if (posix_err == EINTR)
                {
                    err = CR_ERR_PROC_INTERRUPTED;
                }

                if ((err == CR_ERR_OK) && (posix_err == ECHILD))
                {
                    child->pid = (pid_t)0;
                    child->state = CR_PROC_CHILD_LOST;
                    err = CR_ERR_PROC_CHILD_LOST;
                }

                if (err == CR_ERR_OK)
                {
                    err = CR_ERR_PROC_WAIT_FAILED;
                }
            }
            else if (waited == (pid_t)0)
            {
                err = CR_ERR_PROC_PENDING;
            }
            else if (waited != child->pid)
            {
                err = CR_ERR_PROC_INVALID_STATE;
            }
            else
            {
                /*
                 * No-op: PID is equal to the PID of the actual child process
                 * and it has exited.
                 */
                ;
            }

            if (err == CR_ERR_OK)
            {
                if (WIFEXITED(status) != 0)
                {
                    child->term = CR_PROC_EXITED;
                    child->exit_code = WEXITSTATUS(status);
                }
                else if (WIFSIGNALED(status) != 0)
                {
                    child->term = CR_PROC_SIGNALED;
                    child->term_signal = WTERMSIG(status);
                }
                else
                {
                    err = CR_ERR_UNEXPECTED;
                }
            }
        }
        else
        {
            err = CR_ERR_PROC_INVALID_STATE;
        }
    }

    if (err == CR_ERR_OK)
    {
        child->pid = (pid_t)0;
        child->state = CR_PROC_CHILD_RESULT;
    }
#else
    err = CR_ERR_UNSUPPORTED;
#endif

    return err;
}

enum cr_err
crpclose(struct cr_proc_child *child)
{
    /*
     * This function is essentially no-op on POSIX platforms as there is nothing
     * to close, really. However, it is here to maintain API parity with Windows
     * implementations. The function should not reset the child as `crpinit`
     * must be called anyway before re-using the same child, and this function
     * should not invalidate the stored result.
     */
    enum cr_err err = CR_ERR_OK;

    CR_ASSERT(child != NULL);

    if (child->state == CR_PROC_CHILD_ACTIVE)
    {
        err = CR_ERR_PROC_CHILD_ACTIVE;
    }

    return err;
}
