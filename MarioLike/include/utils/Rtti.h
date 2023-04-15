#pragma once
#include <string>

class Rtti {
public:
	virtual std::string GetClassRttiName() { return ""; };
	virtual std::string GetStaticRttiName() { return ""; };
};

#define DEFINE_RTTI(classname) std::string GetClassRttiName() override {return #classname;} \
							   static std::string GetStaticRName() {return #classname;};
