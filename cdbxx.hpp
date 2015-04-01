#ifndef U1D846B6D_ABC1_4269_A606_E61EB3A2B4C3
#define U1D846B6D_ABC1_4269_A606_E61EB3A2B4C3

#include <string>

#include <cdb.h>

class cdbxx {
private:
	int fd;
	mutable struct cdb cdb;
public:
	cdbxx(const std::string& filename);
	virtual ~cdbxx();
	std::string operator[](const std::string& key) const;
};

#endif
