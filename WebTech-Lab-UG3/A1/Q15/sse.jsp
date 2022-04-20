<%
response.setContentType("text/event-stream"); 
response.setCharacterEncoding("UTF-8");

Integer val1=new java.util.Random().nextInt(10)+40;
Integer val2=new java.util.Random().nextInt(10)+30;

try{
	while(true){
		//val1+=new java.util.Random().nextInt(200)
		out.print("event: stock_one\n");
		out.print("data: "+val1+"."+new java.util.Random().nextInt(100)+"\n\n");

		out.print("event: stock_two\n");
		out.print("data: "+val2+"."+new java.util.Random().nextInt(100)+"\n\n");
		out.flush();
		Thread.sleep(2000);
	}
}
catch(Exception e)
{
out.print(e);
}
%>