all: tcp udp

tcp: tcp_client tcp_server

udp: udp_client udp_server

tcp_client: tcpclient.c
	gcc -o tcpclient.out tcpclient.c

udp_client: udpclient.c
	gcc -o udpclient.out udpclient.c

tcp_server: tcpserver.c
	gcc -o tcpserver.out tcpserver.c

udp_server: udpserver.c
	gcc -o udpserver.out udpserver.c

clean:
	rm *.out *.o -f
	clear