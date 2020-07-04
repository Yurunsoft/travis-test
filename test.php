<?php

use Swoole\Coroutine;
use Swoole\Timer;


// $data = unserialize('a:18:{i:0;a:2:{s:4:"name";s:8:"item_fee";s:5:"value";s:3:"5.8";}i:1;a:2:{s:4:"name";s:8:"base_fee";s:5:"value";s:3:"3.4";}i:2;a:2:{s:4:"name";s:8:"step_fee";s:5:"value";s:3:"1.3";}i:3;a:2:{s:4:"name";s:14:"size_first_fee";s:5:"value";s:4:"23.2";}i:4;a:2:{s:4:"name";s:13:"size_item_fee";s:5:"value";s:5:"119.5";}i:5;a:2:{s:4:"name";s:16:"size_free_weight";s:5:"value";s:1:"0";}i:6;a:2:{s:4:"name";s:16:"weight_first_fee";s:5:"value";s:4:"23.2";}i:7;a:2:{s:4:"name";s:15:"weight_item_fee";s:5:"value";s:5:"119.5";}i:8;a:2:{s:4:"name";s:18:"weight_free_weight";s:5:"value";s:1:"0";}i:9;a:2:{s:4:"name";s:10:"free_money";s:5:"value";s:5:"10000";}i:10;a:2:{s:4:"name";s:16:"fee_compute_mode";s:5:"value";s:0:"";}i:11;a:2:{s:4:"name";s:11:"free_weight";s:5:"value";s:1:"0";}i:12;a:2:{s:4:"name";s:14:"size_first_fee";s:5:"value";s:4:"23.2";}i:13;a:2:{s:4:"name";s:13:"size_item_fee";s:5:"value";s:5:"119.5";}i:14;a:2:{s:4:"name";s:16:"size_free_weight";s:5:"value";s:1:"0";}i:15;a:2:{s:4:"name";s:16:"weight_first_fee";s:5:"value";s:4:"23.2";}i:16;a:2:{s:4:"name";s:15:"weight_item_fee";s:5:"value";s:5:"119.5";}i:17;a:2:{s:4:"name";s:18:"weight_free_weight";s:5:"value";s:1:"0";}}');
$data = unserialize('a:12:{i:0;a:2:{s:4:"name";s:8:"item_fee";s:5:"value";s:3:"5.8";}i:1;a:2:{s:4:"name";s:8:"base_fee";s:5:"value";s:3:"3.4";}i:2;a:2:{s:4:"name";s:8:"step_fee";s:5:"value";s:3:"1.3";}i:3;a:2:{s:4:"name";s:14:"size_first_fee";s:5:"value";s:4:"23.2";}i:4;a:2:{s:4:"name";s:13:"size_item_fee";s:5:"value";s:5:"119.5";}i:5;a:2:{s:4:"name";s:16:"size_free_weight";s:5:"value";s:1:"0";}i:6;a:2:{s:4:"name";s:16:"weight_first_fee";s:5:"value";s:4:"23.2";}i:7;a:2:{s:4:"name";s:15:"weight_item_fee";s:5:"value";s:5:"119.5";}i:8;a:2:{s:4:"name";s:18:"weight_free_weight";s:5:"value";s:1:"0";}i:9;a:2:{s:4:"name";s:10:"free_money";s:5:"value";s:5:"10000";}i:10;a:2:{s:4:"name";s:16:"fee_compute_mode";s:5:"value";s:0:"";}i:11;a:2:{s:4:"name";s:11:"free_weight";s:5:"value";s:1:"0";}}');
var_dump($data);exit;
for($i = 12; $i <= 17; ++$i)
{
    unset($data[$i]);
}
var_dump($data);
var_dump(serialize($data));
exit;
var_dump(PHP_BINARY );exit;

class A
{
    public static $test;

    public static function test1()
    {
        $time = microtime(true);
        for($i = 0; $i < 100000; ++$i)
        {
            static::$test = [];
            static::set([]);
        }
        var_dump(microtime(true) - $time);
    }

    public static function test2()
    {
        $time = microtime(true);
        for($i = 0; $i < 100000; ++$i)
        {
            static::set(static::$test = []);
        }
        var_dump(microtime(true) - $time);
    }

    public static function set()
    {

    }
}
A::test1();
A::test2();
exit;

$a = 0;
for($i = 0; $i < 1000000; ++$i)
{
    Timer::tick(1000, function() use(&$a){
        ++$a;
    });
}
Timer::tick(1000, function() use(&$a){
    var_dump($a);
});
return;
var_dump(strtotime('2079-06-21 12:34:56'));
exit;
var_dump(base64_encode(1));
var_dump(base64_encode(65535));

$str1 = '003C-0014-0001-01-14-01-01-00000002';

$str2 = 60;
var_dump(base64_encode($str2));

$str = 'E4gD6AKNAh4OEAACCigACwHoCqwABQqgAAk=';

$result = '';
for($i = 0; $i < strlen($str); ++$i)
{
    $result .= chr(base_convert($str[$i], 16, 10));
}

var_dump($result, base64_encode($result), '138803E8028D021E0E1000020A28000B01E80AAC00050AA00009');

$a = base64_decode('E4gD6AKNAh4OEAACCigACwHoCqwABQqgAAk=');

$str = '138803E8028D021E0E1000020A28000B01E80AAC00050AA00009';
for($i = 0; $i < strlen($str); ++$i)
{

}
