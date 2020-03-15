#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <cache/cache.h>

#include "vcc_strutils_if.h"

// https://pubs.opengroup.org/onlinepubs/7908799/xsh/strtol.html
VCL_STRING
vmod_hex_to_decimal(VRT_CTX, VCL_STRING input)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

	if (input == NULL || *input == '\0')
		return(NULL);

	// convert string hex to integer
	char *ptr;
	long ret;
	ret = strtol(input, &ptr, 16);

	// VCL WAY starts here
	char *p;
	unsigned u, v;

	u = WS_Reserve(ctx->ws, 0); /* Reserve some work space */
	p = ctx->ws->f;		/* Front of workspace area */
	v = snprintf(p, u, "%ld", ret);

	v++;
	if (v > u) {
		/* No space, reset and leave */
		WS_Release(ctx->ws, 0);
		return (NULL);
	}

	/* Update work space with what we've used */
	WS_Release(ctx->ws, v);
	return (p);
}

