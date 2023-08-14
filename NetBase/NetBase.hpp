#pragma once

#include <memory>
#include <thread>
#include <deque>
#include <vector>
#include <type_traits>

//#ifdef _WIN32_WINDOWS
//#define _WIN32_WINDOWS = 0x0A00# 
//#endif
#define ASIO_STANDALONE

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>