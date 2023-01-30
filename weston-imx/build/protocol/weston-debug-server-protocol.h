/* Generated by wayland-scanner 1.18.0 */

#ifndef WESTON_DEBUG_SERVER_PROTOCOL_H
#define WESTON_DEBUG_SERVER_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-server.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct wl_client;
struct wl_resource;

/**
 * @page page_weston_debug The weston_debug protocol
 * @section page_ifaces_weston_debug Interfaces
 * - @subpage page_iface_weston_debug_v1 - weston internal debugging
 * - @subpage page_iface_weston_debug_stream_v1 - A subscribed debug stream
 * @section page_copyright_weston_debug Copyright
 * <pre>
 *
 * Copyright © 2017 Pekka Paalanen pq@iki.fi
 * Copyright © 2018 Zodiac Inflight Innovations
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * </pre>
 */
struct weston_debug_stream_v1;
struct weston_debug_v1;

/**
 * @page page_iface_weston_debug_v1 weston_debug_v1
 * @section page_iface_weston_debug_v1_desc Description
 *
 * This is a generic debugging interface for Weston internals, the global
 * object advertized through wl_registry.
 *
 * WARNING: This interface by design allows a denial-of-service attack. It
 * should not be offered in production, or proper authorization mechanisms
 * must be enforced.
 *
 * The idea is for a client to provide a file descriptor that the server
 * uses for printing debug information. The server uses the file
 * descriptor in blocking writes mode, which exposes the denial-of-service
 * risk. The blocking mode is necessary to ensure all debug messages can
 * be easily printed in place. It also ensures message ordering if a
 * client subscribes to more than one debug stream.
 *
 * The available debugging features depend on the server.
 *
 * A debug stream can be one-shot where the server prints the requested
 * information and then closes it, or continuous where server keeps on
 * printing until the client stops it. Or anything in between.
 * @section page_iface_weston_debug_v1_api API
 * See @ref iface_weston_debug_v1.
 */
/**
 * @defgroup iface_weston_debug_v1 The weston_debug_v1 interface
 *
 * This is a generic debugging interface for Weston internals, the global
 * object advertized through wl_registry.
 *
 * WARNING: This interface by design allows a denial-of-service attack. It
 * should not be offered in production, or proper authorization mechanisms
 * must be enforced.
 *
 * The idea is for a client to provide a file descriptor that the server
 * uses for printing debug information. The server uses the file
 * descriptor in blocking writes mode, which exposes the denial-of-service
 * risk. The blocking mode is necessary to ensure all debug messages can
 * be easily printed in place. It also ensures message ordering if a
 * client subscribes to more than one debug stream.
 *
 * The available debugging features depend on the server.
 *
 * A debug stream can be one-shot where the server prints the requested
 * information and then closes it, or continuous where server keeps on
 * printing until the client stops it. Or anything in between.
 */
extern const struct wl_interface weston_debug_v1_interface;
/**
 * @page page_iface_weston_debug_stream_v1 weston_debug_stream_v1
 * @section page_iface_weston_debug_stream_v1_desc Description
 *
 * Represents one subscribed debug stream, created with
 * weston_debug_v1.subscribe. When the object is created, it is associated
 * with a given file descriptor. The server will continue writing to the
 * file descriptor until the object is destroyed or the server sends an
 * event through the object.
 * @section page_iface_weston_debug_stream_v1_api API
 * See @ref iface_weston_debug_stream_v1.
 */
/**
 * @defgroup iface_weston_debug_stream_v1 The weston_debug_stream_v1 interface
 *
 * Represents one subscribed debug stream, created with
 * weston_debug_v1.subscribe. When the object is created, it is associated
 * with a given file descriptor. The server will continue writing to the
 * file descriptor until the object is destroyed or the server sends an
 * event through the object.
 */
extern const struct wl_interface weston_debug_stream_v1_interface;

/**
 * @ingroup iface_weston_debug_v1
 * @struct weston_debug_v1_interface
 */
struct weston_debug_v1_interface {
	/**
	 * destroy factory object
	 *
	 * Destroys the factory object, but does not affect any other
	 * objects.
	 */
	void (*destroy)(struct wl_client *client,
			struct wl_resource *resource);
	/**
	 * subscribe to a debug stream
	 *
	 * Subscribe to a named debug stream. The server will start
	 * printing to the given file descriptor.
	 *
	 * If the named debug stream is a one-shot dump, the server will
	 * send weston_debug_stream_v1.complete event once all requested
	 * data has been printed. Otherwise, the server will continue
	 * streaming debug prints until the subscription object is
	 * destroyed.
	 *
	 * If the debug stream name is unknown to the server, the server
	 * will immediately respond with weston_debug_stream_v1.failure
	 * event.
	 * @param name debug stream name
	 * @param streamfd write stream file descriptor
	 * @param stream created debug stream object
	 */
	void (*subscribe)(struct wl_client *client,
			  struct wl_resource *resource,
			  const char *name,
			  int32_t streamfd,
			  uint32_t stream);
};

#define WESTON_DEBUG_V1_AVAILABLE 0

/**
 * @ingroup iface_weston_debug_v1
 */
#define WESTON_DEBUG_V1_AVAILABLE_SINCE_VERSION 1

/**
 * @ingroup iface_weston_debug_v1
 */
#define WESTON_DEBUG_V1_DESTROY_SINCE_VERSION 1
/**
 * @ingroup iface_weston_debug_v1
 */
#define WESTON_DEBUG_V1_SUBSCRIBE_SINCE_VERSION 1

/**
 * @ingroup iface_weston_debug_v1
 * Sends an available event to the client owning the resource.
 * @param resource_ The client's resource
 * @param name debug stream name
 * @param description human-readable description of the debug scope
 */
static inline void
weston_debug_v1_send_available(struct wl_resource *resource_, const char *name, const char *description)
{
	wl_resource_post_event(resource_, WESTON_DEBUG_V1_AVAILABLE, name, description);
}

/**
 * @ingroup iface_weston_debug_stream_v1
 * @struct weston_debug_stream_v1_interface
 */
struct weston_debug_stream_v1_interface {
	/**
	 * close a debug stream
	 *
	 * Destroys the object, which causes the server to stop writing
	 * into and closes the associated file descriptor if it was not
	 * closed already.
	 *
	 * Use a wl_display.sync if the clients needs to guarantee the file
	 * descriptor is closed before continuing.
	 */
	void (*destroy)(struct wl_client *client,
			struct wl_resource *resource);
};

#define WESTON_DEBUG_STREAM_V1_COMPLETE 0
#define WESTON_DEBUG_STREAM_V1_FAILURE 1

/**
 * @ingroup iface_weston_debug_stream_v1
 */
#define WESTON_DEBUG_STREAM_V1_COMPLETE_SINCE_VERSION 1
/**
 * @ingroup iface_weston_debug_stream_v1
 */
#define WESTON_DEBUG_STREAM_V1_FAILURE_SINCE_VERSION 1

/**
 * @ingroup iface_weston_debug_stream_v1
 */
#define WESTON_DEBUG_STREAM_V1_DESTROY_SINCE_VERSION 1

/**
 * @ingroup iface_weston_debug_stream_v1
 * Sends an complete event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
weston_debug_stream_v1_send_complete(struct wl_resource *resource_)
{
	wl_resource_post_event(resource_, WESTON_DEBUG_STREAM_V1_COMPLETE);
}

/**
 * @ingroup iface_weston_debug_stream_v1
 * Sends an failure event to the client owning the resource.
 * @param resource_ The client's resource
 * @param message human readable reason
 */
static inline void
weston_debug_stream_v1_send_failure(struct wl_resource *resource_, const char *message)
{
	wl_resource_post_event(resource_, WESTON_DEBUG_STREAM_V1_FAILURE, message);
}

#ifdef  __cplusplus
}
#endif

#endif
