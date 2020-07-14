<?php
namespace Imi\Test\HttpServer\Cron;

use Imi\Cron\Annotation\Cron;
use Imi\Cron\Contract\ICronTask;

/**
 * @Cron(id="CronInCronProcess", second="3n", type="cron_process")
 */
class CronInCronProcess implements ICronTask
{
    /**
     * 执行任务
     *
     * @param string $id
     * @param mixed $data
     * @return void
     */
    public function run(string $id, $data)
    {
        var_dump('cron_process');
    }

}
