package org.seckill.dao;

import org.apache.ibatis.annotations.Param;
import org.seckill.entity.Seckill;

import java.util.Date;
import java.util.List;
import java.util.Map;

public interface SeckillDao {
    /**
    *减库存
    * @param seckillId
    * @param killTime
    * @return 如果影响行数>Ⅰ，表示更新的记录行数
     */
    int reduceNumber(@Param("seckillId")long seckillId, @Param("killTime") Date killTime);

    /**
     *根据id查询秒杀对象
     * @param seckillId
     * @return
     */
    Seckill queryById(long seckillId);
    /**
     * 根据偏移量查询秒杀商品列表
     * @param offet
     * @param limit
     * @return
     */
    List<Seckill>queryAll(@Param("offset") int offet, @Param("limit") int limit);

    /**
     * @return void
     * 使用存储过程执行秒杀
     * @Date 17:23 2019/3/20
     * @Param [paramMap]
     **/

    void killByProcedure(Map<String, Object> paramMap);
}
