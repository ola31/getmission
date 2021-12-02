#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt16.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>


void run_sub_pub_again_node(void);
/*
#include <pthread.h>
#include <unistd.h>
void *t_function(void *data){
  pid_t pid;
  pthread_t tid;

  pid = getpid();
  tid = pthread_self();

  char * thread_name = (char*)data;
  run_sub_pub_again_node();
}
*/
//#include <cstdlib>

std::string command;
std::string command_stop1;
std::string command_stop2;
std::string command_stop3;
std::string command_stop4;
std::string command_stop5;
std::string command_stop6;
std::string command_stop7;

const char *c;

const char *a;
const char *d;
const char *o;
const char *oo;
const char *p;
const char *s;

const char *m;
const char *j;

void cmd_string_Callback(const std_msgs::String::ConstPtr& cmd_msg)
{
  std::string command_string = cmd_msg->data;
  std::string adding_string = "gnome-terminal -- ";
  std::string command_string2 = adding_string+command_string;
  const char *s_cmd = command_string2.c_str();
  system(s_cmd);

}

void mission_Callback(const std_msgs::UInt16 msg)
{
    if(msg.data == 1){
        ROS_INFO("Mission: AutoDriving");

        command = "gnome-terminal -- rosrun run auto_parking_new auto_parking_new_node";
        command_stop1 = "rosnode kill /auto_parking_new_node";
    }

    else if(msg.data == 2){
        ROS_INFO("Mission: Door");

        command = "gnome-terminal -- rosrun door_state door_state";
        command_stop2 = "rosnode kill /door_state";
    }

    else if(msg.data == 3){
        ROS_INFO("Mission: Obstacle");
        command = "gnome-terminal -- roslaunch obstacle_avoid_new obstacle_avoid_new.launch";
        //command_stop3 = "rosnode kill /wall_following";
        //command = "gnome-terminal -- rosrun turtlesim turtlesim_node";
        command_stop3 = "rosnode kill /obstacle_avoid_new_node /ydlidar_node /base_link_to_laser4";
    }

    else if(msg.data == 4){
        ROS_INFO("Mission: Parking");


        command = "gnome-terminal -- roslaunch auto_parking_new auto_parking_new.launch";
        command_stop4 = "rosnode kill /auto_parking_new_node /ydlidar_node /base_link_to_laser4";

    }

    else if(msg.data == 5){
        ROS_INFO("Mission: Stair");
        //command = "roslaunch ";
    }

    else if(msg.data == 60){
        ROS_INFO("md_driver start");

        command = "gnome-terminal -- rosrun md_driver md_driver_demo_node";
        c = command.c_str();
        system(c);
    }

    else if(msg.data == 70){
        ROS_INFO("Joystick start");

        command = "gnome-terminal -- roslaunch rosjoy_to_cmdvel rosjoy_to_cmdvel.launch";
        c = command.c_str();
        system(c);
    }


    else if(msg.data == 0){
        ROS_INFO("Mission Start!!");

        c = command.c_str();
        system(c);
    }

    else if(msg.data == 9){
        ROS_INFO("Mission All Stop!!");

        a = command_stop1.c_str();
        d = command_stop2.c_str();
        o = command_stop3.c_str();
        oo = command_stop4.c_str();

        system(a);
        system(d);
        system(o);
        system(oo);
        //system(p);
        //system(s);
    }

    if(msg.data == 20){
        ROS_INFO("Front CAM ON");
        std::string command_cam = "gnome-terminal -- roslaunch usb_cam usb_cam-test.launch video_divice:=/dev/video0";
        const char *c_cam = command_cam.c_str();
        system(c_cam);
    }




    if(msg.data == 11){
        //command_stop1 = "rosnode kill /autodriving_state";
        a = command_stop1.c_str();
        system(a);
    }
    else if(msg.data == 12){
        //command_stop2 = "rosnode kill /door_state";
        d = command_stop2.c_str();
        system(d);
    }
    else if(msg.data == 13){
        //command = "rosnode kill /wall_following";
        o = command_stop3.c_str();
        system(o);
    }
    else if(msg.data == 14){
        //command = "rosnode kill /drok3_parking";
        p = command_stop4.c_str();
        system(p);
    }
    else if(msg.data == 15){
        //command = "rosnode kill /door_state";
        //system(command);
    }

    else if(msg.data == 61){
        command_stop6 = "rosnode kill /md_driver_node";
        m = command_stop6.c_str();
        system(m);
    }

    else if(msg.data == 71){
        command_stop7 = "rosnode kill /joy_node /rosjoy_2_cmdvel_node /teleop_twist_joy";
        j = command_stop7.c_str();
        system(j);
    }

    else if(msg.data == 21){
        std::string command_stop_cam = "rosnode kill /usb_cam";
        const char *stop_cam_c = command_stop_cam.c_str();
        system(stop_cam_c);
    }
    

    if(msg.data == 99){
       run_sub_pub_again_node();
    }


}

void run_sub_pub_again_node(void){
  std::string command_run_node = "gnome-terminal -x rosrun sub_pub_again sub_pub_again_node";
  //std::string command_run_node = "/home/kudos/script/sub_pub_again_start.sh";
  //std::string command_run_node = "gnome-terminal -x bash /home/kudos/ping_check";
  const char *c_runnode = command_run_node.c_str();
  system(c_runnode);
  //std::system("rosrun sub_pub_again sub_pub_again_node");
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "getmission");
    ros::NodeHandle nh;
/*
    pthread_t p_thread[2];
    int thr_id;
    int status;
    char p1[] = "thread 1";

    thr_id = pthread_create(&p_thread[0],NULL,t_function, (void *)p1);
    if(thr_id <0){
      perror("thread create error");
      exit(0);
    }
    pthread_join(p_thread[0], (void **)&status);
*/
    //run_sub_pub_again_node();
    ros::Subscriber sub = nh.subscribe("mission", 10, mission_Callback);
    ros::Subscriber cmd_string_sub = nh.subscribe("/gui_terminal_command", 10, cmd_string_Callback);


    ros::spin();

    return 0;
}
