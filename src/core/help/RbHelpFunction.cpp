#include "RbHelpFunction.h"

using namespace RevBayesCore;

const std::vector<std::string>& RbHelpFunction::getAliases( void ) const
{
    // return a const reference to the internal value
    return aliases;
}

const std::vector<RbHelpArgument>& RbHelpFunction::getArguments( void ) const
{
    // return a const reference to the internal value
    return arguments;
}


const std::string& RbHelpFunction::getAuthor( void ) const
{
    // return a const reference to the internal value
    return author;
}


const std::vector<std::string>& RbHelpFunction::getDescription( void ) const
{
    // return a const reference to the internal value
    return description;
}


const std::vector<std::string>& RbHelpFunction::getDetails( void ) const
{
    // return a const reference to the internal value
    return details;
}


const std::string& RbHelpFunction::getExample( void ) const
{
    // return a const reference to the internal value
    return example;
}


const std::string& RbHelpFunction::getName( void ) const
{
    // return a const reference to the internal value
    return name;
}


const std::vector<RbHelpReference>& RbHelpFunction::getReferences( void ) const
{
    // return a const reference to the internal value
    return references;
}


const std::string& RbHelpFunction::getReturnValue( void ) const
{
    // return a const reference to the internal value
    return returnValue;
}


const std::vector<std::string>& RbHelpFunction::getSeeAlso( void ) const
{
    // return a const reference to the internal value
    return seeAlso;
}


const std::string& RbHelpFunction::getTitle( void ) const
{
    // return a const reference to the internal value
    return title;
}


const std::string& RbHelpFunction::getUsage( void ) const
{
    // return a const reference to the internal value
    return usage;
}


void RbHelpFunction::setAliases(const std::vector<std::string> &a)
{
    // overwrite the internal value with the new value
    aliases = a;
}


void RbHelpFunction::setArguments(const std::vector<RbHelpArgument> &a)
{
    // overwrite the internal value with the new value
    arguments = a;
}


void RbHelpFunction::setAuthor(const std::string &a)
{
    // overwrite the internal value with the new value
    author = a;
}

void RbHelpFunction::setDescription(const std::vector<std::string> &d)
{
    // overwrite the internal value with the new value
    description = d;
}


void RbHelpFunction::setDetails(const std::vector<std::string> &d)
{
    // overwrite the internal value with the new value
    details = d;
}


void RbHelpFunction::setExample(const std::string &e)
{
    // overwrite the internal value with the new value
    example = e;
}


void RbHelpFunction::setName(const std::string &n)
{
    // overwrite the internal value with the new value
    name = n;
}


void RbHelpFunction::setSeeAlso(const std::vector<std::string> &s)
{
    // overwrite the internal value with the new value
    seeAlso = s;
}


void RbHelpFunction::setReferences(const std::vector<RbHelpReference> &r)
{
    // overwrite the internal value with the new value
    references = r;
}


void RbHelpFunction::setReturnValue(const std::string &r)
{
    // overwrite the internal value with the new value
    returnValue = r;
}


void RbHelpFunction::setTitle(const std::string &t)
{
    // overwrite the internal value with the new value
    title = t;
}


void RbHelpFunction::setUsage(const std::string &u)
{
    // overwrite the internal value with the new value
    usage = u;
}