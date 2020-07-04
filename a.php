<?php

use Swoole\Event;
use Swoole\Runtime;
Runtime::enableCoroutine();

go(function(){
    file_get_contents(__FILE__);
});
Event::wait();
Runtime::enableCoroutine(false);


register_shutdown_function(function(){
    echo 'Shutdown memory:', PHP_EOL, `free -m`, PHP_EOL;
});

$descriptorspec = [
    ['pipe', 'r'],  // 标准输入，子进程从此管道中读取数据
    ['pipe', 'w'],  // 标准输出，子进程向此管道中写入数据
];
$cmd = 'php ' . __DIR__ . '/b.php';
$pipes = null;
$processHndler = proc_open($cmd, $descriptorspec, $pipes);
$records2 = [];
while(!feof($pipes[1]))
{
    $content = fgets($pipes[1]);
    if(false !== $content)
    {
        if(2 === count($records2))
        {
            array_shift($records2);
        }
        $records2[] = $content;
        echo $content;
    }
}

do {
    $status = proc_get_status($processHndler);
} while($status['running'] ?? false);
foreach($pipes as $pipe)
{
    fclose($pipe);
}
proc_close($processHndler);

var_dump($status, $records2);