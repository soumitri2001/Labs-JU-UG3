<%@page import="java.sql.*" %>

<%!
	static final String ACCOUNT_TABLE = "accounts";

	static boolean tableExists(Connection conn, String tableName) throws SQLException {
        Statement stmt = conn.createStatement();
        
        ResultSet rs = stmt.executeQuery("SELECT count(*) "
        + "FROM information_schema.tables "
        + "WHERE table_name = '" + tableName + "' AND table_schema = 'test' "
        + "LIMIT 1;");

        rs.next();
        return rs.getInt(1) != 0;
    }

    static void _initDB(Connection conn) throws SQLException {
        Statement stmt = conn.createStatement();
        stmt.clearBatch();
        
        if (tableExists(conn, ACCOUNT_TABLE)) {
            return;
        }

        stmt.execute("CREATE TABLE " + ACCOUNT_TABLE + " (user varchar(255) PRIMARY KEY, password varchar(255))");
    }
%>

<%
	try {
		Class.forName("com.mysql.jdbc.Driver");
		// String url = "jdbc:mysql://localhost:3306/test?user=root&password=password";
  //       Connection con = DriverManager.getConnection(url);
  		Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");
  		_initDB(con);

  		String username = request.getParameter("user");
  		String oldPassword = request.getParameter("oldPassword");
  		String newPassword = request.getParameter("newPassword");
  		String confirmPassword = request.getParameter("confirmPassword");

  		// out.println("username : " + username + "\tpassword : " + password);

  		Statement stmt = con.createStatement();
  		String query = "select user, password from " + ACCOUNT_TABLE +" where user = '"+username+"'";
  		ResultSet result = stmt.executeQuery(query);

  		if(result.next()) {
  			if(result.getString(2).equals(oldPassword)){
  				if(!newPassword.equals(confirmPassword)){
  					out.println("Provided passwords didn't match");
  				} else {
  					String updateQuery = "UPDATE " + ACCOUNT_TABLE +" SET password='"+newPassword+"' WHERE user='"+username+"'";
  					stmt.executeUpdate(updateQuery);
  					out.println("Password updated!");
  				}
  			}
  			else
  				out.println("Sorry please check your password and try again!!");
  		} else {
  			out.println("Sorry :( inalid username!");
  		}

  		stmt.close();
  		con.close();

	} catch (Exception e) {
		out.println(e);
	}
%>