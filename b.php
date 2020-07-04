<?php

use Swoole\Event;
use Swoole\Timer;
use Swoole\Runtime;
use Swoole\Coroutine;
use Swoole\Coroutine\Channel;

class Test
{
    public static $a;
}

class A
{
    /**
     * 队列
     * @var \Swoole\Coroutine\Channel
     */
    protected $queue;

    public function __construct()
    {
    }

    public function init()
    {
        $this->queue = new Channel(100);
    }

    public function __destruct()
    {
        var_dump($this->queue, Coroutine::getuid());
        var_dump($this->queue->close());
    }

    public function test()
    {
        $this->queue->push(1);
    }
}

$statusCode = 0;
go(function() use(&$statusCode){
    go(function() use(&$statusCode){
        Runtime::enableCoroutine();
        fopen(__FILE__, 'r');
        fopen(__FILE__, 'r');
        fopen(__FILE__, 'r');
        fopen(__FILE__, 'r');
        fopen(__FILE__, 'r');
        Test::$a = new A;
        Test::$a->init();
        var_dump(Coroutine::stats());
        Event::exit();
    });
});
Event::wait();

exit($statusCode);