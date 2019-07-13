package tcp;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.net.*;
import java.io.*;
import javax.swing.border.*;

public class Frame1
extends JFrame
implements Runnable {
JPanel contentPane;
Label label1 = new Label();
Label label2 = new Label();
TextField textField1 = new TextField();
TextField textField2 = new TextField();
Button button1 = new Button();
TextArea textArea1 = new TextArea();
DatagramPacket sendpacket, receivepacket;
DatagramSocket sendsocket, receivesocket;
boolean Run = false;

public Frame1() {
enableEvents(AWTEvent.WINDOW_EVENT_MASK);
try {
  jbInit();
}
catch (Exception e) {
  e.printStackTrace();
}
}

private void jbInit() throws Exception {
contentPane = (JPanel)this.getContentPane();
border1 = new EtchedBorder(EtchedBorder.RAISED, Color.white,
                           new Color(178, 178, 178));
label1.setFont(new java.awt.Font("Dialog", 0, 12));
label1.setText("发送信息");
label1.setBounds(new Rectangle(13, 66, 63, 21));
contentPane.setLayout(null);
this.setDefaultCloseOperation(EXIT_ON_CLOSE);
this.setResizable(false);
this.setSize(new Dimension(363, 275));
this.setTitle("UDP信息传输");
label2.setEnabled(true);
label2.setFont(new java.awt.Font("Dialog", 0, 12));
label2.setForeground(Color.black);
label2.setText("远程IP地址");
label2.setBounds(new Rectangle(12, 36, 64, 23));
try {
  sendsocket = new DatagramSocket(); 
}
catch (SocketException se) {
  se.printStackTrace();
  System.exit(0);
}
button1.setEnabled(false);
button1.setFont(new java.awt.Font("Dialog", 0, 12));
button1.setLabel("发送");
button1.setBounds(new Rectangle(287, 64, 59, 24));
button1.addActionListener(new java.awt.event.ActionListener() {
  public void actionPerformed(ActionEvent e) {
    button1_actionPerformed(e);
  }
});
textField2.setFont(new java.awt.Font("DialogInput", 0, 12));
textField2.setSelectionStart(11);
textField2.setText("127.0.0.1");
textField2.setBounds(new Rectangle(77, 36, 123, 24));
textArea1.setFont(new java.awt.Font("DialogInput", 0, 12));
textArea1.setBounds(new Rectangle(7, 93, 279, 141));
textField1.setFont(new java.awt.Font("DialogInput", 0, 12));
textField1.setSelectionEnd(6);
textField1.setText("Hello!");
textField1.setBounds(new Rectangle(76, 64, 209, 23));
label3.setBounds(new Rectangle(231, 36, 55, 23));
label3.setText("远程端口");
label3.setFont(new java.awt.Font("Dialog", 0, 12));
label3.setEnabled(true);
BCls.setActionCommand("清除");
BCls.setFont(new java.awt.Font("Dialog", 0, 12));
BCls.setLabel("清除");
BCls.setBounds(new Rectangle(290, 118, 61, 32));
BCls.addActionListener(new java.awt.event.ActionListener() {
  public void actionPerformed(ActionEvent e) {
    BCls_actionPerformed(e);
  }
});
textField3.setFont(new java.awt.Font("DialogInput", 0, 12));
textField3.setSelectionStart(5);
textField3.setText("10000");
textField3.setBounds(new Rectangle(289, 36, 61, 24));
label4.setBounds(new Rectangle(284, 168, 70, 23));
label4.setText("");
label4.setFont(new java.awt.Font("Dialog", 0, 11));
label4.setAlignment(Label.CENTER);
label4.setEnabled(true);
label5.setEnabled(true);
label5.setFont(new java.awt.Font("Dialog", 0, 12));
label5.setLocale(java.util.Locale.getDefault());
label5.setText("本地端口");
label5.setBounds(new Rectangle(231, 7, 55, 23));
label6.setAlignment(Label.CENTER);
label6.setEnabled(true);
label6.setFont(new java.awt.Font("Dialog", 0, 11));
label6.setText("");
label6.setBounds(new Rectangle(284, 192, 70, 23));
textField4.setBounds(new Rectangle(289, 6, 61, 24));
textField4.setText("10000");
textField4.setSelectionStart(5);
textField4.setFont(new java.awt.Font("DialogInput", 0, 12));
checkbox1.setFont(new java.awt.Font("DialogInput", 0, 12));
checkbox1.setLabel("通信/设置");
checkbox1.setBounds(new Rectangle(135, 8, 87, 21));
checkbox1.addMouseListener(new java.awt.event.MouseAdapter() {
  public void mouseClicked(MouseEvent e) {
    checkbox1_mouseClicked(e);
  }
});
label7.setEnabled(true);
label7.setAlignment(Label.CENTER);
label7.setFont(new java.awt.Font("Dialog", 0, 11));
label7.setForeground(Color.black);
label7.setText("USTC AUTO");
label7.setBounds(new Rectangle(7, 7, 117, 23));
contentPane.add(textField2, null);
contentPane.add(textField1, null);
contentPane.add(label1, null);
contentPane.add(textArea1, null);
contentPane.add(button1, null);
contentPane.add(label3, null);
contentPane.add(label2, null);
contentPane.add(BCls, null);
contentPane.add(textField3, null);
contentPane.add(label6, null);
contentPane.add(label4, null);
contentPane.add(label5, null);
contentPane.add(textField4, null);
contentPane.add(label7, null);
contentPane.add(checkbox1, null);
Thread thread = new Thread(this);
thread.start();
}

protected void processWindowEvent(WindowEvent e) {
super.processWindowEvent(e);
if (e.getID() == WindowEvent.WINDOW_CLOSING) {
  System.exit(0);
}
}

void button1_actionPerformed(ActionEvent e) {
String str = textField2.getText();
if (str.compareTo("") != 0) {
  try {
    textArea1.append("S: " +
                     textField1.getText() + "\n");
    byte data[] = textField1.getText().getBytes();
    String datas = new String(data);
	String sentence;
	String modifiedSentence;
	Socket clientSocket = new Socket("JanedeMacBook-Pro.local", 6789);
	DataOutputStream outToServer = new DataOutputStream(
			clientSocket.getOutputStream());
	BufferedReader inFromServer =
			new BufferedReader(new InputStreamReader(
					clientSocket.getInputStream()));
	outToServer.writeBytes(datas + '\n');
	modifiedSentence = inFromServer.readLine();
	System.out.println("FROM SERVER: " +
			modifiedSentence);
  }
  catch (IOException exc) {
    textArea1.append(exc.toString() + "\n");
    exc.printStackTrace();
  }
}
else {
  textArea1.setText("请输入远程IP地址!");
}
}

Border border1;
Button BCls = new Button();
Label label3 = new Label();
Label label4 = new Label();
Label label5 = new Label();
Label label6 = new Label();
Label label7 = new Label();
TextField textField3 = new TextField();
TextField textField4 = new TextField();
Checkbox checkbox1 = new Checkbox();
CheckboxGroup checkboxGroup1 = new CheckboxGroup();

void BCls_actionPerformed(ActionEvent e) {
textArea1.setText("");
}

void checkbox1_mouseClicked(MouseEvent e) {
if (checkbox1.getState()) {
  try {
    textField4.setEnabled(!true);
    receivesocket = new DatagramSocket(Integer.parseInt(textField4.getText().
        trim()));
  }
  catch (SocketException se) {
return;
  }
  Run = true;
  button1.setEnabled(true);
}
else {
  Run = !true;
  button1.setEnabled(!true);
  textField4.setEnabled(true);
  receivesocket.close();
}
}

public void run() {
Thread thisThread = Thread.currentThread();
while (true) {
  if (!Run) {
    try {
      thisThread.sleep(100);
    }
    catch (InterruptedException e) {
    }
    continue;
  }
  try{
	  	String clientSentence;
	  	String capitalizedSentence;
	  	ServerSocket welcomeSocket = new ServerSocket(6789);
		Socket connectionSocket = welcomeSocket.accept();
		BufferedReader inFromClient =
				new BufferedReader(new InputStreamReader(
						connectionSocket.getInputStream()));
		DataOutputStream outToClient = 
				new DataOutputStream(
						connectionSocket.getOutputStream());
		clientSentence = inFromClient.readLine();
		capitalizedSentence =
				clientSentence.toUpperCase() + '\n';
		outToClient.writeBytes(capitalizedSentence);
		welcomeSocket.close();
	    textArea1.append("R: " +
	    		capitalizedSentence + "\n");
	}
  catch (IOException se) {
      textArea1.append(se.toString() + "\n");
      se.printStackTrace();
    }
}
}
}
