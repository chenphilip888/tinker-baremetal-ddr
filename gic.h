/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _RK_GIC_H_
#define _RK_GIC_H_

#include "registers.h"

void config_GIC( int N, int CPU_target );
void config_interrupt ( int N, int CPU_target );
 
#endif
