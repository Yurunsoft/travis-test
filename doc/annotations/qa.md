# 注解相关问题

本页列出注解相关常见问题，欢迎大家补充。

* **如何忽略一些我不想被扫描到的类？**

在项目配置文件中配置：

```php
return [
    // 忽略扫描的命名空间
    'ignoreNamespace'   =>  [
        'Imi\Test\Component\Annotation\A\*',    // 忽略扫描该命名空间下所有类
        'Imi\Test\Component\Annotation\B\TestB',// 忽略该类
    ],
]
```

* **怎样忽略扫描指定注解**

在项目的 `Main.php` 中写入：

```php
<?php
namespace ImiApp;

use Imi\Main\AppBaseMain;
use Yurun\Doctrine\Common\Annotations\AnnotationReader;

class Main extends AppBaseMain
{
    public function __init()
    {
        AnnotationReader::addGlobalIgnoredName('xxx');
    }

}
```
