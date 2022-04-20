<html>
<head>
	<title>URL rewriting</title>
</head>
<body>
<%
int num=0;
String temp=request.getParameter("num");
if(temp!=null)
num=Integer.parseInt(temp);
%>
<a href="urlrewrite.jsp?num=<%=num-1%>">Prev</a>
<%
out.println(num);
%>
<a href="urlrewrite.jsp?num=<%=num+1%>">Next</a>
</body>
</html>