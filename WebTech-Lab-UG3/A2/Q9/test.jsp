<%@page import="java.sql.*"%>
<html lang="en">
  <%! 

  static final String QPAPER_TABLE = "XML";
  

  static boolean tableExists(Connection conn, String tableName) throws SQLException {
      Statement stmt = conn.createStatement();
      
      ResultSet rs = stmt.executeQuery("SELECT count(*) "
      + "FROM information_schema.tables "
      + "WHERE table_name = '" + tableName + "' "
      + "LIMIT 1;");

      rs.next();
      return rs.getInt(1) != 0;
  }

  static void initDB(Connection conn) throws SQLException {
      Statement stmt = conn.createStatement();
      stmt.clearBatch();
      
      if (tableExists(conn, QPAPER_TABLE)) {
          
        return;

      }
      
      stmt.execute("CREATE TABLE " + QPAPER_TABLE + " ("
      + "    qno int AUTO_INCREMENT PRIMARY KEY,"
      + "    text TEXT NOT NULL,"
      + "    optionA TEXT,"
      + "    optionB TEXT,"
      + "    optionC TEXT,"
      + "    optionD TEXT,"
      + "    answerKey TEXT NOT NULL,"
      + "    answer TEXT NOT NULL"
      + " )");

      stmt.execute("INSERT INTO " + QPAPER_TABLE + " (text, optionA,optionB,optionC,optionD,answerKey,answer) VALUES "
      + "(\"What is full form of jsp?\", \"Java Servlet Paging\",\"Java Server Pages\",\"Jakarta Service Page\",\"Java Simulation Package\",\"optionB\",\"Java Server Pages\"),"
     + "(\"Which of the following is not a valid a HTTP method?\", \"GET\",\"POST\",\"DELETE\",\"FIT\",\"optionD\",\"FIT\")"
      );
      
  } 

%>
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Assignment2-Q9(Test)</title>
</head>
<body>
    <%
    try { 
          Class.forName("com.mysql.jdbc.Driver");
          // String url = "jdbc:mysql://localhost:3306/test?user=root&password=password";
          // Connection con = DriverManager.getConnection(url);
          Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");
          initDB(con);
          Statement stmt = con.createStatement();
          ResultSet rs = stmt.executeQuery("SELECT qno, text, optionA, optionB, optionC, optionD FROM "+ QPAPER_TABLE );
          out.println("<form method=\"POST\" action=\"result.jsp\">");
          
          while(rs.next())
          {
            out.println("<p>" + rs.getString("qno") + ". " + rs.getString("text") + "\n"+"</p>");
            out.println("<br>");
            out.println("<input type=\"radio\" name=\"question" + rs.getString("qno")+"\" value=\"optionA\">");
            out.println("<label for=\"question" + rs.getString("qno") + "\">" + rs.getString("optionA") + "</label>");
            out.println("<br>");
            out.println("<input type=\"radio\" name=\"question" + rs.getString("qno")+"\" value=\"optionB\">");
            out.println("<label for=\"question" + rs.getString("qno") + "\">" + rs.getString("optionB") + "</label>");
            out.println("<br>");
            out.println("<input type=\"radio\" name=\"question" + rs.getString("qno")+"\" value=\"optionC\">");
            out.println("<label for=\"question" + rs.getString("qno") + "\">" + rs.getString("optionC") + "</label>");
            out.println("<br>");
            out.println("<input type=\"radio\" name=\"question" + rs.getString("qno")+"\" value=\"optionD\">");
            out.println("<label for=\"question" + rs.getString("qno") + "\">" + rs.getString("optionD") + "</label>");
            out.println("<br>");
        }
        out.println("<input type=\"submit\"></submit>");

          out.println("</form>");
        
        stmt.close();
        con.close();

    } catch(Exception e) {
    
        out.println("Error");
        out.println(e);

    }

  %>
</body>
</html>