import os, random, shutil

def moveimg(imgDir, imgtarDir, labelDir, labeltarDir):
    pathDir = os.listdir(imgDir)  # 取图片的原始路径
    filenumber = len(pathDir)
    rate = 0.2  # 自定义抽取图片的比例
    picknumber = int(filenumber * rate)  # 按照rate比例从文件夹中取一定数量图片
    sample = random.sample(pathDir, picknumber)  # 随机选取picknumber数量的样本图片
    print(sample)
    for name in sample:
        shutil.move(imgDir + "/" + name, imgtarDir + "/" + name)
        shutil.move(labelDir + "/" + name[:-4] + '.txt', labeltarDir + "/" + name[:-4] + '.txt')
    return
 
def movelabel(file_list, file_label_train, file_label_val):
    for i in file_list:
        if i.endswith('.jpg'):
            filename = file_label_train + "/" + i[:-4] + '.txt'
            if os.path.exists(filename):
                shutil.move(filename, file_label_val)
                print(i + "处理成功！")
 
 
 
if __name__ == '__main__':
    '''
    使用说明：
    先运行代码片段1,再分别在images和lables文件夹下手动创建train和val文件夹,
    将images和labels文件夹下所有文件移动到各自的train文件夹中,
    再注释掉代码片段1,运行代码片段2
    '''
    # 1
    fileDir = "images"  # 源图片文件夹路径
    
    file_list = os.listdir(fileDir)
    file_label_train = "images"  # 源图片标签路径
    file_label_val = "labels"  # 标签
    # 移动到新的文件路径
    movelabel(file_list, file_label_train, file_label_val)

    # 2
    # imgDir = 'images/train'  # 图片集地址
    # imgtarDir = 'images/val'  # 图片移动到新的文件夹路径
    # labelDir = 'labels/train'  # 标签集地址
    # labeltarDir = 'labels/val'  # 标签移动到新的文件夹路径
    # moveimg(imgDir, imgtarDir, labelDir, labeltarDir)