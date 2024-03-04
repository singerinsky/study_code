/*
 * @file: 
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-11-09 10:04:27
 * @brief: 
 */
#pragma once
#include "gtest/gtest.h"

#include "../wsstackrecorder.h"
#include "../shmmgr.h"

void test_stack1();

void test_stack2();

void function_call(int index_dep, int &dep_rst);
