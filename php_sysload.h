/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Robert Eisele <robert@xarg.org>                              |
  | Site: http://www.xarg.org/project/php-sysload/                       |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_SYSLOAD_H
#define PHP_SYSLOAD_H

#define PHP_SYSLOAD_VERSION "1.0.0"
#define PHP_SYSLOAD_EXTNAME "sysload"

#ifdef ZTS
# include "TSRM.h"
#endif

PHP_MINFO_FUNCTION(sysload);
PHP_MINIT_FUNCTION(sysload);
PHP_RINIT_FUNCTION(sysload);
PHP_MSHUTDOWN_FUNCTION(sysload);

extern zend_module_entry sysload_module_entry;
#define phpext_sysload_ptr &sysload_module_entry

#endif

