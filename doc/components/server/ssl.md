# SSL

本页介绍有关 HTTPS、WSS 的配置方法。

有两个方式，第一种是直接在 imi 服务器配置中设置，第二种是在 Nginx 层配置。

> 这边更加推荐在 Nginx 层设置

## 通过 imi 配置

项目 `config.php`：

```php
[
    // 主服务器配置
    'mainServer'    =>    [
        'namespace' =>  'ImiApp\WebSocketServer',
        'type'      =>  Imi\Server\Type::WEBSOCKET,
        'host'      =>  '127.0.0.1',
        'port'      =>  8082,
        'mode'      =>  SWOOLE_BASE,
        'sockType'  =>  SWOOLE_SOCK_TCP | SWOOLE_SSL, // SSL 需要设置一下 sockType
        'configs'   =>  [
            'worker_num'            =>  1,
            'task_worker_num'       =>  1,
            'task_enable_coroutine' =>  true,
            // 配置证书
            'ssl_cert_file'     =>  '/server.crt',
            'ssl_key_file'      =>  '/server.key',
        ],
    ],

    // 子服务器（端口监听）配置
    'subServers'        =>    [
        'ApiServer'     =>  [
            'namespace' =>  'ImiApp\ApiServer',
            'type'      =>  Imi\Server\Type::HTTP,
            'host'      =>  '127.0.0.1',
            'port'      =>  8080,
            'sockType'  =>  SWOOLE_SOCK_TCP | SWOOLE_SSL, // SSL 需要设置一下 sockType
            'configs'   =>  [
                // 配置证书
                'ssl_cert_file'     =>  '/server.crt',
                'ssl_key_file'      =>  '/server.key',
            ]
        ],
    ],
]
```

## 通过 Nginx 配置

### HTTPS

```conf
server {
    listen 443 ssl;
    server_name {域名};
    access_log  /var/log/nginx/{域名}.access.log  main;
    error_log  /var/log/nginx/{域名}.error.log  error;
    ssl_certificate      {证书}.pem;
    ssl_certificate_key  {证书}.key;

    location / {
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_pass http://127.0.0.1:8080; # imi 服务 HTTP 地址
    }
}
```

### WSS

```conf
server {
    listen 443 ssl;
    server_name {域名};
    access_log  /var/log/nginx/{域名}.access.log  main;
    error_log  /var/log/nginx/{域名}.error.log  error;
    ssl_certificate      {证书}.pem;
    ssl_certificate_key  {证书}.key;

    # websocket
    location / { # 全部
    # location ~* ^/ws/(.+) { # 指定路径
        proxy_http_version 1.1;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "upgrade";
        proxy_pass http://127.0.0.1:8082/$1?$args; # imi 服务 WebSocket 地址
    }
}
```
