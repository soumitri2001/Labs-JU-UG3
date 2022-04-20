<%@page import="java.sql.*" %>

<%! 
    static final String table = "users";

    static boolean tableExists(Connection con, String tableName) throws SQLException {
        Statement stmt = con.createStatement();
        
        ResultSet rs = stmt.executeQuery("SELECT count(*) "
        + "FROM information_schema.tables "
        + "WHERE table_name = '" + tableName + "' "
        + "LIMIT 1;");

        rs.next();
        return rs.getInt(1) != 0;
    }

    static void _initDB(Connection con) throws SQLException {
        Statement stmt = con.createStatement();
        if (!tableExists(con, table)) {
            stmt.execute("CREATE TABLE " + table + " ("
                + "login_name VARCHAR(255) PRIMARY KEY,"
                + "pass VARCHAR(255),"
                + "email VARCHAR(255),"
                + "name VARCHAR(255),"
                + "phone DECIMAL(10)"
                + ")"
            );
        }
    }
%>

<%
    String loginName = request.getParameter("loginName");
    String pass = request.getParameter("pass");

    boolean allData = true;
    boolean success = false;
    String mssg = "";

    if (loginName == null || pass == null) {
            allData = false;
    }

    if (allData) {

        try { 
            Class.forName("com.mysql.jdbc.Driver");
            // String url = "jdbc:mysql://localhost:3306/test?user=root&password=password";
            // Connection con = DriverManager.getConnection(url);
            // Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");
            _initDB(con);
            
            Statement stmt = con.createStatement(); 
    
            ResultSet rs = stmt.executeQuery("SELECT pass FROM " + table + " WHERE login_name = \"" + loginName + "\"" );
            if (rs.next()) {
                if (rs.getString(1).equals(pass)) {
                    success = true;
                } else {
                    mssg = "Incorrect password";
                }
            } else {
                mssg = "Incorrect username";
            }
    
            stmt.close();
            con.close(); 
        }
        catch (Exception e) { 
            response.sendError(500, e.getMessage());
        } 

    }

%>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>Login</title>
</head>

<body>
    <form method="post">
        <label for="loginName">Login Name</label>
        <input required type="text" name="loginName" id="loginName">
        <br>
        <label for="pass">Password</label>
        <input required type="password" name="pass" id="pass">
        <br><br>
        <button>Submit</button>
    </form>

    <h3> <%= (!allData) ? "Login:" : (success) ? "Can Login!" : mssg%> </h3>
</body>

</html>