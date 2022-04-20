<%@page import="java.sql.*"%>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <%
    try { 
          Class.forName("com.mysql.jdbc.Driver");
            // String url = "jdbc:mysql://localhost:3306/test?user=root&password=password";
            // Connection con = DriverManager.getConnection(url);
            Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");          
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT answerKey from XML");

          int correct = 0, total = 0;
          while(rs.next())
          {
            total++;
            if(rs.getString("answerKey").equals(request.getParameter("question"  + total)))
                correct++;   
         }

          stmt.close();
          con.close();
          out.println("Total questions: " + total);
          out.println("Correctly answered: " + correct);
          out.println("Incorrect: " + (total-correct));
        

    } catch(Exception e) {
    
        out.println("Error");
        out.println(e);

    }

  %>
</body>
</html>