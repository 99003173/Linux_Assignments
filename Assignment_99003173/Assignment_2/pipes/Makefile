all: client_pipe.c server_pipe.c
	gcc $< -o client.out
	gcc server_pipe.c -o server.out
client.out: client_pipe.c
	gcc $^ -o $@
server.out: server_pipe.c
	gcc $^ -o $@
rm:
	rm -rf *.out CS_FIFO
