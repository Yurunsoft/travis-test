<?php
declare(strict_types=1);

namespace KafkaTest\Base\Consumer;

use Kafka\Consumer\State;
use KafkaTest\TestUtil;
use PHPUnit\Framework\TestCase;

final class StateTest extends TestCase
{
    /**
     * @test
     */
    public function stopShouldNotBreakWhenNoWatchersExist(): void
    {
        $state = new State(TestUtil::getConsumerConfig());
        $state->init();
        $state->stop();

        self::assertAttributeSame([], 'callStatus', $state);
    }
}
