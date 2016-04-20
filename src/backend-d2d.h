/*
 * WinDrawLib
 * Copyright (c) 2015-2016 Martin Mitas
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef WD_BACKEND_D2D_H
#define WD_BACKEND_D2D_H

#include "misc.h"

#include <d2d1.h>


#define D2D_CANVASTYPE_BITMAP       0
#define D2D_CANVASTYPE_DC           1
#define D2D_CANVASTYPE_HWND         2

#define D2D_CANVASFLAG_RECTCLIP   0x1

typedef struct d2d_canvas_tag d2d_canvas_t;
struct d2d_canvas_tag {
    WORD type;
    WORD flags;
    union {
        ID2D1RenderTarget* target;
        ID2D1BitmapRenderTarget* bmp_target;
        ID2D1HwndRenderTarget* hwnd_target;
    };
    ID2D1GdiInteropRenderTarget* gdi_interop;
    ID2D1Layer* clip_layer;
};


extern const D2D1_MATRIX_3X2_F d2d_base_transform;

extern ID2D1Factory* d2d_factory;

static inline BOOL
d2d_enabled(void)
{
    return (d2d_factory != NULL);
}

static inline void
d2d_init_color(D2D_COLOR_F* c, WD_COLOR color)
{
    c->r = WD_RVALUE(color) / 255.0f;
    c->g = WD_GVALUE(color) / 255.0f;
    c->b = WD_BVALUE(color) / 255.0f;
    c->a = WD_AVALUE(color) / 255.0f;
}

int d2d_init(void);
void d2d_fini(void);

d2d_canvas_t* d2d_canvas_alloc(ID2D1RenderTarget* target, WORD type);

void d2d_reset_clip(d2d_canvas_t* c);

void d2d_reset_transform(ID2D1RenderTarget* target);
void d2d_apply_transform(ID2D1RenderTarget* target, D2D1_MATRIX_3X2_F* matrix);

void d2d_setup_arc_segment(D2D1_ARC_SEGMENT* arc_seg,
                    float cx, float cy, float r,
                    float base_angle, float sweep_angle);
ID2D1Geometry* d2d_create_arc_geometry(float cx, float cy, float r,
                    float base_angle, float sweep_angle, BOOL pie);


#endif  /* WD_BACKEND_D2D_H */
