#include "YAML.h"
#include "StringUtilities.h"

using namespace YAML;

Attribute::Attribute( std::string v ) : Element(v)
{
}

Attribute::Attribute( std::string v, std::vector<Element*> it ) : Element(v)
{
    if ( it.empty() == false )
    {
        children.push_back( new Node(it) );
    }
}

Attribute::~Attribute()
{
    for(size_t i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
}

Attribute::Attribute( std::string v, std::string it ) : Element(v)
{
    if ( it != "" )
    {
        Node* node = new Node;

        node->elements.push_back( new Element(it) );

        children.push_back(node);
    }
}

Attribute::Attribute( std::string v, std::vector<std::string> it ) : Element(v)
{
    if ( it.empty() == false )
    {
        Node* node = new Node;

        for(size_t i = 0; i < it.size(); i++)
        {
            node->elements.push_back( new Element(it[i]) );
        }

        children.push_back(node);
    }
}

Node::Node()
{
}

Node::Node(const std::vector<Element*>& it) : elements(it)
{
}

Node::~Node()
{
    for(size_t i = 0; i < elements.size(); i++)
    {
        delete elements[i];
    }
}

std::string Node::render(size_t depth)
{
    std::string result;

    if( dynamic_cast<Attribute*>(elements.front()) == NULL )
    {
        if( elements.size() == 1)
        {
            std::string v = elements.front()->value;
            StringUtilities::replaceSubstring(v,"\n","\\n");
            StringUtilities::replaceSubstring(v,"'","''");
            result += "'" + v + "'\n";
        }
        else
        {
            std::string indent(depth*4, ' ');

            for(size_t i = 0; i < elements.size(); i++)
            {
                std::string v = elements[i]->value;
                StringUtilities::replaceSubstring(v,"\n","\\n");
                StringUtilities::replaceSubstring(v,"'","''");

                std::string pad = "- ";

                result += indent + pad + "'" + v + "'\n";
            }
        }
    }
    else
    {
        std::string indent(depth*4, ' ');

        // go through each element of the node
        for(size_t i = 0; i < elements.size(); i++)
        {
            std::string pad = (i == 0 ? "- " : "  ");

            // create the first line for the element
            result += indent + pad + elements[i]->value + ":";

            // if this is an entry, it may have child elements
            Attribute* attribute = dynamic_cast<Attribute*>(elements[i]);

            std::vector<Node*> children = attribute->children;

            if ( children.size() == 1 && children.front()->elements.size() == 1)
            {
                result += " ";
            }
            else
            {
                result += "\n";
            }

            for(size_t j = 0; j < children.size(); j++)
            {
                result += children[j]->render(depth + 1);
            }
        }
    }

    return result;
}
