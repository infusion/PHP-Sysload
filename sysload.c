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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_ini.h"
#include "php_sysload.h"
#include "SAPI.h"

static function_entry sysload_functions[] = {
    {NULL, NULL, NULL}
};

zend_module_entry sysload_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_SYSLOAD_EXTNAME,
    sysload_functions,
    PHP_MINIT(sysload),
    PHP_MSHUTDOWN(sysload),
    PHP_RINIT(sysload),
    NULL,
    PHP_MINFO(sysload),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_SYSLOAD_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_SYSLOAD
ZEND_GET_MODULE(sysload)
#endif

PHP_INI_BEGIN()
PHP_INI_ENTRY("sysload.one-minute", "1.0", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("sysload.five-minutes", "0.5", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("sysload.ten-minutes", "0.3", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("sysload.header", "X-Sysload: Critical", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("sysload.force-exit", "1", PHP_INI_ALL, NULL)
PHP_INI_END()

PHP_MINFO_FUNCTION(sysload)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "sysload support", "enabled");
    php_info_print_table_row(2, "sysload version", PHP_SYSLOAD_VERSION);
    php_info_print_table_end();
}

PHP_MINIT_FUNCTION(sysload)
{
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_RINIT_FUNCTION(sysload)
{
	float load[3];
	int i;
	char buffer[64];
	char *p;
	FILE *fd;

	if(NULL != (fd = VCWD_FOPEN("/proc/loadavg", "r")) && NULL != fgets(buffer, 64, fd)) {
		p = strtok(buffer, " ");
		for(; NULL != p && i < 3; i++) {
			load[i] = atof(p);
			p = strtok(NULL, " ");
		}
		fclose(fd);

		if(load[0] > INI_FLT("sysload.one-minute") || load[1] > INI_FLT("sysload.five-minutes") || load[2] > INI_FLT("sysload.ten-minutes")) {
			i = strlen(INI_STR("sysload.header"));
			if(i > 0) {
				sapi_header_line h = { INI_STR("sysload.header"), i, 0 };
				sapi_header_op(SAPI_HEADER_REPLACE, &h TSRMLS_CC);
				if(INI_BOOL("sysload.force-exit")) {
					php_header();
					zend_bailout();
				}
			}
		}
	}
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(sysload)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

