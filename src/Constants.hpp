#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#define LOG(x) std::cout << x << std::endl
#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
static size_t SCREEN_WIDTH = 2000;
static size_t SCREEN_HEIGHT = 1200;

// BRANCH DEV jebffb4be3fdhdb3wyd