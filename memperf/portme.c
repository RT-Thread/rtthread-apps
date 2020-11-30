/*
 * Copyright (c) 2020 SummerGift (summergift2019@gmail.com)
 *
 * MIT License
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-27     SummerGift   first version
 */

#include "portme.h"

static CORETIMETYPE start_time_val, stop_time_val;

void start_time_mp(void)
{
    GETMYTIME(&start_time_val);
}

void stop_time_mp(void)
{
    GETMYTIME(&stop_time_val);
}

CORETIMETYPE get_time_mp(void)
{
    CORETIMETYPE elapsed = (CORETIMETYPE) (MYTIMEDIFF(stop_time_val, start_time_val));
    return elapsed;
}
