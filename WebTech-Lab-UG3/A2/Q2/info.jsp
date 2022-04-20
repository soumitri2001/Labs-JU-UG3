<%@page import="java.sql.*" %>
<%@page import="java.util.*" %>

<%! 

    static final String STUDENT_TABLE = "student";
    static final String DEPT_TABLE = "dept";

    static boolean tableExists(Connection con, String tableName) throws SQLException {
        Statement stmt = con.createStatement();
        
        ResultSet rs = stmt.executeQuery("SELECT count(*) "
        + "FROM information_schema.tables "
        + "WHERE table_name = '" + tableName + "' AND table_schema = 'test' "
        + "LIMIT 1;");

        rs.next();
        return rs.getInt(1) != 0;
    }

    static void _initDB(Connection con) throws SQLException {
        Statement stmt = con.createStatement();
        stmt.clearBatch();
        
        if (tableExists(con, STUDENT_TABLE)) {
            stmt.execute("DROP TABLE " + STUDENT_TABLE);

        }

        if (tableExists(con, DEPT_TABLE)) {
            stmt.execute("DROP TABLE " + DEPT_TABLE);
        }

        stmt.execute("CREATE TABLE " + DEPT_TABLE + " (dept_name varchar(255) PRIMARY KEY)");
        stmt.execute("INSERT INTO " + DEPT_TABLE + " VALUES (\"IT\"), (\"CSE\"), (\"ECE\"), (\"EE\"), (\"IEE\")");

        stmt.execute("CREATE TABLE " + STUDENT_TABLE + " ("
        + "    roll_no int AUTO_INCREMENT PRIMARY KEY,"
        + "    student_name varchar(255),"
        + "    dept_name varchar(255),"
        + "    FOREIGN KEY (dept_name) REFERENCES " + DEPT_TABLE + "(dept_name)"
        + " )");

        stmt.execute("INSERT INTO " + STUDENT_TABLE + " (student_name, dept_name) VALUES "
        + "(\"Soumitri\", \"IT\"),"
        + "(\"Sourav\", \"IT\"),"
        + "(\"Jake\", \"IT\"),"
        + "(\"Holt\", \"ECE\"),"
        + "(\"Alex\", \"ECE\"),"
        + "(\"Kaiming\", \"CSE\"),"
        + "(\"Cohen\", \"CSE\"),"
        + "(\"Riddhi\", \"EE\"),"
        + "(\"Barun\", \"EE\"),"
        + "(\"Arun\", \"IEE\"),"
        + "(\"Anjan\", \"IEE\")");
    } 

%>

<html lang="en">

<head>
    <title>Student's Database</title>
</head>

<body>
    <% 
        ArrayList<String> searchNameResult = new ArrayList<>();
        ArrayList<String> depts = new ArrayList<>();
        ArrayList<String> deptNameResult = new ArrayList<>();
        String searchName = request.getParameter("searchName");
        String deptName = request.getParameter("deptName");

        try { 
            // load the Driver Class --> registers a Driver instance with the DriverManager 
            Class.forName("com.mysql.jdbc.Driver");
            // String url = "jdbc:mysql://localhost:3306/test?user=root&password=password";
            // Connection con = DriverManager.getConnection(url);
            Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");            
            _initDB(con);
            
            Statement stmt = con.createStatement(); 

            if (searchName != null) {
                ResultSet rs = stmt.executeQuery("SELECT * FROM " + STUDENT_TABLE +" WHERE student_name LIKE '%" + searchName + "%'");
                while (rs.next()) {
                    searchNameResult.add(rs.getString(1) + " " + rs.getString(2) + " " + rs.getString(3));
                }
            }

            if (deptName != null) {
                ResultSet rs = stmt.executeQuery("SELECT * FROM " + STUDENT_TABLE + " WHERE dept_name = '" + deptName + "'");
                while (rs.next()) {
                    deptNameResult.add(rs.getString(1) + " " + rs.getString(2) + " " + rs.getString(3));
                }
            } 

            ResultSet rs = stmt.executeQuery("SELECT * FROM " + DEPT_TABLE);
            while (rs.next()) {
                depts.add(rs.getString(1));
            }

            stmt.close();
            con.close(); 
        } catch (Exception e) { 
            out.println(e); 
        } 
    %>
    <h2>Search Student by name</h2>
    <form method="post">
        <input type="text" name="searchName" required>
        <button>Search</button>
    </form>
    <p>
        <%=(searchName != null) ? "search for '" + searchName + "'" : ""%>
    </p>
    <p>
    <% 
        for (String s : searchNameResult) {
            out.println(s);
            out.println("<br>");
        }
    %>
    </p>
    <hr>
    <h2>Search Student by department</h2>

    <form method="post">
        <select name="deptName" required>
            <option disabled value="" <%= (deptName == null) ? "selected" : "" %>>Select a department</option>
            <%
                for (String dept : depts) {
                    String selected = (dept.equals(deptName)) ? "selected" : "";
                    out.println("<option value=\""+ dept + "\" " + selected + ">" + dept + "</option>");
                } 
            %>
        </select>
        <button>Submit</button>
    </form>

    <p>
        <%= (deptName == null) ? "" : "Showing students in '" + deptName + "' department" %>
    </p>
    <p>
        <% 
            for (String s : deptNameResult) {
                out.println(s);
                out.println("<br>");
            }
        %>
    </p>
</body>

</html>