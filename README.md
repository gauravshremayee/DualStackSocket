# DualStackSocket
Dual Stack TCP Client Server in C


#To Execute .below are steps

#client side :-
gcc client_ipv6.c -o client_dual_stack

#server side 

gcc server_dual_stack.c -o server_dual_stack

#Server side  ipv4 

server_dual_stack 4001

#client side ipv4 test 
./client_dual_stack <ipv4_address>  4001

#Server side  ipv6

./server_dual_stack 4002


IPv6 TCP Server Started...
Incoming connection from client having IPv6 address: ffff:ffff:xxxx:
Message from client: This is a string from client!

#client side ipv4=6 test 
./client_dual_stack <ipv6_address>  4002
#Sample o/p:-
IPv6 TCP Client Started...

server1 is 8▒▒ and server2 is (null)
Message from server: Server got your message

