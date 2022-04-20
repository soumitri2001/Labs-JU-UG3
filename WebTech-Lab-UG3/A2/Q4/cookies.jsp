<!DOCTYPE html>
<html>
<head>
	<title>Cookies</title>
</head>
<body>
<%
int num=0;
Cookie cookie=null;
Cookie[] cookies=request.getCookies();
for(int i=0;i<cookies.length;i++){
	if(cookies[i].getName().equals("number")){
        cookie = cookies[i];
    }
    if(cookie!=null){
        String button=request.getParameter("button");
		if(button!=null){
			if(button.equals("next"))
				num=Integer.parseInt(cookie.getValue())+1;
			else
				num=Integer.parseInt(cookie.getValue())-1;
		}
    }
}
response.addCookie(new Cookie("number",String.valueOf(num)));
out.println(num);
%>
<form method="post">
	<input type="submit" name="button" value="prev">
	<input type="submit" name="button" value="next">

</form>
</body>
</html>