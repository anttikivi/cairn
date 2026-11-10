# SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
#
# SPDX-License-Identifier: LGPL-3.0-or-later

import subprocess
import sys
import unittest

HELPER = sys.argv.pop(1)

# Must be kept up to date with src/crio.c.
MAX_OUTPUT_BYTES = 4096


class IOTest(unittest.TestCase):
    def check_output(
        self, stream: str, scenario: str, payload: str, expected: bytes
    ):
        result = subprocess.run(
            [HELPER, stream, scenario, payload],
            capture_output=True,
            timeout=5,
            check=False,
        )

        self.assertEqual(
            result.returncode, 0, msg=f"io failed: {result.stderr!r}"
        )

        if stream == "stdout":
            self.assertEqual(result.stdout, expected)
            self.assertEqual(result.stderr, b"")
        else:
            self.assertEqual(result.stdout, b"")
            self.assertEqual(result.stderr, expected)

    def test_output(self):
        cases = [
            ("text", "", b""),
            ("text", "hello", b"hello"),
            ("text", "hello\nworld\n", b"hello\nworld\n"),
            ("embed", "", b"abc"),
        ]

        for stream in ["stdout", "stderr"]:
            for scenario, payload, expected in cases:
                with self.subTest(
                    stream=stream, scenario=scenario, payload=payload
                ):
                    self.check_output(stream, scenario, payload, expected)

    def test_length_boundaries(self):
        for stream in ["stdout", "stderr"]:
            for size in [MAX_OUTPUT_BYTES - 1, MAX_OUTPUT_BYTES]:
                with self.subTest(stream=stream, size=size):
                    self.check_output(stream, "text", "a" * size, b"a" * size)

            with self.subTest(stream=stream, scenario="oversized"):
                self.check_output(
                    stream,
                    "oversized",
                    "a" * (MAX_OUTPUT_BYTES + 1),
                    b"",
                )

    def test_invalid_destination(self):
        for stream in ["stdout", "stderr"]:
            with self.subTest(stream=stream):
                self.check_output(stream, "invalid-handle", "hello", b"")


if __name__ == "__main__":
    _ = unittest.main()
