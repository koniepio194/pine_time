# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
set(DTC_OVERLAY_FILE "/Users/piotrek/Desktop/pine_time/pine_time/src/pine_time.dts")
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(pine_time)

target_sources(app PRIVATE ../src/main.c)
