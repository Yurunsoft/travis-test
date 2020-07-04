<?php
go(function(){
    $client = new Swoole\Coroutine\Client(SWOOLE_SOCK_UDP);
    $client->sendto('45.117.102.111', 9502, 'test');
    while(true)
    {
        var_dump($client->recv());
    }
});