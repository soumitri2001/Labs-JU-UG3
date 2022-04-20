<%@page import="java.sql.*" %>

<%! 
    static final String table = "users";

    static boolean tableExists(Connection conn, String tableName) throws SQLException {
        Statement stmt = conn.createStatement();
        
        ResultSet rs = stmt.executeQuery("SELECT count(*) "
        + "FROM information_schema.tables "
        + "WHERE table_name = '" + tableName + "' "
        + "LIMIT 1;");

        rs.next();
        return rs.getInt(1) != 0;
    }

    static void _initDB(Connection conn) throws SQLException {
        Statement stmt = conn.createStatement();
        if (!tableExists(conn, table)) {
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
    String email = request.getParameter("email");
    String phone = request.getParameter("phone");
    String name = request.getParameter("name");

    boolean success = false;
    String message = "";

    if (loginName == null || pass == null ||
        email == null || phone == null || name == null ) {
            response.sendError(400, "Some parameters are missing!");
    } 
    else {
        try { 
            Class.forName("com.mysql.jdbc.Driver");
            // String url = "jdbc:mysql://localhost:3306/test?user=root&password=password";
            // Connection con = DriverManager.getConnection(url);
            // Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");

            _initDB(con);
            
            Statement stmt = con.createStatement(); 

            stmt.execute("INSERT INTO " + table + " VALUES (\"" 
                + loginName + "\", \"" + pass + "\", \"" +email + "\", \"" 
                + name + "\", " + phone + ")");

            stmt.close();
            con.close(); 
            message = "Account created!";
        }
        catch (SQLIntegrityConstraintViolationException e) {
            message = "Username already taken!";
        } 
        catch (Exception e) { 
            response.sendError(500, e.getMessage());
        } 
    }

%>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>Adding data in database</title>
</head>

<body>
    <p> <%= message %> </p>
    <p> <a href="login.jsp">Login</a></p>
</body>

</html>