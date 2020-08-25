<?php
namespace KafkaTest;

use Kafka\ConsumerConfig;
use Kafka\ProducerConfig;

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
        if(null !== static::$producerConfig)
        {
            return static::$producerConfig;
        }
        return static::$producerConfig = new ProducerConfig;
    }

    public static function getConsumerConfig(): ConsumerConfig
    {
        if(null !== static::$consumerConfig)
        {
            return static::$consumerConfig;
        }
        return static::$consumerConfig = new ConsumerConfig;
    }

}
