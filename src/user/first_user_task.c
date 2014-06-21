#include <user.h>

//static int start, end;

void
idleTask(){
	int x;

	while (1){
		//need to figure out how to exit idleTask
	}
}

void testGetcCom2(){
	int i;
	for(i = 0; 1; i++){
		char c = getc(COM2);
		putc(COM2, c);
		//bwputc(COM2, c);
		//bwprintf(COM2, "%d\r\n", i);
	}
	//bwprintf(COM2, "testGetcCom2 exiting...\r\n");
	Exit();
}


void
firstUserTask()
{
	/* DO NOT CHANGE THE ORDER OF THE FOLLOWING FUNCTION CALLS	*/ 
	int nameServerTID =  Create(2, nameServer);
	bwprintf( COM2, "%s\033[HNameServer initialized.\r\nTID of NameServer: %u(should be 1)\r\n", clearScreen, nameServerTID);
	int clockServerTID = Create(2, clockServer);
	bwprintf( COM2, "ClockServer initialized.\r\nTID of ClockServer: %u(should be 2)\r\n", clockServerTID);
	int uart2ServerTID = Create(2, UART2_Server);
	bwprintf( COM2, "UART2_Server initialized.\r\nTID of UART2_Server: %u(should be 4)\r\n", uart2ServerTID);

	Create(3, testGetcCom2);

	Create(16, idleTask);

	Exit();
}
