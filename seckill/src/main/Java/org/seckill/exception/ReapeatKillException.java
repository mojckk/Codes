package org.seckill.exception;

/**
 * @ClassName ReapeatKillException
 * 重复秒杀异常（运行期异常）
 * @Date 2019/3/1722:32
 **/
public class ReapeatKillException extends SeckillException{

    public ReapeatKillException(String message) {
        super(message);
    }

    public ReapeatKillException(String message, Throwable cause) {
        super(message, cause);
    }
}
