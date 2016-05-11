dnl $Id$
dnl config.m4 for extension php_keeper

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(php_keeper, for php_keeper support,
dnl Make sure that the comment is aligned:
dnl [  --with-php_keeper             Include php_keeper support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(php_keeper, whether to enable php_keeper support,
Make sure that the comment is aligned:
[  --enable-php_keeper           Enable php_keeper support])

if test "$PHP_PHP_KEEPER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-php_keeper -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/php_keeper.h"  # you most likely want to change this
  dnl if test -r $PHP_PHP_KEEPER/$SEARCH_FOR; then # path given as parameter
  dnl   PHP_KEEPER_DIR=$PHP_PHP_KEEPER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for php_keeper files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHP_KEEPER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHP_KEEPER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the php_keeper distribution])
  dnl fi

  dnl # --with-php_keeper -> add include path
  dnl PHP_ADD_INCLUDE($PHP_KEEPER_DIR/include)

  dnl # --with-php_keeper -> check for lib and symbol presence
  dnl LIBNAME=php_keeper # you may want to change this
  dnl LIBSYMBOL=php_keeper # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHP_KEEPER_DIR/$PHP_LIBDIR, PHP_KEEPER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHP_KEEPERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong php_keeper lib version or lib not found])
  dnl ],[
  dnl   -L$PHP_KEEPER_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PHP_KEEPER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(php_keeper, php_keeper.c keeper_engine.c keeper_module.c keeper_rec.c keeper_sapi.c keeper_setting.c, $ext_shared)
fi
