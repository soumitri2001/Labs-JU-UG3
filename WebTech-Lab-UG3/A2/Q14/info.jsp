<%@page import="java.sql.*" %>

<%!
    static final String SEMESTER_TABLE = "semesterTable";
    static final String ROLL_TABLE = "rollTable";
    static final String SUBJECT_TABLE = "SubjectTable";
    static final String RESULT_TABLE = "ResultTable";

    static boolean tableExists(Connection con, String tableName) throws SQLException {
        Statement stmt = con.createStatement();

        ResultSet rs = stmt.executeQuery("SELECT count(*) " 
            + " FROM information_schema.tables " 
            + " WHERE table_name = '" + tableName + "' AND table_schema = 'test' "
            + "LIMIT 1;");
        
        rs.next();
        return rs.getInt(1) != 0;
    }

    static void _initDB(Connection con) throws SQLException {
        Statement stmt = con.createStatement();
        stmt.clearBatch();

        if (tableExists(con, SEMESTER_TABLE)){
            stmt.execute("DROP TABLE " + SEMESTER_TABLE + ";");
        }

        if (tableExists(con, ROLL_TABLE)){
            stmt.execute("DROP TABLE " + ROLL_TABLE + ";");
        }

        if (tableExists(con, SUBJECT_TABLE)){
            stmt.execute("DROP TABLE " + SUBJECT_TABLE + ";");
        }

        if (tableExists(con, RESULT_TABLE)){
            stmt.execute("DROP TABLE " + RESULT_TABLE + ";");
        }

        stmt.execute(" CREATE TABLE " + SEMESTER_TABLE + " (" 
            + "semId INT,"
            + "semName VARCHAR(15),"
            + "PRIMARY KEY (semId));");

        stmt.execute(" CREATE TABLE " + ROLL_TABLE + " (" 
            + "semId INT,"
            + "rollNo VARCHAR(4),"
            + "PRIMARY KEY (rollNo));");

        stmt.execute(" CREATE TABLE " + SUBJECT_TABLE + " (" 
            + "semId INT,"
            + "subject VARCHAR(30),"
            + "PRIMARY KEY (subject));");
            
        stmt.execute(" CREATE TABLE " + RESULT_TABLE + " (" 
            + "semId INT,"
            + "rollNo VARCHAR(4),"
            + "subject VARCHAR(30),"
            + "marks INT,"
            + "PRIMARY KEY (semId, rollNo, subject));");

        stmt.execute("INSERT INTO " + SEMESTER_TABLE + " VALUES (" + 1 + ", 'First Semester')");
        stmt.execute("INSERT INTO " + SEMESTER_TABLE + " VALUES (" + 3 + ", 'Third Semester')");
        stmt.execute("INSERT INTO " + SEMESTER_TABLE + " VALUES (" + 5 + ", 'Fifth Semester')");
        stmt.execute("INSERT INTO " + SEMESTER_TABLE + " VALUES (" + 7 + ", 'Seventh Semester')");
         
        stmt.execute("INSERT INTO " + ROLL_TABLE + " VALUES ("+ 1 + ", 2501)"); 
        stmt.execute("INSERT INTO " + ROLL_TABLE + " VALUES ("+ 1 + ", 2502)"); 
        stmt.execute("INSERT INTO " + ROLL_TABLE + " VALUES ("+ 3 + ", 2401)"); 
        stmt.execute("INSERT INTO " + ROLL_TABLE + " VALUES ("+ 3 + ", 2402)"); 
        stmt.execute("INSERT INTO " + ROLL_TABLE + " VALUES ("+ 5 + ", 2301)"); 
        stmt.execute("INSERT INTO " + ROLL_TABLE + " VALUES ("+ 5 + ", 2302)");  
        stmt.execute("INSERT INTO " + ROLL_TABLE + " VALUES ("+ 7 + ", 2201)"); 
        stmt.execute("INSERT INTO " + ROLL_TABLE + " VALUES ("+ 7 + ", 2202)");  

        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 1 + ", 'PHYSICS')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 1 + ", 'CHEMISTRY')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 1 + ", 'SOCIOLOGY')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 3 + ", 'CPNM')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 3 + ", 'ENGINEERING DRAWING')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 3 + ", 'GRAPH THEORY')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 5 + ", 'DSA')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 5 + ", 'WEB TECHNOLOGIES')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 5 + ", 'LINEAR ALGEBRA')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 7 + ", 'IMAGE PROCESSING')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 7 + ", 'MACHINE LEARNING')"); 
        stmt.execute("INSERT INTO " + SUBJECT_TABLE + " VALUES ("+ 7 + ", 'DBMS')"); 
        
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 1 + ", 2501, 'PHYSICS', 95)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 1 + ", 2501, 'CHEMISTRY', 91)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 1 + ", 2501, 'SOCIOLOGY', 85)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 1 + ", 2502, 'PHYSICS', 83)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 1 + ", 2502, 'CHEMISTRY', 86)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 1 + ", 2502, 'SOCIOLOGY', 79)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 3 + ", 2401, 'CPNM', 82)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 3 + ", 2401, 'ENGINEERING DRAWING', 74)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 3 + ", 2401, 'GRAPH THEORY', 71)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 3 + ", 2402, 'CPNM', 90)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 3 + ", 2402, 'ENGINEERING DRAWING', 93)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 3 + ", 2402, 'GRAPH THEORY', 77)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 5 + ", 2301, 'DSA', 98)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 5 + ", 2301, 'WEB TECHNOLOGIES', 96)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 5 + ", 2301, 'LINEAR ALGEBRA', 94)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 5 + ", 2302, 'DSA', 74)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 5 + ", 2302, 'WEB TECHNOLOGIES', 78)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 5 + ", 2302, 'LINEAR ALGEBRA', 79)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 7 + ", 2201, 'IMAGE PROCESSING', 84)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 7 + ", 2201, 'MACHINE LEARNING', 89)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 7 + ", 2201, 'DBMS', 88)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 7 + ", 2202, 'IMAGE PROCESSING', 94)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 7 + ", 2202, 'MACHINE LEARNING', 82)");
        stmt.execute("INSERT INTO " + RESULT_TABLE + " VALUES ("+ 7 + ", 2202, 'DBMS', 97)");
    }

%>

<% 
    try{
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");            
        _initDB(con);
        Statement stmt = con.createStatement();

        if (request.getParameter("semester")!=null && request.getParameter("rollNo")==null){
            String semester = request.getParameter("semester");
            String query = "SELECT " + ROLL_TABLE + ".rollNo FROM " + SEMESTER_TABLE 
                + " INNER JOIN " + ROLL_TABLE + " ON " + SEMESTER_TABLE + ".semId = " + ROLL_TABLE + ".semId " 
                + "WHERE " + SEMESTER_TABLE + ".semId = " + semester + ";";
            ResultSet result = stmt.executeQuery(query);
            while (result.next()){
                out.println(result.getString(1));
            }
            out.println("rollEnds");

            String query2 = "SELECT " + SUBJECT_TABLE + ".subject FROM " + SEMESTER_TABLE 
            + " INNER JOIN " + SUBJECT_TABLE + " ON " + SEMESTER_TABLE + ".semId = " + SUBJECT_TABLE + ".semId " 
            + "WHERE " + SEMESTER_TABLE + ".semId = " + semester + ";";
            ResultSet result2 = stmt.executeQuery(query2);
            while (result2.next()){
                out.println(result2.getString(1));
            }
        }

        else if (request.getParameter("semester")!=null && request.getParameter("rollNo")!=null){
            String semester = request.getParameter("semester");
            String rollNo = request.getParameter("rollNo");
            String subject = request.getParameter("subject");

            String query = "SELECT marks FROM " + RESULT_TABLE 
            + " WHERE semId = " + semester + " AND rollNo = " + rollNo 
            + " AND subject = '" + subject + "';";
            ResultSet result3 = stmt.executeQuery(query);
            while (result3.next()){
                out.println(result3.getString(1));
            }
        }


    }catch(Exception e){
        out.println(e);
    }

%>