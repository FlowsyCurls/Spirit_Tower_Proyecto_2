// A C# program for Client 
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

//Prueba cliente

namespace Client
{

	class Program
	{
		private static byte[] messageSent;
		private static Socket sender;
		private static int byteSent;
		private static byte[] messageReceived;
		private static int byteRecv;

		// Main Method 
		static void Main(string[] args)
		{
			ExecuteClient();
		}

		/**
		 * Envia un mensaje al servidor
		 * 
		 */
		private static void sendMessage(string msg)
        {

			messageSent = Encoding.ASCII.GetBytes(msg);
			byteSent = sender.Send(messageSent);

		}
		/**
		 * 
		 * Recibe un mensaje del servidor
		 * 
		 */

		private static void receiveMessage()
        {
			messageReceived = new byte[1024];

			byteRecv = sender.Receive(messageReceived);
			Console.WriteLine("Message from Server -> {0}", Encoding.ASCII.GetString(messageReceived, 0, byteRecv));

		}

		// ExecuteClient() Method 
		static void ExecuteClient()
		{

			try
			{
				// Establish the remote endpoint 
				// for the socket. This example 
				// uses port 7777 on the local 
				// computer. 
				IPHostEntry ipHost = Dns.GetHostEntry(Dns.GetHostName());
				IPAddress ipAddr = ipHost.AddressList[0];
				IPEndPoint localEndPoint = new IPEndPoint(ipAddr, 7777);

				// Creation TCP/IP Socket using 
				// Socket Class Costructor 
				sender = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

				try{

					// Connect Socket to the remote 
					// endpoint using method Connect() 
					sender.Connect(localEndPoint);

					// We print EndPoint information 
					// that we are connected 
					Console.WriteLine("Socket connected to -> {0} ", sender.RemoteEndPoint.ToString());

					// Creation of messagge that 
					// we will send to Server 

					sendMessage("Primer mensaje");

					receiveMessage();

					sendMessage("1");

					// Close Socket using 
					// the method Close() 
					sender.Shutdown(SocketShutdown.Both);
					sender.Close();
				}

				// Manage of Socket's Exceptions 
				catch (ArgumentNullException ane)
				{
					Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
				}

				catch (SocketException se)
				{
					Console.WriteLine("SocketException : {0}", se.ToString());
				}

				catch (Exception e)
				{
					Console.WriteLine("Unexpected exception : {0}", e.ToString());
				}
			}

			catch (Exception e)
			{
				Console.WriteLine(e.ToString());
			}
		}
	}
}
