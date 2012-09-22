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
     * @param pBuf Buffer containing xml document.
     * @param size Buffer length.
     *
     * @return Root node fo xml document. NULL if failed.
     */
    XmlNode *loadMemory(const char *pBuf, int size);

    /**
     * @brief Dump current node and all its descendant to specified buffer.
     *
     * @param pCurNode  Current node.
     * @param pBuf [out]  Buffer to store xml document.
     *
     * @return 0 if a success, or -1
     */
    int saveToBuffer(XmlNode *pCurNode, std::string *pBuf) const;

    /**
     * @brief Dump the whole xml document to specified buffer.
     *
     * @param pBuf [out] Buffer to store xml document.
     *
     * @return 0 if a success, or -1
     */
    int saveToBuffer(std::string *pBuf) const;

    /**
     * @brief Save the whole xml document to specified disk file.
     *
     * @param file Disk file name.
     *
     * @return 0 if a success, or -1
     */
    int saveToFile(const std::string &file) const;

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
     * @param pCurNode Current node.
     *
     * @return Parent node, NULL if failed.
     */
    XmlNode *getParentNode(XmlNode *pCurNode) const;

    /**
     * @brief Get first child of current node.
     *        Note: Comment, Newline or Indent in xml document may be parsed
     *              as a node. So result of this method may be confused.
     *
     * @param pCurNode Current node.
     *
     * @return First child node, NULL if failed.
     */
    XmlNode *getChildNode(XmlNode *pCurNode) const;

    /**
     * @brief Get all children of current node.
     *
     * @param pCurNode Current node.
     * @param pNodeList [out] Child nodes list.
     *
     * @return 0 if a success, or -1
     */
    int getChildNodes(
        XmlNode *pCurNode,
        std::list<XmlNode *> *pNodeList
    ) const;

    /**
     * @brief Get a child of current node whose name is "nodeName",
     *          if there are several nodes have the name "nodeName",
     *          return the first one.
     *
     * @param pCurNode Current node.
     * @param nodeName Name of child node.
     *
     * @return First child node named "nodeName", NULL if failed.
     */
    XmlNode *getChildNodeByNodeName(
        XmlNode *pCurNode,
        const std::string &nodeName
    ) const;

    /**
     * @brief Get all children of current node whose name is "nodeName".
     *
     * @param pCurNode Current node.
     * @param nodeName Name of child node.
     * @param pNodeList [out] Child nodes list.
     *
     * @return 0 if a success, or -1
     */
    int getChildNodesByNodeName(
        XmlNode *pCurNode,
        const std::string &nodeName,
        std::list<XmlNode *> *pNodeList
    ) const;

    /**
     * @brief Get node value of a specified child of current node.
     *
     * @param pCurNode Current node.
     * @param childNodeName Child node name.
     *
     * @return node value, empty if failed or node value is empty itself.
     */
    std::string getChildNodeValueByNodeName(
        XmlNode *pCurNode,
        const std::string &childNodeName
    ) const;

    /**
     * @brief Get node value.
     *
     * @param pCurNode
     *
     * @return node value, empty if failed or node value is empty itself.
     */
    std::string getNodeValue(XmlNode *pCurNode) const;

    /**
     * @brief Set current node value.
     *
     * @param pCurNode
     * @param value
     *
     * @return
     */
    int setNodeValue(XmlNode *pCurNode, const std::string &value);

    /**
     * @brief Add a child node to "pParentNode", whose name is "nodeName"
     *          and value is "nodeValue".
     *
     * @param pParentNode
     * @param nodeName
     * @param nodeValue
     *
     * @return
     */
    XmlNode *addChildNode(
        XmlNode *pParentNode,
        const std::string &nodeName,
        const std::string &nodeValue
    );

    /**
     * @brief Add a child node named "nodeName" to "pParentNode".
     *
     * @param pParentNode
     * @param nodeName
     *
     * @return
     */
    XmlNode *addChildNode(
        XmlNode *pParentNode,
        const std::string &nodeName
    );

    /**
     * @brief Add node "pChildNode" to "pParentNode" as its children.
     *
     * @param pParentNode
     * @param pChildNode
     *
     * @return
     */
    XmlNode *addChildNode(XmlNode *pParentNode, XmlNode *pChildNode);

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
     * @param pCurNode
     * @param xpath
     *
     * @return
     */
    XmlNode *getNodeByXPath(
        XmlNode *pCurNode,
        const std::string &xpath
    ) const;

    /**
     * @brief Query several nodes by XPath expression.
     *
     * @param xpath
     * @param pNodeList [out]
     *
     * @return 0 if a success, or -1
     */
    int getNodesByXPath(
        const std::string &xpath,
        std::list<XmlNode *> *pNodeList
    ) const;

    int getNodesByXPath(
        XmlNode *pCurNode,
        const std::string &xpath,
        std::list<XmlNode *> *pNodeList
    ) const;

    /**
     * @brief Query node value by XPath.
     *
     * @param xpath
     * @param pValue [out]
     *
     * @return node value, empty if failed or node value is empty itself
     */
    std::string getNodeValueByXPath(
        const std::string &xpath
    ) const;

    std::string getNodeValueByXPath(
        XmlNode *pCurNode,
        const std::string &xpath
    ) const;

private:
    xmlDoc *_pDoc;
};

}  // namespace ossfs

#endif  // xml_Xml_H_

