<?php
namespace Imi\Test\Component\Tests\Util;

use Imi\Test\BaseTest;

/**
 * @testdox Imi\Util\Args
 */
class ArgsTest extends BaseTest
{
    public function testArgs1()
    {
        $this->assertEquals(<<<ASSERT
array(0) {
}
bool(false)
bool(false)
bool(false)

ASSERT
, $this->php(dirname(__DIR__, 2) . '/Util/Args/a.php'));
    }

    public function testArgs2()
    {
        $this->assertEquals(<<<ASSERT
array(3) {
  ["a"]=>
  string(1) "1"
  ["b"]=>
  bool(true)
  ["c"]=>
  string(5) "iminb"
}
bool(true)
bool(true)
bool(true)

ASSERT
, $this->php(dirname(__DIR__, 2) . '/Util/Args/a.php', '-a 1 -b -c "iminb"'));
    }

    public function testArgs3()
    {
        $this->assertEquals(<<<ASSERT
array(0) {
}
bool(false)
bool(false)
bool(false)

ASSERT
, $this->php(dirname(__DIR__, 2) . '/Util/Args/b.php', 'abc'));
    }

    public function testArgs4()
    {
        $this->assertEquals(<<<ASSERT
array(3) {
  ["a"]=>
  string(1) "1"
  ["b"]=>
  bool(true)
  ["c"]=>
  string(5) "iminb"
}
bool(true)
bool(true)
bool(true)

ASSERT
, $this->php(dirname(__DIR__, 2) . '/Util/Args/b.php', 'abc -a 1 -b -c "iminb"'));
    }

    public function testArgs5()
    {
        $this->assertEquals(<<<ASSERT
array(3) {
  ["a"]=>
  string(1) "1"
  ["b"]=>
  bool(true)
  ["c"]=>
  string(5) "iminb"
}
NULL
bool(false)
array(4) {
  ["a"]=>
  string(1) "1"
  ["b"]=>
  bool(true)
  ["c"]=>
  string(5) "iminb"
  ["null"]=>
  string(8) "not null"
}
string(8) "not null"
bool(true)

ASSERT
        , $this->php(dirname(__DIR__, 2) . '/Util/Args/c.php', 'abc -a 1 -b -c "iminb"'));
    }
}
