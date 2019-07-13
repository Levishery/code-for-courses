import java.io.*; 
import java.net.*; 
import java.util.*; 

public class WebServer{ 
  public static void main(String args[])throws Exception{    
	int i = 0;
	ServerSocket listenSocket=new ServerSocket(6789); 

	while(true) {
	Socket connectionSocket = listenSocket.accept(); 
	i++;
	System.out.print("收到新的请求\n");
	SubThread connection=new SubThread();
	connection.setSocket(connectionSocket);
	connection.setnum(i);
	Thread thread = new Thread(connection);
	String name = Integer.toString(i);
	thread.setName(name);
	thread.start();//启动线程
	}

  } 
}

class SubThread implements Runnable{//线程子类

	private Socket connectionSocket;

	public void setSocket(Socket id)
	{
			this.connectionSocket = id;
	}

	private int num;

	public void setnum(int i)
	{
			this.num = i;
	}
	
	public void run(){//线程启动后运行此方法
		try{
		System.out.println("当前活动线程数目:"+Thread.activeCount());
	  Thread.currentThread().getThreadGroup().list();
		String requestMessageLine; 
		String fileName=""; 
		BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream())); 
		DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream()); 
		requestMessageLine=inFromClient.readLine(); 
		StringTokenizer tokenizedLine = new StringTokenizer(requestMessageLine); 

		if(tokenizedLine.nextToken().equals("GET")){ 
		 fileName=tokenizedLine.nextToken(); 
		 if(fileName.startsWith("/")==true)
			 fileName=fileName.substring(1); 
		 File file=new File(fileName); 
		 int numOfBytes=(int)file.length(); 
		 FileInputStream inFile=new FileInputStream(fileName); 
		 byte[] fileInBytes=new byte[numOfBytes]; 
		 inFile.read(fileInBytes); 
		 outToClient.writeBytes("HTTP/1.0 200 Document Follows\r\n"); 
		 if(fileName.endsWith(".jpg")) 
			 outToClient.writeBytes("Content-Type:image/jpeg\r\n"); 
		 if(fileName.endsWith(".gif")) 
			 outToClient.writeBytes("Content-Type:image/gif\r\n"); 
		 outToClient.writeBytes("Content-Length:"+numOfBytes+"\r\n"); 
		 outToClient.writeBytes("\r\n"); 
		 outToClient.write(fileInBytes,0,numOfBytes); 
		 System.out.print("连接数："+num +"		");
		 connectionSocket.close(); 
		 inFile.close();
		}

		else System.out.println("Bad Request Message"); 
		} 
	
		catch(Exception e){
			e.printStackTrace();
		}

		System.out.println(num+":请求处理完毕!");
	}		
}