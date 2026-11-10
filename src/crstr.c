/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <crstr.h>

size_t
crsnlen(const char *s, size_t n)
{
    size_t len = 0U;
    if (s != NULL)
    {
        while ((len < n) && (s[len] != '\0'))
        {
            len++;
        }
    }
    return len;
}

int
crsncmp(const char *l, size_t n, const char *r, size_t m)
{
    int result = 0;

    if ((l == NULL) || (r == NULL))
    {
        if (l != r)
        {
            result = (l == NULL) ? -1 : 1;
        }
    }
    else
    {
        unsigned char a;
        unsigned char b;
        size_t i = 0U;

        while ((i < n) && (i < m) && (l[i] != '\0') && (l[i] == r[i]))
        {
            i++;
        }

        a = (i < n) ? (unsigned char)l[i] : (unsigned char)'\0';
        b = (i < m) ? (unsigned char)r[i] : (unsigned char)'\0';
        if (a < b)
        {
            result = -1;
        }
        else if (a > b)
        {
            result = 1;
        }
        else
        {
            ; /* no-op, result is already zero */
        }
    }

    return result;
}
