#ifndef mpdu_h
#define mpdu_h
#include <cstring>

class mpdu
{ //message pdu
	char hdr[6];
	char sdu[60];

public:
	mpdu() { strcpy(hdr, ""), strcpy(sdu, ""); }
	mpdu(std::string h, std::string s) { strcpy(hdr, h.c_str()), strcpy(sdu, s.c_str()); }
	std::string getHdr() { return hdr; }
	void setHdr(std::string s) { strcpy(hdr, s.c_str()); }
	void setSdu(std::string c) { strcpy(sdu, c.c_str()); }
	std::string getSdu() { return sdu; }
	std::string flatten() { return getHdr() + "@delim@" + getSdu(); } //compresses header and sdu in one std::string. Messages must be sent compressed.
	void unFlatten(std::string s)
	{ //transforms a std::string flatten and saves it into header and sdu
		int del = s.find("@delim@");
		setHdr(s.substr(0, del));
		setSdu(s.substr(del + 7));
	}
	friend std::ostream &operator<<(std::ostream &os, mpdu m)
	{
		return os << "[" << m.getHdr() << ", " << m.getSdu() << "]";
	}
};
#endif