http:My_http.o Service.o Handle_head.o Read_File.o SendToClient.o Error_handle.o
		gcc My_http.o Service.o Handle_head.o Read_File.o SendToClient.o Error_handle.o -o http

My_http.o:My_http.c
			gcc -c My_http.c
Service.o:Service.c
			gcc -c Service.c
Handle_head.o:Handle_head.c
			gcc -c Handle_head.c
Read_File.o:Read_File.c
			gcc -c Read_File.c
SendToClient.o:SendToClient.c
			gcc -c SendToClient.c
Error_handle.o:Error_handle.c
			gcc -c Error_handle.c


clean:
	rm  -f  *.o
