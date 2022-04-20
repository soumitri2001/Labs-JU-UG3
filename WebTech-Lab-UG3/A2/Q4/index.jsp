<!DOCTYPE html>
<html>
<head>
	<title>Session</title>
</head>
<body>
<%
int num=0;
String number=(String)session.getAttribute("number");
if(number!=null){
	String button=request.getParameter("button");
	if(button!=null){
		if(button.equals("next")){
            num=Integer.parseInt(number)+1;
        }
		else{
			num=Integer.parseInt(number)-1;
        }
	}
}
session.setAttribute("number",String.valueOf(num));
out.println(num);
%>
<form method="post">
	<input type="submit" name="button" value="prev">
	<input type="submit" name="button" value="next">

</form>
</body>
</html>