<?php
$atomic = new \Swoole\Atomic(1);
var_dump($atomic->wakeup(), $atomic->get());

$atomic = new \Swoole\Atomic(0);
var_dump($atomic->wakeup(), $atomic->get());

$atomic = new \Swoole\Atomic(0);
var_dump($atomic->wait(1), $atomic->get());

$atomic = new \Swoole\Atomic(1);
var_dump($atomic->wait(1), $atomic->get());
