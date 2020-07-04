# 跨域和 OPTIONS 请求

imi 框架内置了一个 `OptionsMiddleware` 中间件，用于解决使用 `application/json` 请求时，浏览器会先发送一个 `OPTIONS` 请求。并且可以解决跨域头问题。

类名：`\Imi\Server\Http\Middleware\OptionsMiddleware`

别名：`OptionsMiddleware`

中间件使用方法：<https://doc.imiphp.com/components/httpserver/middleware.html>

## 参数设置

一般来讲，默认的配置足以满足绝大部分场景。

如果有特殊需求，你可以在服务器配置中的 `beans.OptionsMiddleware` 中配置该中间件的参数。

下面给出的是默认参数值：

```php
[
    'beans' =>  [
        'OptionsMiddleware' =>  [
            // 设置允许的 Origin，为 null 时允许所有，为数组时允许多个
            'allowOrigin'       =>  null,
            // 允许的请求头
            'allowHeaders'      =>  'Authorization, Content-Type, Accept, Origin, If-Match, If-Modified-Since, If-None-Match, If-Unmodified-Since, X-Requested-With, X-Id, X-Token, Cookie',
            // 允许的跨域请求头
            'exposeHeaders'     =>  'Authorization, Content-Type, Accept, Origin, If-Match, If-Modified-Since, If-None-Match, If-Unmodified-Since, X-Requested-With, X-Id, X-Token, Cookie',
            // 允许的请求方法
            'allowMethods'      =>  'GET, POST, PATCH, PUT, DELETE',
            // 是否允许跨域 Cookie
            'allowCredentials'  =>  'true',
            // 当请求为 OPTIONS 时，是否中止后续中间件和路由逻辑，一般建议设为 true
            'optionsBreak'      =>  true,
        ],
    ],
]
```
