/*
 * H.26L/H.264/AVC/JVT/14496-10/... encoder/decoder
 * Copyright (c) 2003 Michael Niedermayer <michaelni@gmx.at>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * Context Adaptive Binary Arithmetic Coder.
 */

#ifndef AVCODEC_CABAC_H
#define AVCODEC_CABAC_H

#include <stdint.h>

#include "put_bits.h"

struct AVCodecCodingHooks;

extern const uint8_t ff_h264_cabac_tables[512 + 4*2*64 + 4*64 + 63];
#define H264_NORM_SHIFT_OFFSET 0
#define H264_LPS_RANGE_OFFSET 512
#define H264_MLPS_STATE_OFFSET 1024
#define H264_LAST_COEFF_FLAG_OFFSET_8x8_OFFSET 1280

#define CABAC_BITS 16
#define CABAC_MASK ((1<<CABAC_BITS)-1)

typedef struct CABACContext{
    int low;
    int range;
    int outstanding_count;
    const uint8_t *bytestream_start;
    const uint8_t *bytestream;
    const uint8_t *bytestream_end;
    PutBitContext pb;

    struct CABACHooks *coding_hooks;
    void *coding_hooks_opaque;
}CABACContext;

void ff_init_cabac_encoder(CABACContext *c, uint8_t *buf, int buf_size);
int ff_init_cabac_decoder(CABACContext *c, const uint8_t *buf, int buf_size, struct AVCodecCodingHooks* coding_hooks);
int ff_reset_cabac_decoder(CABACContext *c, const uint8_t *buf, int buf_size);

int ff_get_cabac(CABACContext *c, uint8_t * const state);
int ff_get_cabac_bypass(CABACContext *c);
int ff_get_cabac_bypass_sign(CABACContext *c, int val);
int ff_get_cabac_terminate(CABACContext *c);
const uint8_t* ff_cabac_skip_bytes(CABACContext *c, int n);

#endif /* AVCODEC_CABAC_H */
