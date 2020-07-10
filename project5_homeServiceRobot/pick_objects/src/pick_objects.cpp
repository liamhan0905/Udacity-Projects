#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char **argv)
{
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal first_goal;

  // set up the frame parameters
  first_goal.target_pose.header.frame_id = "map";
  first_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  first_goal.target_pose.pose.position.x = -3.45;
  first_goal.target_pose.pose.position.y = -2.87;
  first_goal.target_pose.pose.orientation.w = 0.00247;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick up goal");
  ac.sendGoal(first_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, reached desired pickup goal");
  else
    ROS_INFO("The base failed to move to pick up goal for some reason");

  ros::Duration(5.0).sleep();

  move_base_msgs::MoveBaseGoal second_goal;

  // set up the frame parameters
  second_goal.target_pose.header.frame_id = "map";
  second_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  second_goal.target_pose.pose.position.x = 1.0;
  second_goal.target_pose.pose.position.y = -2.85;
  second_goal.target_pose.pose.orientation.w = -0.0014;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off goal");
  ac.sendGoal(second_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, reached desired drop off goal");
  else
    ROS_INFO("The base failed to move to drop off goal for some reason");
  return 0;
}
