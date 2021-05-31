#include "includes.h"
#include "mpdu.h"
#ifndef SV_MQ_H
#define SV_MQ_H
#define K 1024
#define MAXMSG (6 * K + sizeof(long)) //message maximum size

#ifndef __USE_GNU
struct msgbuf
{
  long mtype;    /* message type, must be > 0 */
  char mtext[1]; /* message data */
};
#endif

class sv_mq
{ //message queue en system V
  std::string keyString;
  key_t ktKey;
  int mq; //mqd message queue descriptor
public:
  sv_mq(std::string givenKey = "/default");
  void del();
  std::string getName() { return keyString; }
  int getmq() { return mq; }
  void send(mpdu msg);
  mpdu *receive();
  friend std::ostream &operator<<(std::ostream &os, sv_mq mq);
};

sv_mq::sv_mq(std::string givenKey)
{
  int oflag;
  oflag = 0644 | IPC_CREAT;
  if (givenKey[0] != '/')
    givenKey = '/' + givenKey;
  keyString = "/tmp" + givenKey;
  std::string cmd = "touch " + keyString;
  system(cmd.c_str()); // in System V the key MUST be a file
  ktKey = ftok(keyString.c_str(), 1);
  mq = msgget(ktKey, oflag);
  if (mq == -1)
  {
    std::cerr << "can't open/create queue" << std::endl;
    std::cerr << "Queue <" << keyString << "," << mq << "> " << std::endl;
    exit(1);
  }
}

void sv_mq::del()
{
  int retcode;
  retcode = msgctl(mq, IPC_RMID, NULL);
  if (retcode == -1)
  {
    std::cerr << "Can't close queue" << std::endl;
    std::cerr << "Queue<" << keyString << "," << mq << "> " << std::endl;
    exit(1);
  }
  std::string cmd = "rm " + keyString;
  system(cmd.c_str());
}

void sv_mq::send(mpdu msg)
{
  struct msgbuf *messageBuffer;
  int type = 1;
  size_t messageLength = msg.flatten().size();
  // char * s_msg=reinterpret_cast<char *>(&msg);
  messageBuffer = static_cast<struct msgbuf *>(calloc(sizeof(long) + messageLength, sizeof(char)));
  messageBuffer->mtype = type;
  // change to memcpy
  memcpy(messageBuffer->mtext, msg.flatten().c_str(), messageLength);
  int retcode;
  //cout<<"Sending ("<<messageBuffer->mtype<<","<<messageBuffer->mtext<<"messageLength="<<messageLength<<")"<<std::endl;
  retcode = msgsnd(mq, messageBuffer, messageLength, 0);
  if (retcode == -1)
  {
    std::cerr << "Couldn't send message" << std::endl;
    std::cerr << "Queue<" << keyString << "," << mq << "> " << std::endl;
    exit(1);
  }
  //free memory
  free((void *)messageBuffer);
}

mpdu *sv_mq::receive()
{
  struct msgbuf *buffer;
  int long_buf = MAXMSG;
  buffer = static_cast<struct msgbuf *>(malloc(MAXMSG));
  int messageSize = 0;
  int type = 1;
  messageSize = msgrcv(mq, buffer, MAXMSG, type, 0); //espera mensaje si no hay en la cola
  if (messageSize == -1)
  {
    std::cerr << "Couldn't receive message." << std::endl;
    std::cerr << "Queue<" << keyString << "," << mq << "> " << std::endl;
    exit(1);
  }
  //  cout<<"Received <"<<buffer->mtext<<">, l="<<messageSize<<std::endl;
  buffer->mtext[messageSize] = '\0'; //add end of c_string
                                     //  cout<<"Trunk <"<<buffer->mtext<<">, l="<<messageSize<<std::endl;

  mpdu *messagePDU = new mpdu();
  messagePDU->unFlatten(buffer->mtext);
  free((void *)buffer);
  return messagePDU;
}

std::ostream &operator<<(std::ostream &os, sv_mq msgq)
{
  msqid_ds mqid;
  msgctl(msgq.mq, IPC_STAT, &mqid);
  return os << "(queue " << msgq.mq << "<" << msgq.keyString << "> " << mqid.msg_qnum << " messages )"
            << "[send " << mqid.msg_lspid << " receive " << mqid.msg_lrpid << "]";
}
#endif
