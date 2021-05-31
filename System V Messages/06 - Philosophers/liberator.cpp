#include "includes.h"

using namespace std;

int main(int argc, char *argv[])
{
	sv_mq control("control");//eliminates the general message queue
	mpdu message;
	message.setHdr(END);
	control.send(message);
}