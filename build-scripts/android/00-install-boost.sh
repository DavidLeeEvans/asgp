#!/bin/sh

set -e

. $(dirname $0)/config.sh

BOOST_VER1=1
BOOST_VER2=55
BOOST_VER3=0

ARCHIVE_NAME="boost_${BOOST_VER1}_${BOOST_VER2}_${BOOST_VER3}.tar.bz2"
ARCHIVE_MD5="d6eef4b4cacb2183f2bf265a5a03a354"
BOOST_SOURCE_DIR="boost_${BOOST_VER1}_${BOOST_VER2}_${BOOST_VER3}"

DOWNLOAD_LINK="http://downloads.sourceforge.net/project/boost/boost/$BOOST_VER1.$BOOST_VER2.$BOOST_VER3/${ARCHIVE_NAME}?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost%2F${BOOST_VER1}.${BOOST_VER2}.${BOOST_VER3}%2F&ts=1291326673&use_mirror=freefr"

ARCHIVE=$(download_file "$DOWNLOAD_LINK" "$ARCHIVE_NAME" "$ARCHIVE_MD5")

cd $CACHE

if [ -d "$BOOST_SOURCE_DIR" ]
then
    cd $BOOST_SOURCE_DIR
else
    tar xf "$ARCHIVE"
    cd "$BOOST_SOURCE_DIR"
    patch -p0 < "$PATCHES/boost-endian.diff"
    patch -p0 < "$PATCHES/boost-filesystem.diff"
    patch -p0 < "$PATCHES/boost-user-config.diff"
fi

[ -f ./bjam ] || ./bootstrap.sh

export PATH=$ANDROID_TOOLCHAIN_ROOT/bin/:$PATH
export NO_BZIP2=1

ARGS=

if [ ! -z "$LDFLAGS" ]
then
    ./bjam $ARGS target-os=linux \
           toolset=gcc-androidR10e \
           link=static \
           runtime-link=static \
           cxxflags="$CXXFLAGS" \
           linkflags="$LDFLAGS" \
           --stagedir=android \
           --without-python \
           --without-serialization \
           --prefix=$INSTALL_PREFIX \
           release \
           install
else
    ./bjam $ARGS target-os=linux \
           toolset=gcc-androidR10e \
           link=static \
           runtime-link=static \
           cxxflags="$CXXFLAGS" \
           --stagedir=android \
           --without-python \
           --without-serialization \
           --prefix=$INSTALL_PREFIX \
           release \
           install
fi

set_shell_variable ANDROID_BOOST_INCLUDE_DIR "$INSTALL_PREFIX/include/"
