<?php
$serv = new Swoole\Server('0.0.0.0', 9502, SWOOLE_PROCESS, SWOOLE_SOCK_UDP); 

//监听数据接收事件
$serv->on('Packet', function ($serv, $data, $clientInfo) {
	go(function() use($serv, $clientInfo, $data){
		// for($i = 0; $i < 10; ++$i)
		// {
		// 	$serv->sendto($clientInfo['address'], $clientInfo['port'], "Server ".$data . ':' . $i);
		// 	\Swoole\Coroutine::sleep(1);
		// }
		$serv->sendto($clientInfo['address'], $clientInfo['port'], $data);
	});
});

//启动服务器
$serv->start(); 