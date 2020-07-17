<?php
$atomic = new \Swoole\Atomic(1);
var_dump($atomic->wait(3));