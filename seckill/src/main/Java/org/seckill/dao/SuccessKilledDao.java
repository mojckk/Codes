package org.seckill.dao;

import org.apache.ibatis.annotations.Param;
import org.seckill.entity.SuccessKilled;

/**
 * @ClassName SuccessKilledDao
 **/
public interface SuccessKilledDao {
    /**
     * @Date 12:01 2019/3/13
     * @Param [seckillId, userPhone]
     * @return int
     * 插入的行数
     **/

    int insertSuccessKilled(@Param("seckillId") long seckillId, @Param("userPhone")long userPhone);
    /**
     * 根据id查询SuccessKilled 并携带秒杀产品对象实体
     * @Date 13:09 2019/3/13
     * @Param [seckillId]
     * @return org.seckill.entity.SuccessKilled
     **/

    SuccessKilled queryByIdWithSeckill(@Param("seckillId")long seckillId,@Param("userPhone")long userPhone);
}
