#!/bin/bash

swooleVersion="4.5.2"

wget -O swoole.tar.gz https://github.com/swoole/swoole-src/archive/v$swooleVersion.tar.gz

swooleDir="swoole-src-${swooleVersion}"

tar -xzf swoole.tar.gz
rm swoole.tar.gz

cd $swooleDir

phpize && ./configure && make -j && make install

cd ../

rm -rf $swooleDir

php --ri swoole
