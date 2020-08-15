<?php
if(!extension_loaded('FFI'))
{
    throw new \RuntimeException('If you want to use FFI mode, you must use PHP>=7.4 and enable FFI extension');
}

function getLibExt()
{
    switch(PHP_OS)
    {
        case 'Darwin':
            return 'dylib';
        case 'Windows':
            return 'dll';
        default:
            return 'so';
    }
}

$ffi = FFI::cdef(<<<HEADER
void init_chinese_util();
HEADER, dirname(__DIR__) . '/build/libchinese_util.' . getLibExt());
$ffi->init_chinese_util();
$dataPath = dirname(__DIR__) . '/data';
init_chinese_dict($dataPath . '/charsData.json', $dataPath . '/pinyinData.json');
