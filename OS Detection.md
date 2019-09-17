# 操作系统探测

## nmap -O Address 或 nmap -A Address 

    使用TCP / IP堆栈指纹识别进行远程操作系统检测。至少一个打开一个关闭的端口时检查很有效。
    --osscan-limit:跳过不符合的主机 。至少一个打开一个关闭的端口时检查很有效。设置此选项，Nmap甚至不会针对不符合此条件的主机尝试操作系统检测。只有在使用-O或-A请求OS检测时才有意义。
    --osscan-guess; --fuzzy: 打印猜测的OS。当Nmap无法检测到完美的OS匹配时，大胆的猜测近似匹配的对象。
    --max-os-tries: 指定重复次数。当Nmap无法检测到完美的OS匹配时,默认重复5次。条件不好时2次。


## sudo nmap -O -v scanme.nmap.org
 
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-17 08:54 CST
    Initiating Ping Scan at 08:54
    Scanning scanme.nmap.org (45.33.32.156) [4 ports]
    Completed Ping Scan at 08:54, 0.20s elapsed (1 total hosts)
    Initiating Parallel DNS resolution of 1 host. at 08:54
    Completed Parallel DNS resolution of 1 host. at 08:54, 0.42s elapsed
    Initiating SYN Stealth Scan at 08:54
    Scanning scanme.nmap.org (45.33.32.156) [1000 ports]
    Discovered open port 22/tcp on 45.33.32.156
    Discovered open port 80/tcp on 45.33.32.156
    Discovered open port 31337/tcp on 45.33.32.156
    Discovered open port 9929/tcp on 45.33.32.156
    Completed SYN Stealth Scan at 08:54, 16.22s elapsed (1000 total ports)
    Initiating OS detection (try #1) against scanme.nmap.org (45.33.32.156)
    Retrying OS detection (try #2) against scanme.nmap.org (45.33.32.156)
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.17s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    Not shown: 991 closed ports
    PORT      STATE    SERVICE
    22/tcp    open     ssh
    80/tcp    open     http
    135/tcp   filtered msrpc
    139/tcp   filtered netbios-ssn
    445/tcp   filtered microsoft-ds
    593/tcp   filtered http-rpc-epmap
    4444/tcp  filtered krb524
    9929/tcp  open     nping-echo
    31337/tcp open     Elite
    Aggressive OS guesses: Linux 2.6.18 (87%), Linux 2.6.32 (87%), Linux 2.6.32 or 3.10 (87%), Linux 2.6.39 (87%), Linux 3.10 - 3.12 (87%), Linux 4.4 (87%), WatchGuard Fireware 11.8 (87%), Synology DiskStation Manager 5.1 (87%), Linux 2.6.35 (87%), Linux 4.9 (87%)
    No exact OS matches for host (test conditions non-ideal).
    Uptime guess: 5.145 days (since Thu Sep 12 05:26:25 2019)
    Network Distance: 15 hops
    TCP Sequence Prediction: Difficulty=255 (Good luck!)
    IP ID Sequence Generation: All zeros

    Read data files from: /usr/bin/../share/nmap
    OS detection performed. Please report any incorrect results at https://nmap.org/submit/ .
    Nmap done: 1 IP address (1 host up) scanned in 22.65 seconds
            Raw packets sent: 1205 (54.904KB) | Rcvd: 1040 (42.984KB)


## sudo nmap -sV -O -v scanme.nmap.org

    虽然TCP指纹识别是一种强大的OS检测方法，但查询开放端口以获取线索是另一种有效的方法。 某些应用程序（如Microsoft IIS）仅在单个平台上运行（因此将其丢弃），而许多其他应用程序在过于冗长的横幅消息中泄露其平台。 添加-sV选项可启用Nmap版本检测，该版本经过培训可以查找这些线索（以及其他信息）。

    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-17 09:12 CST
    NSE: Loaded 45 scripts for scanning.
    Initiating Ping Scan at 09:12
    Scanning scanme.nmap.org (45.33.32.156) [4 ports]
    Completed Ping Scan at 09:12, 0.21s elapsed (1 total hosts)
    Initiating Parallel DNS resolution of 1 host. at 09:12
    Completed Parallel DNS resolution of 1 host. at 09:12, 0.00s elapsed
    Initiating SYN Stealth Scan at 09:12
    Scanning scanme.nmap.org (45.33.32.156) [1000 ports]
    Discovered open port 80/tcp on 45.33.32.156
    Discovered open port 22/tcp on 45.33.32.156
    Discovered open port 9929/tcp on 45.33.32.156
    Discovered open port 31337/tcp on 45.33.32.156
    Completed SYN Stealth Scan at 09:12, 17.26s elapsed (1000 total ports)
    Initiating Service scan at 09:12
    Scanning 4 services on scanme.nmap.org (45.33.32.156)
    Completed Service scan at 09:12, 6.38s elapsed (4 services on 1 host)
    Initiating OS detection (try #1) against scanme.nmap.org (45.33.32.156)
    Retrying OS detection (try #2) against scanme.nmap.org (45.33.32.156)
    NSE: Script scanning 45.33.32.156.
    Initiating NSE at 09:13
    Completed NSE at 09:13, 0.80s elapsed
    Initiating NSE at 09:13
    Completed NSE at 09:13, 0.72s elapsed
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.16s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    Not shown: 991 closed ports
    PORT      STATE    SERVICE        VERSION
    22/tcp    open     ssh            OpenSSH 6.6.1p1 Ubuntu 2ubuntu2.13 (Ubuntu Linux; protocol 2.0)
    80/tcp    open     http           Apache httpd 2.4.7 ((Ubuntu))
    135/tcp   filtered msrpc
    139/tcp   filtered netbios-ssn
    445/tcp   filtered microsoft-ds
    593/tcp   filtered http-rpc-epmap
    4444/tcp  filtered krb524
    9929/tcp  open     nping-echo     Nping echo
    31337/tcp open     tcpwrapped
    Aggressive OS guesses: Linux 2.6.32 (88%), Linux 2.6.18 (87%), Linux 3.4 (87%), Linux 3.5 (87%), Linux 4.2 (87%), Linux 4.4 (87%), Synology DiskStation Manager 5.1 (87%), WatchGuard Fireware 11.8 (87%), Linux 2.6.35 (87%), Linux 3.10 (87%)
    No exact OS matches for host (test conditions non-ideal).
    Uptime guess: 5.157 days (since Thu Sep 12 05:26:25 2019)
    Network Distance: 13 hops
    TCP Sequence Prediction: Difficulty=262 (Good luck!)
    IP ID Sequence Generation: All zeros
    Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

    Read data files from: /usr/bin/../share/nmap
    OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
    Nmap done: 1 IP address (1 host up) scanned in 32.76 seconds
            Raw packets sent: 1119 (51.136KB) | Rcvd: 1036 (42.824KB)


### Device type
    所以被识别的指纹都会被分为一个或者多个类型。
    Device Type: router|firewall

### Running
    当没有完全匹配时，nmap将字段更改为running（只是猜测），并在每个候选家族名称后的括号中添加一个准确率百分比（100%是完全匹配）。如果没有指纹是完全匹配的，则忽略该行。
    Linux 2.4.X|2.5.X|2.6.X.

### OS CPE  
    显示了操作系统的通用平台枚举（cpe）表示（如果可用）。它还可以具有硬件类型的cpe表示。os cpe以cpe:/o开头，硬件cpe以cpe:/h开头。
    CPE: cpe:/o:linux:linux_kernel

### OS details
    如果没有任何完美的匹配，但有一些接近的猜测，则将该字段重命名为aggressive os guesses，并在括号中显示指纹，后面跟着一个百分比，指定每个匹配的接近程度。
    Aggressive OS guesses: Linux 2.6.32 (88%), Linux 2.6.18 (87%), Linux 3.4 (87%), Linux 3.5 (87%), Linux 4.2 (87%), Linux 4.4 (87%), Synology DiskStation Manager 5.1 (87%), WatchGuard Fireware 11.8 (87%), Linux 2.6.35 (87%), Linux 3.10 (87%)

### Uptime guess
    检查报头中的时间戳选项。通过观察几个响应，nmap可以确定当前值和增长率。简单的线性外推确定启动时间。如果目标在其syn/ack数据包中提供零或没有时间戳选项，或者根本没有应答，则忽略正常运行时间猜测。如果nmap无法识别时间戳增量率，或者它看起来可疑（如30年的正常运行时间），则该行也将被省略。
    Uptime guess: 5.157 days (since Thu Sep 12 05:26:25 2019)

### Network Distance
    计算nmap和目标主机之间的路由器数量。扫描本地主机时，距离为零，对于同一网段上的计算机，距离为一。路径上的每个附加路由器都会将一个添加到跃点计数中。nmap在无法计算该线时会省略该线（对相关探测没有响应）。
    Network Distance: 13 hops

### TCP Sequence Prediction
    TCP初始序列号生成较差的系统容易受到盲目TCP欺骗攻击。换句话说，您可以与这些系统建立完全连接，并在欺骗不同的IP地址时发送（但不接收）数据。目标的日志将显示欺骗性IP，您可以利用它们之间的任何信任关系。

   许多操作系统已被修复为使用RFC 1948提出的不可预测的初始序列号。出于这些原因，此行仅以详细模式打印。许多供应商仍然提供易受攻击的操作系统和设备，这使得它们对于OS检测目的是有价值的，该类描述了目标使用的ISN生成算法，难度是粗略估计系统进行盲IP欺骗的难度（0是最简单的）。带括号的评论基于难度指数，范围从琐碎的笑话到轻松，中等，强大，值得挑战，最后祝你好运！
    TCP Sequence Prediction: Difficulty=262 (Good luck!)

### IP ID sequence generation
    许多系统基于如何在IP数据包中生成低16位ID字段，无意中泄露了有关其流量级别的敏感信息。这可能被滥用来欺骗针对其他系统的端口扫描，以及用于“TCP空闲扫描（-SI）”一节中讨论的其他恶意目的。此字段描述nmap能够识别的id生成算法。许多系统为与之通信的每个主机使用不同的IP ID空间。在这种情况下，它们可能看起来很脆弱（例如显示增量类），同时仍然能够抵御诸如空闲扫描之类的攻击。出于这个原因，IP ID序列生成行仅以详细模式打印。如果nmap在os检测期间没有收到足够的响应，它将忽略整行。测试主机是否易受空闲扫描僵尸攻击的最佳方法是使用-si对其进行测试。
    IP ID Sequence Generation: All zeros


## tcp/ip指纹识别方法
    发送16个TCP，UDP，ICMP探针确定打开和关闭的端口。这些报文专门利用的RFC文档中的描述不清的地方而设计。侦听响应。分析并组合这些响应中的许多属性以生成指纹。如果没有响应，则每个探测包都被跟踪并重新发送一次。所有这些数据包都是具有随机IP ID值的IPv4数据报文。如果未找到开放的端口，Nmap会跳过对开放的TCP端口的探测。而后Nmap会先检查是否找到了一个确认关闭的TCP或UDP端口。如果还没有，Nmap将随机选择一个端口并希望获得最佳效果。


## Probes Sent发送的探测报文

### Sequence generation (SEQ, OPS, WIN, and T1)序列生成测试（SEQ，OPS，WIN和T1）
    Nmap会发送一系列六个TCP探测报文以生成这四个测试的响应结果。探测报文的时间间隔为精确的100ms，因此发送的总时间为500ms。这里确切的时序是非常重要的，因为我们检测中用到的一些序列算法（初始序列号，IP ID和TCP时间戳）都是与时间密切相关的。 这里总时间被选择为500ms，以便我们可靠地检测常见的2 Hz TCP时间戳序列。

    每个探测都是发送TCP SYN数据包到远程计算机上已检测到的开放端口的。序列seq和确认号ack是随机的（但每一个的情况都会被保留，因此Nmap可以区分每一个的响应）。检测的精度要求探测报文的一致性，因此即使用户主动使用–data-length请求，数据报文中也不会有有效的数据负载。

    这些数据包在TCP选项中有很多不同的使用方式，还有不同的TCP窗口大小值。 以下列表提供了六个数据包的具体选项和值。 列出的窗口大小的值并不会反映窗口缩放的值。EOL是TCP选项结束符，默认情况下许多嗅探工具都不会显示。


### 包#1：窗口缩放（10），NOP，MSS（1460），时间戳（TSval：0xFFFFFFFF; TSecr：0），允许SACK。 窗口大小为1。\
![](./assets/52411.png)
![](./assets/524113.png)
![](./assets/524111.png)
![](./assets/524112.png)

### 包#2： MSS（1400），窗口缩放（0），允许SACK，时间戳（TSval：0xFFFFFFFF; TSecr：0），EOL。 窗口大小为63。
![](./assets/52412.png)
![](./assets/524123.png)
![](./assets/524121.png)
![](./assets/524122.png)

###    包#3：时间戳（TSval：0xFFFFFFFF; TSecr：0），NOP，NOP，窗口缩放（5），NOP，MSS（640）。 窗口大小为4。
![](./assets/52413.png)
![](./assets/524133.png)
![](./assets/524131.png)
![](./assets/524132.png)

###    包#4：允许SACK，时间戳（TSval：0xFFFFFFFF; TSecr：0），窗口缩放（10），EOL。 窗口大小为4。
![](./assets/52414.png)
![](./assets/524143.png)
![](./assets/524141.png)
![](./assets/524142.png)

###    包#5： MSS（536），允许SACK，时间戳（TSval：0xFFFFFFFF; TSecr：0），窗口缩放（10），EOL。 窗口大小是16。
![](./assets/52415.png)
![](./assets/524153.png)
![](./assets/524151.png)
![](./assets/524152.png)

###    包#6： MSS（265），允许SACK，时间戳（TSval：0xFFFFFFFF; TSecr：0）。 窗口大小是512.
![](./assets/52416.png)
![](./assets/524163.png)
![](./assets/524161.png)
![](./assets/524162.png)


    这些测试的结果包括四个类别。 第一个SEQ探测包含基于探测包的序列分析的结果，测试结果表现为GCD，SP，ISR，TI，II，TS和SS的数值。下一个OPS测试包含每个探测报文对应响应结果的TCP选项（测试名称为O1到06）。同理，WIN测试包含响应的窗口大小（名为W1到W6）。与这些探测报文相关的最后一项T1，包含对数据包#1的响应的各种测试值，这些结果决定R，DF，T，TG，W，S，A，F，O，RD和Q的测试值。而这项T1测试仅针对第一个探测报文报告，因为它们对于接下来每个探测报文的反应总是几乎完全相同的。


###  ICMP echo ICMP响应测试（IE）
    发送两个ICMP响应请求数据包到目标。 
    
### ICMP包1
    IP DF位会置位，服务类型（TOS） 字节值为0，代码为9（即使它应该为0），序列号为295， IP ID和ICMP请求标识符随机，以及120字节的0x00用于数据有效载荷。
![](./assets/2325.png)
![](./assets/2333.png)


### ICMP包2
    ping询问也类似，除了使用四个TOS（ IP_TOS_RELIABILITY ），代码为零，发送150个字节的数据，并且ICMP请求标识符和序列号也从先前的值加1。
![](./assets/2326.png)
![](./assets/2335.png)

    将这两种探测报文的响应，组合为R，DFI，T，TG和CD的测试结果。只有两个探测报文都引出响应，R值才为真（Y）。 T和CD值仅来自第一个探测的响应结果，因为两次的结果会完全一致。 DFI是针对特殊的双探测报文ICMP外壳的定制测试。

    这些ICMP探测会在TCP序列探测之后立即进行，以确保共享IP ID序列号测试的有效结果

### TCP explicit congestion notification (ECN) TCP显式拥塞通知测试（ECN）
    测试目标TCP栈中是否支持显式拥塞通知（ECN）。Nmap通过发送一个SYN数据包对此进行测试，该数据包设置了ECN、CWR和ECE拥塞控制标志。对于不相关（到ECN）测试，即使未设置紧急标志，也使用0xF7F5的紧急字段值，确认号为0，序列号随机，窗口大小为3，并且紧接在CWR位之前的保留位被置位。 TCP选项是：窗口缩放（10），NOP，MSS（1460），允许SACK，NOP，NOP，探测报文被发送到开放端口。

    如果收到响应，则记录R，DF，T，TG，W，O，CC和Q的测试值。
![](./assets/2328.png)
![](./assets/2342.png)
![](./assets/2343.png)
![](./assets/2388.png) 
![](./assets/2399.png) 
![](./assets/2400.png) 


### TCP (T2–T7) TCP测试（T2 - T7）
    T2到T7测试每个会发送一个TCP探测包。除了有一个例外，其他包的TCP选项数据都是（十六进制） 03030A0102040109080AFFFFFFFF000000000402。这20个字节对应于：窗口缩放（10），NOP，MSS（265），时间戳（TSval：0xFFFFFFFF; TSecr：0），然后允许SACK。 这里例外的情况是指T7使用的窗口缩放为15而不是10。每个探测报文的变量特征如下所述：


###    T2发送一个TCP空（无标志设置< NONE>）数据包，其中IP DF置位，窗口大小为128，发送到开放端口。
![](./assets/2329.png) 
![](./assets/2344.png) 
![](./assets/2350.png) 
![](./assets/2355.png) 
![](./assets/2389.png) 
![](./assets/2402.png) 
![](./assets/2408.png) 
![](./assets/2415.png) 


###    T3发送一个TCP SYN，FIN，URG和PSH标志置位数据包，其中IP DF未置位，窗口大小为256，发送到开放端口。
![](./assets/2331.png) 
![](./assets/2345.png) 
![](./assets/2351.png) 
![](./assets/2356.png) 
![](./assets/2390.png) 
![](./assets/2403.png) 
![](./assets/2409.png)
![](./assets/2416.png) 


###    T4发送一个TCP ACK数据包，其中IP DF置位，窗口大小为1024，发送到开放端口。
![](./assets/2334.png)
![](./assets/2347.png)
![](./assets/2352.png)
![](./assets/2357.png)
![](./assets/2391.png)
![](./assets/2405.png)
![](./assets/2410.png)
![](./assets/2417.png) 


###    T5发送一个TCP SYN数据包，其中IP DF未置位，窗口大小为31337，发送到关闭端口。
![](./assets/2336.png)
![](./assets/2346.png)
![](./assets/2394.png)
![](./assets/2404.png)

###   T6发送一个TCP ACK数据包，其中IP DF置位，窗口大小为32768，发送到关闭端口。
![](./assets/2337.png)
![](./assets/2348.png)
![](./assets/2353.png)
![](./assets/2358.png)
![](./assets/2395.png)
![](./assets/2406.png)
![](./assets/2413.png)
![](./assets/2418.png)



###    T7发送一个TCP FIN，URG和PSH标志置位数据包，其中IP DF未置位，窗口大小为65535，发送到关闭端口。
![](./assets/2339.png)
![](./assets/2349.png)
![](./assets/2354.png)
![](./assets/2359.png)
![](./assets/2398.png)
![](./assets/2407.png)
![](./assets/2414.png)
![](./assets/2419.png)

    在每种情况下，将每一次的结果添加到指纹中，其结果为R，DF，T，TG，W，S，A，F，O，RD和Q的测试值。


### UDP (U1) UDP测试（U1）



## Response Tests各种测试内容

### TCP ISN greatest common divisor (GCD)

### TCP ISN counter rate (ISR)
### TCP ISN sequence predictability index (SP)


### IP ID sequence generation algorithm (TI, CI, II)
### Shared IP ID sequence Boolean (SS)
### TCP timestamp option algorithm (TS)
### TCP options (O, O1–O6)
### TCP initial window size (W, W1–W6)
### Responsiveness (R)
### IP don't fragment bit (DF)
### Don't fragment (ICMP) (DFI)

### IP initial time-to-live (T)
### IP initial time-to-live guess (TG)
### Explicit congestion notification (CC)
### TCP miscellaneous quirks (Q)
### TCP sequence number (S)
### TCP acknowledgment number (A)
### TCP flags (F)

### TCP RST data checksum (RD)
### IP total length (IPL)
### Unused port unreachable field nonzero (UN)
### Returned probe IP total length value (RIPL)
### Returned probe IP ID value (RID)
### Integrity of returned probe IP checksum value (RIPCK)
### Integrity of returned probe UDP checksum (RUCK)
### Integrity of returned UDP data (RUD)
### ICMP response code (CD)

### TCP (T2–T7)