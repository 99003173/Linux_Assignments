all: mq_client.c mq_server.c
	gcc $< -lrt -o c.out
	gcc mq_server.c -lrt -o s.out
rm:
	rm -rf *.out 
