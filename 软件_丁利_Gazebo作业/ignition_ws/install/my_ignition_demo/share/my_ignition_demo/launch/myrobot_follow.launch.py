import os.path
from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    pkg_share = FindPackageShare(package="my_ignition_demo").find("my_ignition_demo")
    rviz_config_path = os.path.join(pkg_share, f'launch/{"myrobot_follow.rviz"}')
    params_file = os.path.join(
        get_package_share_directory('my_ignition_demo')
        , 'config', 'params.yaml'
    )
    return LaunchDescription([
        ExecuteProcess(
            cmd=['ign gazebo',
                 'src/my_ignition_demo/src/myworld.sdf'
            ],
            output='screen',
            shell=True,
        ),
        Node(
            package='ros_ign_bridge',
            executable='parameter_bridge',
            name='message_bridge',
            arguments=['/cmd_vel@geometry_msgs/msg/Twist@ignition.msgs.Twist'],
            output='screen'
        ),
        Node(
            package='ros_ign_image',
            executable='image_bridge',
            arguments=['camera'],
            output='screen',
            name='camera'
        ),
        Node(
            package='my_ignition_demo',
            executable='myrobot_follow',
            parameters=[params_file]
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            output='screen',
            arguments=['-d', rviz_config_path]
        )
    ])