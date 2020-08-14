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

curl -o composer.phar https://getcomposer.org/composer-stable.phar && chmod +x composer.phar && sudo mv -f composer.phar /usr/local/bin/composer && composer -V;

phpIniFile=$(php -r "echo php_ini_loaded_file();")

echo "xdebug.var_display_max_children=128" >> $phpIniFile
echo "xdebug.var_display_max_data=512" >> $phpIniFile
echo "xdebug.var_display_max_depth=16" >> $phpIniFile
