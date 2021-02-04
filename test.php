<?php

function test()
{
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_URL, 'https://httpbin.org/');
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_exec($curl);
    curl_close($curl);
}

Co\run('test');
Co\run('test');
