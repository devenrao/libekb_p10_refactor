AC_INIT([libekb],[1.2])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])
AC_SUBST(SONAME_CURRENT, 1)
AC_SUBST(SONAME_REVISION, 0)
AC_SUBST(SONAME_AGE, 0)

case "$host" in
	arm*-*-*) ARCH="arm" ;;
	powerpc64-*-*) ARCH="ppc64" ;;
	powerpc64le-*-*) ARCH="ppc64le" ;;
	x86_64) ARCH="x86_64" ;;
	*) ARCH=$(uname -m) ;;
esac

if test "$ARCH" = "x86_64" ; then
	AC_MSG_NOTICE([Building on X86])
	TARGET_ENDIAN="-DHAVE_LITTLE_ENDIAN"
elif test "$ARCH" = "aarch64" ; then
	AC_MSG_NOTICE([Building on ARM64])
	TARGET_ENDIAN="-DHAVE_LITTLE_ENDIAN"
elif test "$ARCH" = "arm" ; then
	AC_MSG_NOTICE([Building on ARM])
	TARGET_ENDIAN="-DHAVE_LITTLE_ENDIAN"
elif test "$ARCH" = "ppc64" ; then
	AC_MSG_NOTICE([Building on PPC64])
	TARGET_ENDIAN="-DHAVE_BIG_ENDIAN"
elif test "$ARCH" = "ppc64le" ; then
	AC_MSG_NOTICE([Building on PPC64LE])
	TARGET_ENDIAN="-DHAVE_LITTLE_ENDIAN"
else
	AC_MSG_ERROR([libekb cannot be built on $ARCH platform])
fi
AC_SUBST([TARGET_ENDIAN])

AC_ARG_ENABLE([db-install],
	AS_HELP_STRING([--enable-db-install],
		       [Enable installation of attribute database]))
AM_CONDITIONAL([BUILD_DB], [test "x$enable_db_install" = "xyes"])

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AM_PROG_AR
LT_INIT
AC_CHECK_TOOL([OBJCOPY],[objcopy])

PKG_CHECK_MODULES([TARGETING],   [libtargeting])
PKG_CHECK_MODULES([HWACCESS],    [libhwaccess])
PKG_CHECK_MODULES([TARGETSVC],   [libtargetsvc])
PKG_CHECK_MODULES([TRANSPORT],   [libtransport])
LIBS="$TARGETING_LIBS $HWACCESS_LIBS $TARGETSVC_LIBS $TRANSPORT_LIBS $LIBS"

AC_LANG([C++])
CXXFLAGS="$CXXFLAGS -std=c++20"

m4_syscmd([make -f Makefile.generate > Makefile.proc.am])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT
