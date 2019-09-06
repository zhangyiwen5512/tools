# 1

    主机--ISP--Internet
    主机host  端系统end system
    主机--通信链路link或交换机switch--连接
    两种交换机：路由器router 链路层交换机link-layer switch

## 网络核心

    端系统和交换机和链路构成
    分组交换--报文，链路交换--帧
    链路交换：频分复用时分复用
    对比 分组交换优于链路交换
    结点总时延=结点处理时延+排队时延+传输时延+传播时延

## OSI7层模型

    封装，首部字段+有效载荷字段

### 应用层，应用层的信息分组称为报文message

    HTTP协议，web的应用层协议，使用TCP，默认端口80
    无状态协议。采用非持续连接，发送一个对象后关闭连接。采用持续连接，HTTP1.1之后可以使用，保持TCP连接打开
    RFC2616 HTTP1.1，RFC7520 HTTP/2。由客户和服务器程序实现。web文档由对象组成，一个对象是一个小文件。一个html基本文件和多个引用对象组成。html基本文件通过通过URL找到其他对象。URL = 主机名 + 路径名
    CR LF被定义为行结束符。头文件字段可被折叠到多行上，只要下一行开头是空白符。空白符可以被视为SP。在解释字段值或向下游发送前，接收方一个SP可代替任意空白区域

### HTTP参数

    版本 HTTP/1.1。<major>.<minor> major在协议中的消息格式变化时增加 minor在加入新特性时增加。proxy/gateway接收到了更高版本的请求，或降低版本，或返回一个错误，或切换到隧道行为。当HTTP/1.1消息传给HTTP/1.0时，会重新构造消息废弃新的特性，被解读为HTTP/1.0
    client的版本不应高于server支持的最高版本。client仅在尝试发送一次失败后降低版本发送。
    505版本不匹配，server发送HTTP/1.0,若其判断client处理规范错误

    URI统一资源定位符，绝对地址始终以方案名称及冒号开头，URI太长可能返回414
    URL（http://host[:port][abs_path[?query]]），默认80端口，若是相对地址加上/
    分块编码 chunk = 块大小 CRLF 块数据 CRLF。last-chunk = “0” 【chunk—extension】CRLF。trailer = *(entity-header CRLF)在末尾包含额外到HTTP表头字段
    HTTP消息 =   开始行
                头文件字段 \r\n
                \r\n
                消息体

#### HTTP请求报文

    SP = 空格 = 20
    GET /wireshark-labs/INTRO-wireshark-file1.html HTTP/1.1\r\n
    Host: gaia.cs.umass.edu\r\n
    Connection: keep-alive\r\n
    Upgrade-Insecure-Requests: 1\r\n
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.132 Safari/537.36\r\n
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n
    Accept-Encoding: gzip, deflate\r\n
    Accept-Language: zh-CN,zh;q=0.9\r\n
    \r\n 

    0000   a0 63 91 3e 71 61 a4 5e 60 ef 99 9f 08 00 45 00   .c.>qa.^`.....E.
    0010   02 06 00 00 40 00 40 06 b8 f1 0a 0a 00 73 80 77   ....@.@......s.w
    0020   f5 0c e2 e8 00 50 b0 b3 57 63 e8 8f 08 49 80 18   .....P..Wc...I..
    0030   08 16 7e 20 00 00 01 01 08 0a 4d fc 7b 61 7a 36   ..~ ......M.{az6
    0040   0f f4 47 45 54 SP 2f 77 69 72 65 73 68 61 72 6b   ..GET /wireshark
    0050   2d 6c 61 62 73 2f 49 4e 54 52 4f 2d 77 69 72 65   -labs/INTRO-wire
    0060   73 68 61 72 6b 2d 66 69 6c 65 31 2e 68 74 6d 6c   shark-file1.html
    0070   SP 48 54 54 50 2f 31 2e 31 \r \n 48 6f 73 74 3a    HTTP/1.1..Host:
    0080   SP 67 61 69 61 2e 63 73 2e 75 6d 61 73 73 2e 65    gaia.cs.umass.e
    0090   64 75 \r \n 43 6f 6e 6e 65 63 74 69 6f 6e 3a SP   du..Connection: 
    00a0   6b 65 65 70 2d 61 6c 69 76 65 \r \n 55 70 67 72   keep-alive..Upgr
    00b0   61 64 65 2d 49 6e 73 65 63 75 72 65 2d 52 65 71   ade-Insecure-Req
    00c0   75 65 73 74 73 3a SP 31 \r \n 55 73 65 72 2d 41   uests: 1..User-A
    00d0   67 65 6e 74 3a SP 4d 6f 7a 69 6c 6c 61 2f 35 2e   gent: Mozilla/5.
    00e0   30 SP 28 4d 61 63 69 6e 74 6f 73 68 3b SP 49 6e   0 (Macintosh; In
    00f0   74 65 6c SP 4d 61 63 SP 4f 53 SP 58 SP 31 30 5f   tel Mac OS X 10_
    0100   31 34 5f 34 29 SP 41 70 70 6c 65 57 65 62 4b 69   14_4) AppleWebKi
    0110   74 2f 35 33 37 2e 33 36 SP 28 4b 48 54 4d 4c 2c   t/537.36 (KHTML,
    0120   SP 6c 69 6b 65 SP 47 65 63 6b 6f 29 SP 43 68 72    like Gecko) Chr
    0130   6f 6d 65 2f 37 36 2e 30 2e 33 38 30 39 2e 31 33   ome/76.0.3809.13
    0140   32 SP 53 61 66 61 72 69 2f 35 33 37 2e 33 36 \r   2 Safari/537.36.
    0150   \n 41 63 63 65 70 74 3a SP 74 65 78 74 2f 68 74   .Accept: text/ht
    0160   6d 6c 2c 61 70 70 6c 69 63 61 74 69 6f 6e 2f 78   ml,application/x
    0170   68 74 6d 6c 2b 78 6d 6c 2c 61 70 70 6c 69 63 61   html+xml,applica
    0180   74 69 6f 6e 2f 78 6d 6c 3b 71 3d 30 2e 39 2c 69   tion/xml;q=0.9,i
    0190   6d 61 67 65 2f 77 65 62 70 2c 69 6d 61 67 65 2f   mage/webp,image/
    01a0   61 70 6e 67 2c 2a 2f 2a 3b 71 3d 30 2e 38 2c 61   apng,*/*;q=0.8,a
    01b0   70 70 6c 69 63 61 74 69 6f 6e 2f 73 69 67 6e 65   pplication/signe
    01c0   64 2d 65 78 63 68 61 6e 67 65 3b 76 3d 62 33 \r   d-exchange;v=b3.
    01d0   \n 41 63 63 65 70 74 2d 45 6e 63 6f 64 69 6e 67   .Accept-Encoding
    01e0   3a SP 67 7a 69 70 2c SP 64 65 66 6c 61 74 65 \r   : gzip, deflate.
    01f0   \n 41 63 63 65 70 74 2d 4c 61 6e 67 75 61 67 65   .Accept-Language
    0200   3a SP 7a 68 2d 43 4e 2c 7a 68 3b 71 3d 30 2e 39   : zh-CN,zh;q=0.9
    0210   \r \n \r \n                                       ....

#### <font color=red>HTTP响应报文

<font color=red>HTTP/1.1 200 OK\r\n
<font color=blue>Date: Tue, 03 Sep 2019 07:21:13 GMT\r\n
<font color=green>Server: Apache/2.4.6 (CentOS) OpenSSL/1.0.2k-fips PHP/5.4.16 mod_perl/2.0.10 Perl/v5.16.3\r\n
<font color=black>Last-Modified: Tue, 03 Sep 2019 05:59:01 GMT\r\n
<font color=#D02090>ETag: "51-5919fc9021bea"\r\n
<font color=#FF6347>Accept-Ranges: bytes\r\n
<font color=#008080>Content-Length: 81\r\n
<font color=#A0522D>Keep-Alive: timeout=5, max=100\r\n
<font color=#FF0000>Connection: Keep-Alive\r\n
<font color=#98FB98>Content-Type: text/html; charset=UTF-8\r\n
<font color=black>\r\n


    正文内容
    <html>\n
    Congratulations!  You've downloaded the first Wireshark lab file!\n
    </html>\n

    0000   a4 5e 60 ef 99 9f a0 63 91 3e 71 61 08 00 45 00   .^`....c.>qa..E.
    0010   01 ea 18 93 40 00 30 06 b0 7a 80 77 f5 0c 0a 0a   ....@.0..z.w....
    0020   00 73 00 50 e2 e8 e8 8f 08 49 b0 b3 59 35 80 18   .s.P.....I..Y5..
    0030   00 eb 40 5c 00 00 01 01 08 0a 7a 36 10 dc 4d fc   ..@\......z6..M.
    0040   7b 61 48 54 54 50 2f 31 2e 31 20 32 30 30 20 4f   {aHTTP/1.1 200 O
    0050   4b 0d 0a 44 61 74 65 3a 20 54 75 65 2c 20 30 33   K..Date: Tue, 03
    0060   20 53 65 70 20 32 30 31 39 20 30 37 3a 32 31 3a    Sep 2019 07:21:
    0070   31 33 20 47 4d 54 0d 0a 53 65 72 76 65 72 3a 20   13 GMT..Server: 
    0080   41 70 61 63 68 65 2f 32 2e 34 2e 36 20 28 43 65   Apache/2.4.6 (Ce
    0090   6e 74 4f 53 29 20 4f 70 65 6e 53 53 4c 2f 31 2e   ntOS) OpenSSL/1.
    00a0   30 2e 32 6b 2d 66 69 70 73 20 50 48 50 2f 35 2e   0.2k-fips PHP/5.
    00b0   34 2e 31 36 20 6d 6f 64 5f 70 65 72 6c 2f 32 2e   4.16 mod_perl/2.
    00c0   30 2e 31 30 20 50 65 72 6c 2f 76 35 2e 31 36 2e   0.10 Perl/v5.16.
    00d0   33 0d 0a 4c 61 73 74 2d 4d 6f 64 69 66 69 65 64   3..Last-Modified
    00e0   3a 20 54 75 65 2c 20 30 33 20 53 65 70 20 32 30   : Tue, 03 Sep 20
    00f0   31 39 20 30 35 3a 35 39 3a 30 31 20 47 4d 54 0d   19 05:59:01 GMT.
    0100   0a 45 54 61 67 3a 20 22 35 31 2d 35 39 31 39 66   .ETag: "51-5919f
    0110   63 39 30 32 31 62 65 61 22 0d 0a 41 63 63 65 70   c9021bea"..Accep
    0120   74 2d 52 61 6e 67 65 73 3a 20 62 79 74 65 73 0d   t-Ranges: bytes.
    0130   0a 43 6f 6e 74 65 6e 74 2d 4c 65 6e 67 74 68 3a   .Content-Length:
    0140   20 38 31 0d 0a 4b 65 65 70 2d 41 6c 69 76 65 3a    81..Keep-Alive:
    0150   20 74 69 6d 65 6f 75 74 3d 35 2c 20 6d 61 78 3d    timeout=5, max=
    0160   31 30 30 0d 0a 43 6f 6e 6e 65 63 74 69 6f 6e 3a   100..Connection:
    0170   20 4b 65 65 70 2d 41 6c 69 76 65 0d 0a 43 6f 6e    Keep-Alive..Con
    0180   74 65 6e 74 2d 54 79 70 65 3a 20 74 65 78 74 2f   tent-Type: text/
    0190   68 74 6d 6c 3b 20 63 68 61 72 73 65 74 3d 55 54   html; charset=UT
    01a0   46 2d 38 0d 0a 0d 0a 3c 68 74 6d 6c 3e 0a 43 6f   F-8....<html>.Co
    01b0   6e 67 72 61 74 75 6c 61 74 69 6f 6e 73 21 20 20   ngratulations!  
    01c0   59 6f 75 27 76 65 20 64 6f 77 6e 6c 6f 61 64 65   You've downloade
    01d0   64 20 74 68 65 20 66 69 72 73 74 20 57 69 72 65   d the first Wire
    01e0   73 68 61 72 6b 20 6c 61 62 20 66 69 6c 65 21 0a   shark lab file!.
    01f0   3c 2f 68 74 6d 6c 3e 0a                           </html>.

### 运输层，运输层分组称为报文段segment，在两个应用程序端点之间传输信息

### 网络层，数据报datagram，在两个主机之间传输

### 链路层，帧frame，从一个路由结点到另一个

### 物理层，传输比特 