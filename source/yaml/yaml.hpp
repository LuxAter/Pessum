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

      void operator=(int value);
      void operator=(double value);
      void operator=(std::string value);
      void operator=(const char* value);
      void operator=(bool value);
      void operator=(const Node& value);

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

    std::ostream& operator<<(std::ostream& out, const Node& node);
  }  // namespace yaml
}  // namespace pessum

#endif

