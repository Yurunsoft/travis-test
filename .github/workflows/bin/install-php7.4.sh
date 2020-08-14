#!/bin/bash

add-apt-repository ppa:ondrej/php -y -u

apt-get update

apt install -y php7.4-cli php7.4-bcmath php7.4-curl php7.4-dev hp7.4-mbstring php7.4-zip

php -v
php -m
php-config --version
php-config --include-dir
php-config --libs
php-config --ldflags
php-config --extension-dir
