import java.io.IOException;
import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import javax.websocket.server.PathParam;
import java.util.*;

@ServerEndpoint(value="/chat/{username}")
public class chatServer
{
	static List<chatServer> users=new ArrayList<>();
	private String username;
	private Session session;

	@OnOpen
	public void OnOpen(@PathParam("username") String username,Session session)
	{
		this.username=username;
		this.session=session;
		users.add(this);
		sendMessage(username+" : joined.");
		System.out.println(username);
	} 

	@OnClose
	public void OnClose()
	{
		users.remove(this);
		sendMessage(username+" : left.");
	}

	@OnMessage
	public void OnMessage(String message)
	{
		String msg=username+" : "+message;
		sendMessage(msg);
	}

	private static void sendMessage(String message)
	{
		for(chatServer user : users)
		{
			try{
				user.session.getBasicRemote().sendText(message);
			}
			catch(IOException e)
			{
				users.remove(user);
				e.printStackTrace();
			}
		}
	}

}