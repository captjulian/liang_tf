cmake_minimum_required(VERSION 2.8.3)
project(liang_tf)

set(liang_tf_SOURCE_DIR
        sources)

set(liang_tf_INCLUDE_DIR
        include
        )
set(liang_tf_SOURCE_FILES
  ${liang_tf_SOURCE_DIR}/my_tf.cpp
  )
      
set(liang_tf_HEADER_FILES
  )



find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  rospy    
  trajectory_msgs
  tf
  message_generation
  geometry_msgs
  eigen_conversions
  nav_msgs
)


#find_package(nbvplanner REQUIRED)

find_package(OpenSoT REQUIRED)

find_package(cartesian_interface REQUIRED)


#add_service_files(
#  FILES
  
#)

#generate_messages(
#  DEPENDENCIES
#  geometry_msgs  # Or other packages containing msgs
#)

#add_message_files(
#  FILES
#  TrainTimes.msg
#)

generate_messages(
  DEPENDENCIES
  geometry_msgs  # Or other packages containing msgs
  std_msgs
)


include_directories(${Eigen_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS} ${OpenSoT_INCLUDE_DIRS} 
${liang_tf_INCLUDE_DIR})

catkin_package(
  INCLUDE_DIRS ${Eigen_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS} ${interface_human_aware_centauro_INCLUDE_DIR}
  LIBRARIES ${catkin_LIBRARIES}
  CATKIN_DEPENDS trajectory_msgs tf roscpp std_msgs geometry_msgs nav_msgs
)

add_library(liang_tf_lib ${liang_tf_SOURCE_FILES} ${liang_tf_HEADER_FILES})
add_dependencies(liang_tf_lib ${catkin_EXPORTED_TARGETS})
target_link_libraries(liang_tf_lib ${catkin_LIBRARIES} ${OpenSoT_LIBRARIES} ${cartesian_interface_LIBRARIES})


add_executable(centauro_tf_broadcaster sources/my_tf.cpp)
target_link_libraries(centauro_tf_broadcaster
  ${catkin_LIBRARIES}
)
add_dependencies(centauro_tf_broadcaster ${catkin_EXPORTED_TARGETS})





