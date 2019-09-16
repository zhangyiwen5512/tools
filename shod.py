import shodan
import shodan.helpers as helpers



KEY = "w7pBRw0JRSHvRMiuVjubU4MEUJi57T6R"
api = shodan.Shodan(KEY)


actionName = ''

result = {}


try:
    # shodan search搜索
    # minify禁用概要, page输出页数
    # Facets摘要信息
#    result = api.search('', minify=False, page=1)

    # shodan host主机查找
    # history获取IP地址的完整历史记录
#    result = api.host('', history=True)

    # shodan scan扫描
#    result = api.scan('')

    # shdan stream实时数据流
#    result = api.stream.banners('')

    # shodan create_alert网络提醒
    # 需要提供一个提醒名称和一个IP范围
    # expires设置提醒的时间
    result = api.create_alert('', '', expires=10)



except shodan.APIError as e:
    print("ERROR: {}".format(e))

if not result:
    print("empty result")
    exit(0)


# shodan alert订阅
    # 将提醒作实时数据流的监视,网络提醒时会返回提醒ID
    for banners in api.stream.alert(result['id']):
        print(banners)

    # shodan alert clear                                                清除所有alert
    # shodan alert list                                                 列出alert列表，确认有无alert
    # shodan alert create "Temporary alert" 198.20.69.0/24              创建一个新的alert
    # shodan stream --alert=ODMD34NFPLJBRSTC --datadir=alert-data       订阅监视提醒，并存储数据。ODMD34NFPLJBRSTC警报ID

# shodan.helpers.iterate_files(‘’)遍历Shodan数据文件得到banners
# for banner in helpers.iterate_files(datafile):



# shodan download --limit -1 xx.json.gz has_下载数据
