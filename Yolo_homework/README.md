# YOLO 作业说明
1. 自动切分训练集和验证集：datasetdepart.py
2. 训练平台：autodl pytorch-1.11.1 cuda-11.7
3. 测试结果视频：Yolo_homework/test_video.mp4
4. 训练参数见 yolo5-face/ 文件夹
   - train.py
    ```python
    parser.add_argument('--weights', type=str, default='weights/yolov5s.pt', help='initial weights path')
    parser.add_argument('--cfg', type=str, default='models/yolov5s.yaml', help='model.yaml path')
    parser.add_argument('--data', type=str, default='data/coco128.yaml', help='data.yaml path')
    parser.add_argument('--img-size', nargs='+', type=int, default=[800, 640], help='[train, test] image sizes')
    parser.add_argument('--epochs', type=int, default=100)
    parser.add_argument('--batch-size', type=int, default=32, help='total batch size for all GPUs')
    ```
   - data/coco128.yaml
    ```yaml
    train: data/images/train  # 128 images
    val: data/images/val  # 128 images

    # number of classes
    nc: 6

    # class names
    names: [ 'blue_r', 'blue_not_hitted', 'blue_hitted', 'red_r', 'red_not_hitted', 'red_hitted' ]
    ```
   - yolov5s.yaml
    ```yaml
    nc: 6  # number of classes
    ```