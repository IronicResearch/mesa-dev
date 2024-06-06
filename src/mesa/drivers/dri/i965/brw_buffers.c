/*
 * Copyright 2003 VMware, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL VMWARE AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "brw_context.h"
#include "brw_buffers.h"
#include "brw_fbo.h"
#include "brw_mipmap_tree.h"

#include "main/fbobject.h"
#include "main/framebuffer.h"
#include "main/renderbuffer.h"

static void
brw_drawbuffer(struct gl_context *ctx)
{
   if (_mesa_is_front_buffer_drawing(ctx->DrawBuffer)) {
      struct brw_context *const brw = brw_context(ctx);

      /* If we might be front-buffer rendering on this buffer for the first
       * time, invalidate our DRI drawable so we'll ask for new buffers
       * (including the fake front) before we start rendering again.
       */
      if (brw->driContext->driDrawablePriv)
          dri2InvalidateDrawable(brw->driContext->driDrawablePriv);
      brw_prepare_render(brw);
   }
   else if (ctx->Visual.stereoMode) {
      struct brw_context *const brw = brw_context(ctx);

      // FIXME: complete rendering left stereo buffer
      // before switching to right stereo buffer,
      // like implicit glXSwapBuffers() call
      //    pdraw->psc->driScreen->swapBuffers(pdraw, 0, 0, 0, flush);

      __DRIdrawable *dri_drawable = brw->driContext->driDrawablePriv;
      __DRIscreen *dri_screen = brw->driContext->driScreenPriv;

      //__DRIcontext *driContext = intel->driContext;
      //__DRIdrawable *driDrawable = driContext->driDrawablePriv;
      //__DRIscreen *const screen = intel->intelScreen->driScrnPriv;
      //__DRIscreen *const dri_screen = brw->screen->driScrnPriv; 
      //    void (*flushSwapBuffers)(__DRIdrawable *driDrawable, void *loaderPrivate);

      //FIXME: crashes
      //if (dri_drawable && dri_screen && dri_screen->driver)
      //   dri_screen->driver->SwapBuffers(dri_drawable);

      //FIXME: uncompilable
      //if (dri_screen && dri_screen->driScreen)
      //   dri_screen->driScreen->swapBuffers(dri_drawable, 0, 0, 0, true);

#if 0
      //FIXME: hangs
      if (dri_screen != NULL && dri_screen->image.loader->flushSwapBuffers != NULL)
         dri_screen->image.loader->flushSwapBuffers(dri_drawable, dri_screen->loaderPrivate);
#endif
      brw_glFlush(ctx, 0);

      brw_prepare_render(brw);
   }
}


static void
brw_readbuffer(struct gl_context * ctx, GLenum mode)
{
   if (_mesa_is_front_buffer_reading(ctx->ReadBuffer)) {
      struct brw_context *const brw = brw_context(ctx);

      /* If we might be front-buffer reading on this buffer for the first
       * time, invalidate our DRI drawable so we'll ask for new buffers
       * (including the fake front) before we start reading again.
       */
      if (brw->driContext->driDrawablePriv)
          dri2InvalidateDrawable(brw->driContext->driReadablePriv);
      brw_prepare_render(brw);
   }
}


void
brw_init_buffer_functions(struct dd_function_table *functions)
{
   functions->DrawBuffer = brw_drawbuffer;
   functions->ReadBuffer = brw_readbuffer;
}
