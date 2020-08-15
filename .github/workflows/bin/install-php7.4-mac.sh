#!/bin/bash
PHP_VERSION="7.4"
brew install php@$PHP_VERSION;
brew link --force --overwrite php@7.4

php -v
php -m
php-config

echo $(brew --prefix)/opt/php/lib/

echo "a:"
ls $(brew --prefix)/opt/php/lib/

echo "b:"
ls $(brew --prefix)/opt/php/lib/php/

echo "c:"
ls $(brew --prefix)/opt/php/lib/httpd/

curl -o composer.phar https://getcomposer.org/composer-stable.phar && chmod +x composer.phar && sudo mv -f composer.phar /usr/local/bin/composer && composer -V;
