package org.seckill.exception;

/**
 * @ClassName SeckillCloseException
 * 秒杀关闭异常
 * @Date 2019/3/1722:34
 **/
public class SeckillCloseException extends SeckillException{

    public SeckillCloseException(String message) {
        super(message);
    }

    public SeckillCloseException(String message, Throwable cause) {
        super(message, cause);
    }
}
