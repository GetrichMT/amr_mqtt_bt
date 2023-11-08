#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <mosquitto.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/pose.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */
const struct mosquitto_message *mqtt_msg;
std::string mqtt_topic = "";
std::string mqtt_msgs = "";
std::string prev_mqtt_msgs = "";
double target_x = -999.99;
double target_y = -999.99;
double target_z = -999.99;
double target_w = -999.99;
struct mosquitto *mosq;
class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
      : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    goal_publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("goal_pose", rclcpp::SystemDefaultsQoS());
    timer_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "topic amr/request " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "New message with topic %s: %s\n", mqtt_topic.c_str(), mqtt_msgs.c_str());
    // RCLCPP_INFO(this->get_logger(), "New message with topic %s: %s\n", mqtt_msg->topic,  ((char *) mqtt_msg->payload));
    if (mqtt_msgs != prev_mqtt_msgs)
    {
      if ((mqtt_topic != "") && (mqtt_msgs != ""))
      {
        publisher_->publish(message);
        if (mqtt_msgs == "get_trolley1")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2.launch.py'");
            a = 1;
            std::string pub_msg = "Get Trolley 1";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "put_down_trolley1")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2_2.launch.py'");
            a = 1;
            std::string pub_msg = "Trolley Down 1";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "move1")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2_3.launch.py'");
            a = 1;
            std::string pub_msg = "goto pos 1";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "get_trolley2")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2_4.launch.py'");
            a = 1;
            std::string pub_msg = "Get Trolley 2";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "put_down_trolley2")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2_5.launch.py'");
            a = 1;
            std::string pub_msg = "Trolley Down 2";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "move2")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2_6.launch.py'");
            a = 1;
            std::string pub_msg = "goto pos 2";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "get_trolley3")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2_7.launch.py'");
            a = 1;
            std::string pub_msg = "Get Trolley 3";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "put_down_trolley3")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2_8.launch.py'");
            a = 1;
            std::string pub_msg = "Trolley Down 3";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "move3")
        {
          int a = 0;
          if (a == 0)
          {
            system("gnome-terminal -e 'ros2 launch bt_ros2 bt_ros2_9.launch.py'");
            a = 1;
            std::string pub_msg = "goto pos 3";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
          }
        }
        if (mqtt_msgs == "done")
        {
          int a = 0;
          if (a == 0)
          {
            std::string pub_msg = "idle";
            mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
            a = 1;
          }
        }
      }
      prev_mqtt_msgs = mqtt_msgs;
    }
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_publisher_;
  size_t count_;
};
void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
  printf("ID: %d\n", *(int *)obj);
  if (rc)
  {
    printf("Error with result code: %d\n", rc);
    exit(-1);
  }
  mosquitto_subscribe(mosq, NULL, "amr/request", 0);
  std::string pub_msg = "idle";
  mosquitto_publish(mosq, NULL, "amr/status", pub_msg.length(), pub_msg.c_str(), 1, true);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
  // mqtt_msg = &msg;
  printf("New message with topic %s: %s\n", msg->topic, (char *)msg->payload);
  mqtt_topic = msg->topic;
  mqtt_msgs = (char *)msg->payload;
}
int main(int argc, char *argv[])
{
  int rc, id = 12;

  mosquitto_lib_init();

  mosq = mosquitto_new("subscribe-test", true, &id);
  mosquitto_connect_callback_set(mosq, on_connect);
  mosquitto_message_callback_set(mosq, on_message);

  rc = mosquitto_connect(mosq, "localhost", 1883, 10);
  if (rc)
  {
    printf("Could not connect to Broker with return code %d\n", rc);
    return -1;
  }

  rclcpp::init(argc, argv);
  mosquitto_loop_start(mosq);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  mosquitto_loop_stop(mosq, true);

  mosquitto_disconnect(mosq);
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
  return 0;
}
