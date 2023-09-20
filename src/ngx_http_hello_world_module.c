//
// Created by cuong on 16/10/2021.
//

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

#define HELLO_WORLD "hello world\r\n"

static char * ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
// static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_hello_world_redirect(ngx_http_request_t *r);

static ngx_command_t ngx_http_hello_world_commands[] = {
        {ngx_string("hello_world"), /* Module directive */
         NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
         ngx_http_hello_world,
         0,
         0,
         NULL
        },

        ngx_null_command
};

// static u_char ngx_hello_world[] = HELLO_WORLD;

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

ngx_int_t
ngx_http_hello_world_redirect(ngx_http_request_t *r)
{
    ngx_str_t  uri, args;

    ngx_str_set(&uri, "/foo");
    ngx_str_set(&args, "bar=1");

    return ngx_http_internal_redirect(r, &uri, &args);
}


// static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r){
//     ngx_buf_t *b;
//     ngx_chain_t out;

//     ngx_table_elt_t *callback_url;
//     ngx_table_elt_t *callback_method;

//     size_t len = 0;
//     u_char *p;
//     uintptr_t escape;
//     u_char *url;
//     u_char *method;

//     /* Set the Content-Type header. */
//     r->headers_out.content_type.len = sizeof("text/plain") - 1;
//     r->headers_out.content_type.data = (u_char *) "text/plain";

//     ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
//             "ngx_http_hello_world_handler setting up variable done");

//     /* Allocate a new buffer for sending out the reply. */
//     b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

//     /* Insertion in the buffer chain. */
//     out.buf = b;
//     out.next = NULL;

//     b->pos = ngx_hello_world;
//     b->last = ngx_hello_world + sizeof(ngx_hello_world) - 1;
//     b->memory = 1;
//     b->last_buf = 1;

//     callback_url = ngx_list_push(&r->headers_out.headers);
//     if (callback_url == NULL) {
//         return NGX_ERROR;
//     }

//     callback_method = ngx_list_push(&r->headers_out.headers);
//     if (callback_method == NULL) {
//             return NGX_ERROR;
//     }

//     /* Allocate and parse request URL and method */
//     url = ngx_pnalloc(r->pool, 512);
//     if (url == NULL) {
//         return NGX_DECLINED;
//     }

//     method = ngx_pnalloc(r->pool, 64);
//     if (method == NULL) {
//         return NGX_DECLINED;
//     }

//     ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
//             "ngx_http_hello_world_handler allocate done");

//     if (r->http_connection->ssl) {
//         p = ngx_cpymem(url, "https%3A//", 10);
//         len += 10;
//     } else {
//         ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
//             "ngx_http_hello_world_handler no ssl");
//         p = ngx_cpymem(url, "http%3A//", 9);
//         len += 9;
//     }

//     p = ngx_cpymem(p, r->headers_in.host->value.data,
//             r->headers_in.host->value.len);
//     len += r->headers_in.host->value.len;

//     ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
//             "ngx_http_hello_world_handler 1 %s", url);

//     if (r->quoted_uri || r->space_in_uri) {
//         ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
//             "ngx_http_hello_world_handler escape");
//         escape = 2 * ngx_escape_uri(NULL, r->uri.data, r->uri.len, NGX_ESCAPE_URI);
//         ngx_escape_uri(p, r->uri.data, r->uri.len, NGX_ESCAPE_URI);
//         len += escape + r->uri.len;
//     } else {
//         ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
//             "ngx_http_hello_world_handler no escape");
//         ngx_memcpy(p, r->uri.data, r->uri.len);
//         len += r->uri.len;
//     }

//     ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
//             "ngx_http_hello_world_handler 2 %s", url);

//     callback_url->hash = 1;
//     ngx_str_set(&callback_url->key, "Callback-URL");
//     // ngx_str_set(&callback_url->value, "foo");
//     callback_url->value.data = url;
//     callback_url->value.len = len;

//     ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
//             "ngx_http_hello_world_handler 3 %s", url);

//     // Callback method
//     ngx_memcpy(method, r->method_name.data, r->method_name.len);
//     len = r->method_name.len;

//     callback_method->hash = 1;
//     ngx_str_set(&callback_method->key, "Callback-Method");
//     // ngx_str_set(&callback_method->value, "foo");
//     callback_method->value.data = method;
//     callback_method->value.len = len;

//     /* Sending the headers for the reply. */
//     r->headers_out.status = NGX_HTTP_OK;
//     r->headers_out.content_length_n = sizeof(ngx_hello_world) - 1;
//     ngx_http_send_header(r); /* Send the headers */

//     /* Send the body, and return the status code of the output filter chain. */
//     return ngx_http_output_filter(r, &out);
// }

static char * ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf){
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    // clcf->handler = ngx_http_hello_world_handler;
    clcf->handler = ngx_http_hello_world_redirect;

    return NGX_CONF_OK;
}


