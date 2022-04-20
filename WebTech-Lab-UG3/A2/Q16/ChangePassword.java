package Q16;

import javax.faces.bean.ManagedBean;
import java.sql.*;

@ManagedBean
public class ChangePassword {
    private static final String ACCOUNT_TABLE = "accounts";

    private String loginName;
    private String currentPassword;
    private String newPassword;
    private String confirmPassword;
    private String result;

    public ChangePassword() {
        result = "";
    }

    public void change() {

        if (!newPassword.equals(confirmPassword)) {
            result = "new entered passwords dont match";
            return;
        }

        try {
            Class.forName("com.mysql.jdbc.Driver");
            // String url = "jdbc:mysql://localhost:3306/test?user=root&password=password";
            // Connection conn = DriverManager.getConnection(url);
            Connection conn = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");

            _initDB(conn);

            Statement stmt = conn.createStatement();

            ResultSet rs = stmt.executeQuery("SELECT password FROM " + ACCOUNT_TABLE + " WHERE user = \"" + loginName + "\"");
            if (rs.next()) {
                if (rs.getString(1).equals(currentPassword)) {
                    stmt.execute("UPDATE " + ACCOUNT_TABLE + " SET password = \"" + newPassword + "\" WHERE user = \""
                            + loginName + "\"");
                    result = "updated!";
                } else {
                    result = "incorrect password";
                }
            } else {
                result = "incorrect username";
            }

            stmt.close();
            conn.close();

        } catch (Exception e) {
            result = e.toString();
        }
    }

    public String getLoginName() {
        return loginName;
    }

    public String getCurrentPassword() {
        return currentPassword;
    }

    public String getNewPassword() {
        return newPassword;
    }

    public String getConfirmPassword() {
        return confirmPassword;
    }

    public String getResult() {
        return result;
    }

    public void setLoginName(String loginName) {
        this.loginName = loginName;
    }

    public void setCurrentPassword(String currentPassword) {
        this.currentPassword = currentPassword;
    }

    public void setNewPassword(String newPassword) {
        this.newPassword = newPassword;
    }

    public void setConfirmPassword(String confirmPassword) {
        this.confirmPassword = confirmPassword;
    }

    public void setResult(String result) {
        this.result = result;
    }

    private void _initDB(Connection conn) throws SQLException {
        Statement stmt = conn.createStatement();
        if (!tableExists(conn, ACCOUNT_TABLE)) {
            stmt.execute("CREATE TABLE " + ACCOUNT_TABLE + " (user varchar(255) PRIMARY KEY, password varchar(255))");
        }
    }

    private boolean tableExists(Connection conn, String tableName) throws SQLException {
        Statement stmt = conn.createStatement();

        ResultSet rs = stmt.executeQuery("SELECT count(*) "
                + "FROM information_schema.tables "
                + "WHERE table_name = '" + tableName + "' "
                + "LIMIT 1;");

        rs.next();
        return rs.getInt(1) != 0;
    }
}
