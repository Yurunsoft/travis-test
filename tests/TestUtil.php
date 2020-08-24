<?php
namespace KafkaTest;

use Kafka\ConsumerConfig;
use Kafka\ProducerConfig;
use Kafka\Protocol\Protocol;

abstract class TestUtil
{
    /**
     * @var \Kafka\ProducerConfig
     */
    private static $producerConfig;

    /**
     * @var \Kafka\ConsumerConfig
     */
    private static $consumerConfig;

    public static function getProducerConfig(): ProducerConfig
    {
        if(static::$producerConfig)
        {
            return static::$producerConfig;
        }
        return static::$producerConfig = new ProducerConfig;
    }

    public static function getConsumerConfig(): ConsumerConfig
    {
        if(static::$consumerConfig)
        {
            return static::$consumerConfig;
        }
        return static::$consumerConfig = new ConsumerConfig;
    }

}
