/*
 * @file Hmac.h
 * @brief Hash-based Message Authentication Code.
 *          Using SHA1 for message digest algorithm.
 *
 * @version 1.0
 * @date Tue Sep 25 17:17:08 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef digest_Hmac_H_
#define digest_Hmac_H_


#include <string>

#include <openssl/hmac.h>


namespace ossfs
{


class Hmac
{
public:
    static const unsigned int DIGEST_LENGTH;
    static const unsigned int HEX_DIGEST_LENGTH;

public:
    Hmac();

    ~Hmac();

    /**
     * @brief Get the digest in one call.
     *
     * @param key
     * @param data
     *
     * @return
     */
    static std::string hmac(
        const std::string &key,
        const std::string &data
    );

    /**
     * @brief Initialize hmac context.
     *
     * @param key
     *
     * @return 
     */
    bool init(const std::string &key);

    /**
     * @brief Add new data in order to compute message digest.
     *
     * @param data
     *
     * @return 
     */
    bool update(const std::string &data);

    /**
     * @brief Finalize the computing.
     *
     * @return 
     */
    bool final();

    /**
     * @brief get raw digest after init, update and final
     *
     * @return 
     */
    std::string digest() const;

    /**
     * @brief get digest in hex format
     *
     * @return 
     */
    std::string digestHex() const;

private:
    HMAC_CTX _ctx;
    unsigned char *_md;
};


}  // namespace ossfs


#endif  // digest_Hmac_H_


