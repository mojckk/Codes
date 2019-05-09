package org.seckill;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

/**
 * @ClassName DatabaseTest
 * @Author丑丑
 * @Date 2019/3/1515:24
 **/
public class DatabaseTest {
    private static final String driver="com.mysql.jdbc.Driver"; //8.0之后
    private static final String url= "jdbc:mysql://localhost:3308/seckill?useUnicode=true&characterEncoding=utf-8";
    private static final String username="root";
    private static final String password="123456";
    private static Connection conn=null;

    public static void main(String[] args) throws Exception {
        //加载驱动
        Class.forName(driver);
        //获得数据库连接
        conn = DriverManager.getConnection(url, username, password);
        //操作数据库
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("select name,number from seckill ");
        while (rs.next()) {
            System.out.println(rs.getString("name") + "," + rs.getInt("number"));
        }

    }
}
