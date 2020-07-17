<?php
$atomic = new \Swoole\Atomic(1);
var_dump($atomic->get(), $atomic->wakeup(), $atomic->get());

$atomic = new \Swoole\Atomic(0);
var_dump($atomic->get(), $atomic->wakeup(), $atomic->get());

$atomic = new \Swoole\Atomic(0);
var_dump($atomic->wait(3), $atomic->get());

$atomic = new \Swoole\Atomic(1);
var_dump($atomic->wait(3), $atomic->get());
