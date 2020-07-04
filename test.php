<?php

use Swoole\Coroutine;
use Swoole\Runtime;

Runtime::enableCoroutine();

// timeout not work
// Coroutine::set([
//     'socket_connect_timeout'    => 3,
//     'socket_read_timeout'       => 3,
//     'socket_write_timeout'      => 3,
//     'socket_dns_timeout'        => 3,
//     'socket_timeout'            => 3,
// ]);

Co\run(function(){
    var_dump(time() . ':' . count(Coroutine::exec('exec php -i')));
});