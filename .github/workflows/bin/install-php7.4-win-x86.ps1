$vcredist_url="https://aka.ms/vs/16/release/vc_redist.x86.exe"

$php_url="https://windows.php.net/downloads/releases/php-7.4.9-nts-Win32-vc15-x86.zip"

$php_dev_url="https://windows.php.net/downloads/releases/php-devel-pack-7.4.9-nts-Win32-vc15-x86.zip"

$cacert_pem_url="https://curl.haxx.se/ca/cacert.pem"

Invoke-Webrequest $vcredist_url -Outfile "vcredist.exe"

Invoke-Webrequest $php_url -Outfile "php.zip"

Invoke-Webrequest $php_dev_url -Outfile "php_dev.zip"

Invoke-Webrequest $cacert_pem_url -Outfile "C:\cacert.pem"

.\vcredist.exe /Q

Expand-Archive "php.zip" "C:\php"

Expand-Archive "php_dev.zip" "C:\"

[environment]::SetEnvironmentvariable("PHP_DEV_PATH", "C:\php-7.4.9-devel-vc15-x64", "Machine")

(gc C:\php\php.ini-development) -replace ';extension_dir = "ext"', 'extension_dir = "C:\php\ext"' | Out-File C:\php\php.ini -encoding Utf8

(gc C:\php\php.ini) -replace ';extension=ffi', 'extension=ffi' | Out-File C:\php\php.ini -encoding Utf8

(gc C:\php\php.ini) -replace ';extension=curl', 'extension=curl' | Out-File C:\php\php.ini -encoding Utf8

(gc C:\php\php.ini) -replace ';extension=mb_string', 'extension=mb_string' | Out-File C:\php\php.ini -encoding Utf8

(gc C:\php\php.ini) -replace ';extension=openssl', 'extension=openssl' | Out-File C:\php\php.ini -encoding Utf8

(gc C:\php\php.ini) -replace ';curl.cainfo =', 'curl.cainfo = "C:\cacert.pem"' | Out-File C:\php\php.ini -encoding Utf8

(gc C:\php\php.ini) -replace ';openssl.cafile=', 'openssl.cafile="C:\cacert.pem"' | Out-File C:\php\php.ini -encoding Utf8

[environment]::SetEnvironmentvariable("PATH", [environment]::GetEnvironmentvariable("PATH") + ";C:\php", "Machine")

php -v
php -m

php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"
php composer-setup.php --install-dir=C:\php
php -r "unlink('composer-setup.php');"
php -r "file_put_contents('C:\php\composer.bat', 'php C:\php\composer.phar %1');"

composer -V

Invoke-Webrequest "https://phar.phpunit.de/phpunit-9.phar" -Outfile "C:\php\phpunit.phar"

php -r "file_put_contents('C:\php\phpunit.bat', 'php C:\php\phpunit.phar %1');"

php C:\php\phpunit.phar --version

C:\php\phpunit.bat --version

phpunit --version
