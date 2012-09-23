/*
 * @file Xml.h
 * @brief A very simple wrapper for libxml2.
 *
 * @version 1.0
 * @date Wed Jul 18 19:58:22 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef xml_Xml_H_
#define xml_Xml_H_

#include <string>
#include <list>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

namespace ossfs
{

typedef xmlNode XmlNode;

class Xml
{
public:
    Xml();

    virtual ~Xml();

    /**
     * @brief Load xml document from a disk file.
     *
     * @param file Disk file name.
     *
     * @return Root node of xml document. NULL if failed.
     */
    XmlNode *loadFile(const std::string &file);

    /**
     * @brief Load xml document from memory area.
     *
     * @param buf Buffer containing xml document.
     * @param size Buffer length.
     *
     * @return Root node fo xml document. NULL if failed.
     */
    XmlNode *loadMemory(const char *buf, int size);

    /**
     * @brief Dump current node and all its descendant to specified buffer.
     *
     * @param curNode  Current node.
     * @param buf [out]  Buffer to store xml document.
     *
     * @return
     */
    bool saveToBuffer(XmlNode *curNode, std::string *buf) const;

    /**
     * @brief Dump the whole xml document to specified buffer.
     *
     * @param buf [out] Buffer to store xml document.
     *
     * @return
     */
    bool saveToBuffer(std::string *buf) const;

    /**
     * @brief Save the whole xml document to specified disk file.
     *
     * @param file Disk file name.
     *
     * @return 0 if a success, or -1
     */
    bool saveToFile(const std::string &file) const;

    /**
     * @brief Create a new xml document in memory from scratch.
     *
     * @param rootName Name of root node.
     *
     * @return Root node, or NULL if failed.
     */
    XmlNode *createDocument(const std::string &rootName);

    /**
     * @brief Get root node of current xml document.
     *
     * @return Root node, NULL if failed.
     */
    XmlNode *getRootNode() const;

    /**
     * @brief Get parent node of current node.
     *
     * @param curNode Current node.
     *
     * @return Parent node, NULL if failed.
     */
    XmlNode *getParentNode(XmlNode *curNode) const;

    /**
     * @brief Get first child of current node.
     *        Note: Comment, Newline or Indent in xml document may be parsed
     *              as a node. So result of this method may be confused.
     *
     * @param curNode Current node.
     *
     * @return First child node, NULL if failed.
     */
    XmlNode *getChildNode(XmlNode *curNode) const;

    /**
     * @brief Get all children of current node.
     *
     * @param curNode Current node.
     * @param nodeList [out] Child nodes list.
     *
     * @return
     */
    bool getChildNodes(
        XmlNode *curNode,
        std::list<XmlNode *> *nodeList
    ) const;

    /**
     * @brief Get a child of current node whose name is "nodeName",
     *          if there are several nodes have the name "nodeName",
     *          return the first one.
     *
     * @param curNode Current node.
     * @param nodeName Name of child node.
     *
     * @return First child node named "nodeName", NULL if failed.
     */
    XmlNode *getChildNodeByNodeName(
        XmlNode *curNode,
        const std::string &nodeName
    ) const;

    /**
     * @brief Get all children of current node whose name is "nodeName".
     *
     * @param curNode Current node.
     * @param nodeName Name of child node.
     * @param nodeList [out] Child nodes list.
     *
     * @return
     */
    bool getChildNodesByNodeName(
        XmlNode *curNode,
        const std::string &nodeName,
        std::list<XmlNode *> *nodeList
    ) const;

    /**
     * @brief Get node value of a specified child of current node.
     *
     * @param curNode Current node.
     * @param childNodeName Child node name.
     *
     * @return node value, empty if failed or node value is empty itself.
     */
    std::string getChildNodeValueByNodeName(
        XmlNode *curNode,
        const std::string &childNodeName
    ) const;

    bool getChildNodeValueByNodeName(
        XmlNode *curNode,
        const std::string &childName,
        std::string *value
    ) const;

    /**
     * @brief Get node value.
     *
     * @param curNode
     *
     * @return node value, empty if failed or node value is empty itself.
     */
    std::string getNodeValue(XmlNode *curNode) const;

    bool getNodeValue(XmlNode *curNode, std::string *value) const;

    /**
     * @brief Set current node value.
     *
     * @param curNode
     * @param value
     *
     * @return
     */
    bool setNodeValue(XmlNode *curNode, const std::string &value);

    /**
     * @brief Add a child node to "pParentNode", whose name is "nodeName"
     *          and value is "nodeValue".
     *
     * @param parentNode
     * @param nodeName
     * @param nodeValue
     *
     * @return
     */
    XmlNode *addChildNode(
        XmlNode *parentNode,
        const std::string &nodeName,
        const std::string &nodeValue
    );

    /**
     * @brief Add a child node named "nodeName" to "pParentNode".
     *
     * @param parentNode
     * @param nodeName
     *
     * @return
     */
    XmlNode *addChildNode(
        XmlNode *parentNode,
        const std::string &nodeName
    );

    /**
     * @brief Add node "pChildNode" to "pParentNode" as its children.
     *
     * @param parentNode
     * @param childNode
     *
     * @return
     */
    XmlNode *addChildNode(XmlNode *parentNode, XmlNode *childNode);

    /**
     * @brief Query a node by XPath.
     *
     * @param xpath
     *
     * @return
     */
    XmlNode *getNodeByXPath(const std::string &xpath) const;

    /**
     * @brief Query a node by XPath using relative path.
     *
     * @param curNode
     * @param xpath
     *
     * @return
     */
    XmlNode *getNodeByXPath(
        XmlNode *curNode,
        const std::string &xpath
    ) const;

    /**
     * @brief Query several nodes by XPath expression.
     *
     * @param xpath
     * @param nodeList [out]
     *
     * @return
     */
    bool getNodesByXPath(
        const std::string &xpath,
        std::list<XmlNode *> *nodeList
    ) const;

    bool getNodesByXPath(
        XmlNode *curNode,
        const std::string &xpath,
        std::list<XmlNode *> *nodeList
    ) const;

    /**
     * @brief Query node value by XPath.
     *
     * @param xpath
     *
     * @return node value, empty if failed or node value is empty itself
     */
    std::string getNodeValueByXPath(
        const std::string &xpath
    ) const;

    bool getNodeValueByXPath(
        const std::string &xpath,
        std::string *value
    ) const;

    /**
     * @brief Query node value by relative XPath.
     *
     * @param curNode current node
     * @param xpath xpath expression relative to current node
     *
     * @return
     */
    std::string getNodeValueByXPath(
        XmlNode *curNode,
        const std::string &xpath
    ) const;

    bool getNodeValueByXPath(
        XmlNode *curNode,
        const std::string &xpath,
        std::string *value
    ) const;

private:
    xmlDoc *_doc;
};

}  // namespace ossfs

#endif  // xml_Xml_H_

