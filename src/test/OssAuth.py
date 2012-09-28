#!/bin/python

import base64
import hmac
import sha

h = hmac.new("OtxrzxIsfpFjA7SwPzILwy8Bw21TLhquhboDYROV",
             "PUT\nc8fdb181845a4ca6b8fec737b3581d76\ntext/html\nThu, 17 Nov 2005 18:49:58 GMT\nx-oss-magic:abracadabra\nx-oss-meta-author:foo@bar.com\n/quotes/nelson", sha)

# print h.digest().strip()
print h.digest()

print base64.encodestring(h.digest()).strip()
