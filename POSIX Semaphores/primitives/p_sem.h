#include "includes.h"
#ifndef SEM_H
#define SEM_H

class p_sem
{
  std::string key;
  sem_t *sem;
  public:
    p_sem(std::string cla="/default",int initialValue=1);
    void del();
    std::string getname() {return key;}
    sem_t* getsem()  {return sem;}
    void post();
    void wait();
    friend std::ostream& operator <<(std::ostream& os, p_sem sem);
 };

p_sem::p_sem(std::string cla,int valorInicial)
{
  if (cla[0] != '/') cla='/'+cla;
  key=cla;
  sem=sem_open(key.c_str(),O_RDWR|O_CREAT,S_IREAD|S_IWRITE,valorInicial); //permits 0600
  if (sem==SEM_FAILED)
  {
		perror ("cannot open/create semaphore");
		std::cerr<<"Semaphore <"<<key<<"> "<<std::endl;
		exit(1);
  }
}

void p_sem::del()
{
  int retcode;
  retcode=sem_close (sem);
    if (retcode==-1){
 		perror ("Cannot close semaphore");
		std::cerr<<"Semaphore<"<<key<<"> "<<std::endl; 
 		exit(1);}
  retcode=sem_unlink(key.c_str());
  if (retcode==-1)
  {
		perror ("Cannot erase semaphore");
		std::cerr<<"Queue<"<<key<<"> "<<std::endl; 
		exit(1);
  }
}

void p_sem::post()
{
  int retcode;
  retcode=sem_post(sem);
  if (retcode==-1)
  {
 		perror ("cannot post to semaphore");
		std::cerr<<"Semaphore<"<<key<<"> "<<std::endl; 
 		exit(1);
  }
}

void p_sem::wait()
{
  int retcode;
  retcode=sem_wait(sem);
  if (retcode==-1)
  {
 		perror ("Cannot wait on semaphore");
		std::cerr<<"Semaphore<"<<key<<"> "<<std::endl; 
 		exit(1);
  }
}

std::ostream& operator <<(std::ostream& os, p_sem sem)
{
  int value, retcode;
  retcode=sem_getvalue(sem.sem, &value);
    if (retcode==-1)
    {
    perror ("Cannot obtain value of semaphore");
    std::cerr<<"Semaphore<"<<sem.key<<"> "<<std::endl; 
    exit(1);
  }
  return os<<"Semaphore "<<sem.key<<"("<<value<<")";
}

#endif
