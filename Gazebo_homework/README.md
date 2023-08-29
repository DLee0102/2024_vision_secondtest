# ignition、Rviz2仿真 作业说明
1. 安装环境
```terminal
cd path/to/Gazebo_homework/ignition_ws
. install/setup.bash
```
2. 运行
ros2 launch my_ignition_demo myrobot_follow.launch.py
3. 运行结果展示
</br>追踪绿色方块
![Alt text](<images/Peek 2023-08-29 09-04.gif>)
</br>追踪黄色方块
![Alt text](<images/Peek 2023-08-29 09-08.gif>)
1. 运行简要说明
   - 运行launch文件后自动打开Gazebo窗口和Rviz2中的Image窗口
   - 追踪方块的颜色可在ignition_ws/config/params.yaml中修改