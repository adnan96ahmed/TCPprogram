Adnan Ahmed - 0883865
CIS*3210 - Assignment 1 README

References:
The main coding files, TCPserver.c and TCPclient.c - 
CIS*3210 Moodle:
https://moodle.socs.uoguelph.ca/

Code for getaddrinfo() - 
http://beej.us/guide/bgnet/output/html/multipage/getaddrinfoman.html

Code for fread() - 
http://www.cplusplus.com/reference/cstdio/fread/

How to run the program:

- first type ‘make’
- run the server by typing ‘./server ’, followed by the port number: ’12004’
  	-> for example: ./server 12004

- when the server is running, run the client on the same port as the server on its IP or domain name by typing ‘./client ‘, followed by the server-IP or domain name and port number: ‘SERVER-IP:PORT’, followed by the file name to read from: ‘test.txt’, followed by an optional argument of the buffer length: ’10’
	-> for example: ./client 127.0.0.1:12004 test.txt 10

- run the script when the server is running, by typing ‘./pythonScript.py ’, followed by the number of clients to run: ’10’, followed by the server-IP or domain name and port number: ‘SERVER-IP:PORT’, followed by the file name to read from: ‘test.txt’, followed by an optional argument of the buffer length: ’10’
	-> for example: ./pythonScript.py 10 127.0.0.1:12004 test.txt 10

Limitations:
The highest and also the default buffer length size is 4096 bytes, this is because the server file has a fixed size for how many bytes it will receive. 

