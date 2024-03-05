#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <vector>

#include "../../includes/containers/group.hpp"
#include "../../src/lib/tinyxml2.h"

#define T2 tinyxml2

namespace containers
{
  class Group {
  private:
    std::vector<std::string> model_files = {};

  public:
  
    Group(std::string file)
    {
      static const char* f = file.c_str();
      T2::XMLDocument doc;
      doc.LoadFile(f);
      T2::XMLElement * model_elem = doc.RootElement()->FirstChildElement("group")->FirstChildElement("models");

      while (model_elem) {
	const char** model_file;
	model_elem->QueryStringAttribute("file", model_file);
	this->model_files.push_back(std::string(* model_file));
	model_elem = model_elem->NextSiblingElement("model");
      }
    }
  };
};
