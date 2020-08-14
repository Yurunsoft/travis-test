@echo off

vcredist_url="https://download.microsoft.com/download/9/3/F/93FCF1E7-E6A4-478B-96E7-D4B285925B00/vc_redist.x64.exe"

php_url="https://windows.php.net/downloads/releases/php-7.4.9-nts-Win32-vc15-x64.zip"

php_dev_url="https://windows.php.net/downloads/releases/php-devel-pack-7.4.9-nts-Win32-vc15-x64.zip"

Invoke-Webrequest $env:vcredist_url -Outfile "vcredist.exe"

Invoke-Webrequest $env:php_url -Outfile "php.zip"

Invoke-Webrequest $env:php_dev_url -Outfile "php_dev.zip"

.\vcredist.exe /Q

Expand-Archive "php.zip" "C:\php"

Expand-Archive "php_dev.zip" "C:\"

set PHP_DEV_PATH=C:\php-7.4.9-devel-vc15-x64

del /F /Q vcredist.exe php.zip php_dev.zip

(gc C:\php\php.ini-development) -replace ';extension_dir = "ext"', ';extension_dir = ""C\php\ext""' | Out-File C:\php\php.ini

(gc C:\php\php.ini) -replace ';extension=ffi', 'extension=ffi' | Out-File C:\php\php.ini

(gc C:\php\php.ini) -replace ';extension=curl', 'extension=curl' | Out-File C:\php\php.ini

(gc C:\php\php.ini) -replace ';extension=mb_string', 'extension=mb_string' | Out-File C:\php\php.ini

(gc C:\php\php.ini) -replace ';extension=openssl', 'extension=openssl' | Out-File C:\php\php.ini

set PATH=%PATH%;C:\PHP

php -v
php -m

php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"
php composer-setup.php --install-dir=C:\php
php -r "unlink('composer-setup.php');"
php -r "file_put_contents('C:\php\composer.bat', '@echo off php C:\php\composer.phar')"

composer -V

Invoke-Webrequest "https://phar.phpunit.de/phpunit-9.phar" -Outfile "C:\php\phpunit.phar"

php -r "file_put_contents('C:\php\phpunit.bat', '@echo off php C:\php\phpunit.phar')"

phpunit --version
