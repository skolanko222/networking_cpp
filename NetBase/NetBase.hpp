#pragma once

#include <memory>
#include <thread>
#include <deque>
#include <vector>

#ifdef _WIN32
#define _WIN32_WINDOWS = 0x0A00
#endif
#define ASIO_STANDALONE

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>