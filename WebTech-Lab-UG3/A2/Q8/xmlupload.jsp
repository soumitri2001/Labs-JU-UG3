<%@page import="javax.servlet.annotation.MultipartConfig"%>
<%@page import="java.sql.*"%>
<%@page import="java.io.InputStream"%>
<%@page import="helper.XMLInserter"%>


    <%
        Part filePart = request.getPart("file"); 
        // String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); 
        if(filePart != null)
        { 
            InputStream fileContent = filePart.getInputStream();
            XMLInserter ins = new XMLInserter();
            ins.insert(fileContent);
            out.println("Successful Upload!");
        }
        else{
            out.println("Upload failed!");
        }

            
    %>
