#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cdb.h>

#include "cdbxx.hpp"

cdbxx::cdbxx(const std::string& filename)
{
	fd = ::open(filename.c_str(), O_RDONLY);
	if (fd == -1) {
		throw std::system_error(errno, std::system_category());
	}
	if (cdb_init(&cdb, fd) != 0) {
		::close(fd);
		throw std::runtime_error("unable to initialize cdb");
	}
}

cdbxx::~cdbxx()
{
	cdb_free(&cdb);
	close(fd);
}

std::string cdbxx::operator[](const std::string& key) const
{
	if (cdb_find(&cdb, key.c_str(), key.length()) > 0) {
		unsigned vpos = cdb_datapos(&cdb);
		unsigned vlen = cdb_datalen(&cdb);
		char val[vlen];
		cdb_read(&cdb, val, vlen, vpos);
		return std::string(val, vlen);
	} else {
		throw std::out_of_range("key not found");
	}
}

/*
int main() {
	cdbxx c("cidades");
	for (int i = 0; ; i++) {
		try {
			std::cout << c[std::to_string(i)] << std::endl;
		} catch (std::out_of_range& e) {
			break;
		}
	}
}
*/
