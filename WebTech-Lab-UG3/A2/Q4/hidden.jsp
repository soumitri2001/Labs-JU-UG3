<!DOCTYPE html>
<html>
<head>
	<title>Hidden field</title>
</head>
<body>
<%
int num=0;
String number=request.getParameter("current");
String button=request.getParameter("button");
	if(button!=null){
		if(button.equals("next"))
			num=Integer.parseInt(number)+1;
		else
			num=Integer.parseInt(number)-1;
	}
out.println(num);
%>
</body>
<form method="post">
	<input type="hidden" name="current" value="<%=num%>">
	<input type="submit" name="button" value="prev">
	<input type="submit" name="button" value="next">
</form>
</html>