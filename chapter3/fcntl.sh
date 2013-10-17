#!/usr/bin/env bash

../bin/fcntl_test 0 < /dev/tty

../bin/fcntl_test 2 2>>/tmp/s

../bin/fcntl_test 5 5<>/tmp/s


