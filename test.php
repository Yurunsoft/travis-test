<?php
$atomic = new \Swoole\Atomic(1);
var_dump($atomic->get(), $atomic->wait(3), $atomic->get());