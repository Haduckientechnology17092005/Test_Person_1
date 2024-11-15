#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "person.h"
#include "FileManage.h"


Person* login(const std::string& username, const std::string& password);

#endif