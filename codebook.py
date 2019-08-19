# command + / 批量注释
# alt + shift + 箭头 移动代码





# 序列分解位单独变量,只要是可迭代对象都可以分解
# data = ['A', 'X', (1, 2)]
# data = {'A', 'X', (1, 2)}
# A, X, n = data
#
# print(A, X, n)


# *表达式可以提取序列中的一部分, num中包含了多个值
# record = ["A", 50, 123, 111, 'XC', (1, 2, 3), [3, 4, 5]]
# a, *num, xc, t, m = record
# print(a, num, xc, t, m)
#
# A, *NUM, M = record
# print(NUM)


# 输出最后的N个元素
# from collections import deque  # 队列
#
#
# def s(n):
#     q = deque(maxlen=n)  # 新记录进入时旧记录自动删除
#     yield q  # 生成器函数，产生迭代器输出最后的N的元素


# # 找到最大或最小的N个元素
# nums = [1, 8, 2, 23, 7, -4, 18, 23, 42, 37, 2]
# # N = 1 使用max()或min()
# print(max(nums), min(nums))

# # N不大时用heapq.nlargest()或heapq.nsmallest(),
# # heapq可以按照键值排序字典
# import heapq
# heapq.heapify(nums)
# print(nums, heapq.nlargest(3, nums), heapq.nsmallest(3, nums))

# # N接近序列长度时排序后切片
# print(sorted(nums)[:10], sorted(nums)[-10:])


# # 字典defaultdict, OrderedDict
# from collections import defaultdict, OrderedDict
# d = defaultdict(list)  # 允许重复元素
# d = defaultdict(set)  # 消除重复元素
# d = OrderedDict()  # 始终有序的字典


# # 字典计算,利用zip(),将键值对翻转，只能使用一次
# # 字典对key()和items()支持集合操作，可以找出相同的键值对&，减去部分键值对-
# prices = {'A': 10, 'B': 20, 'C': 30, 'D': 40}
# print(min(zip(prices.values(), prices.keys())))
# print(max(zip(prices.values(), prices.keys())))


# # 字典排序 itemgetter可以用lambda表达式代替
# from operator import itemgetter
# b = [{'x': 2, 'y': 4}, {'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 1, 'y': 2}, {'x': 2, 'y': 4}, {'x': 1, 'y': 4}]
# print(sorted(b, key=itemgetter('x')))
# print(sorted(b, key=itemgetter('y')))


# # 自定义排序 attrgetter可以用lambda表达式代替
# # 按照属性排序
# class User(object):
#     def __init__(self, id):
#         self.user_id = id
#
#     def __repr__(self):  # 调用print返回对象信息
#         return "User_id({})".format(self.user_id)
#
# from operator import attrgetter
# u = [User(132), User(233454), User(322), User(9238)]
# for i in u:
#     print(i)
# print(u)
# print(sorted(u, key=attrgetter("user_id")))


# # 顺序不变的情况下删去重复元素
# a = [1, 5, 2, 1, 9, 1, 5, 10]
# b = [{'x': 2, 'y': 4}, {'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 1, 'y': 2}, {'x': 2, 'y': 4}, {'x': 1, 'y': 4}]
#
# # def deldupe(a):
# #     already = set()
# #     for ele in a:
# #
# #         if ele not in already:
# #             yield ele
# #             already.add(ele)
#
# def deldupe(a, key=None):
#     already = []
#     for ele in a:
#         if key is None:
#             if ele not in already:
#                 yield ele
#                 already.append(ele)
#         else:
#             for k in ele.keys():
#                 if k in key:
#                     if ele not in already:
#                         yield ele
#                         already.append(ele)
#
#
# print(list(deldupe(a)))
# print(list(deldupe(b, ['x', 'y'])))
# print(list(deldupe(b, ['x'])))
#
# # 顺序可变
# print(set(a))


# # 智能切片并命名
# i = [1, 5, 2, 1, 9, 1, 5, 10]
# a = slice(0, 4, 2)  # 切刀
# a = i.indices(len(i))
# print(i[a], i[a.start], i[a.stop], i[a.step])


# # 智能计数 Counter对象可以作运算
# from collections import Counter
# words = ['s', 'f', 'g', 'g', 'w', 'w', 'f', 'h', 'i', 'y', 't', 'g', 'k', 'v', 'c', 'v', 'a', 's', 's', 's', 's', 'v', 'q', ]
# more_words = ['f', 'h', 'i', 'y', 't', 'g', 'k', 'v', 'c', 'v', 'a', ]
# b = Counter(more_words)
# c = Counter(words)
# print(c)
# c.update(more_words)
# print(c)
#
# print(b)
# print(b + c, '\n', c - b)
# print(c.most_common(3))


# 分组记录字典数据
# groupby 找出相同的key的相同值的数据归为一类
# from operator import itemgetter, attrgetter
# from itertools import groupby
# b = [{'x': 2, 'y': 4}, {'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 1, 'y': 2}, {'x': 2, 'y': 4}, {'x': 1, 'y': 4}]
# b.sort(key=itemgetter('x'))
# for key, value in groupby(b, key=itemgetter('x')):
#     for i in value:
#         print(i)
#
# b.sort(key=itemgetter('y'))
# for key, value in groupby(b, key=itemgetter('y')):
#     for i in value:
#         print(i)
#
# 以某个关键字的值为key分类存储数据
# key=i['x']
# from collections import defaultdict
# a = defaultdict(list)
# for i in b:
#     a[i['x']].append(i)
# for i in a[2]:
#     print(i)


# # 筛选元素，分组，提取
# b = [{'x': 2, 'y': 4}, {'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 1, 'y': 2}, {'x': 2, 'y': 4}, {'x': 1, 'y': 4}]
# # 列表推导和生产器表达式
# a = [x for x in b if x['x'] == 1]  # else 可以代替旧值
# print(a)
#
# # filter（）函数
# def ff (val):
#     return val['x'] == 1
#
# c = list(filter(ff, b))  # 必须用list将迭代器变为列表
# print(c)
#
# # compress 按照提供的布尔序列挑选出True元素
# from itertools import compress
# more = [x['x'] == 1 for x in b]
# print(more)
# print(list(compress(b, more)))  # 必须用list将迭代器变为列表
#
# # 提取一部分字典
# d = {'x': 1, 'y': 2, 'c': 2, 'd': 1}
# dic = {key: value for key, value in d.items() if key in ['c', 'x']}
# print(dic)


# # namedtuple()给元组或列表的某些部分命名，使得其更佳易读
# from collections import namedtuple
# thing = namedtuple('sth', ['price', 'date'])
# a = thing(1.2, 2019)
# print(a.date, a.price)


# # 多个字典或映射合并
# d = {'x': 1, 'y': 2, 'c': 2, 'd': 1}
# c = {'x': 3, 'd': 4}
# from collections import ChainMap
# dic = ChainMap(d, c)  # ChainMap与原始字典同步
# print(dic)
# new_dict = d
# new_dict.update(c)  # update不与原始字典同步
# print(new_dict)
# for i in dic.items():
#     print(i)
# for i in new_dict.items():
#     print(i)


# # 分割字符串
# # 固定分割符 split按照固定的分割符
# words = 'nobody:*:-2:2:Unprivileged User:/var/empty:/usr/bin/false'
# *trash, path1, path2 = words.split(':')
# print(path1, path2)
# # 任意多个分割符
# lines = 'sadd asfseg: sadasf, sadafas,asdas,    fdsfsd'
# import re  # 正则化表达式, 不同模式匹配
# # '^abc'以abc开头，同startswith， 'abc$'以abc结尾，同endswith
# print(re.split('[:;,\s]\s*', lines))
# print(re.findall('(^fff|sadd|fsd|fff$)', lines))
# print(re.findall('fsd|fff$', lines))
# print(lines.startswith(tuple(['sadd', 'fff'])))
# print(lines.endswith(tuple(['fsd', 'fff'])))
#
# # re.match匹配返回True或False。
# # pattern = re.compile()生成一个模式用于. pattern.march()
# # re.findall()可以匹配整个文本
# find = re.findall('[\w]*fs[\w]*', lines)
# print(find)
#
# pat = re.compile('([\w]*)(fs)([\w]*)')
# find = pat.findall(lines)
# list(find)  # 找到分组提取
# print(find)

# m = re.finditer('([\w]*)(fs)([\w]*)', lines, flags=re.IGNORECASE)
# flags = re.IGNORECASE智能re.*中使用, 忽略大小写
# flags = re.DOTALL让.可以匹配包括换行符在内的所以字符，作多行匹配
# (?:.|\n)只匹配不捕获，也可以作多行匹配
# for x in m:
#     # 提取分组
#     print(x.groups())
#     print(x.group(1))
#     print(x.group(2))
#     print(x.group(3))


# # 查找和替换
# # str.replace
# lines = 'sadd asfseg: sadasf, sadafas,asdas,    fdsfsd'
# print(lines)
# print(lines.replace('f', 'x'))
#
# # 正则表达式re
# import re
# pattern = re.compile(r'fs')
# print(pattern.sub('xx', lines))


# 清除垃圾字符
# strip只能清除开头或结尾的
lines = ' sadd- asf-seg: sa-dasf, sad-afas,as=das,    fdsf-sd '
print(lines)
lines.strip()
lines.lstrip('-=')
lines.rstrip("-=")
lines = lines.strip()

lines = lines.replace('-', '')
lines = lines.replace('=', '')

import re
lines = re.sub('\s+', ' ', lines)

print(lines)
print()

# 逐行清洗数据
remap = {
    ord(' '): ''
}

with open('atjob') as f:
    words = (line.strip() for line in f)
    for word in list(words):
        a = re.sub('^#[.*]+', '', word)
        print(a)




