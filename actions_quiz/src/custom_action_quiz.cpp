#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib_tutorials/FibonacciAction.h>
#include <actions_quiz/CustomActionMsg.h>
#include <std_msgs/Empty.h>

class CustomAction
{
protected:

  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  actionlib::SimpleActionServer<actions_quiz::CustomActionMsg> as_; 
  std::string action_name_;
  // create messages that are used to publish feedback and result
  actions_quiz::CustomActionMsgFeedback feedback_;

public:

  CustomAction(std::string name) :
    as_(nh_, name, boost::bind(&CustomAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~CustomAction(void)
  {
  }

  void executeCB(const actions_quiz::CustomActionMsgGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    bool success = true;
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::Empty>("/drone/takeoff", 1000);
    ros::Publisher pub2 = nh.advertise<std_msgs::Empty>("/drone/land", 1000);
    if (goal = "TAKEOFF")
        {
            std_msgs::Empty takeoff;
            pub.publish(takeoff);
        }
    else
    {
        std_msgs::Empty land;
        pub2.publish(land);
    }
    // push_back the seeds for the fibonacci sequence
    feedback_.sequence.clear();
    feedback_.sequence.push_back(0);
    feedback_.sequence.push_back(1);

    // publish info to the console for the user
    ROS_INFO("%s: Executing, creating fibonacci sequence of order %i with seeds %i, %i", action_name_.c_str(), goal->order, feedback_.sequence[0], feedback_.sequence[1]);

    // start executing the action
    for(int i=1; i<=goal->order; i++)
    {
      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        break;
      }
      feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i-1]);
      // publish the feedback
      as_.publishFeedback(feedback_);
      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
      r.sleep();
    }

    if(success)
    {
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded(feedback_);
    }
  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "action_custom_msg");
  ros::NodeHandle nh;
  CustomAction customaction("action_custom_msg");
  ros::Publisher pub = nh.advertise<std_msgs::Empty>("/drone/takeoff", 1000);
  ros::Publisher pub2 = nh.advertise<std_msgs::Empty>("/drone/land", 1000);
  ros::spin();

  return 0;
}