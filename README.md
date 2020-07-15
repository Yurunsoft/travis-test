# yurun-crawler

[![Latest Version](https://img.shields.io/packagist/v/yurunsoft/php-crawler.svg)](https://packagist.org/packages/yurunsoft/php-crawler)
[![Travis](https://img.shields.io/travis/Yurunsoft/php-crawler.svg)](https://travis-ci.org/Yurunsoft/php-crawler)
[![Php Version](https://img.shields.io/badge/php-%3E=7.1-brightgreen.svg)](https://secure.php.net/)
[![Swoole Version](https://img.shields.io/badge/swoole-%3E=4.3.0-brightgreen.svg)](https://github.com/swoole/swoole-src)
[![imi Doc](https://img.shields.io/badge/docs-passing-green.svg)](https://doc.imiphp.com)
[![imi License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/Yurunsoft/php-crawler/blob/master/LICENSE)

## 介绍

宇润爬虫框架(Yurun Crawler) 是一个低代码、高性能、分布式爬虫采集框架，基于 imi 框架开发，运行在 Swoole 常驻内存的协程环境。

为什么会开发这个框架？最近有爬虫需求，调研了一些市面上现有的 PHP 爬虫框架功能都十分简陋，需要编写的重复代码极多。

Yurun Crawler 的目标是能够用最少的代码，方便快速地实现爬虫采集功能。

Yurun Crawler 的愿景是成为宇宙第一爬虫框架，以后提到爬虫就想到 Yurun Crawler 可以一把梭实现！

## 功能特性

* 低代码，几乎不需要编写代码，大部分逻辑依靠注解实现
* 高性能，基于 [imi](https://www.imiphp.com/) + [Swoole](https://www.swoole.com/) 常驻内存及协程实现
* 分布式，采集的流程由消息队列推动，依靠 Redis 等中间件实现纯天然的分布式特性
* 支持下载器并发限流
* 内置解析能力强，支持：Dom 解析、正则、JSON
* 代理 IP 池，支持：MySQL、Redis
* 支持定时采集
* 支持模型存储
* 易扩展

## 概念

### 采集项目

有时候，我们会先采集列表页，再采集内容页

列表页、内容页，都是采集项目，他们的下载、解析、处理逻辑可能都不相同

### 下载器

负责请求网址，下载并存储内容。

多协程的架构下，支持同时下载海量数据。

支持限流。

### 数据模型

定义需要从页面中，提取的内容属性。

### 解析器

负责解析下载后的内容，从中提取需要的信息，返回数据模型。

首个版本支持：Dom 解析、正则、JSON。

### 处理器

解析器解析出数据模型后，交由处理器进行处理。

### 存储器

负责将解析后的数据存储入库，支持多种存储方式，并且可以自由扩展。

### 代理 IP 池

实现代理 IP 池抽象，开发者可以很方便地对接不同接口方。
