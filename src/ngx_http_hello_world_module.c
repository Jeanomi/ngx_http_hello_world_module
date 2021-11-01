//
// Created by cuong on 16/10/2021.
//

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include "../../nginx-1.16.1/src/core/ngx_config.h"
#include "../../nginx-1.16.1/src/core/ngx_core.h"
#include "../../nginx-1.16.1/src/http/ngx_http.h"

#define HELLO_WORLD "hello world\r\n"

static char * ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r);

static ngx_command_t ngx_http_hello_world_commands[] = {
        {ngx_string("hello_world"), /* Module directive */
         NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
         ngx_http_hello_world,
         0,
         0,
         NULL
        },

        ngx_null_command
};

static u_char ngx_hello_world[] = HELLO_WORLD;

static ngx_http_module_t ngx_http_hello_world_module_ctx = {
        NULL,
        NULL,

        NULL,
        NULL,

        NULL,
        NULL,

        NULL,
        NULL
}; /* Module context */

ngx_module_t ngx_http_hello_world_module = {
        NGX_MODULE_V1,
        &ngx_http_hello_world_module_ctx, /* module context */
        ngx_http_hello_world_commands, /* module directives */
        NGX_HTTP_MODULE, /* module type */
        NULL, /* init master */
        NULL, /* init module */
        NULL, /* init process */
        NULL, /* init thread */
        NULL, /* init thread */
        NULL, /* init process */
        NULL, /* init master */
        NGX_MODULE_V1_PADDING
}; /* Module definition */
world
static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r){
    ngx_buf_t *b;
    ngx_chain_t out;

    /* Set the Content-Type header. */
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *) "text/plain";

    /* Allocate a new buffer for sending out the reply. */
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

    /* Insertion in the buffer chain. */
    out.buf = b;
    out.next = NULL;

    b->pos = ngx_hello_world;
    b->last = ngx_hello_world + sizeof(ngx_hello_world) - 1;
    b->memory = 1;
    b->last_buf = 1;

    /* Sending the headers for the reply. */
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = sizeof(ngx_hello_world) - 1;
    ngx_http_send_header(r); /* Send the headers */

    /* Send the body, and return the status code of the output filter chain. */
    return ngx_http_output_filter(r, &out);
}

static char * ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf){
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_hello_world_handler;

    return NGX_CONF_OK;
}


