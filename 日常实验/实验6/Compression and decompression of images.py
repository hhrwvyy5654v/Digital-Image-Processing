# -*- encoding: utf-8 -*-
'''
@File    :   main.py
@Time    :   2022/05/20 20:37:32
@Author  :   HuangRongQuan 
@Version :   1.0
@Contact :   huang_rongquan@outlook.com
'''
import os
import six


class HuffNode(object):
    """_定义一个HuffNode虚类,包含两个虚方法_

    Args:
        object (_type_): _description_
    """

    # 获取节点的权重函数
    def get_weight(self):
        raise NotImplementedError(
            "抽象节点类未定义'get_weight'")
    # 获取此节点是否是叶节点的函数
    def isleaf(self):
        raise NotImplementedError(
            "抽象节点类未定义 'isleaf'")


class LeafNode(HuffNode):
    """_树叶节点类_

    Args:
        HuffNode (_type_): _description_
    """
    
    # 初始化树节点,需要初始化的对象参数有节点值value及其出现的频率frequency
    def __init__(self, value=0, frequency=0,):
        super(LeafNode, self).__init__()
        # 节点的值
        self.value = value
        self.weight = frequency

    # 基类的方法,返回True,代表是叶节点
    def isleaf(self):
        return True

    # 基类的方法,返回对象属性 weight,表示对象的权重
    def get_weight(self):
        return self.weight

    # 获取叶子节点的字符的值
    def get_value(self):
        return self.value


class IntlNode(HuffNode):
    """_中间节点类_

    Args:
        HuffNode (_type_): _description_
    """
    # 初始化中间节点,需要初始化的对象参数有:左孩子、右孩子、节点权重
    def __init__(self, left_child=None, right_child=None):
        super(IntlNode, self).__init__()
        # 节点的值
        self.weight = left_child.get_weight() + right_child.get_weight()
        # 节点的左右子节点
        self.left_child = left_child
        self.right_child = right_child

    # 基类的方法,返回False,代表是中间节点
    def isleaf(self):
        return False

    # 基类的方法,返回对象属性 weight,表示对象的权重
    def get_weight(self):
        return self.weight

    # 获取左孩子
    def get_left(self):
        return self.left_child

    # 获取右孩子
    def get_right(self):
        return self.right_child


class HuffTree(object):
    """_霍夫曼编码树_

    Args:
        object (_type_): _description_
    """
    # 初始化霍夫曼编码树,需要初始化的对象参数有:根节点标记、节点的值、节点权重、左孩子、右孩子
    def __init__(self, flag, value =0, frequency=0, left_tree=None, right_tree=None):

        super(HuffTree, self).__init__()
        if flag == 0:
            self.root = LeafNode(value, frequency)
        else:
            self.root = IntlNode(left_tree.get_root(), right_tree.get_root())

    # 获取霍夫曼编码树的根节点
    def get_root(self):
        return self.root

    # 获取霍夫曼编码树的根节点的权重
    def get_weight(self):
        return self.root.get_weight()

    # 采用递归的方法遍历霍夫曼编码树,并以此方式将得到每个字符对应的霍夫曼编码保存在字典char_frequency中
    def traverse_huffman_tree(self, root, code, char_frequency):
        if root.isleaf():
            char_frequency[root.get_value()] = code
            print(("it = %c  and  frequency = %d  code = %s")%(chr(root.get_value()),root.get_weight(), code))
            return None
        else:
            self.traverse_huffman_tree(root.get_left(), code+'0', char_frequency)
            self.traverse_huffman_tree(root.get_right(), code+'1', char_frequency)



def Create_HuffmanTree(list_hufftrees):
    """_构造huffman树_

    Args:
        list_hufftrees (_type_): _description_

    Returns:
        _type_: _description_
    """
    while len(list_hufftrees) >1 :
        # 按照信源符号出现概率(weight)对霍夫曼树进行从小到大的排序
        list_hufftrees.sort(key=lambda x: x.get_weight()) 
        # 跳出weight的最小两个huffman编码树
        temp1 = list_hufftrees[0]
        temp2 = list_hufftrees[1]
        list_hufftrees = list_hufftrees[2:]
        #构造新的霍夫曼树
        new_huffman_tree = HuffTree(1, 0, 0, temp1, temp2)
        #将霍夫曼树存放入到数组中
        list_hufftrees.append(new_huffman_tree)

    # 数组中最后剩下来的那棵树,就是构造的Huffman编码树
    return list_hufftrees[0]


def compress(input_file_name:str, output_file_name:str):
    """_压缩文件_

    Args:
        input_file_name (str): _被压缩的文件的地址_
        output_file_name (str): _压缩文件的存放地址_
    """
    #以二进制的方式打开文件 
    f = open(input_file_name,'rb')
    filedata = f.read()
    # 获取文件的字节总数
    filesize = f.tell()

    # 统计byte的取值[0-255]的每个值出现的频率,并保存在字典char_frequency中
    char_frequency = {}
    for x in range(filesize):
        temp = filedata[x] 
        if temp in char_frequency.keys():
            char_frequency[temp] = char_frequency[temp] + 1
        else:
            char_frequency[temp] = 1

    # 输出统计结果
    for temp in char_frequency.keys():
        print(temp,' : ',char_frequency[temp])

    # 开始构造原始的霍夫曼编码树数组,用于构造Huffman编码树
    list_hufftrees = []
    for x in char_frequency.keys():
        # 使用霍夫曼编码树的构造函数,定义一棵只包含一个叶节点的霍夫曼编码树
        temp = HuffTree(0, x, char_frequency[x], None, None)
        # 将其添加到数组 list_hufftrees 当中
        list_hufftrees.append(temp)

    # 保存叶节点的个数
    length = len(char_frequency.keys())
    output = open(output_file_name, 'wb')

    # 一个int型的数有四个字节,所以将其分成四个字节写入到输出文件当中
    a4 = length&255
    length = length>>8
    a3 = length&255
    length = length>>8
    a2 = length&255
    length = length>>8
    a1 = length&255
    output.write(six.int2byte(a1))
    output.write(six.int2byte(a2))
    output.write(six.int2byte(a3))
    output.write(six.int2byte(a4))

    # 遍历字典char_frequency
    for x in char_frequency.keys():
        output.write(six.int2byte(x))
        temp = char_frequency[x]
        # 同样出现的次数是int型,分成四个字节写入到压缩文件当中
        a4 = temp&255
        temp = temp>>8
        a3 = temp&255
        temp = temp>>8
        a2 = temp&255
        temp = temp>>8
        a1 = temp&255
        output.write(six.int2byte(a1))
        output.write(six.int2byte(a2))
        output.write(six.int2byte(a3))
        output.write(six.int2byte(a4))

    # 构造霍夫曼编码树,并且获取到每个字符对应的编码
    temp = Create_HuffmanTree(list_hufftrees)
    temp.traverse_huffman_tree(temp.get_root(),'',char_frequency)
    
    # 开始对文件进行压缩操作
    code = ''
    for i in range(filesize):
        key = filedata[i] 
        code = code + char_frequency[key]
        out = 0
        while len(code)>8:
            for x in range(8):
                out = out<<1
                if code[x] == '1':
                    out = out|1
            code = code[8:]
            output.write(six.int2byte(out))
            out = 0

    # 处理剩下来的不满8位的code
    output.write(six.int2byte(len(code)))
    out = 0
    for i in range(len(code)):
        out = out<<1
        if code[i]=='1':
            out = out|1
    for i in range(8-len(code)):
        out = out<<1
    # 把最后一位给写入到文件当中
    output.write(six.int2byte(out))
    # 关闭输出文件,文件压缩完毕
    output.close()



def decompress(input_file_name:str, output_file_name:str):
    """_解压缩文件_

    Args:
        input_file_name (str): _压缩文件的地址_
        output_file_name (str): _解压缩文件的存放地址_
    """
    # 读取文件
    f = open(input_file_name,'rb')
    filedata = f.read()
    # 获取文件的字节总数
    filesize = f.tell()

    #读取压缩文件中保存的树的叶节点的个数
    #一次读取4个字节,代表一个int型的值
    a1 = filedata[0]
    a2 = filedata[1]
    a3 = filedata[2]
    a4 = filedata[3]    
    j = 0
    j = j|a1
    j = j<<8
    j = j|a2
    j = j<<8
    j = j|a3
    j = j<<8
    j = j|a4

    leaf_node_size = j


    # 读取压缩文件中保存的相信的原文件中[0-255]出现的频率的信息
    # 构造一个字典char_frequency,重建霍夫曼编码树
    char_frequency = {}
    for i in range(leaf_node_size):
        c = filedata[4+i*5+0] 

        # 同样的,出现的频率是int型的,读区四个字节来读取到正确的数值
        a1 = filedata[4+i*5+1]
        a2 = filedata[4+i*5+2]
        a3 = filedata[4+i*5+3]
        a4 = filedata[4+i*5+4]
        j = 0
        j = j|a1
        j = j<<8
        j = j|a2
        j = j<<8
        j = j|a3
        j = j<<8
        j = j|a4
        print(c, j)
        char_frequency[c] = j

    # 重建霍夫曼编码树,与压缩文件中建立霍夫曼编码树的方法一致
    list_hufftrees = []
    for x in char_frequency.keys():
        temp = HuffTree(0, x, char_frequency[x], None, None)
        list_hufftrees.append(temp)
        
    temp = Create_HuffmanTree(list_hufftrees)
    temp.traverse_huffman_tree(temp.get_root(),'',char_frequency)

    # 使用重建的huffman编码树,对压缩文件进行解压缩
    output = open(output_file_name, 'wb')
    code = ''
    currnode = temp.get_root()
    for x in range(leaf_node_size*5+4,filesize):
        c = filedata[x]
        for i in range(8):
            if c&128:
                code = code +'1'
            else:
                code = code + '0'
            c = c<<1

        while len(code) > 24:
            if currnode.isleaf():
                tem_byte = six.int2byte(currnode.get_value())
                output.write(tem_byte)
                currnode = temp.get_root()

            if code[0] == '1':
                currnode = currnode.get_right()
            else:
                currnode = currnode.get_left()
            code = code[1:]


    # 处理最后的24位
    sub_code = code[-16:-8]
    last_length = 0
    for i in range(8):
        last_length = last_length<<1
        if sub_code[i] == '1':
            last_length = last_length|1

    code = code[:-16] + code[-8:-8 + last_length]

    while len(code) > 0:
            if currnode.isleaf():
                tem_byte = six.int2byte(currnode.get_value())
                output.write(tem_byte)
                currnode = temp.get_root()

            if code[0] == '1':
                currnode = currnode.get_right()
            else:
                currnode = currnode.get_left()
            code = code[1:]

    if currnode.isleaf():
        tem_byte = six.int2byte(currnode.get_value())
        output.write(tem_byte)
        currnode = temp.get_root()

    # 关闭文件,解压缩完毕
    output.close()


if __name__ == '__main__':
    compress("./pedestrian.jpg","./pedestrian")
    original_size=os.path.getsize("./pedestrian.jpg")
    Compressed_size=os.path.getsize("./pedestrian")
    decompress("./pedestrian","./pedestrian.png")
    print("图像压缩比:",'%.2f'%Compressed_size/original_size)