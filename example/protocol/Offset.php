<?php
declare(strict_types=1);

require dirname(__DIR__, 2) . '/vendor/autoload.php';

use Kafka\Protocol;
use Kafka\Socket;

$data = [
    'replica_id' => -1,
    'data' => [
        [
            'topic_name' => 'test',
            'partitions' => [
                [
                    'partition_id' => 1,
                    'offset' => 12,
                    'time' => -2,
                ],
            ],
        ],
    ],
];

Protocol::init('1.0.0');
$requestData = Protocol::encode(Protocol::OFFSET_REQUEST, $data);

$socket = new Socket('127.0.0.1', 9092);
$socket->setOnReadable(function ($data): void {
    $coodid = \Kafka\Protocol\Protocol::unpack(\Kafka\Protocol\Protocol::BIT_B32, substr($data, 0, 4));
    $result = Protocol::decode(Protocol::OFFSET_REQUEST, substr($data, 4));
    echo json_encode($result);
    \Amp\Loop::stop();
});

$socket->connect();
$socket->write($requestData);
\Amp\Loop::run(function () use ($socket, $requestData): void {
});
