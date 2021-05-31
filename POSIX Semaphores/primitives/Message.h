#ifndef Message_h
#define Message_h

#include "includes.h"

class Message{
	bool last;
	char data [40];
	public:
		Message() {
			strcpy (data,"");
			last=false;
			}
		Message(std::string d) {
			strcpy (data,d.c_str());
			last=false;
			}
		Message (const Message & m){
			strcpy(data,m.data);
			last=false;
			}
		std::string getData(){return data;};
		void setData(std::string d){
		  strcpy (data,d.c_str());
		  last=false;
		}
		
		void setLast(){last=true;};
		bool isLast(){return last;};
	
		friend std::ostream& operator<<(std::ostream& os, Message m){
			os<<"("<<m.getData();
			if (m.isLast()) os<<", last";
			return os<<")";
			} 
};
#endif
