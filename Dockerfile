FROM phpswoole/swoole:4.5.2-php7.1

WORKDIR /opt/kafka-php

CMD ["./vendor/bin/phpunit", "--testsuite", "functional"]
