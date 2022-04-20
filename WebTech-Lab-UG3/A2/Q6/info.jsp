<%@page import="java.sql.*" %>

<%!
	static final String DISTRICT_TABLE = "districts";
	static final String STATE_TABLE = "states";

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
        
        if (tableExists(conn, DISTRICT_TABLE)) {
            stmt.execute("DROP TABLE " + DISTRICT_TABLE);
        }

        if (tableExists(conn, STATE_TABLE)) {
            stmt.execute("DROP TABLE " + STATE_TABLE);
        }

        stmt.execute(" CREATE TABLE "+ STATE_TABLE + " ("
      	+	"stateId INT,"
      	+	"state VARCHAR(20),"
      	+	"PRIMARY KEY (stateId);");

        stmt.execute("CREATE TABLE " + DISTRICT_TABLE + " ("
      	+	"stateId INT REFERENCES states (stateId),"
      	+	"district VARCHAR (30),"
      	+	"info VARCHAR (500),"
      	+	"PRIMARY KEY (district);");

		stmt.execute("INSERT INTO " + STATE_TABLE + " VALUES ("+ 1 +", 'West Bengal')");
		stmt.execute("INSERT INTO " + STATE_TABLE + " VALUES ("+ 2 +", 'Maharashtra')");
		stmt.execute("INSERT INTO " + STATE_TABLE + " VALUES ("+ 2 +", 'Odisha')");

		stmt.execute("INSERT INTO " + DISTRICT_TABLE + " VALUES (" + 1 +", 'Kolkata', 'Kolkata (formerly Calcutta) is the capital of West Bengal state. Founded as an East India Company trading post, it was Indian capital under the British Raj'");
		stmt.execute("INSERT INTO " + DISTRICT_TABLE + " VALUES (" + 1 +", 'Howrah', 'Howrah is the second smallest district after Kolkata. It has thousands of years of rich heritage in the form of the great Bengali kingdom of Bhurshut. The district is named after its headquarters, the city of Howrah.'");
		stmt.execute("INSERT INTO " + DISTRICT_TABLE + " VALUES (" + 1 +", 'Bardhaman', 'Bardhaman district (also spelled Burdwan or Barddhaman or Vardhaman) was a district in West Bengal.T he headquarters of the district was Bardhaman, and it housed the cities of Asansol and Durgapur. Indian revolutionary Rashbehari Bose was born in village Subaldaha, Bardhaman district.'");
		stmt.execute("INSERT INTO " + DISTRICT_TABLE + " VALUES (" + 2 +", 'Aurangabad', 'Aurangabad District is one of the 36 districts of the state of Maharashtra in western India.'");
		stmt.execute("INSERT INTO " + DISTRICT_TABLE + " VALUES (" + 2 +", 'Cuttack', 'Cuttack is located in the coastal part of the state and its administrative headquarters are located in the city of Cuttack. As of 2011 Census, after Ganjam, it is the second most populous district of Odisha (out of 30), with a population of 2,624,470.'");

    }
%>

<%
	try{
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");
		_initDB(con);
		
		Statement stmt = con.createStatement();
		
		if (request.getParameter("state")!=null){
			String state = request.getParameter("state");
			String query = "select district.district, state.state from '" + DISTRICT_TABLE + "' as district inner join '" + STATE_TABLE +"' as state on district.stateId = state.stateId where state='" + state + "'";
			ResultSet result = stmt.executeQuery(query);
			while (result.next()){
				out.println(result.getString(1));
			}
		}
		else if (request.getParameter("district")!=null){
			String district = request.getParameter("district");
			String query = "select info from '" + DISTRICT_TABLE "' as districts where districts.district = '" + district + "'";
			ResultSet result = stmt.executeQuery(query);
			while (result.next()){
				out.println(result.getString(1));
			}
		}
		
	}
	catch (Exception e) {
		out.println(e);
	}
%>