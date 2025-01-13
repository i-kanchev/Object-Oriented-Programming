#include "Customer.h"

Customer::Customer(const size_t id, const String& name, const String& address)
{
    this->id = id;
    this->name = name;
    this->address = address;
}

const size_t Customer::getId() const
{
    return id;
}

const String& Customer::getName() const
{
    return name;
}

Customer* Customer::clone() const
{
    return new Customer(*this);
}
