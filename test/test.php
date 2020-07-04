<?php

/**
 * Encode in Base32 based on RFC 4648.
 * Requires 20% more space than base64
 * Great for case-insensitive filesystems like Windows and URL's  (except for = char which can be excluded using the pad option for urls)
 *
 * @author Bryan Ruiz
 */
class Base36
{
    /**
     * @var array
     */
    protected $map = array(
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', //  7
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', // 15
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x', // 23
        'y', 'z', '2', '3', '4', '5', '6', '7', // 31
        '0'  // padding char
    );

    /**
     * @var array
     */
    protected $flippedMap = array(
        'a' => '0', 'b' => '1', 'c' => '2', 'd' => '3', 'e' => '4', 'f' => '5', 'g' => '6', 'h' => '7',
        'i' => '8', 'j' => '9', 'k' => '10', 'l' => '11', 'm' => '12', 'n' => '13', 'o' => '14', 'p' => '15',
        'q' => '16', 'r' => '17', 's' => '18', 't' => '19', 'u' => '20', 'v' => '21', 'w' => '22', 'x' => '23',
        'y' => '24', 'z' => '25', '2' => '26', '3' => '27', '4' => '28', '5' => '29', '6' => '30', '7' => '31'
    );

    /**
     * Encodes data with base36.
     *
     * @param string $input The original data, as a string.
     * @param bool $padding Use padding false when encoding for urls
     * @return string Base36 encoded string
     */
    public function encode($input, $padding = true)
    {
        if (empty($input)) {
            return "";
        }
        $input = str_split($input);
        $binaryString = "";
        $inputCount = count($input);
        for ($i = 0; $i < $inputCount; $i++) {
            $binaryString .= str_pad(base_convert(ord($input[$i]), 10, 2), 8, '0', STR_PAD_LEFT);
        }
        $fiveBitBinaryArray = str_split($binaryString, 5);
        $base32 = "";
        $i = 0;
        $fiveCount = count($fiveBitBinaryArray);
        while ($i < $fiveCount) {
            $base32 .= $this->map[base_convert(str_pad($fiveBitBinaryArray[$i], 5, '0'), 2, 10)];
            $i++;
        }
        if ($padding && ($x = strlen($binaryString) % 40) != 0) {
            if ($x == 8) {
                $base32 .= str_repeat($this->map[32], 6);
            } else {
                if ($x == 16) {
                    $base32 .= str_repeat($this->map[32], 4);
                } else {
                    if ($x == 24) {
                        $base32 .= str_repeat($this->map[32], 3);
                    } else {
                        if ($x == 32) {
                            $base32 .= $this->map[32];
                        }
                    }
                }
            }
        }
        return $base32;
    }

    /**
     * Decodes data encoded with base36.
     *
     * @param string $input The encoded data.
     * @return bool|string the original data or false on failure.
     */
    public function decode($input)
    {
        if (empty($input)) {
            return false;
        }
        $paddingCharCount = substr_count($input, $this->map[32]);
        $allowedValues = array(6, 4, 3, 1, 0);
        if (!in_array($paddingCharCount, $allowedValues)) {
            return false;
        }
        for ($i = 0; $i < 4; $i++) {
            if ($paddingCharCount == $allowedValues[$i] &&
                substr($input, -($allowedValues[$i])) != str_repeat($this->map[32], $allowedValues[$i])
            ) {
                return false;
            }
        }
        $input = str_replace('0', '', $input);
        $input = str_split($input);
        $binaryString = "";
        $count = count($input);
        for ($i = 0; $i < $count; $i = $i + 8) {
            $x = "";
            if (!in_array($input[$i], $this->map)) {
                return false;
            }
            for ($j = 0; $j < 8; $j++) {
                if (!isset($input[$i + $j])) {
                    continue;
                }
                $x .= str_pad(base_convert($this->flippedMap[$input[$i + $j]], 10, 2), 5, '0', STR_PAD_LEFT);
            }
            $eightBits = str_split($x, 8);
            $bitCount = count($eightBits);
            for ($z = 0; $z < $bitCount; $z++) {
                $binaryString .= (($y = chr(base_convert($eightBits[$z], 2, 10))) || ord($y) == 48) ? $y : "";
            }
        }
        // Converting a binary (\0 terminated) string to a PHP string
        $result = rtrim($binaryString, "\0");
        return $result;
    }
}

$base36 = new Base36;
$a = $base36->encode('宇润真帅啊');
var_dump($a);
$b = $base36->decode($a);
var_dump($b);

$key = 'abc';
$a = $base36->encode(openssl_encrypt('宇润真帅啊', 'AES-128-CBC', $key, 0, \str_repeat(chr(0), openssl_cipher_iv_length('AES-128-CBC'))));
var_dump($a);

$b = openssl_decrypt($base36->decode($a), 'AES-128-CBC', $key, 0, \str_repeat(chr(0), openssl_cipher_iv_length('AES-128-CBC')));
var_dump($b);
