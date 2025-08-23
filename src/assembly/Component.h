#pragma once
#include <string>

class Component {
public:
    explicit Component(std::string name);
    const std::string& name() const;
private:
    std::string name_;
};

