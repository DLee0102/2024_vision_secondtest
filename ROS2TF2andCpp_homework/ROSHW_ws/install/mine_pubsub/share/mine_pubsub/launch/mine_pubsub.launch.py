import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    params_file = os.path.join(
        get_package_share_directory('mine_pubsub')
        , 'config', 'params.yaml'
    )
    oreyard_node = Node(
        package='mine_pubsub',
        executable='oreyard',
        parameters=[params_file]
    )
    ld = LaunchDescription([
        oreyard_node
    ])
    return ld