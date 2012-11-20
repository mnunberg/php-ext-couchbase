/*
  +----------------------------------------------------------------------+
  | PHP Version 5														 |
  +----------------------------------------------------------------------+
  | Copyright 2012 Couchbase, Inc.										 |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License");		 |
  | you may not use this file except in compliance with the License.	 |
  | You may obtain a copy of the License at								 |
  |		http://www.apache.org/licenses/LICENSE-2.0						 |
  | Unless required by applicable law or agreed to in writing, software	 |
  | distributed under the License is distributed on an "AS IS" BASIS,	 |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or		 |
  | implied. See the License for the specific language governing		 |
  | permissions and limitations under the License.						 |
  +----------------------------------------------------------------------+
  | Author: Mark Nunberg	   <mnunberg@haskalah.org>					 |
  +----------------------------------------------------------------------+
*/

/**
 * This file contains all the boilerplate, function declarations, and option
 * entries which set up the glue for this extension
 */

#include "internal.h"

/* {{{ COUCHBASE_FUNCTIONS_ARG_INFO
 */
COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_connect, 0, 0, 1)
ZEND_ARG_INFO(0, host)
ZEND_ARG_INFO(0, user)
ZEND_ARG_INFO(0, password)
ZEND_ARG_INFO(0, bucket)
ZEND_ARG_INFO(0, persistent)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_add, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_set, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_set_multi, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_ARRAY_INFO(0, values, 0)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_replace, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_append, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_prepend, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_cas, 0, 0, 4)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, cache_cb)
ZEND_ARG_INFO(1, cas_token)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_INFO(0, lock)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get_multi, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_ARRAY_INFO(0, keys, 0)
ZEND_ARG_ARRAY_INFO(1, cas_tokens, 1)
ZEND_ARG_INFO(0, flags)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_INFO(0, lock)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get_delayed, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_ARRAY_INFO(0, keys, 0)
ZEND_ARG_INFO(0, with_cas)
ZEND_ARG_INFO(0, cb)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_INFO(0, lock)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_touch, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_touch_multi, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_ARRAY_INFO(0, keys, 0)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_fetch, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_fetch_all, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_view, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, doc_name)
ZEND_ARG_INFO(0, view_name)
ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_ARG_INFO(0, return_errors)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_view_gen_query, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, doc_name)
ZEND_ARG_INFO(0, view_name)
ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_ARG_INFO(0, return_errors)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_increment, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, create)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, initial)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_decrement, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, create)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, initial)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_delete, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get_stats, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_flush, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_result_code, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_result_message, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_set_option, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, option)
ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get_option, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, option)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get_servers, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_num_replicas, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get_version, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get_client_version, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_observe, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_INFO(1, details)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_observe_multi, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_ARRAY_INFO(0, key_to_cas, 0)
ZEND_ARG_INFO(1, details)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_key_durability, 0, 0, 4)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_key_durability_multi, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_ARRAY_INFO(0, key_to_cas, 0)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_get_timeout, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_set_timeout, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ COUCHBASE_METHODS_ARG_INFO
 */
COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_construct, 0, 0, 1)
ZEND_ARG_INFO(0, host)
ZEND_ARG_INFO(0, user)
ZEND_ARG_INFO(0, password)
ZEND_ARG_INFO(0, bucket)
ZEND_ARG_INFO(0, persistent)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_add, 0, 0, 2)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_set, 0, 0, 2)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_setmulti, 0, 0, 1)
ZEND_ARG_ARRAY_INFO(0, values, 0)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_replace, 0, 0, 2)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_append, 0, 0, 2)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_prepend, 0, 0, 2)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_cas, 0, 0, 3)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_get, 0, 0, 1)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, cache_cb)
ZEND_ARG_INFO(1, cas_token)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_INFO(0, lock)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_getmulti, 0, 0, 1)
ZEND_ARG_ARRAY_INFO(0, keys, 0)
ZEND_ARG_ARRAY_INFO(1, cas_tokens, 1)
ZEND_ARG_INFO(0, flags)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_INFO(0, lock)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_getdelayed, 0, 0, 1)
ZEND_ARG_ARRAY_INFO(0, keys, 0)
ZEND_ARG_INFO(0, with_cas)
ZEND_ARG_INFO(0, cb)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_INFO(0, lock)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_touch, 0, 0, 2)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_touchmulti, 0, 0, 2)
ZEND_ARG_ARRAY_INFO(0, keys, 0)
ZEND_ARG_INFO(0, expiry)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_fetch, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_fetchall, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_view, 0, 0, 1)
ZEND_ARG_INFO(0, doc_name)
ZEND_ARG_INFO(0, view_name)
ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_ARG_INFO(0, return_errors)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_view_gen_query, 0, 0, 1)
ZEND_ARG_INFO(0, doc_name)
ZEND_ARG_INFO(0, view_name)
ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_ARG_INFO(0, return_errors)
ZEND_END_ARG_INFO()


COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_increment, 0, 0, 1)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, create)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, initial)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_decrement, 0, 0, 1)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, create)
ZEND_ARG_INFO(0, expiration)
ZEND_ARG_INFO(0, initial)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_delete, 0, 0, 1)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_getstats, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_flush, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_resultcode, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_resultmessage, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_setoption, 0, 0, 2)
ZEND_ARG_INFO(0, option)
ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_getoption, 0, 0, 1)
ZEND_ARG_INFO(0, option)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_numreplicas, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_getservers, 0, 0, 0)
ZEND_END_ARG_INFO()


COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_observe, 0, 0, 2)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_INFO(1, details)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_observe_multi, 0, 0, 1)
ZEND_ARG_ARRAY_INFO(0, key_to_cas, 0)
ZEND_ARG_INFO(1, details)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_key_durability, 0, 0, 3)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, cas)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_key_durability_multi, 0, 0, 2)
ZEND_ARG_ARRAY_INFO(0, key_to_cas, 0)
ZEND_ARG_ARRAY_INFO(0, durability, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_get_timeout, 0, 0, 0)
ZEND_END_ARG_INFO()

COUCHBASE_ARG_PREFIX
ZEND_BEGIN_ARG_INFO_EX(arginfo_m_set_timeout, 0, 0, 1)
ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()


/* }}} */

/* {{{ couchbase_functions[]
 */
static zend_function_entry couchbase_functions[] = {
	PHP_FE(couchbase_connect, arginfo_connect)
	PHP_FE(couchbase_add, arginfo_add)
	PHP_FE(couchbase_set, arginfo_set)
	PHP_FE(couchbase_set_multi, arginfo_set_multi)
	PHP_FE(couchbase_replace, arginfo_replace)
	PHP_FE(couchbase_prepend, arginfo_prepend)
	PHP_FE(couchbase_append, arginfo_append)
	PHP_FE(couchbase_cas, arginfo_cas)
	PHP_FE(couchbase_get, arginfo_get)
	PHP_FE(couchbase_get_multi, arginfo_get_multi)
	PHP_FE(couchbase_get_delayed, arginfo_get_delayed)
	PHP_FE(couchbase_touch, arginfo_touch)
	PHP_FE(couchbase_touch_multi, arginfo_touch_multi)
	PHP_FE(couchbase_fetch, arginfo_fetch)
	PHP_FE(couchbase_fetch_all, arginfo_fetch_all)
	PHP_FE(couchbase_view, arginfo_view)
	PHP_FE(couchbase_view_gen_query, arginfo_view_gen_query)
	PHP_FE(couchbase_increment, arginfo_increment)
	PHP_FE(couchbase_decrement, arginfo_decrement)
	PHP_FE(couchbase_get_stats, arginfo_get_stats)
	PHP_FE(couchbase_delete, arginfo_delete)
	PHP_FE(couchbase_flush, arginfo_flush)
	PHP_FE(couchbase_get_result_code, arginfo_result_code)
	PHP_FE(couchbase_get_result_message, arginfo_result_message)
	PHP_FE(couchbase_set_option, arginfo_set_option)
	PHP_FE(couchbase_get_option, arginfo_get_option)
	PHP_FE(couchbase_get_servers, arginfo_get_servers)
	PHP_FE(couchbase_get_num_replicas, arginfo_num_replicas)
	PHP_FE(couchbase_get_version, arginfo_get_version)
	PHP_FE(couchbase_get_client_version, arginfo_get_client_version)
	PHP_FE(couchbase_observe, arginfo_observe)
	PHP_FE(couchbase_observe_multi, arginfo_observe_multi)
	PHP_FE(couchbase_key_durability, arginfo_key_durability)
	PHP_FE(couchbase_key_durability_multi, arginfo_key_durability_multi)
	PHP_FE(couchbase_get_timeout, arginfo_get_timeout)
	PHP_FE(couchbase_set_timeout, arginfo_set_timeout) {
		NULL, NULL, NULL
	}
};
/* }}} */

/* {{{ couchbase_methods[]
 */
static zend_function_entry couchbase_methods[] = {
	PHP_ME(couchbase, __construct, arginfo_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(couchbase, add, arginfo_m_add, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, set, arginfo_m_set, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, setMulti, arginfo_m_setmulti, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, replace, arginfo_m_replace, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, prepend, arginfo_m_prepend, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, append, arginfo_m_append, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, cas, arginfo_m_cas, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, get, arginfo_m_get, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getMulti, arginfo_m_getmulti, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getDelayed, arginfo_m_getdelayed, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, touch, arginfo_m_touch, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, touchMulti, arginfo_m_touchmulti, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, fetch, arginfo_m_fetch, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, fetchAll, arginfo_m_fetchall, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, view, arginfo_m_view, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, viewGenQuery, arginfo_m_view_gen_query, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, delete, arginfo_m_delete, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getStats, arginfo_m_getstats, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, flush, arginfo_m_flush, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, increment, arginfo_m_increment, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, decrement, arginfo_m_decrement, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getResultCode, arginfo_m_resultcode, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getResultMessage, arginfo_m_resultmessage, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, setOption, arginfo_m_setoption, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getOption, arginfo_m_getoption, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getVersion, arginfo_get_version, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getClientVersion, arginfo_get_client_version, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getNumReplicas, arginfo_m_numreplicas, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getServers, arginfo_m_getservers, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, observe, arginfo_m_observe, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, observeMulti, arginfo_m_observe_multi, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, keyDurability, arginfo_m_key_durability, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, keyDurabilityMulti, arginfo_m_key_durability_multi, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, getTimeout, arginfo_m_get_timeout, ZEND_ACC_PUBLIC)
	PHP_ME(couchbase, setTimeout, arginfo_m_set_timeout, ZEND_ACC_PUBLIC) {
		NULL, NULL, NULL
	}
};
/* }}} */


/* OO style APIs */
/* {{{ proto Couchbase::__construct(string $host[, string $user[, string $password[, string $bucket[, bool $persistent = false]]]])
*/
PHP_METHOD(couchbase, __construct)
{
	php_couchbase_create_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::get(string $key[, callback $cache_cb[, string &$cas_tokey[, int $expiry[, bool $lock]]]])
 */
PHP_METHOD(couchbase, get)
{
	php_couchbase_get_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 1);
}
/* }}} */

/* {{{ proto Couchbase::getMulti(array $keys[, array &cas[, int $flag[, int $expiry[, bool $lock]]]])
 */
PHP_METHOD(couchbase, getMulti)
{
	php_couchbase_get_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 1);
}
/* }}} */

/* {{{ proto Couchbase::touch(string $key, int $expiry)
 */
PHP_METHOD(couchbase, touch)
{
	php_couchbase_touch_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 1);
}
/* }}} */

/* {{{ proto Couchbase::touchMulti(array $keys, int $expiry)
 */
PHP_METHOD(couchbase, touchMulti)
{
	php_couchbase_touch_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 1);
}
/* }}} */

/* {{{ proto Couchbase::cas(string $cas, string $key, mixed $value[, int $expiration])
 */
PHP_METHOD(couchbase, cas)
{
	php_couchbase_cas_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::add(string $key, mixed $value[, int $expiration])
 */
PHP_METHOD(couchbase, add)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_ADD, 0, 1);
}
/* }}} */

/* {{{ proto Couchbase::set(string $key, mixed $value[, int $expiration])
 */
PHP_METHOD(couchbase, set)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_SET, 0, 1);
}
/* }}} */

/* {{{ proto Couchbase::setMulti(array $values[, int $expiration])
 */
PHP_METHOD(couchbase, setMulti)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_SET, 1, 1);
}
/* }}} */

/* {{{ proto Couchbase::prepend(string $key[, string $cas = '0'])
 */
PHP_METHOD(couchbase, prepend)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_PREPEND, 0, 1);
}
/* }}} */

/* {{{ proto Couchbase::append(string $key[, string $cas = '0'])
 */
PHP_METHOD(couchbase, append)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_APPEND, 0, 1);
}
/* }}} */

/* {{{ proto Couchbase::replace(string $key, mixed $value[, int $expiration[, string $cas = '0']])
 */
PHP_METHOD(couchbase, replace)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_REPLACE, 0, 1);
}
/* }}} */

/* {{{ proto Couchbase::increment(string $key[, int $offset = 1[, bool $create = false[, int $expiration = 0[, int $initial = 0]]]])
 */
PHP_METHOD(couchbase, increment)
{
	php_couchbase_arithmetic_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, '+', 1);
}
/* }}} */

/* {{{ proto Couchbase::decrement(string $key[, int $offset = 1[, bool $create = false[, int $expiration = 0[, int $initial = 0]]]])
 */
PHP_METHOD(couchbase, decrement)
{
	php_couchbase_arithmetic_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, '-', 1);
}
/* }}} */

/* {{{ proto Couchbase::getStats(void)
 */
PHP_METHOD(couchbase, getStats)
{
	php_couchbase_stats_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::getDelayed(array $keys[, bool $with_cas[, callback $value_cb[, int $expiry[, bool $locking]]]])
 */
PHP_METHOD(couchbase, getDelayed)
{
	php_couchbase_get_delayed_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::fetch(void)
 */
PHP_METHOD(couchbase, fetch)
{
	php_couchbase_fetch_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 1);
}
/* }}} */

/* {{{ proto Couchbase::fetchAll(void)
 */
PHP_METHOD(couchbase, fetchAll)
{
	php_couchbase_fetch_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 1);
}
/* }}} */

/* {{{ proto Couchbase::view(string $doc_name, string $view_name[, array $options])
 */
PHP_METHOD(couchbase, view)
{
	php_couchbase_view_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 0);
}
/* }}} */

/* {{{ proto Couchbase::viewGenQuery(string $doc_name, string $view_name[, array $options)
 */
PHP_METHOD(couchbase, viewGenQuery)
{
	php_couchbase_view_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 1);
}
/* }}} */


/* {{{ proto Couchbase::delete(string $key[, string $cas = '0'])
 */
PHP_METHOD(couchbase, delete)
{
	php_couchbase_remove_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::flush(void)
 */
PHP_METHOD(couchbase, flush)
{
	php_couchbase_flush_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::getResultCode(void)
 */
PHP_METHOD(couchbase, getResultCode)
{
	php_couchbase_res *couchbase_res;
	PHP_COUCHBASE_GET_PARAMS(couchbase_res,
			PHP_COUCHBASE_ARG_F_OO | PHP_COUCHBASE_ARG_F_ONLYVALID, "");
	RETURN_LONG(couchbase_res->rc);
}
/* }}} */

/* {{{ proto Couchbase::getResultMessage(void)
 */
PHP_METHOD(couchbase, getResultMessage)
{
	php_couchbase_get_result_message_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::setOption(int $option, int $value)
 */
PHP_METHOD(couchbase, setOption)
{
	php_couchbase_set_option_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::getOption(int $option)
 */
PHP_METHOD(couchbase, getOption)
{
	php_couchbase_get_option_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::getVersion(void)
 */
PHP_METHOD(couchbase, getVersion)
{
	php_couchbase_version_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::getClientVersion(void)
 */
PHP_METHOD(couchbase, getClientVersion)
{
	RETURN_STRING(PHP_COUCHBASE_VERSION, 1);
}
/* }}} */

PHP_METHOD(couchbase, getNumReplicas)
{
	php_couchbase_get_num_replicas_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU,
	                                    PHP_COUCHBASE_ARG_F_OO);
}

PHP_METHOD(couchbase, getServers)
{
	php_couchbase_get_servers_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU,
	                               PHP_COUCHBASE_ARG_F_OO);
}

/* {{{ proto Couchbase::observe(string $key, string $cas, &$details)
 */
PHP_METHOD(couchbase, observe)
{
	php_couchbase_observe_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 1, 0); /* multi, oo, poll */
}
/* }}} */

/* {{{ proto Couchbase::observeMulti(array $key_to_cas, &$details)
 */
PHP_METHOD(couchbase, observeMulti)
{
	php_couchbase_observe_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 1, 0); /* multi, oo, poll */
}
/* }}} */

/* {{{ proto Couchbase::keyDurability(string $key, string $cas, array $durability)
 */
PHP_METHOD(couchbase, keyDurability)
{
	php_couchbase_observe_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 1, 1); /* multi, oo, poll */
}
/* }}} */

/* {{{ proto Couchbase::keyDurability(array $key_to_cas, array $durability)
 */
PHP_METHOD(couchbase, keyDurabilityMulti)
{
	php_couchbase_observe_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 1, 1); /* multi, oo, poll */
}
/* }}} */

/* {{{ proto Couchbase::getTimeout() */
PHP_METHOD(couchbase, getTimeout)
{
	php_couchbase_get_timeout_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto Couchbase::setTimeout(int $timeout) */
PHP_METHOD(couchbase, setTimeout)
{
	php_couchbase_set_timeout_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* procedural APIs*/
/* {{{ proto couchbase_connect(string $host[, string $user[, string $password[, string $bucket[, bool $persistent = false]]]])
*/
PHP_FUNCTION(couchbase_connect)
{
	php_couchbase_create_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_get(resource $couchbase, string $key[, callback $cache_cb[, string &$cas_tokey[, int $expiry[, bool $lock]]]])
 */
PHP_FUNCTION(couchbase_get)
{
	php_couchbase_get_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_get_multi(resource $couchbase, array $keys[, array &cas[, int $flag[, int $expiry[, bool $lock]]]])
 */
PHP_FUNCTION(couchbase_get_multi)
{
	php_couchbase_get_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 0);
}
/* }}} */

/* {{{ proto couchbase_touch(resource $couchbase, string $key, int $expiry)
 */
PHP_FUNCTION(couchbase_touch)
{
	php_couchbase_touch_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_touch_multi(resource $couchbase, array $keys, int $expiry)
 */
PHP_FUNCTION(couchbase_touch_multi)
{
	php_couchbase_touch_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 0);
}
/* }}} */

/* {{{ proto couchbase_cas(resource $couchbase, string $cas, string $key, mixed $value[, int $expiration])
 */
PHP_FUNCTION(couchbase_cas)
{
	php_couchbase_cas_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_add(resource $couchbase, string $key, mixed $value[, int $expiration])
 */
PHP_FUNCTION(couchbase_add)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_ADD, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_set(resource $couchbase, string $key, mixed $value[, int $expiration])
 */
PHP_FUNCTION(couchbase_set)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_SET, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_set_multi(resource $couchbase, array $values[, int $expiration])
 */
PHP_FUNCTION(couchbase_set_multi)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_SET, 1, 0);
}
/* }}} */

/* {{{ proto couchbase_prepend(resource $couchbase, string $key[, string $cas = '0'])
 */
PHP_FUNCTION(couchbase_prepend)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_PREPEND, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_append(resource $couchbase, string $key[, string $cas = '0'])
 */
PHP_FUNCTION(couchbase_append)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_APPEND, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_replace(resource $couchbase, string $key, mixed $value[, int $expiration[, string $cas = '0']])
 */
PHP_FUNCTION(couchbase_replace)
{
	php_couchbase_store_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, LCB_REPLACE, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_increment(resource $couchbase, string $key[, int $offset = 1[, bool $create = false[, int $expiration = 0[, int $initial = 0]]]])
 */
PHP_FUNCTION(couchbase_increment)
{
	php_couchbase_arithmetic_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, '+', 0);
}
/* }}} */

/* {{{ proto couchbase_decrement(resource $couchbase, string $key[, int $offset = 1[, bool $create = false[, int $expiration = 0[, int $initial = 0]]]])
 */
PHP_FUNCTION(couchbase_decrement)
{
	php_couchbase_arithmetic_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, '-', 0);
}
/* }}} */

/* {{{ proto couchbase_get_stats(resource $couchbase)
 */
PHP_FUNCTION(couchbase_get_stats)
{
	php_couchbase_stats_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_get_delayed(resource $couchbase, array $keys[, bool $with_cas[, callback $value_cb[, int $expiry[, bool $lock]]]])
 */
PHP_FUNCTION(couchbase_get_delayed)
{
	php_couchbase_get_delayed_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_fetch(resource $couchbase)
 */
PHP_FUNCTION(couchbase_fetch)
{
	php_couchbase_fetch_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_fetch_all(resource $couchbase)
 */
PHP_FUNCTION(couchbase_fetch_all)
{
	php_couchbase_fetch_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 0);
}
/* }}} */

/* {{{ proto couchbase_view(resource $couchbase, string $doc_name, string $view_name[, array $options])
 */
PHP_FUNCTION(couchbase_view)
{
	php_couchbase_view_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 0);
}
/* }}} */

/* {{{ proto couchbase_view_gen_query(resource $couchbase string $doc_name, string $view_name[,array $options])
 */
PHP_FUNCTION(couchbase_view_gen_query)
{
	php_couchbase_view_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 1);
}
/* }}} */

/* {{{ proto couchbase_delete(resource $couchbase, string $key[, string $cas = '0'])
 */
PHP_FUNCTION(couchbase_delete)
{
	php_couchbase_remove_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_flush(resource $couchbase)
 */
PHP_FUNCTION(couchbase_flush)
{
	php_couchbase_flush_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_get_result_code(resource $couchbase)
 */
PHP_FUNCTION(couchbase_get_result_code)
{
	php_couchbase_res *couchbase_res;
	PHP_COUCHBASE_GET_PARAMS(couchbase_res,
			PHP_COUCHBASE_ARG_F_FUNCTIONAL|PHP_COUCHBASE_ARG_F_ONLYVALID,
			"");

	RETURN_LONG(couchbase_res->rc);
}
/* }}} */

/* {{{ proto couchbase_get_result_message(resource $couchbase)
 */
PHP_FUNCTION(couchbase_get_result_message)
{
	php_couchbase_get_result_message_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */


/* {{{ proto couchbase_set_option(resource $couchbase, int $option, int $value)
 */
PHP_FUNCTION(couchbase_set_option)
{
	php_couchbase_set_option_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_get_option(resource $couchbase, int $option)
 */
PHP_FUNCTION(couchbase_get_option)
{
	php_couchbase_get_option_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_get_version(void)
 */
PHP_FUNCTION(couchbase_get_version)
{
	php_couchbase_version_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_get_client_version(void)
 */
PHP_FUNCTION(couchbase_get_client_version)
{
	RETURN_STRING(PHP_COUCHBASE_VERSION, 1);
}
/* }}} */


/* {{ proto couchbase_get_num_replicas(void)
 */
PHP_FUNCTION(couchbase_get_num_replicas)
{
	php_couchbase_get_num_replicas_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU,
	                                    PHP_COUCHBASE_ARG_F_FUNCTIONAL);
}
/* }}} */


/* {{{ proto couchbase_get_servers(void)
 */
PHP_FUNCTION(couchbase_get_servers)
{
	php_couchbase_get_servers_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU,
	                               PHP_COUCHBASE_ARG_F_FUNCTIONAL);
}
/* }}} */

/* {{{ proto couchbase_observe(resource $couchbase, string $key, string $cas, &$details)
 */
PHP_FUNCTION(couchbase_observe)
{
	php_couchbase_observe_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 0, 0); /* multi, oo, poll */
}
/* }}} */

/* {{{ proto couchbase_observe_multi(resource $couchbase, array $key_to_cas, &$details)
 */
PHP_FUNCTION(couchbase_observe_multi)
{
	php_couchbase_observe_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 0, 0); /* multi, oo, poll */
}
/* }}} */

/* {{{ proto couchbase_key_durability(resource $couchbase, string $key, string $cas, array $durability)
 */
PHP_FUNCTION(couchbase_key_durability)
{
	php_couchbase_observe_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0, 0, 1); /* multi, oo, poll */
}
/* }}} */

/* {{{ proto couchbase_key_durability_multi(resource $couchbase, string $key_to_cas, array $durability)
 */
PHP_FUNCTION(couchbase_key_durability_multi)
{
	php_couchbase_observe_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1, 0, 1); /*multi, oo, poll */
}
/* }}} */

/* {{{ proto couchbase_get_timeout(resource $couchbase) */
PHP_FUNCTION(couchbase_get_timeout)
{
	php_couchbase_get_timeout_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto couchbase_set_timeout(resource $couchbase, int $timeout) */
PHP_FUNCTION(couchbase_set_timeout)
{
	php_couchbase_set_timeout_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */



ZEND_DECLARE_MODULE_GLOBALS(couchbase)

PHP_COUCHBASE_LOCAL
int le_couchbase;
PHP_COUCHBASE_LOCAL
int le_pcouchbase;
zend_class_entry *couchbase_ce;


/* {{{ couchbase_module_entry
 */
#if ZEND_MODULE_API_NO >= 20050922
static const zend_module_dep coucubase_deps[] = {
#ifdef HAVE_JSON_API
	ZEND_MOD_REQUIRED("json")
#endif
	{
		NULL, NULL, NULL
	}
};
#endif

zend_module_entry couchbase_module_entry = {
#if ZEND_MODULE_API_NO >= 20050922
	STANDARD_MODULE_HEADER_EX, NULL,
	(zend_module_dep *)coucubase_deps,
#else
	STANDARD_MODULE_HEADER,
#endif
	"couchbase",
	couchbase_functions,
	PHP_MINIT(couchbase),
	PHP_MSHUTDOWN(couchbase),
	PHP_RINIT(couchbase),		 /* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(couchbase),	 /* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(couchbase),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_COUCHBASE_VERSION,
#endif
	PHP_MODULE_GLOBALS(couchbase),
	PHP_GINIT(couchbase),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_COUCHBASE
ZEND_GET_MODULE(couchbase)
#endif

/* {{{ OnUpdateCompressor
 */
static PHP_INI_MH(OnUpdateCompressor)
{
	if (!new_value || !strcmp(new_value, "none")) {
		COUCHBASE_G(compressor_real) = COUCHBASE_COMPRESSION_NONE;
	} else if (!strcmp(new_value, "fastlz")) {
		COUCHBASE_G(compressor_real) = COUCHBASE_COMPRESSION_FASTLZ;
#ifdef HAVE_COMPRESSION_ZLIB
	} else if (!strcmp(new_value, "zlib")) {
		COUCHBASE_G(compressor_real) = COUCHBASE_COMPRESSION_ZLIB;
#endif
	} else {
		return FAILURE;
	}
	return OnUpdateString(entry, new_value, new_value_length, mh_arg1, mh_arg2, mh_arg3, stage TSRMLS_CC);
}
/* }}} */

/* {{{ OnUpdateSerializer
 */
static PHP_INI_MH(OnUpdateSerializer)
{
	if (!new_value) {
		COUCHBASE_G(serializer_real) = COUCHBASE_SERIALIZER_DEFAULT;
	} else if (!strcmp(new_value, "php")) {
		COUCHBASE_G(serializer_real) = COUCHBASE_SERIALIZER_PHP;
#ifdef HAVE_JSON_API
	} else if (!strcmp(new_value, "json")) {
		COUCHBASE_G(serializer_real) = COUCHBASE_SERIALIZER_JSON;
	} else if (!strcmp(new_value, "json_array")) {
		COUCHBASE_G(serializer_real) = COUCHBASE_SERIALIZER_JSON_ARRAY;
#endif
	} else {
		return FAILURE;
	}

	return OnUpdateString(entry, new_value, new_value_length, mh_arg1, mh_arg2, mh_arg3, stage TSRMLS_CC);
}
/* }}} */

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
STD_PHP_INI_ENTRY(PCBC_INIENT_SERIALIZER, PCBC_INIDEFL_SERIALIZER,
		PHP_INI_ALL, OnUpdateSerializer, serializer, zend_couchbase_globals, couchbase_globals)

STD_PHP_INI_ENTRY(PCBC_INIENT_COMPALGO, PCBC_INIDEFL_COMPALGO,
		PHP_INI_ALL, OnUpdateCompressor, compressor, zend_couchbase_globals, couchbase_globals)

STD_PHP_INI_ENTRY(PCBC_INIENT_COMPFACTOR, PCBC_INIDEFL_COMPFACTOR,
		PHP_INI_ALL, OnUpdateReal, compression_factor, zend_couchbase_globals, couchbase_globals)

STD_PHP_INI_ENTRY(PCBC_INIENT_COMPTHRESH, PCBC_INIDEFL_COMPTHRESH,
		PHP_INI_ALL, OnUpdateLong, compression_threshold, zend_couchbase_globals, couchbase_globals)

STD_PHP_INI_ENTRY(PCBC_INIENT_OBS_INTERVAL, PCBC_INIDEFL_OBS_INTERVAL,
		PHP_INI_ALL, OnUpdateLong, durability_default_poll_interval, zend_couchbase_globals, couchbase_globals) /* units of microseconds, 100k = a tenth of a second */

STD_PHP_INI_ENTRY(PCBC_INIENT_OBS_TIMEOUT, PCBC_INIDEFL_OBS_TIMEOUT,
		PHP_INI_ALL, OnUpdateLong, durability_default_timeout, zend_couchbase_globals, couchbase_globals) /* also units of microseconds, 40M = 40sec */
PHP_INI_END()
/* }}} */


/* module functions */
/* {{{ PHP_GINIT_FUNCTION
*/
PHP_GINIT_FUNCTION(couchbase)
{
}
/* }}} */


#define PCBC_XAPIOPTIONS \
	XX("SUCCESS", LCB_SUCCESS) \
	XX("AUTH_CONTINUE", LCB_AUTH_CONTINUE) \
	XX("DELTA_BADVAL", LCB_DELTA_BADVAL) \
	XX("E2BIG", LCB_E2BIG) \
	XX("EBUSY", LCB_EBUSY) \
	XX("EINTERNAL", LCB_EINTERNAL) \
	XX("EINVAL", LCB_EINVAL) \
	XX("ENOMEM", LCB_ENOMEM) \
	XX("ERROR", LCB_ERROR) \
	XX("ETMPFAIL", LCB_ETMPFAIL) \
	XX("KEY_EEXISTS", LCB_KEY_EEXISTS) \
	XX("KEY_ENOENT", LCB_KEY_ENOENT) \
	XX("NETWORK_ERROR", LCB_NETWORK_ERROR) \
	XX("NOT_MY_VBUCKET", LCB_NOT_MY_VBUCKET) \
	XX("NOT_STORED", LCB_NOT_STORED) \
	XX("NOT_SUPPORTED", LCB_NOT_SUPPORTED) \
	XX("UNKNOWN_COMMAND", LCB_UNKNOWN_COMMAND) \
	XX("UNKNOWN_HOST", LCB_UNKNOWN_HOST) \
	\
	/* php-specific codes */ \
	XX("OPT_SERIALIZER", COUCHBASE_OPT_SERIALIZER) \
	XX("OPT_COMPRESSION", COUCHBASE_OPT_COMPRESSION) \
	XX("OPT_PREFIX_KEY", COUCHBASE_OPT_PREFIX_KEY) \
	XX("OPT_IGNOREFLAGS", COUCHBASE_OPT_IGNOREFLAGS) \
	/* serializers */ \
	XX("SERIALIZER_PHP", COUCHBASE_SERIALIZER_PHP) \
	XX("SERIALIZER_JSON", COUCHBASE_SERIALIZER_JSON) \
	XX("SERIALIZER_JSON_ARRAY", COUCHBASE_SERIALIZER_JSON_ARRAY) \
	/* compressors */ \
	XX("COMPRESSION_NONE", COUCHBASE_COMPRESSION_NONE) \
	XX("COMPRESSION_FASTLZ", COUCHBASE_COMPRESSION_FASTLZ) \
	XX("COMPRESSION_ZLIB", COUCHBASE_COMPRESSION_ZLIB) \
	XX("GET_PRESERVE_ORDER", COUCHBASE_GET_PRESERVE_ORDER) \
	XX("OPT_VOPTS_PASSTHROUGH", COUCHBASE_OPT_VOPTS_PASSTHROUGH)

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(couchbase)
{
	zend_class_entry ce;

	REGISTER_INI_ENTRIES();

#define XX(strbase, val) \
	REGISTER_LONG_CONSTANT("COUCHBASE_"strbase, val, CONST_PERSISTENT|CONST_CS);
	PCBC_XAPIOPTIONS
#undef XX

	le_couchbase = zend_register_list_destructors_ex(php_couchbase_res_dtor, NULL, PHP_COUCHBASE_RESOURCE, module_number);
	le_pcouchbase = zend_register_list_destructors_ex(NULL, php_couchbase_pres_dtor, PHP_COUCHBASE_PERSISTENT_RESOURCE, module_number);

	INIT_CLASS_ENTRY(ce, "Couchbase", couchbase_methods);
	couchbase_ce = zend_register_internal_class_ex(&ce, NULL, NULL TSRMLS_CC);

#define XX(strbase, val) \
	zend_declare_class_constant_long(couchbase_ce, ZEND_STRL(strbase), val TSRMLS_CC);
	PCBC_XAPIOPTIONS
#undef XX

	zend_declare_property_null(couchbase_ce, ZEND_STRL(COUCHBASE_PROPERTY_HANDLE), ZEND_ACC_PRIVATE TSRMLS_CC);
    init_couchbase_cluster(module_number TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(couchbase)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(couchbase)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(couchbase)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(couchbase)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "couchbase support", "enabled");
	php_info_print_table_row(2, "version", PHP_COUCHBASE_VERSION);

#ifdef HAVE_JSON_API
	php_info_print_table_row(2, "json support", "yes");
#else
	php_info_print_table_row(2, "json support", "no");
#endif
	php_info_print_table_row(2, "fastlz support", "yes");

#ifdef HAVE_COMPRESSION_ZLIB
	php_info_print_table_row(2, "zlib support", "yes");
#else
	php_info_print_table_row(2, "zlib support", "no");
#endif

	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

