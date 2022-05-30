#define LXML_NO_EXCEPTIONS
#include "include/lxml.hpp"
#include <iostream>

int main(){
    LXml::Library lib;

    const auto xml_str = R"(
        <html>
            <head>
                <title>Hello, World!</title>
                <p>This is a paragraph in head.</p>
            </head>
            <body>
                <h1>Hello, World!</h1>
                <p>This is a paragraph in body.</p>
            </body>
            <attr name="attr1" value="value1"></attr>
        </html>
    )";

    auto xml = LXml::XmlDocument::Parse(xml_str);
    auto root = xml.root_node();
    if(root == nullptr){
        std::cout << "root node is null" << std::endl;
    }
    std::cout << root.name() << std::endl;
    //For each child node
    for(auto node : root.children()){
        std::cout << "node name: " << node.name() << std::endl;
        std::cout << "node value: " << node.value() << std::endl;
    }
    //Try XPath
    auto results = root.xpath("//attr");
    if(results.is_nodeset()){
        std::cout << "XPath result is nodeset" << std::endl;
        for(auto node : results){
            //Try apply xpath on node
            std::cout << "node name: " << node.name() << std::endl;
            std::cout << "node value: " << node.value() << std::endl;
            std::cout << "node attribute: " << node.attribute("name") << std::endl;
        }
    }
    else if(results.is_string()){
        std::cout << results.as_string() << std::endl;
    }

    //Try new 
    auto doc = LXml::XmlDocument::New();
    doc.set_root(LXml::Node::New("root"));
    std::cout << doc.root_node().is_null() << std::endl;
    std::cout << doc.to_string() << std::endl;
}