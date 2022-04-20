package helper;
import java.util.*;
import java.sql.*;
import org.w3c.dom.*;
import javax.xml.parsers.*;
import javax.xml.xpath.*; 
import java.io.*;
public class XMLInserter
{
    static final String QPAPER_TABLE = "xml_file";
    

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
        + "    qno int NOT NULL AUTO_INCREMENT PRIMARY KEY,"
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

    
    private static String getAttrValue(Node node,String attrName) 
    {
        
        if ( ! node.hasAttributes() ) return "";
        NamedNodeMap nmap = node.getAttributes();
        if ( nmap == null ) return "";
        Node n = nmap.getNamedItem(attrName);
        if ( n == null ) return "";
        return n.getNodeValue();
    }

    static private String getTextContent(Node parentNode,String childName) 
    {
        NodeList nlist = parentNode.getChildNodes();
        for (int i = 0 ; i < nlist.getLength() ; i++) {
        Node n = nlist.item(i);
        String name = n.getNodeName();
        if ( name != null && name.equals(childName) )
            return n.getTextContent();
        }
        return "";
    }

    public void insert(String path)
    {
        try{  

			Class.forName("com.mysql.jdbc.Driver");
            //String url = "jdbc:mysql://localhost:3306/test?user=root&password=password";
            //Connection con = DriverManager.getConnection(url);
            Connection con = DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");			
            initDB(con);
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
           // factory.setValidating(true);
            Document doc = factory.newDocumentBuilder().parse(path);

            XPath xpath = XPathFactory.newInstance().newXPath();
            Object res = xpath.evaluate("/question-paper/question", doc, XPathConstants.NODESET);
            NodeList nlist = (NodeList) res;
            PreparedStatement stmt = con.prepareStatement("INSERT INTO xml_file(\n" + 
            "text, optionA, optionB, optionC, optionD, answerKey, answer)\n" +
              "VALUES(?, ?, ?, ?, ?, ?, ?)");
          
                  for (int i = 0 ; i < nlist.getLength() ; i++) 
                  {
                    Node node = nlist.item(i);
                    List<String> columns = Arrays.asList(
                        getTextContent(node, "text"),
                        getTextContent(node, "optionA"),
                        getTextContent(node, "optionB"),
                        getTextContent(node, "optionC"),
                        getTextContent(node, "optionD"),
                        getAttrValue(node.getChildNodes().item(node.getChildNodes().getLength()-2), "value"),
                        getTextContent(node, "answer"));
                    for (int n = 0 ; n < columns.size() ; n++) 
                    {
                          stmt.setString(n+1, columns.get(n).trim());
        //                System.out.println(columns.get(n).trim());
                    }
                    stmt.execute();
                }

            stmt.close();
            con.close();

			}catch(Exception e){ 
				System.out.println("Error:");
				System.out.println(e);
			}  
    }

    public void insert(InputStream path)
    {
        try{  

			Class.forName("com.mysql.jdbc.Driver");
            Connection con=DriverManager.getConnection("jdbc:mysql://172.16.4.50:3306/test", "be1983", "WxDwZTVd");
			initDB(con);
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            //factory.setValidating(true);
            Document doc = factory.newDocumentBuilder().parse(path);

            XPath xpath = XPathFactory.newInstance().newXPath();
            Object res = xpath.evaluate("/question-paper/question", doc, XPathConstants.NODESET);
            NodeList nlist = (NodeList) res;
            PreparedStatement stmt = con.prepareStatement("INSERT INTO xml_file(\n" + 
            "text, optionA, optionB, optionC, optionD, answerKey, answer)\n" +
              "VALUES(?, ?, ?, ?, ?, ?, ?)");
          
                  for (int i = 0 ; i < nlist.getLength() ; i++) 
                  {
                    Node node = nlist.item(i);
                    List<String> columns = Arrays.asList(
                        getTextContent(node, "text"),
                        getTextContent(node, "optionA"),
                        getTextContent(node, "optionB"),
                        getTextContent(node, "optionC"),
                        getTextContent(node, "optionD"),
                        getAttrValue(node.getChildNodes().item(node.getChildNodes().getLength()-2), "value"),
                        getTextContent(node, "answer"));
                    for (int n = 0 ; n < columns.size() ; n++) {
                          stmt.setString(n+1, columns.get(n).trim());
                    }
                    stmt.execute();
                }

            stmt.close();
            con.close();

			}catch(Exception e){ 
				System.out.println("Error:");
				System.out.println(e);
			}  
    }


    public static void main(String args[])
    {
        XMLInserter x = new XMLInserter();
        x.insert(args[0]);
    }
}