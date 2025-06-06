/* _DRI_ structs split out from dri_util.h */

#ifndef _DRI_RECS_H_
#define _DRI_RECS_H_

#include <GL/gl.h>
#include <GL/internal/dri_interface.h>
#include "util/xmlconfig.h"

/**
 * Per-screen private driver information.
 */
struct __DRIscreenRec {
    /**
     * Driver-specific entrypoints provided by the driver's
     * __DRIDriverVtableExtensionRec.
     */
    const struct __DriverAPIRec *driver;

    /**
     * Current screen's number
     */
    int myNum;

    /**
     * File descriptor returned when the kernel device driver is opened.
     * 
     * Used to:
     *   - authenticate client to kernel
     *   - map the frame buffer, SAREA, etc.
     *   - close the kernel device driver
     */
    int fd;

    /**
     * Device-dependent private information (not stored in the SAREA).
     * 
     * This pointer is never touched by the DRI layer.
     */
    void *driverPrivate;

    void *loaderPrivate;

    int max_gl_core_version;
    int max_gl_compat_version;
    int max_gl_es1_version;
    int max_gl_es2_version;

    const __DRIextension **extensions;

    const __DRIswrastLoaderExtension *swrast_loader;

    struct {
	/* Flag to indicate that this is a DRI2 screen.  Many of the above
	 * fields will not be valid or initializaed in that case. */
	const __DRIdri2LoaderExtension *loader;
	const __DRIimageLookupExtension *image;
	const __DRIuseInvalidateExtension *useInvalidate;
        const __DRIbackgroundCallableExtension *backgroundCallable;
    } dri2;

    struct {
        const __DRIimageLoaderExtension *loader;
    } image;

    struct {
       const __DRImutableRenderBufferLoaderExtension *loader;
    } mutableRenderBuffer;

    driOptionCache optionInfo;
    driOptionCache optionCache;

    unsigned int api_mask;

    int stereo_mode;
};

#endif /* _DRI_RECS_H_ */
