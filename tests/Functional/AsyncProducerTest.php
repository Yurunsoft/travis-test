<?php
declare(strict_types=1);

namespace KafkaTest\Functional;

use Kafka\Producer;
use Kafka\ProducerConfig;
use Kafka\Protocol;
use KafkaTest\TestUtil;

final class AsyncProducerTest extends ProducerTest
{
    /**
     * @test
     *
     * @runInSeparateProcess
     */
    public function sendAsyncMessages(): void
    {
        $this->configureProducer();

        $messagesSent = false;
        $error        = null;

        $producer = new Producer(TestUtil::getProducerConfig(), [$this, 'createMessages']);
        $producer->success(
            function (array $response) use (&$messagesSent): void {
                self::assertNotEmpty($response);

                foreach ($response['data'][0]['partitions'] as $partition) {
                    self::assertSame(0, $partition['errorCode']);
                }

                $messagesSent = true;
            }
        );
        $producer->error(
            function (int $errorCode) use (&$error): void {
                $error = $errorCode;
            }
        );
        $producer->send();

        self::assertTrue(
            $messagesSent,
            'It was not possible to send the messages, reason: ' . Protocol::getError((int) $error)
        );
    }
}
