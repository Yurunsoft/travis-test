#!/bin/bash

swooleVersion="4.5.2"

wget -O swoole.tar.gz https://github.com/swoole/swoole-src/archive/v$swooleVersion.tar.gz

swooleDir="swoole-src-${swooleVersion}"

tar -xzf swoole.tar.gz
rm swoole.tar.gz

cd $swooleDir

phpize && ./configure && make -j && make install

echo "extension = swoole.so" >> $(php -r "echo php_ini_loaded_file();")

cd ../

rm -rf $swooleDir

php --ri swoole
