#!/bin/bash
PHP_VERSION="7.4"
brew install php@$PHP_VERSION;
export PATH="$(brew --prefix php)/bin:$PATH";

php -v
php -m
php-config --version
php-config --include-dir
php-config --libs
php-config --ldflags
php-config --extension-dir

export PHP_INI_FILE="/usr/local/etc/php/$PHP_VERSION/php.ini";
curl -o composer.phar https://getcomposer.org/composer-stable.phar && chmod +x composer.phar && sudo mv -f composer.phar /usr/local/bin/composer && composer -V;
