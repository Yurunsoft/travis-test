<?php

use Swoole\Coroutine;
use Swoole\Timer;

class SplPriorityAscQueue extends SplPriorityQueue
{
    public function compare($priority1, $priority2)
    {
        if ($priority1 === $priority2) return 0;
        return $priority1 < $priority2 ? 1 : -1;
    }
}

$q = new \SplPriorityAscQueue;
$a = 0;
go(function() use($q){
    while(true)
    {
        $time = time() + 1;
        for($i = 0; $i < 1000000; ++$i)
        {
            $q->insert([
                'value' =>  $i,
                'p'     =>  $time,
            ], $time);
        }
        Coroutine::sleep(1);
    }
});
go(function() use($q, &$a){
    while(true)
    {
        $time = time();
        foreach($q as $v)
        {
            // var_dump(sprintf('k=%s, v=%s', $k, $v));
            // var_dump($time, $v['p']);
            if($time < $v['p'])
            {
                $q->insert($v, $v['p']);
                break;
            }
            ++$a;
        }

        Coroutine::sleep(1);
    }
});
Timer::tick(1000, function() use(&$a){
    var_dump($a);
});

return;
//创建websocket服务器对象，监听0.0.0.0:9502端口
$ws = new Swoole\WebSocket\Server("0.0.0.0", 9502);

//监听WebSocket连接打开事件
$ws->on('open', function ($ws, $request) {
    var_dump($request->fd, $request->get, $request->server);
    $ws->push($request->fd, "hello, welcome\n");
});

//监听WebSocket消息事件
$ws->on('message', function ($ws, $frame) {
    echo "Message: {$frame->data}\n";
    $ws->push($frame->fd, "server: {$frame->data}");
});

//监听WebSocket连接关闭事件
$ws->on('close', function ($ws, $fd) {
    echo "client-{$fd} is closed\n";
});

$ws->on('request', function(swoole_http_request $request, swoole_http_response $response) {
    $response->end("<h1>hello swoole</h1>");
});

$ws->start();