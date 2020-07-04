# 断线重连

使用 WebSocket、Http2、TCP 等长连接协议时，很多场景会需要断线重连功能。

我们使用一个标记（UID），来绑定连接。

断线重连就是连接断开后，该连接的上下文数据会继续保留，在一定时间内重连，就可以恢复上下文数据。

一般用于游戏重连、减少重连后的网络通信、减轻前端开发压力等场景。

> 断线重连视频介绍：<https://www.bilibili.com/video/BV1GC4y1s7yf>

## 配置说明

在服务器配置文件中的`beans`节下配置：

```php
[
    // 连接上下文存储器
    'ConnectContextStore'   =>  [
        'handlerClass'  =>  \Imi\Server\ConnectContext\StoreHandler\Redis::class,
        // 断开连接后，上下文数据保留时长，单位：秒
        'ttl'           =>  600,
    ],
    // 连接绑定器
    'ConnectionBinder'  =>  [
        // Redis 连接池名称
        'redisPool' =>  'redis',
        // redis中第几个库
        'redisDb'   =>  0,
        // 键，多个服务共用 redis 请设为不同的，不然会冲突
        'key'       =>  'imi:wsTest:connectionBinder:map',
    ],
]
```

## 使用说明

### 绑定连接

```php
use Imi\ConnectContext;
$memberId = 1; // 用户标识符

ConnectContext::bind($memberId);
```

### 绑定连接，如果已绑定返回false

```php
use Imi\ConnectContext;
$memberId = 1; // 用户标识符

ConnectContext::bindNx($memberId);
```

### 恢复连接数据

```php
use Imi\ConnectContext;
$memberId = 1; // 用户标识符

ConnectContext::restore($memberId);
```

### 取消绑定

```php
use Imi\ConnectContext;
$memberId = 1; // 用户标识符

ConnectContext::unbind($memberId);
```

### 使用标记（UID）获取连接编号

```php
use Imi\ConnectContext;
$memberId = 1; // 用户标识符

$fd = ConnectContext::getFdByFlag($memberId);
```

### 【批量】使用标记（UID）获取连接编号

```php
use Imi\ConnectContext;
$memberId = 1; // 用户标识符

$fds = ConnectContext::getFdsByFlags([$memberId]); // [1]
```

### 使用连接编号获取标记（UID）

```php
use Imi\ConnectContext;
$fd = 1; // 连接编号

$memberIds = ConnectContext::getFlagByFd($fd);
```

### 【批量】使用连接编号获取标记（UID）

```php
use Imi\ConnectContext;
$fd = 1; // 连接编号

$memberIds = ConnectContext::getFlagsByFds([$fd]); // [1]
```
