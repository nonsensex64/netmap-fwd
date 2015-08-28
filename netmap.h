/*-
 * Copyright (c) 2015, ServerU Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define	NETMAP_GET_BUF(_r)						\
	NETMAP_BUF((_r), (_r)->slot[(_r)->cur].buf_idx)
#define	NETMAP_SLOT_LEN(_r)						\
	(_r)->slot[(_r)->cur].len
#define	NETMAP_RING_NEXT(_r)	 					\
	(_r)->head = (_r)->cur = nm_ring_next((_r), (_r)->cur)
#define	NETMAP_UPDATE_LEN(_r, _len)					\
	do {								\
		if (_len < 60) {					\
			memset(NETMAP_GET_BUF(_r) + _len, 0, 60 - _len);\
			_len = 60;					\
		}							\
		NETMAP_SLOT_LEN(_r) = _len;				\
	} while (0)

int netmap_open(struct nm_if *);
int netmap_close(struct nm_if *);
struct netmap_ring *netmap_get_tx_ring(struct nm_if *);
int netmap_rx_sync(struct nm_if *);
int netmap_tx_sync(struct nm_if *);
