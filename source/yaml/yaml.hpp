#ifndef PESSUM_YAML_HPP
#define PESSUM_YAML_HPP

#include <map>
#include <string>

namespace pessum {
  namespace yaml {
    enum NodeType {
      NONE = 0,
      INT = 1,
      DOUBLE = 2,
      STRING = 3,
      BOOL = 4,
      DICTIONARY = 5,
      LIST = 6
    };
    class Node {
     public:
      Node();
      Node(const Node& copy);

      Node(int value);
      Node(double value);
      Node(std::string value);
      Node(const char* value);
      Node(bool value);

      ~Node();

      bool valid() const;

      int Int() const;
      double Double() const;
      std::string String() const;
      bool Bool() const;

      int type() const;

      int size() const;
      Node& find(std::string key);

      std::string GetString(int level = 0, bool no_rise = false) const;

      void push_back(int value);
      void push_back(double value);
      void push_back(std::string value);
      void push_back(const char* value);
      void push_back(bool value);

      void push_back(Node value);
      void push_back(std::string key, Node value);

      void operator=(int value);
      void operator=(double value);
      void operator=(std::string value);
      void operator=(const char* value);
      void operator=(bool value);
      void operator=(const Node& value);

      explicit operator int();
      explicit operator double();
      explicit operator std::string();
      explicit operator bool();

      Node& operator[](std::string key);
      Node& operator[](int key);

      Node& operator()(std::string key);

      std::map<std::string, Node> sub_nodes_;

     private:
      int node_type_ = NONE;
      int int_;
      double double_;
      std::string string_;
      bool bool_;
    };

    bool is_int(std::string str);

    std::ostream& operator<<(std::ostream& out, const Node& node);

    bool operator==(const Node& a, const Node& b);
    bool operator!=(const Node& a, const Node& b);
    bool operator>(const Node& a, const Node& b);
    bool operator<(const Node& a, const Node& b);
    bool operator>=(const Node& a, const Node& b);
    bool operator<=(const Node& a, const Node& b);

  }  // namespace yaml
}  // namespace pessum

#endif

