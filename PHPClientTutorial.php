<?php
/** (1) Set variables such as "host" and "port" and "message" **/
$host = "127.0.0.1";
$port = 6547;
$message = " Hello server ! 123";
// No Timeout 
set_time_limit(0);
/** (2) Create Socket **/
$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");

/** (3) Connect to the server **/
$result = socket_connect($socket, $host, $port) or die("Could not connect toserver\n");

/** (4) Write to server socket **/
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");

/** (5)  Read the response from the server**/
$result = socket_read($socket, 1024) or die("Could not read server response\n");
echo "Reply From Server  :".$result;

/** (6) Close the socket */
socket_close($socket);
?>