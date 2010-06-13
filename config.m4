PHP_ARG_ENABLE(sysload, for Sysload support, [  --enable-sysload          Enable Sysload support])

if test "$PHP_SYSLOAD" != "no"; then
  AC_DEFINE(HAVE_SYSLOAD, 1, [ ])
  PHP_NEW_EXTENSION(sysload, sysload.c, $ext_shared)
fi

