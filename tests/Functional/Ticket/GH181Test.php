<?php
declare(strict_types=1);

namespace KafkaTest\Functional\Ticket;

use Kafka\Exception\InvalidRecordInSet;
use Kafka\Producer;
use Kafka\ProducerConfig;
use KafkaTest\TestUtil;
use PHPUnit\Framework\TestCase;
use function getenv;

final class GH181Test extends TestCase
{
    public function setUp(): void
    {
        $version = getenv('KAFKA_VERSION') ?: '1.0.0';
        $brokers = getenv('KAFKA_BROKERS') ?: '127.0.0.1:9092';

        if (! $version || ! $brokers) {
            self::markTestSkipped(
                'Environment variables "KAFKA_VERSION" and "KAFKA_BROKERS" must be provided'
            );
        }

        $config = TestUtil::getProducerConfig();
        $config->setMetadataBrokerList($brokers);
        $config->setBrokerVersion($version);

        parent::setUp();
    }

    /**
     * @dataProvider dataProviderTestInvalidRecordSet
     * @group        181
     *
     * @param (string|int)[] $recordSet
     */
    public function testInvalidRecordSet(array $recordSet): void
    {
        $this->expectException(InvalidRecordInSet::class);

        $syncProcess = new Producer\SyncProcess(TestUtil::getProducerConfig(), new Producer\RecordValidator());

        $syncProcess->send([$recordSet]);
    }

    /**
     * @return (string|int)[][][]
     */
    public function dataProviderTestInvalidRecordSet(): array
    {
        return [
            'missing topic'                => [['value' => 'a value']],
            'missing topic – empty string' => [['topic' => '', 'value' => 'a value']],
            'invalid topic type'           => [['topic' => 1, 'value' => 'a value']],
            'missing value'                => [['topic' => 'test']],
            'invalid value type'           => [['topic' => 'test', 'value' => 1]],
            'missing value – empty string' => [['topic' => 'test', 'value' => '']],
            'non-existing topic'           => [
                [
                    'topic' => 'non-existing topic',
                    'value' => 'a value',
                ],
            ],
        ];
    }
}
