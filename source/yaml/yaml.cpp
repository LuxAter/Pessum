#include "yaml.hpp"

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "../log/log.hpp"

pessum::yaml::Node::Node() {}

pessum::yaml::Node::Node(const Node& copy)
    : node_type_(copy.node_type_),
      sub_nodes_(copy.sub_nodes_),
      int_(copy.int_),
      double_(copy.double_),
      string_(copy.string_),
      bool_(copy.bool_) {}

pessum::yaml::Node::Node(int value) : node_type_(INT), int_(value) {}

pessum::yaml::Node::Node(double value) : node_type_(DOUBLE), double_(value) {}

pessum::yaml::Node::Node(std::string value)
    : node_type_(STRING), string_(value) {}

pessum::yaml::Node::Node(const char* value)
    : node_type_(STRING), string_(value) {}

pessum::yaml::Node::Node(bool value) : node_type_(BOOL), bool_(value) {}

pessum::yaml::Node::~Node() {}

bool pessum::yaml::Node::valid() const {
  bool check = false;
  if (node_type_ != NONE) {
    check = true;
  }
  return check;
}

int pessum::yaml::Node::Int() const { return int_; }

double pessum::yaml::Node::Double() const { return double_; }

std::string pessum::yaml::Node::String() const { return string_; }

bool pessum::yaml::Node::Bool() const { return bool_; }

int pessum::yaml::Node::type() const { return node_type_; }

int pessum::yaml::Node::size() const { return sub_nodes_.size(); }

pessum::yaml::Node& pessum::yaml::Node::find(std::string key) {
  std::stringstream ss(key);
  std::string level_key, next_key;
  std::getline(ss, level_key, '.');
  std::getline(ss, next_key);
  for (std::map<std::string, Node>::iterator it = sub_nodes_.begin();
       it != sub_nodes_.end(); ++it) {
    if (it->first == level_key) {
      if ((it->second.type() != DICTIONARY && it->second.type() != LIST) ||
          next_key == std::string()) {
        return it->second;
      } else if (it->second.type() == DICTIONARY || it->second.type() == LIST) {
        Node& ptr = it->second.find(next_key);
        if (ptr.valid() == true) {
          return ptr;
        }
      }
    } else if (node_type_ == LIST) {
      Node& ptr = it->second.find(key);
      if (ptr.valid() == true) {
        return ptr;
      }
    }
  }
  return sub_nodes_["(null)"];
}

std::string pessum::yaml::Node::GetString(int level, bool no_rise) const {
  std::stringstream out;
  if (node_type_ == NONE) {
    out << "(null)";
  } else if (node_type_ == INT) {
    out << int_;
  } else if (node_type_ == DOUBLE) {
    out << double_;
  } else if (node_type_ == STRING) {
    out << string_;
  } else if (node_type_ == BOOL) {
    if (bool_ == true) {
      out << "True";
    } else if (bool_ == false) {
      out << "False";
    }
  } else if (node_type_ == DICTIONARY) {
    if (level != 0 && no_rise == false) {
      out << "\n";
    }
    for (std::map<std::string, Node>::const_iterator it = sub_nodes_.begin();
         it != sub_nodes_.end(); ++it) {
      if (no_rise == false) {
        out << std::string(level * 2, ' ') << it->first << ": "
            << it->second.GetString(level + 1);
      } else if (no_rise == true) {
        out << it->first << ": " << it->second.GetString(level + 1);
      }
      if (it != --sub_nodes_.end()) {
        out << "\n";
      }
    }
  } else if (node_type_ == LIST) {
    if (level != 0) {
      out << "\n";
    }
    for (std::map<std::string, Node>::const_iterator it = sub_nodes_.begin();
         it != sub_nodes_.end(); ++it) {
      out << std::string(level * 2, ' ') << "- "
          << it->second.GetString(level, true);
      if (it != --sub_nodes_.end()) {
        out << "\n";
      }
    }
  }
  return out.str();
}

void pessum::yaml::Node::push_back(int value) {
  (*this)[sub_nodes_.size()] = value;
}

void pessum::yaml::Node::push_back(double value) {
  (*this)[sub_nodes_.size()] = value;
}

void pessum::yaml::Node::push_back(std::string value) {
  (*this)[sub_nodes_.size()] = value;
}

void pessum::yaml::Node::push_back(const char* value) {
  (*this)[sub_nodes_.size()] = value;
}

void pessum::yaml::Node::push_back(bool value) {
  (*this)[sub_nodes_.size()] = value;
}

void pessum::yaml::Node::push_back(Node value) {
  (*this)[sub_nodes_.size()] = value;
}
void pessum::yaml::Node::push_back(std::string key, Node value) {
  if (node_type_ == NONE) {
    node_type_ = DICTIONARY;
  }
  sub_nodes_[key] = value;
}

void pessum::yaml::Node::operator=(const int value) {
  int_ = value;
  node_type_ = INT;
}

void pessum::yaml::Node::operator=(const double value) {
  double_ = value;
  node_type_ = DOUBLE;
}

void pessum::yaml::Node::operator=(const std::string value) {
  string_ = value;
  node_type_ = STRING;
}

void pessum::yaml::Node::operator=(const char* value) {
  string_ = std::string(value);
  node_type_ = STRING;
}

void pessum::yaml::Node::operator=(const bool value) {
  bool_ = value;
  node_type_ = BOOL;
}

void pessum::yaml::Node::operator=(const Node& value) {
  node_type_ = value.node_type_;
  int_ = value.int_;
  double_ = value.double_;
  string_ = value.string_;
  bool_ = value.bool_;
  sub_nodes_ = value.sub_nodes_;
}

pessum::yaml::Node::operator int() { return int_; }

pessum::yaml::Node::operator double() { return double_; }

pessum::yaml::Node::operator std::string() { return string_; }

pessum::yaml::Node::operator bool() { return bool_; }

pessum::yaml::Node& pessum::yaml::Node::operator[](std::string key) {
  node_type_ = DICTIONARY;
  return sub_nodes_[key];
}

pessum::yaml::Node& pessum::yaml::Node::operator[](int key) {
  node_type_ = LIST;
  std::string key_str = std::to_string(key) + "_";
  return sub_nodes_[key_str];
}

pessum::yaml::Node& pessum::yaml::Node::operator()(std::string key) {
  Node& ptr = find(key);
  if (ptr.valid() == true) {
    return ptr;
  } else {
    std::stringstream ss(key);
    std::string level_key;
    ptr = *this;
    while (getline(ss, level_key, '.')) {
      ptr = ptr[level_key];
    }
    return ptr;
  }
}

std::ostream& pessum::yaml::operator<<(std::ostream& out, const Node& node) {
  return out << node.GetString();
}

bool pessum::yaml::operator==(const Node& a, const Node& b) {
  if (a.type() != b.type()) {
    return false;
  } else {
    if (a.type() == NONE) {
      return true;
    } else if (a.type() == INT) {
      return a.Int() == b.Int();
    } else if (a.type() == DOUBLE) {
      return a.Double() == b.Double();
    } else if (a.type() == STRING) {
      return a.String() == b.String();
    } else if (a.type() == BOOL) {
      return a.Bool() == b.Bool();
    } else if (a.type() == DICTIONARY) {
      return a.sub_nodes_ == b.sub_nodes_;
    } else if (a.type() == LIST) {
      return a.sub_nodes_ == b.sub_nodes_;
    }
  }
}

bool pessum::yaml::operator!=(const Node& a, const Node& b) {
  return !(a == b);
}

bool pessum::yaml::operator<(const Node& a, const Node& b) {
  if (a.type() != b.type()) {
    return false;
  } else {
    if (a.type() == NONE) {
      return true;
    } else if (a.type() == INT) {
      return a.Int() < b.Int();
    } else if (a.type() == DOUBLE) {
      return a.Double() < b.Double();
    } else if (a.type() == STRING) {
      return a.String() < b.String();
    } else if (a.type() == BOOL) {
      return a.Bool() < b.Bool();
    } else if (a.type() == DICTIONARY) {
      return a.sub_nodes_ < b.sub_nodes_;
    } else if (a.type() == LIST) {
      return a.sub_nodes_ < b.sub_nodes_;
    }
  }
}

bool pessum::yaml::operator>(const Node& a, const Node& b) {
  if (a.type() != b.type()) {
    return false;
  } else {
    if (a.type() == NONE) {
      return true;
    } else if (a.type() == INT) {
      return a.Int() > b.Int();
    } else if (a.type() == DOUBLE) {
      return a.Double() > b.Double();
    } else if (a.type() == STRING) {
      return a.String() > b.String();
    } else if (a.type() == BOOL) {
      return a.Bool() > b.Bool();
    } else if (a.type() == DICTIONARY) {
      return a.sub_nodes_ > b.sub_nodes_;
    } else if (a.type() == LIST) {
      return a.sub_nodes_ > b.sub_nodes_;
    }
  }
}

bool pessum::yaml::operator<=(const Node& a, const Node& b) {
  if (a.type() != b.type()) {
    return false;
  } else {
    if (a.type() == NONE) {
      return true;
    } else if (a.type() == INT) {
      return a.Int() <= b.Int();
    } else if (a.type() == DOUBLE) {
      return a.Double() <= b.Double();
    } else if (a.type() == STRING) {
      return a.String() <= b.String();
    } else if (a.type() == BOOL) {
      return a.Bool() <= b.Bool();
    } else if (a.type() == DICTIONARY) {
      return a.sub_nodes_ <= b.sub_nodes_;
    } else if (a.type() == LIST) {
      return a.sub_nodes_ <= b.sub_nodes_;
    }
  }
}

bool pessum::yaml::operator>=(const Node& a, const Node& b) {
  if (a.type() != b.type()) {
    return false;
  } else {
    if (a.type() == NONE) {
      return true;
    } else if (a.type() == INT) {
      return a.Int() >= b.Int();
    } else if (a.type() == DOUBLE) {
      return a.Double() >= b.Double();
    } else if (a.type() == STRING) {
      return a.String() >= b.String();
    } else if (a.type() == BOOL) {
      return a.Bool() >= b.Bool();
    } else if (a.type() == DICTIONARY) {
      return a.sub_nodes_ >= b.sub_nodes_;
    } else if (a.type() == LIST) {
      return a.sub_nodes_ >= b.sub_nodes_;
    }
  }
}
