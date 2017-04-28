/* Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02111-1307  USA */

#ifndef LOG_BUILTINS_IMP_H
#define LOG_BUILTINS_IMP_H

#include <mysql/components/services/log_shared.h>


#define LOG_ITEM_MAX 64


typedef struct _log_item_iter
{
  struct _log_line *ll;
  int               index;
} log_item_iter;


typedef struct _log_line
{
  log_type_mask  seen;
  log_item_iter  iter;
  int            count;
  log_item       item[LOG_ITEM_MAX];
} log_line;


// see include/mysql/components/services/log_builtins.h

class log_builtins_imp
{
public:
  static void init();
  static void deinit();

public: /* Service Implementations */
  static DEFINE_METHOD(int,              wellknown_by_type, (log_item_type t));
  static DEFINE_METHOD(int,              wellknown_by_name, (const char *key,
                                                             size_t length));
  static DEFINE_METHOD(log_item_type,    wellknown_get_type, (uint i));
  static DEFINE_METHOD(const char *,     wellknown_get_name, (uint i));

  static DEFINE_METHOD(int,              item_inconsistent, (log_item *li));
  static DEFINE_METHOD(bool,             item_generic_type,
                                                     (log_item_type t));
  static DEFINE_METHOD(bool,             item_string_class,
                                                     (log_item_class c));
  static DEFINE_METHOD(bool,             item_numeric_class,
                                                     (log_item_class c));

  static DEFINE_METHOD(bool,             item_set_int,
                                           (log_item_data *lid, longlong i));
  static DEFINE_METHOD(bool,             item_set_float,
                                           (log_item_data *lid, double f));
  static DEFINE_METHOD(bool,             item_set_lexstring,
                                           (log_item_data *lid,
                                            const char *s, size_t s_len));
  static DEFINE_METHOD(bool,             item_set_cstring,
                                           (log_item_data *lid, const char *s));

  static DEFINE_METHOD(log_item_data *,  item_set_with_key,
                                           (log_item *li, log_item_type t,
                                            const char *key, uint32 alloc));
  static DEFINE_METHOD(log_item_data *,  item_set,
                                           (log_item *li, log_item_type t));

  static DEFINE_METHOD(log_item_data *,  line_item_set_with_key,
                       (log_line *ll,    log_item_type t,
                        const char *key, uint32 alloc));
  static DEFINE_METHOD(log_item_data *,  line_item_set,
                       (log_line *ll,    log_item_type t));

  static DEFINE_METHOD(log_line *,       line_init,
                                              (char *buff, size_t bufsize));
  static DEFINE_METHOD(int,              line_item_count,
                                              (log_line *ll));

  static DEFINE_METHOD(log_type_mask,    line_item_types_seen,
                                              (log_line *ll, log_type_mask m));

  static DEFINE_METHOD(log_item_iter *,  line_item_iter_acquire,
                                              (log_line *ll));
  static DEFINE_METHOD(void,             line_item_iter_release,
                                              (log_item_iter *it));
  static DEFINE_METHOD(log_item *,       line_item_iter_first,
                                              (log_item_iter *it));
  static DEFINE_METHOD(log_item *,       line_item_iter_next,
                                              (log_item_iter *it));
  static DEFINE_METHOD(log_item *,       line_item_iter_current,
                                              (log_item_iter *it));

  static DEFINE_METHOD(int,              line_submit, (log_line *ll));

  static DEFINE_METHOD(int,              message, (int log_type, ...));

  static DEFINE_METHOD(int,              sanitize, (log_item *li));

  static DEFINE_METHOD(const char *,     errmsg_by_errcode, (int
                                                             mysql_errcode));

  static DEFINE_METHOD(longlong,         errcode_by_errsymbol, (const
                                                                char *sym));

  static DEFINE_METHOD(const char *,     label_from_prio, (int prio));


  static DEFINE_METHOD(int,              open_errstream,  (const char *file,
                                                          void **my_errstream));

  static DEFINE_METHOD(int,              write_errstream, (void *my_errstream,
                                                           const char *buffer,
                                                           size_t length));

  static DEFINE_METHOD(int,              dedicated_errstream,
                                                          (void *my_errstream));

  static DEFINE_METHOD(int,              close_errstream,
                                                         (void **my_errstream));
};


class log_builtins_string_imp
{
public:
  static void init();
  static void deinit();

public: /* Service Implementations */
  static DEFINE_METHOD(void *,           malloc, (size_t len));
  static DEFINE_METHOD(char *,           strndup, (const char *fm, size_t len));
  static DEFINE_METHOD(void,             free, (void *ptr));
  static DEFINE_METHOD(size_t,           length, (const char *s));
  static DEFINE_METHOD(char *,           find_first, (const char *s, int c));
  static DEFINE_METHOD(char *,           find_last,  (const char *s, int c));

  static DEFINE_METHOD(int,              compare,  (const char *a,
                                                    const char *b,
                                                    size_t len,
                                                    bool case_insensitive));

  static DEFINE_METHOD(size_t,           substitutev, (char *to, size_t n,
                                                       const char* fmt,
                                                       va_list ap));

  static DEFINE_METHOD(size_t,           substitute, (char *to, size_t n,
                                                      const char* fmt, ...));
};


class log_builtins_tmp_imp
{
public:
  static void init();
  static void deinit();

public: /* Service Implementations */
  static DEFINE_METHOD(bool,             connection_loop_aborted, (void));
};


class log_builtins_syseventlog_imp
{
public:
  static void init();
  static void deinit();

public: /* Service Implementations */
  static DEFINE_METHOD(int,              open,  (const char *name,
                                                int option, int facility));
  static DEFINE_METHOD(int,              write, (enum loglevel level,
                                                 const char *msg));
  static DEFINE_METHOD(int,              close, (void));
};

#endif /* LOG_BUILTINS_IMP_H */
