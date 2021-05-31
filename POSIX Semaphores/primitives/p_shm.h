#include "includes.h"
#ifndef SHM_H
#define SHM_H
#define BUFSIZE 8192

class p_shm
{
  std::string key; 
  int shm;
  public:
    p_shm(std::string givenKey="/default");
    void del();
    int getShm(){return shm;}
    void * map(int size=BUFSIZE);
    std::string getKey(){return key;}
    friend std::ostream& operator <<(std::ostream& os, p_shm shm);
};

p_shm::p_shm(std::string givenKey)
{
  if (givenKey[0] != '/') givenKey='/'+givenKey;
  key=givenKey;
  shm=shm_open(key.c_str(),O_RDWR|O_CREAT,S_IREAD|S_IWRITE); //permits 0600
  if (shm==-1)
  {
		perror ("cannot open/create shared memory");
		std::cerr<<"Key <"<<key<<"> "<<std::endl;
		exit(1);
  }
}

void p_shm::del()
{
  int retcode;
  retcode=shm_unlink(key.c_str());
  if (retcode==-1)
  {
		perror ("Cannot erase shared memory");
		std::cerr<<"Key<"<<key<<"> "<<std::endl; 
		exit(1);
  }
}

std::ostream& operator <<(std::ostream& os, p_shm sharedMemory)
{
  int retcode;
  struct stat value;
  retcode=fstat(sharedMemory.shm, &value);
  if (retcode==-1)
  {
    perror ("cannot do fstat() to the area ");
    std::cerr<<"Key<"<<sharedMemory.key<<"> "<<std::endl; 
    exit(1);
  }
  return os<<"Shared Memory <"<<sharedMemory.key<<">("<<value.st_size<<")";
}

void * p_shm::map(int size)
{
	ftruncate(shm,size);
	return(
		mmap (NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,shm,0));
}

#endif
