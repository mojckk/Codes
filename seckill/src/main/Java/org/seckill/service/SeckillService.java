package org.seckill.service;

import org.seckill.dto.Exposer;
import org.seckill.dto.SeckillExecution;
import org.seckill.entity.Seckill;
import org.seckill.exception.ReapeatKillException;
import org.seckill.exception.SeckillCloseException;
import org.seckill.exception.SeckillException;

import java.util.List;

/**
 *业务接口：站在使用者角度设计接口
 * 三个方面：方法定义粒度，参数，返回类型（return类型/异常）
 **/

public interface SeckillService {
    /**
     * 查询所有秒杀记录
     * @return
     **/
    List<Seckill> getSeckillList();
    /**
     * 查询单个秒杀记录
     * @Date 22:11 2019/3/17
     * @Param [seckillId]
     * @return org.seckill.entity.Seckill
     **/
    Seckill getById(long seckillId);
    /**
     * 秒杀开启是输出秒杀接口地址，
     * 否则输出系统时间和秒杀时间
     *
     * @Date 22:13 2019/3/17
     * @Param [seckillId]
     * @return void
     **/
    
    Exposer exportSeckillUrl(long seckillId);
    /**
     * 执行秒杀操作by存储过程
     * @Date 22:24 2019/3/17
     * @Param [seckillId, userPhone, md5]
     * @return void
     **/

    SeckillExecution executeSeckillProcedure(long seckillId, long userPhone, String md5);
    /**
     * 执行秒杀操作
     * @Date 20:43 2019/3/20
     * @Param
     * @return
     **/

    SeckillExecution executeSeckill(long seckillId,long userPhone,String md5);
}
