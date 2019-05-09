package org.seckill.exception;

/**
 * @ClassName SeckillException
 * 秒杀相关业务异常
 * @Date 2019/3/1722:35
 **/
public class SeckillException extends RuntimeException{

    public SeckillException(String message) {
        super(message);
    }

    public SeckillException(String message, Throwable cause) {
        super(message, cause);
    }
}
