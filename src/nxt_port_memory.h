
/*
 * Copyright (C) Max Romanov
 * Copyright (C) NGINX, Inc.
 */

#ifndef _NXT_PORT_MEMORY_H_INCLUDED_
#define _NXT_PORT_MEMORY_H_INCLUDED_


#define PORT_MMAP_MIN_SIZE (3 * sizeof(uint32_t))

typedef struct nxt_port_mmap_header_s nxt_port_mmap_header_t;

void
nxt_port_mmap_destroy(nxt_port_mmap_t *port_mmap);

void nxt_port_mmaps_destroy(nxt_array_t *port_mmaps, nxt_bool_t destroy_pool);

/*
 * Allocates nxt_but_t structure from port's mem_pool, assigns this buf 'mem'
 * pointers to first available shared mem bucket(s). 'size' used as a hint to
 * acquire several successive buckets if possible.
 *
 * This function assumes that current thread operates the 'port' exclusively.
 */
nxt_buf_t *
nxt_port_mmap_get_buf(nxt_task_t *task, nxt_port_t *port, size_t size);

nxt_int_t nxt_port_mmap_increase_buf(nxt_task_t *task, nxt_buf_t *b,
    size_t size, size_t min_size);

nxt_port_mmap_header_t *
nxt_port_incoming_port_mmap(nxt_task_t *task, nxt_process_t *process,
    nxt_fd_t fd);

void
nxt_port_mmap_write(nxt_task_t *task, nxt_port_t *port,
    nxt_port_send_msg_t *msg, nxt_sendbuf_coalesce_t *sb);

void
nxt_port_mmap_read(nxt_task_t *task, nxt_port_t *port,
    nxt_port_recv_msg_t *msg);

enum nxt_port_method_e {
    NXT_PORT_METHOD_ANY = 0,
    NXT_PORT_METHOD_PLAIN,
    NXT_PORT_METHOD_MMAP
};

typedef enum nxt_port_method_e nxt_port_method_t;

nxt_port_method_t
nxt_port_mmap_get_method(nxt_task_t *task, nxt_port_t *port, nxt_buf_t *b);


#endif /* _NXT_PORT_MEMORY_H_INCLUDED_ */
